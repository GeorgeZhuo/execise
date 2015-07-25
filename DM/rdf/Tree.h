#include <string>
#include <vector>
#include <cmath>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <algorithm>

#define MAX_DEPTH 5
#define MIN_NUM 5
#define MIN_GAIN 0.1
#define TRAIN_NUM 4000
#define FEAT_NUM 30
#define DIMENSION 616

using namespace std;

/*
 * feature : 0 - 616 is the feature value, -1 means leaf node
 * splitValue : the split value of interal node
 * right : the right branch
 * left : the letf branch
*/
struct TreeNode {

    double splitValue;
    int feature;
    TreeNode *right;
    TreeNode *left;
    
    TreeNode(double s, int f, TreeNode *r, TreeNode *l) {

	splitValue = s;
	feature = f;
	right = r;
	left = l;
    }

};

/*
 * This the regression tree for create random forest
*/
class RegTree {

 public:
    RegTree();
    ~RegTree();
    void createTree(double train_example[][DIMENSION], int lable[], int featIndex[]);

    TreeNode* createTree_recursive(double train_example[][DIMENSION], int Size, 
				   int depth, int lable[], int featIndex[]);

    double predict(double test_example[]);

 private:
    // vector< vector<double> > _train_example;
    TreeNode *root;

    // check whether all the examples are the same class
    bool sameClass(int lable[], int size);
    
    // get leaf node type
    double leafNode(int lable[], int size);
    
    // call by distrutor to release resource
    void clear(TreeNode *node);

    // calculate teh variance
    double calVar(int lable[], int size);

    // get split value
    double* getSplitValue(double train_example[][DIMENSION],int size, int feat, int &splitSize);
    // calclate the error
    double calGain(double preVar, double train_example[][DIMENSION], int lable[], 
		  int size, int feat, double value);
    
    // pedict the result
    double predict_recursive(double test_example[], TreeNode *node);

    // choose the best attribute which splits the examples.
    void chooseBestSplit(double train_example[][DIMENSION], int lable[], int size,
			 int featIndex[], int &feature, double &splitValue, double &maxGain);
  
};

