#include "Forest.h"

Forest::Forest(char *train_file, char * test_file) :
    trainFile(train_file), testFile(test_file) {

};

void Forest::train() {
    
    printf("training.....\n");

    double (*train_example)[DIMENSION] = new double[TRAINING_NUM][DIMENSION];
    int *lable = new int[TRAINING_NUM];
    int featIndex[FEATURE_NUM];

    fstream result_file;
    result_file.open("result.txt", ios::out);
    // read file
    readFile(train_example, lable);
    
    // random select some train data

    for (int t = 0; t < TREE_NUM; t++) {
	// select some feature
	printf("tree %d\n", t);
	shuffleData(train_example, lable);
	selectFeatrue(featIndex);
	trees[t].createTree(train_example, lable, featIndex);
	    
    }
    result_file.close();
}
/*
 * randomly shuffle the data
*/
void Forest::shuffleData(double train_example[][DIMENSION], int  lable[]) {

    srand(time(NULL));

    int a, b;
    double tmp[DIMENSION];

    int length = DIMENSION * sizeof(double);

    for (int i = 0; i < TRAINING_NUM; i++) {
	a = rand() % TRAINING_NUM;
	b = rand() % TRAINING_NUM;
	swap(lable[a], lable[b]);

	memcpy(tmp, train_example[a], length);
	memcpy(train_example[a], train_example[b], length);
	memcpy(train_example[b], tmp, length);
    }
    
    int max = 0;
    int result[CLASS_NUM];
    int tmp;
    int _lable;
    int counter = 0;
    for (int i = 0; i < TRAINING_NUM; i++) {
	memset(result, 0, CLASS_NUM * sizeof(int));

	for (int t = 0; t < TREE_NUM; t++) {
	    tmp = (int)trees[t].predict(testing_examples[i]);
	    result[tmp]++;
	}
	for (int k = 0; k < CLASS_NUM; k++) {
	    if (result[k] > max) {
		max = result[k];
		_lable = k;
	    }
	}
	if (_lable + 1 == lable[i])
	    counter++;
    }
    printf("total %d\n", counter);
}

/*
 * randomly select some features
*/
void  Forest::selectFeatrue(int featIndex[]) {

    int tmp;
    for (int i = 0; i < FEATURE_NUM; i++) {
	tmp = rand() % DIMENSION;
	featIndex[i] = tmp;
    }

}

/*
 * reading train data from file
*/
void Forest::readFile(double train_example[][DIMENSION], int lable[]) {
    
    int i = 0;
    char *p;
    char c;
    char buffer[9600];
    const char *delim = ",\r";

    fstream learning_file;
    fstream train_file;
    fstream lable_file;

    learning_file.open(trainFile, ios::in);
    train_file.open("train.txt", ios::out);
    lable_file.open("lable.txt", ios::out);

    if (learning_file == NULL)
	throw exception();

    while (learning_file.get(c) && c != '\n')
	;

    while (!learning_file.eof() && i < TRAINING_NUM) {

	int j = 0;
	learning_file.getline(buffer, 9600, '\n');

	//if (strlen(buffer) == 0)
	//  break;

	p = strtok(buffer, delim);
	
	while (j < DIMENSION + 1 && (p = strtok(NULL, delim))) {
	    train_example[i][j] = atof(p);
	    train_file << atof(p) << ",";
	    
	    j++;
	}
	p = strtok(NULL, delim);
	int _lable = atoi(p);

	lable_file << _lable << endl;
	if (_lable > 26 || _lable < 0) {
	    printf("lable error %d \n", _lable);
	}
	lable[i] = _lable;

	i++;
	train_file << endl;
    }
    learning_file.close();
}


// Testing the result
void Forest::test() {
        
    double (*testing_examples)[DIMENSION - 1] = new double[TESTING_NUM][DIMENSION - 1];

    int i = 0;
    char buffer[9600];
    char *p;
    const char *delim = ",\r";
    fstream testing_file;
    fstream result_file;
    
    //result_file.open("test.txt", ios::out);
    testing_file.open(test_filename, ios::in);
    
    if (testing_file == NULL)
	throw exception();

    // skip the first line of title
    char c;
    while (testing_file.get(c) && c != '\n')
	;
    
    while (!testing_file.eof() && i < TESTING_NUM) {
	
	int j = 0;
	testing_file.getline(buffer, 9600, '\n');

	//if (strlen(buffer) == 0)
	//  break;

	p = strtok(buffer, delim);
	
	//testing_examples[i][j] = 1;

	while (j < DIMENSION - 1 && (p=strtok(NULL, delim))) {
	    testing_examples[i][j] = atof(p);
	    // result_file << testing_examples[i][j] << ",";
	    j++;
	}
	// result_file << endl;
	i++;
    }
    testing_file.close();
    // result_file.close();

    cout << "test data number: " << i << endl;
    
    result_file.open("result.csv", ios::out);
    result_file << "Id,label" << endl;
        
    int max = 0;
    int result[CLASS_NUM];
    int tmp;
    int _lable;
    for (int i = 0; i < TESTING_NUM; i++) {
	memset(result, 0, CLASS_NUM * sizeof(int));

	for (int t = 0; t < TREE_NUM; t++) {
	    tmp = (int)trees[t].predict(testing_examples[i]);
	    result[tmp]++;
	}
	for (int k = 0; k < CLASS_NUM; k++) {
	    if (result[k] > max) {
		max = result[k];
		_lable = k;
	    }
	}

	result_file << i << "," << _lable << endl;
    }
   
    delete[] testing_examples;

}
