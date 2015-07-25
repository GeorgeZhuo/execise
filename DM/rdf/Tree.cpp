#include "RegTree.h"

/*
 * build the decision tree with 
*/
RegTree::RegTree() {

    root = NULL;
    //createTree(train_example, lable, featIndex);
}

RegTree::~RegTree() {
    clear(root);
}

void RegTree::createTree(double train_example[][DIMENSION], 
			 int lable[], int featIndex[]) {
    
    root = createTree_recursive(train_example, TRAIN_NUM, 1, lable, featIndex);
}

TreeNode* RegTree::createTree_recursive(double train_example[][DIMENSION], int Size,
					int depth, int lable[], int featIndex[]) {

    //printf("create tree size: %d depth: %d\n", Size, depth);

    int feature;
    double splitValue;
    double maxGain = -1000.0;
   
    if (sameClass(lable, Size) || depth > MAX_DEPTH || Size <= MIN_NUM) {
	printf("  creat leaf node\n");
	double tmp = leafNode(lable, Size);
	return  new TreeNode(tmp, -1, NULL, NULL);
    }

    chooseBestSplit(train_example, lable, Size, featIndex, feature, splitValue, maxGain);

    // printf("feature: %d, splitValue: %f, maxGain: %f\n", feature, splitValue, maxGain);
    int rSize = 0, lSize = 0;
    if (maxGain > MIN_GAIN) {

	for (int i = 0; i < Size; i++) {

	    if (train_example[i][feature] > splitValue) {
		rSize++;
	    } else {
		lSize++;
	    }
	}
    }
    double (*rTrain_Example)[DIMENSION] = new double[rSize][DIMENSION];
    double (*lTrain_Example)[DIMENSION] = new double[lSize][DIMENSION];
    double *rLable = new double[rSize];
    double *lLable = new double[lSize];
    
    int r = 0, l = 0;
    int length = DIMENSION * sizeof(double);
    // printf("rSize: %d, lSize: %d, gain: %f\n", rSize, lSize, maxGain);
    if  (maxGain > MIN_GAIN) {
	for (int i = 0; i < Size; i++) {
	    
	    // carefull for memory copy
	    if (train_example[i][feature] > splitValue) {
		memcpy(rTrain_Example[r], train_example[i], length);
		rLable[r++] = lable[i];
	    } else {
		memcpy(lTrain_Example[l], train_example[i], length);
		lLable[l++] = lable[i];
	    }
	}

    }
    
    if (lSize == 0 || rSize == 0) {
	double tmp = leafNode(lable, Size);
	return new TreeNode(tmp, -1, NULL, NULL);
    }
    
    TreeNode *right = createTree_recursive(rTrain_Example, rSize, depth + 1, rLable, featIndex);
    TreeNode *letf = createTree_recursive(lTrain_Example, lSize, depth + 1, rLable, featIndex);

    delete[] rTrain_Example;
    delete[] lTrain_Example;
    delete[] rLable;
    delete[] lLable;

    return new TreeNode(splitValue, feature, right, letf);
}

// check whether all the examples are the same class
bool RegTree::sameClass(int lable[], int size) {

    for (int i = 0; i < size - 1; i++) {
	if (lable[i] != lable[i + 1])
	    return false;
    }
    /*printf("in same class\n");
    for (int i = 0; i < size; i++) {
	printf("  %f", lable[i]);
	}*/
    return true;
}
    
// get leaf node type
double RegTree::leafNode(int lable[], int size) {

    int counter[LABLES];

    for (int i = 0; i < size; i++) {
	counter[lable[i]]++;
    }
    int max = 0;
    int _lable;

    for (int j = 0; j < LABLES; j++) {
	if (counter[j] > max) {
	    max = counter[i];
	    _lable = j;
	}
    }
    return (double)_lable;
}

// choose the best attribute which splits the examples.
void RegTree::chooseBestSplit(double train_example[][DIMENSION], int lable[], int size, 
			      int featIndex[], int &feature, double &splitValue, double &maxGain) {

    // printf("in choose split value maxGain %f\n", maxGain);
    for (int i = 0; i < FEAT_NUM; i++ ) {

	int feat = featIndex[i];
	int splitSize;
	double *splitValues = getSplitValue(train_example, size, feat, splitSize);
	double preVar = calVar(lable, size);

	for (int j = 0; j < splitSize; j++) {
	    double value = splitValues[j];
	    double gain = calGain(preVar, train_example, lable, size, feat, value);

	    if (gain > maxGain) {
		maxGain = gain;
		feature = feat;
		splitValue = value;
	    }
	}
	delete[] splitValues;
    }

}

double RegTree:: calVar(int lable[], int size) {
    
	double Mean = 0, Var = 0;
	for (int j = 0; j < size; j++) {
	    Mean += lable[j];
	}
	Mean /= size;

	for (int j = 0; j < size; j++) {
	    Var += (lable[j] - Mean) * (lable[j] - Mean);
	}
	Var *= size;
	    
	return Var;
}

double *RegTree::getSplitValue(double train_example[][DIMENSION], int size,
			       int feat, int &splitSize) {

    double *featValue = new double[size];
    double *splitValue = new double[size];
    double tmp;

    int i;
    for (i = 0; i < size; i++) {
	featValue[i] = train_example[i][feat];
    }

    sort(featValue, featValue + i);

    for (int j = 0; j  < i - 1; j++) {
	tmp = (featValue[j] + featValue[j + 1]) / 2;
	splitValue[j] = tmp;
    }
    splitSize = i;
    delete featValue;

    return splitValue;
    
}

double RegTree:: calGain(double preVar, double train_example[][DIMENSION], 
			int lable[], int size, int feat, double value) {
    
    double *right = new double[size];
    double *left = new double[size];

    int r = 0, l = 0;
    for (int i = 0; i < size; i++) {

	if (train_example[i][feat] > value) {
	    right[r++] = lable[i];
	} else {
	    left[l++] = lable[i];
	}
    }
    double Var = (preVar - calVar(right, r) - calVar(left, l));

    delete[] right;
    delete[] left;

    return Var;
    
}

void RegTree::clear(TreeNode *node) {

    if (node->right != NULL) {
	clear(node->right);
    }
    if (node->left != NULL) {
	clear(node->left);
    }

    delete node;
    node = NULL;
}

double RegTree::predict(double test_example[]) {

    return predict_recursive(test_example, root);
}

double RegTree::predict_recursive(double test_example[], TreeNode *node) {

    if (node->feature == -1) {
	return node->splitValue;
	printf("predict value %f\n", node->splitValue);
    }
    
    if (test_example[node->feature] > node->splitValue) {
	return predict_recursive(test_example, node->right);
    } else {
	return predict_recursive(test_example, node->left);
    }
}
