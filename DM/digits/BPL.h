#include <iostream>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <cstring>
#include <exception>
#include <ctime>
#include <vector>
#include <iomanip>

#define TEMP_TEST 0
#define INPUT_NUM 616
#define ALPHA0 0.015// learning rate.
#define BETA 0.96
#define ZETA 1.01
#define HIDDEN 375 // number of hidden perceptrons.
#define OUT_NUM 26
#define LEARNING_NUM 6238
#define TESTING_NUM 1559
#define DIMENSION 618
#define LAYER_NUM 3
#define MOMENTUM 0.1
#define ITER_NUM 100

class BPL {
public:
    // Initialize learning_examples, testing_examples from file.
    // Initialize weight randomly.
    BPL(const char* learning_dataset, const char* testing_dataset);

    // Release memory.
    ~BPL();

    // Training 
    void train();

    // Testing
    void test();

    // Get output.
    void FeedForward(double *examples);

    // Use output to adjust weight.
    void BackPropogation(double *examples);
  
private:
    // Active function.
    double sigmoid(double x);
    double calErr(double *examples);
    int calCor();
    void saveWeight();
    void restoreWeight();

    const char *train_filename;
    const char *test_filename;
    
    double target[OUT_NUM][OUT_NUM];
    double delta[LAYER_NUM-1][HIDDEN]; // for back propogation.
    double hidden_weight[HIDDEN][INPUT_NUM];
    double output_weight[OUT_NUM][HIDDEN];
    double pre_hidden_weight[HIDDEN][INPUT_NUM];
    double pre_output_weight[OUT_NUM][HIDDEN];
    double output[LAYER_NUM-1][HIDDEN];
    double ALPHA;

};
