#include "LR.h"

using namespace std;

// Initialize learning_examples, testing_examples from file.
LR::LR(const char* learning_dataset, const char* testing_dataset):
    train_filename(learning_dataset), test_filename(testing_dataset) {
    
    for (int i = 0; i < THETA_NUM; ++i) {
	theta[i] = 1;
    }

}

// Release memory.
LR::~LR() {
}

double LR::sum(double x[]) {

    double sum =  0;
    for (int i = 0; i < THETA_NUM; ++i) {
	sum += x[i] * theta[i];
    }

    return sum;
}

// Training the theta
void LR::train() {
   
    double (*learning_examples)[DIMENSION] = new double[LEARNING_NUM + TEMP_TEST][DIMENSION];

    int i = 0;
    char buffer[9600];
    char *p;
    const char *delim = ",\r";
    fstream learning_file;
    fstream ts;
    learning_file.open(train_filename, ios::in);
    //ts.open("a.txt", ios::out);

    if (learning_file == NULL)
	throw exception();
    
    char c;
    while (learning_file.get(c) && c != '\n')
	;

    while (!learning_file.eof() && i < LEARNING_NUM) {

	int j = 0;
	learning_file.getline(buffer, 9600, '\n');

	//if (strlen(buffer) == 0)
	//  break;

	p = strtok(buffer, delim);

	learning_examples[i][j] = 1;
	
	while (++j < DIMENSION && (p=strtok(NULL, delim))) {
	    
	    learning_examples[i][j] = atof(p);
	    //cout << learning_examples[i][j] << ",";
	}
	i++;
    }
    learning_file.close();
    cout << "train data number: " << i << endl;
 
    double Err[LEARNING_NUM];
    double tempth[THETA_NUM];
    double total;
    double error, pre_error;
    ALPHA = ALPHA0;

    for (int i = 0; i < ITER_NUM; i++) {
	cout << "iteration: " << i << endl;
	error = 0;
	total = 0;
	
	if (i % 100 == 0) {
	    ALPHA *= ZETA;
	}
	
	for (int j = 0; j < LEARNING_NUM; ++j) {
	    Err[j] = sum(learning_examples[j]) 
		- learning_examples[j][DIMENSION -1];
	    error += pow(Err[j], 2);
	}

	for (int k = 0; k < THETA_NUM; ++k) {
	    
	    total = 0;
	    for (int j = 0; j < LEARNING_NUM; ++j) {
		total += Err[j] * learning_examples[j][k];
	    }
	    tempth[k] = theta[k] - (ALPHA * total /LEARNING_NUM);
	}

	for (int k = 0; k < THETA_NUM; ++k) {
	    theta[k] = tempth[k];
	}
	
	if (error < PRECISION)
	    break;
    
    }
    cout << "training finishded" << endl;
    cout << "error " << sqrt(error / LEARNING_NUM) << endl;
    double bias = 0;
    for (int i = 0; i < LEARNING_NUM; ++i) {
	
	double y =  learning_examples[i][DIMENSION -1] 
	    - sum(learning_examples[i]);
	bias += pow(y, 2);
    }
    cout  << "bias " << sqrt(bias / LEARNING_NUM) << endl;
 
    delete[] learning_examples;
}

// Testing the result
void LR::test() {

    double (*testing_examples)[DIMENSION - 1] = new double[TESTING_NUM][DIMENSION - 1];
    //double (*result)[2] = new double[TESTING_NUM][2];

    int i = 0;
    char buffer[3200];
    char *p;
    const char *delim = ",\r";
    fstream testing_file;
    fstream result_file;
    
    testing_file.open(test_filename, ios::in);
    
    if (testing_file == NULL)
	throw exception();

    // skip the first line of title
    char c;
    while (testing_file.get(c) && c != '\n')
	;
    
    while (!testing_file.eof() && i < TESTING_NUM) {
	
	int j = 0;
	testing_file.getline(buffer, 3200, '\n');

	if (strlen(buffer) == 0)
	    break;

	p = strtok(buffer, delim);
	
	testing_examples[i][j] = 1;

	while (++j < DIMENSION - 1 && (p=strtok(NULL, delim))) {
	    testing_examples[i][j] = atof(p);
	
	}
	i++;
    }
    testing_file.close();
    cout << "test data number: " << i << endl;

    result_file.open("result.cvs", ios::out);
    result_file << "Id,reference" << endl;
    result_file << std::fixed;
    for (int i = 0; i < TESTING_NUM; i++) {
      
	result_file << i << "," << std::setprecision(6) << 
	    sum(testing_examples[i]) << endl;
    }
    
  delete[] testing_examples;

}
