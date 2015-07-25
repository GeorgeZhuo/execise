#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include "opencv2/opencv_modules.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/stitching/detail/autocalib.hpp"
#include "opencv2/stitching/detail/blenders.hpp"
#include "opencv2/stitching/detail/camera.hpp"
#include "opencv2/stitching/detail/exposure_compensate.hpp"
#include "opencv2/stitching/detail/matchers.hpp"
#include "opencv2/stitching/detail/motion_estimators.hpp"
#include "opencv2/stitching/detail/seam_finders.hpp"
#include "opencv2/stitching/detail/util.hpp"
#include "opencv2/stitching/detail/warpers.hpp"
#include "opencv2/stitching/warpers.hpp"

using namespace std;
using namespace cv;
using namespace cv::detail;

vector<string> img_names;
string result_name = "pano.jpg";

static int parseCmdArgs(int argc, char** argv)
{
    for (int i = 1; i < argc; i++)
	img_names.push_back(argv[i]);

    return 0;
}

int main(int argc, char* argv[])
{
    double work_megapix = 0.6;
    double seam_megapix = 0.1;
    bool try_gpu = false;
    float conf_thresh = 1.f;
    float match_conf = 0.3f;
    float blend_strength = 5;

    int retval = parseCmdArgs(argc, argv);
    if (retval)
        return retval;

    // Check if have enough images
    int num_images = static_cast<int>(img_names.size());
    if (num_images < 2) {
        cout << "Need more images" << endl;
        return -1;
    }

    double work_scale = 1, seam_scale = 1, compose_scale = 1;
    bool is_work_scale_set = false, is_seam_scale_set = false, 
	is_compose_scale_set = false;

    cout << "Finding feature....." << endl;
    // feature
    Ptr<FeaturesFinder> finder;
    finder = new SurfFeaturesFinder();

    Mat full_img, img;
    vector<ImageFeatures> features(num_images);
    vector<Mat> images(num_images);
    vector<Size> full_img_sizes(num_images);
    double seam_work_aspect = 1;

    for (int i = 0; i < num_images; ++i) {

        full_img = imread(img_names[i]);
        full_img_sizes[i] = full_img.size();

        if (full_img.empty())
        {
            cout << "Can't open image " << img_names[i] << endl;
            return -1;
        }

	work_scale = min(1.0, sqrt(work_megapix * 1e6 
				   / full_img.size().area()));
	resize(full_img, img, Size(), work_scale, work_scale);
	seam_scale = min(1.0, sqrt(seam_megapix * 1e6 / full_img.size().area()));
	seam_work_aspect = seam_scale / work_scale;

        (*finder)(img, features[i]);
        features[i].img_idx = i;
        cout << "Features in image #" << i+1 << 
	    ": " << features[i].keypoints.size() << endl;

        resize(full_img, img, Size(), seam_scale, seam_scale);
        images[i] = img.clone();
	/*
	char name[100];
	sprintf(name, "feature_%d.jpg", i);
	drawKeypoints( img, features[i].keypoints, img, 
		   Scalar(255, 0, 0), DrawMatchesFlags::DEFAULT );
	imwrite(name, img);
	*/

    }
    
   
    finder->collectGarbage();
    full_img.release();
    img.release();

    cout << "Matching feature...." << endl;
    vector<MatchesInfo> pairwise_matches;
    BestOf2NearestMatcher matcher(try_gpu, match_conf);
    matcher(features, pairwise_matches);
    matcher.collectGarbage();

    // Leave only images we are sure are from the same panorama
    vector<int> indices = leaveBiggestComponent(features, pairwise_matches, conf_thresh);
    vector<Mat> img_subset;
    vector<string> img_names_subset;
    vector<Size> full_img_sizes_subset;
    for (size_t i = 0; i < indices.size(); ++i) {

        img_names_subset.push_back(img_names[indices[i]]);
        img_subset.push_back(images[indices[i]]);
        full_img_sizes_subset.push_back(full_img_sizes[indices[i]]);
    }

    images = img_subset;
    img_names = img_names_subset;
    full_img_sizes = full_img_sizes_subset;

    HomographyBasedEstimator estimator;
    vector<CameraParams> cameras;
    estimator(features, pairwise_matches, cameras);

    for (size_t i = 0; i < cameras.size(); ++i) {

        Mat R;
        cameras[i].R.convertTo(R, CV_32F);
        cameras[i].R = R;
    }

    Ptr<detail::BundleAdjusterBase> adjuster;
    adjuster = new detail::BundleAdjusterRay();
    adjuster->setConfThresh(conf_thresh);

    Mat_<uchar> refine_mask = Mat::zeros(3, 3, CV_8U);
    refine_mask(0,0) = 1;
    refine_mask(0,1) = 1;
    refine_mask(0,2) = 1;
    refine_mask(1,1) = 1;
    refine_mask(1,2) = 1;
    adjuster->setRefinementMask(refine_mask);
    (*adjuster)(features, pairwise_matches, cameras);

    // Find median focal length
    vector<double> focals;
    for (size_t i = 0; i < cameras.size(); ++i) {
        focals.push_back(cameras[i].focal);
    }

    sort(focals.begin(), focals.end());
    float warped_image_scale;

    if (focals.size() % 2 == 1)
        warped_image_scale = static_cast<float>(focals[focals.size() / 2]);
    else
        warped_image_scale = static_cast<float>(focals[focals.size() / 2 - 1] + focals[focals.size() / 2]) * 0.5f;

    vector<Mat> rmats;
    for (size_t i = 0; i < cameras.size(); ++i)
	rmats.push_back(cameras[i].R);

    waveCorrect(rmats, detail::WAVE_CORRECT_HORIZ);
    for (size_t i = 0; i < cameras.size(); ++i)
	cameras[i].R = rmats[i];

    cout << "Warping images ..... " << endl;

    vector<Point> corners(num_images);
    vector<Mat> masks_warped(num_images);
    vector<Mat> images_warped(num_images);
    vector<Size> sizes(num_images);
    vector<Mat> masks(num_images);

    // Preapre images masks
    for (int i = 0; i < num_images; ++i) {
        masks[i].create(images[i].size(), CV_8U);
        masks[i].setTo(Scalar::all(255));
    }

    // Warp images and their masks
    Ptr<WarperCreator> warper_creator;
    warper_creator = new cv::SphericalWarper();

    if (warper_creator.empty()) {
        cout << "Can't create the following warper '" << "spheric" << "'\n";
        return 1;
    }

    Ptr<RotationWarper> warper = warper_creator->create(static_cast<float>(warped_image_scale * seam_work_aspect));

    for (int i = 0; i < num_images; ++i) {

        Mat_<float> K;
        cameras[i].K().convertTo(K, CV_32F);
        float swa = (float)seam_work_aspect;
        K(0,0) *= swa; K(0,2) *= swa;
        K(1,1) *= swa; K(1,2) *= swa;

        corners[i] = warper->warp(images[i], K, cameras[i].R, INTER_LINEAR, BORDER_REFLECT, images_warped[i]);
        sizes[i] = images_warped[i].size();

        warper->warp(masks[i], K, cameras[i].R, INTER_NEAREST, BORDER_CONSTANT, masks_warped[i]);
	/*
	char name[100];
	sprintf(name, "mask_%d.jpg",i);
	imwrite(name, masks[i]);
	*/
    }

    vector<Mat> images_warped_f(num_images);
    for (int i = 0; i < num_images; ++i)
        images_warped[i].convertTo(images_warped_f[i], CV_32F);

    
    cout << "Compensating images ....." << endl;
    Ptr<ExposureCompensator> compensator = ExposureCompensator::createDefault( ExposureCompensator::GAIN_BLOCKS);
    compensator->feed(corners, images_warped, masks_warped);

    Ptr<SeamFinder> seam_finder;
    seam_finder = new detail::GraphCutSeamFinder(GraphCutSeamFinderBase::COST_COLOR);
    seam_finder->find(images_warped_f, corners, masks_warped);

    // Release unused memory
    images.clear();
    images_warped.clear();
    images_warped_f.clear();
    masks.clear();

    Mat img_warped, img_warped_s;
    Mat dilated_mask, seam_mask, mask, mask_warped;
    Ptr<Blender> blender;
    //double compose_seam_aspect = 1;
    double compose_work_aspect = 1;
    
    cout << "Compose images ....." << endl;
    for (int img_idx = 0; img_idx < num_images; ++img_idx) {

        cout << "Compositing image #" << indices[img_idx]+1 << endl;

        // Read image and resize it if necessary
        full_img = imread(img_names[img_idx]);
        if (!is_compose_scale_set) {
            is_compose_scale_set = true;

            //compose_seam_aspect = compose_scale / seam_scale;
            compose_work_aspect = compose_scale / work_scale;

            // Update warped image scale
            warped_image_scale *= static_cast<float>(compose_work_aspect);
            warper = warper_creator->create(warped_image_scale);

            // Update corners and sizes
            for (int i = 0; i < num_images; ++i) {

                // Update intrinsics
                cameras[i].focal *= compose_work_aspect;
                cameras[i].ppx *= compose_work_aspect;
                cameras[i].ppy *= compose_work_aspect;

                // Update corner and size
                Size sz = full_img_sizes[i];
                if (std::abs(compose_scale - 1) > 1e-1) {

                    sz.width = cvRound(full_img_sizes[i].width * compose_scale);
                    sz.height = cvRound(full_img_sizes[i].height * compose_scale);
                }

                Mat K;
                cameras[i].K().convertTo(K, CV_32F);
                Rect roi = warper->warpRoi(sz, K, cameras[i].R);
                corners[i] = roi.tl();
                sizes[i] = roi.size();
            }
        }
        if (abs(compose_scale - 1) > 1e-1)
            resize(full_img, img, Size(), compose_scale, compose_scale);
        else
            img = full_img;
	/*
	char name[100];
	sprintf(name, "full_%d.jpg", img_idx);
	imwrite(name, full_img);
	*/
        full_img.release();
        Size img_size = img.size();

        Mat K;
        cameras[img_idx].K().convertTo(K, CV_32F);

        // Warp the current image
        warper->warp(img, K, cameras[img_idx].R, INTER_LINEAR, BORDER_REFLECT, img_warped);

        // Warp the current image mask
        mask.create(img_size, CV_8U);
        mask.setTo(Scalar::all(255));
        warper->warp(mask, K, cameras[img_idx].R, INTER_NEAREST, BORDER_CONSTANT, mask_warped);

        // Compensate exposure
        compensator->apply(img_idx, corners[img_idx], img_warped, mask_warped);

        img_warped.convertTo(img_warped_s, CV_16S);
        img_warped.release();
        img.release();
        mask.release();

        dilate(masks_warped[img_idx], dilated_mask, Mat());
        resize(dilated_mask, seam_mask, mask_warped.size());
        mask_warped = seam_mask & mask_warped;

        if (blender.empty()) {

            blender = Blender::createDefault(Blender::MULTI_BAND, try_gpu);
            Size dst_sz = resultRoi(corners, sizes).size();
            float blend_width = sqrt(static_cast<float>(dst_sz.area())) * blend_strength / 100.f;
            if (blend_width < 1.f)
                blender = Blender::createDefault(Blender::NO, try_gpu);
            else {
                MultiBandBlender* mb = dynamic_cast<MultiBandBlender*>(static_cast<Blender*>(blender));
                mb->setNumBands(static_cast<int>(ceil(log(blend_width)/log(2.)) - 1.));
     
            }

            blender->prepare(corners, sizes);
        }
	/*
	char name[100];
	sprintf(name, "mwarped_%d.jpg",img_idx);
	imwrite(name, mask_warped);
	*/
        // Blend the current image
        blender->feed(img_warped_s, mask_warped, corners[img_idx]);
    }

    cout << "Blending images.... " << endl;
    Mat result, result_mask;

    blender->blend(result, result_mask);
    //imwrite("result_mask", result_mask);
    imwrite(result_name, result);

    Mat final = result(Range(50, result.rows - 50), 
		       Range(0, result.cols));
    imwrite("final.jpg", final);

    return 0;
}
