#include <iostream>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <cstring>
#include <exception>
#include <vector>
#include <iomanip>

#define TEMP_TEST 0
#define ALPHA0 0.05 // learning rate.
#define ZETA 0.95
#define LEARNING_NUM 20000
#define TESTING_NUM  26524
#define THETA_NUM 385
#define DIMENSION 1025
#define ITER_NUM 10000
#define PRECISION 5


class LR {
public:
    // Initialize learning_examples, testing_examples from file.
    LR(const char* learning_dataset, const char* testing_dataset);

    // Release memory.
    ~LR();

    // Training 
    void train();

    // Testing
    void test();
    
    double sum(double x[]);

private:

    const char *train_filename;
    const char *test_filename;
    double theta[THETA_NUM];
    double ALPHA;

};
