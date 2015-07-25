import java.awt.image.BufferedImage;  
import java.awt.image.ColorModel;
import java.io.BufferedReader;
import java.io.File;  
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;   
import javax.imageio.ImageIO;
import java.lang.Math;
import java.util.Random;
 
public class ImageDemo {

    private int [][]imageData;
    private int width;
    private int height;

    /*
     * binaryzation the image
     * @param string image name
     * @return binaryzation image
     */
    public BufferedImage binaryzation(String input_img) throws IOException {  
	File file = new File(input_img);
	BufferedImage image = ImageIO.read(file);  	
	
	// get the image pix width and height
	width = image.getWidth();
	height = image.getHeight();
	BufferedImage outImage = new BufferedImage(width, height, BufferedImage.TYPE_INT_RGB);	    
	ColorModel cm = ColorModel.getRGBdefault();
	int red, rgb;
	int r;
	
	// binaryzation each pix 
	for(int i= 0 ; i < width ; i++) {
	    for(int j = 0 ; j < height; j++) {
		rgb = image.getRGB(i, j);
		red = cm.getRed(rgb);
		if (red > 127) {
		    r = 255;
		} else {
		    r = 0;
		}
		outImage.setRGB(i, j, (255 << 24) | (r << 16) | (r << 8 )| r);
	    }
	}

	// save the image file
	File newFile = new File("binaryzation.png");    
	ImageIO.write(outImage, "png", newFile);  

	return outImage;
    }

    
    /*
     * add 10% noice to the image
     * @param string image name
     * @return noice image
     */
    public BufferedImage addNoice(String input_img) throws IOException {  
	File file = new File(input_img);
	BufferedImage image = ImageIO.read(file);  	

	// get the image pix width and height
	width = image.getWidth();
	height = image.getHeight();
	ColorModel cm = ColorModel.getRGBdefault();
	int red, rgb;
	int r;

	// add ten percen noice 
	int noice = (int)(width * height * 0.1);

	for (int i = 0; i < noice; i++) {
	    // randomly to produce random number
	    int number =  (int)(Math.random() * width * height);
	    int h = number / width;
	    int w = number % width;

	    // toggle the pix
	    rgb = image.getRGB(w, h);
	    red = cm.getRed(rgb);
	    if (red > 127) {
		r = 0;
	    } else {
		r = 255;
	    }
	    image.setRGB(w, h, (255 << 24) | (r << 16) | (r << 8 )| r);

	}
		
	// save the image file
	File newFile = new File("addNoice.png"); 
	ImageIO.write(image, "png", newFile);

	return image;
    }

    
    /*
     * denoice 
     * @param string image name
     * @return recovering image
     */
    public BufferedImage denoice(String input_img) throws IOException {  
	File file = new File(input_img);
	BufferedImage image = ImageIO.read(file);

	// get the image pix width and height
	width = image.getWidth();  
	height = image.getHeight();

	BufferedImage outImage = new BufferedImage(width, height, BufferedImage.TYPE_INT_RGB);	    
	ColorModel cm = ColorModel.getRGBdefault();
	imageData = new int[width][height]; // temp array for image data
	int red, rgb;
	int r;
	int couter = 0;

	// read the image data to the array
	for(int i= 0 ; i < width ; i++) {
	    for(int j = 0 ; j < height; j++) {
		rgb = image.getRGB(i, j);
		red = cm.getRed(rgb);
		if (red > 127) {
		    imageData[i][j] = 1;
		} else {
		    imageData[i][j] = -1;
		}
	    }
	}

	int current;
	int curEne;
	int nexEne;
	double T = 100; 
	double T_min = 20; // the mini T for stop the simulated annealing (less than T)
	double control = 0.99; // for controling the temparatur vary speed (0 - 1)
	int weight = 5; // weight for current position to compute the energe
	int dE;

	int totalPixel = width*height;
	int[] randomArray = randomSequence(totalPixel);
	for (int k = 0; k < totalPixel; k++) {
	    int i, j;
	    i = randomArray[k] / height;
	    j = randomArray[k] % height;

	    current = imageData[i][j];
	    imageData[i][j] = 1;
	    curEne = -cmpNeighbor(i, j) - weight * current;
	    imageData[i][j] = -1;
	    nexEne = -cmpNeighbor(i, j) + weight * current;
	    imageData[i][j] = -current;

	    	if (current == 1) {
		    dE = nexEne - curEne;
		} else {
		    dE = curEne - nexEne;
		}

		if (dE >= 0) {
		    imageData[i][j] = current;
		} else {
		    if (T > T_min) {
			double temp = Math.exp( dE / T);
			if (temp > Math.random()) {
			    imageData[i][j] = current;
			}
		    }
		}
		T = control * T;
	 
	}
	// write the image data to the image
	for(int i= 0 ; i < width ; i++) {
	    for(int j = 0 ; j < height; j++) {
		if (imageData[i][j] == 1) {
		    r = 255;
		} else {
		    r = 0;
		}
		outImage.setRGB(i, j, (255 << 24) | (r << 16) | (r << 8 )| r);
	    }
	}

	// save image file
	File newFile = new File("denoice.png");    
	ImageIO.write(outImage, "png", newFile);

	return outImage;
    }

    /* match the two image
     * @param string origin image, recover image
     * @return recover ratio
     */
    public double result(String originFile, String recoverFile) throws IOException {
	
	File file1 = new File(originFile);
	BufferedImage originImage = ImageIO.read(file1);

	File file2 = new File(recoverFile);
	BufferedImage recImage = ImageIO.read(file2);  	

	ColorModel cm = ColorModel.getRGBdefault();
	int red1, red2, rgb1, rgb2;

	width = originImage.getWidth();
	height = originImage.getHeight();

	int counter = 0;
	// match each pix
	for (int i = 0; i < width; i++) {
	    for (int j = 0; j < height; j++) {

		rgb1 = originImage.getRGB(i, j);
		rgb2 = recImage.getRGB(i, j);
		red1 = cm.getRed(rgb1);
		red2 = cm.getRed(rgb2);
		
		if (red1 != red2) {
		    counter++;
		}
		
	    }
	}

	return (1.0 - (double)((double)counter / (width * height)));
    }

    /* calculate the energe of the pix point
     * @param location the pix point
     * @return int energe
     */
    private int cmpNeighbor(int x, int y) {

	int weight1 = 2; // weight for the nearest the 8 locations
	int weight2 = 1; // weight for the outside 16 locations
	int tmpx, tmpy, energy = 0;
	
	// nerghbor locations
	int arr[][] = {
	    	    {-1, -1}, {-1, 0}, {-1, 1},	{0, 1}, {0, -1}, {1, -1}, {1, 0}, {1, 1}, 
		    {-2, -2,}, {-2, -1,}, {-2, 0}, {-2, 1}, {-2, 2}, {-1, -2}, {-1, 2}, {0, -2}, 
		    {0, 2}, {1, -2}, {1, 2}, {2, -2}, {2, -1}, {2, 0}, {2, 1}, {2, 2}
	};

	for (int i = 0; i < 24; i++) {
	    tmpx = x + arr[i][0];
	    tmpy = y + arr[i][1];

	    if (tmpx >= 0 && tmpx < width
		&& tmpy >= 0 && tmpy < height) {
		if (i < 8)
		    energy += imageData[tmpx][tmpy] * weight1 * imageData[x][y];
		else 
		    energy += imageData[tmpx][tmpy]* weight2 * imageData[x][y];
	    }
	}

	return energy;
    }

     private static int[] randomSequence(int total)
    {
	int[] sequence = new int[total];
	int[] result = new int[total];
	Random random = new Random();
	int end = total - 1;

	for (int i = 0; i < total; i++) {
	    sequence[i] = i;
	}

	for (int i = 0; i < total; i++) {
	    int num  = random.nextInt(end + 1);
	    result[i] = sequence[num];
	    sequence[num] = sequence[end--];
	}

	return result;
    }
}
