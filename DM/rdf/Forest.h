#include "RegTree.h"
#include <string.h>
#include <algorithm>

#define TREE_NUM 100
#define FEATURE_NUM 30
#define TRAINING_NUM 6238
#define TREE_TRAIN_NUM 4000
#define TESTING_NUM 1559
#define DIMENSION 616
#define CLASS_NUM 26
#define EXP 2.7182818

using namespace std;

class Forest {

public:
    Forest(char* train_file, char* test_file);

    void train();
    void test();
    
    void shuffleData(double train_example[][DIMENSION], int lable[]);
    void selectFeatrue(int featIndex[]);

    void readFile(double train_example[][DIMENSION], int lable[]);

private:

    RegTree trees[TREE_NUM];
    char *trainFile;
    char *testFile;
};
