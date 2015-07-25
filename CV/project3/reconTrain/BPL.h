#include <iostream>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <cstring>
#include <exception>
#include <ctime>
#include <vector>
#include <iomanip>

#define TEMP_TEST 10000
#define INPUT_NUM 64
#define ALPHA0 0.001// learning rate.
#define BETA 0.96
#define ZETA 1.01
#define HIDDEN 87 // number of hidden perceptrons.
#define OUT_NUM 26
#define LEARNING_NUM 50000
#define TESTING_NUM 10000
#define DIMENSION 65
#define LAYER_NUM 3
#define MOMENTUM 0.1
#define ITER_NUM 100

class BPL {
public:
    // Initialize learning_examples, testing_examples from file.
    // Initialize weight randomly.
    BPL();

    // Release memory.
    ~BPL();

    // Training 
    void train(const char *train_filename);

    // Testing
    void test(int testing_examples[][INPUT_NUM]);

    // Get output.
    void FeedForward(int *examples);

    // Use output to adjust weight.
    void BackPropogation(int *examples);
  
private:
    // Active function.
    double sigmoid(double x);
    double calErr(int *examples);
    int calCor();
    void saveWeight();
    void restoreWeight();

    int target[OUT_NUM][OUT_NUM];
    double delta[LAYER_NUM-1][HIDDEN]; // for back propogation.
    double hidden_weight[HIDDEN][INPUT_NUM];
    double output_weight[OUT_NUM][HIDDEN];
    double pre_hidden_weight[HIDDEN][INPUT_NUM];
    double pre_output_weight[OUT_NUM][HIDDEN];
    double output[LAYER_NUM-1][HIDDEN];
    double ALPHA;

};
