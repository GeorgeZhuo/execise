#include "BPL.h"

using namespace std;

// Initialize learning_examples, testing_examples from file.
// Initialize weight randomly.
BPL::BPL() {

    srand(time(NULL));
    double temp;
    for (int i = 0; i < HIDDEN; i++) {
	for (int j = 0; j < INPUT_NUM; j++) {
	    temp = rand() % 10;
	    if (((int)temp % 2) == 0) {
		hidden_weight[i][j] = temp / 100;
	    } else {
		hidden_weight[i][j] = -(temp / 100);
	    }

	    pre_hidden_weight[i][j] = 0;
	}
    }
    for (int i = 0; i < OUT_NUM; i++) {
	for (int j = 0; j < HIDDEN; j++) {
	    temp = rand() % 10;
	    if (((int)temp % 2) == 0) {
		output_weight[i][j] = temp / 100;
	    } else {
		output_weight[i][j] = -(temp / 100);
	    }

	    pre_output_weight[i][j] = 0;
	}
    }

    // initialize target
    for (int i = 0; i < OUT_NUM; ++i) {
	for (int j = 0; j < OUT_NUM; ++j) {
	    if(i == j)
		target[i][j] = 1;
	    else
		target[i][j] = 0;
	}
    }
}

// Release memory.
BPL::~BPL() {
}

// Get output.
void BPL:: FeedForward(int *examples) {
    
    double sum = 0.0;
    
    // hiden layer
    for (int i = 0; i < HIDDEN ; ++i) {
	sum = 0.0;
	for (int k = 0; k < INPUT_NUM; ++k) {
	    sum += hidden_weight[i][k] * examples[k];
	}
	output[0][i] = sigmoid(sum);
    }

    // output layer
    for (int i = 0; i < OUT_NUM; ++i) {
	sum = 0.0;
	for (int j = 0; j < HIDDEN; ++j) {
	    sum += output_weight[i][j] * output[0][j];
	}

	output[1][i] = sigmoid(sum);
    }
}

// Use output to adjust weight.
void BPL::BackPropogation(int *examples) {

    double sum = 0.0;
    // output layer delta
    for (int i = 0; i < OUT_NUM; ++i) {
	delta[1][i] = (target[(int)examples[DIMENSION -1]][i]
		       - output[1][i]) 
	    * output[1][i] * (1 - output[1][i]);
    }

    // hiden layer delta
    for (int j = 0; j < HIDDEN; ++j) {
	sum = 0.0;
	for (int i = 0; i < OUT_NUM; ++i) {
	    sum += output_weight[i][j] * delta[1][i];
	}

	delta[0][j] = sum * output[0][j] * (1 - output[0][j]);
    }
    // output layer update weight
    for (int i = 0; i < OUT_NUM; ++i) {

	for (int j = 0; j < HIDDEN; ++j) {
	    
	    pre_output_weight[i][j] = MOMENTUM * pre_output_weight[i][j] 
		+ ALPHA * output[0][j] * delta[1][i];
	    output_weight[i][j] += pre_output_weight[i][j];

	}
    }
    
    // hiden layer update weight
    for (int j = 0; j < HIDDEN ; ++j) {

	for (int k = 0; k < INPUT_NUM; ++k) {
	    pre_hidden_weight[j][k] = MOMENTUM * pre_hidden_weight[j][k]
		+ ALPHA * examples[k] * delta[0][j];
	    hidden_weight[j][k] += pre_hidden_weight[j][k];
	}

    }
    
}

// Active function.
double BPL::sigmoid(double x) {
    return (1 / (1 + std::exp(-x)));
}

// Calculate minimal square error
double BPL::calErr(int *examples) {
    double sum = 0.0;

    for (int i = 0; i < OUT_NUM; ++i) {
	sum += pow((target[(int)examples[DIMENSION - 1]][i] - output[1][i]), 2);
    }

    return sum / 2;
}

// Calculate wheter the result is correct
int BPL::calCor() {
    
    int max = 0;
    for (int j = 1; j < OUT_NUM; j++) {
	if (output[1][j] > output[1][max])
	    max = j;
    }
    return max;
}

// restore weight
void BPL::restoreWeight() {

    char flag;
    cout << "restore weight from last time(y or n): ";
    cin >> flag;

    if (flag != 'y')
	return;

    int i = 0;
    char buffer[9600];
    char *p;
    const char *delim = ",\r";
    fstream i_h, h_o;

    i_h.open("hidden.txt",ios::out);
    h_o.open("output.txt", ios::out);
    
    if (i_h == NULL || h_o == NULL)
	throw exception();

    while (!i_h.eof() && i < HIDDEN) {
	
	int j = 0;

	i_h.getline(buffer, 9600, '\n');
	p = strtok(buffer, delim);

	hidden_weight[i][j] = atof(p);
	while (++j < INPUT_NUM && (p=strtok(NULL, delim))) {
	    hidden_weight[i][j] = atof(p);
	}
	i++;
    }
    
    while (!h_o.eof() && i < OUT_NUM) {
	
	int j = 0;

	h_o.getline(buffer, 9600, '\n');
	p = strtok(buffer, delim);

	output_weight[i][j] = atof(p);
	while (++j < HIDDEN && (p=strtok(NULL, delim))) {
	    output_weight[i][j] = atof(p);
	}
	i++;
    }

    i_h.close();
    h_o.close();
}

// save the train weight
void BPL::saveWeight() {

    fstream i_h, h_o;
    i_h.open("hidden.txt",ios::out);
    h_o.open("output.txt", ios::out);

    for (int i = 0; i < HIDDEN; i++) {
	for (int j = 0; j < INPUT_NUM; j++) {
	    i_h << hidden_weight[i][j] << ",";
	}
	i_h << endl;
    }
    for (int i = 0; i < OUT_NUM; i++) {
	for (int j = 0; j < HIDDEN; j++) {
	    h_o << output_weight[i][j] << ",";
	}
	h_o << endl;
    }

    i_h.close();
    h_o.close();

}
// Training the neural net
// max training times 10000
void BPL::train(const char *train_filename) {
    
     int (*learning_examples)[DIMENSION] 
	 = new int[LEARNING_NUM + TEMP_TEST][DIMENSION];

    int i = 0;
    char buffer[9600];
    char *p;
    const char *delim = ",\r";
    fstream learning_file;
    fstream ts;
    learning_file.open(train_filename, ios::in);
    ts.open("a.txt", ios::out);

    if (learning_file == NULL)
	throw exception();
    
    char c;
    /* while (learning_file.get(c) && c != '\n')
       ;*/

    while (!learning_file.eof() && i < LEARNING_NUM + TEMP_TEST) {

	int j = 0;
	learning_file.getline(buffer, 9600, '\n');

	//if (strlen(buffer) == 0)
	//  break;

	p = strtok(buffer, delim);

	//learning_examples[i][j] = 1;
	ts << i << ",";
	
	while (j < DIMENSION && (p=strtok(NULL, delim))) {
	    
	    learning_examples[i][j] = atof(p);
	    ts << learning_examples[i][j] << ",";
	    j++;
	}
	i++;
	ts << endl;
    }
    learning_file.close();
    ts.close();

    cout << "total data number: " << i << endl;
    cout << "train data number: " << LEARNING_NUM << endl;
    cout << "test data number: " << TESTING_NUM << endl;

    int counter;
    int iter = 0;
    double preErr = 0.01;
    double Err;
    
    ALPHA = ALPHA0;
    while (iter < ITER_NUM) {
	cout << "iter " << iter << " " << counter << endl;
	//Err = 0;
	counter = 0;
	for (int i = 0; i < LEARNING_NUM; i++) {
	
	    FeedForward(learning_examples[i]);

	    if (calCor() == (int)learning_examples[i][DIMENSION - 1]) {
		// cout << calCor() << "  "<< (int)learning_examples[i][DIMENSION -1] << endl;
		counter++;
	    }
	
	    BackPropogation(learning_examples[i]);
		   
	}

	ALPHA = BETA * ALPHA;
	iter++;
	
	int max = 0;
	int number = 0;
    
	for (int i = LEARNING_NUM; i < LEARNING_NUM + TEMP_TEST; i++) {

	    FeedForward(learning_examples[i]);

	    if (calCor() == (int)learning_examples[i][DIMENSION - 1])
		number++;

	}

	cout << "correct number " << number << endl;
    }
    cout << "total iter " << iter << endl;

    saveWeight();
    

    delete[] learning_examples;
 }

// Testing the result
void BPL::test(int testing_examples[][INPUT_NUM]) {

    /*
    int (*testing_examples)[DIMENSION - 1] = new int[TESTING_NUM][DIMENSION - 1];
    //double (*result)[2] = new double[TESTING_NUM][2];

    int i = 0;
    char buffer[9600];
    char *p;
    const char *delim = ",\r";
    fstream testing_file;
    fstream result_file;
    
    result_file.open("test.txt", ios::out);
    testing_file.open(test_filename, ios::in);
    
    if (testing_file == NULL)
	throw exception();

    // skip the first line of title
    
    while (!testing_file.eof() && i < TESTING_NUM) {
	
	int j = 0;
	testing_file.getline(buffer, 9600, '\n');

	//if (strlen(buffer) == 0)
	//  break;

	p = strtok(buffer, delim);
	
	//testing_examples[i][j] = 1;

	while (j < DIMENSION - 1 && (p=strtok(NULL, delim))) {
	    testing_examples[i][j] = atof(p);
	    j++;
	    result_file << testing_examples[i][j] << ",";
	}
	result_file << endl;
	i++;
    }
    testing_file.close();
    result_file.close();
    
    cout << "test data number: " << i << endl;
    */
    fstream result_file;
    result_file.open("result.txt", ios::out);
    result_file << "Id,reference" << endl;
        
    int max = 0;
    for (int i = 0; i < TESTING_NUM; i++) {

        FeedForward(testing_examples[i]);
	max = calCor();

	result_file << i << "," << max + 1 << endl;
    }
   
    delete[] testing_examples;

}
