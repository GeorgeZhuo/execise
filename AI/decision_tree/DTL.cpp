
#include "DTL.h"
#include <vector>
using namespace std;

/*
 * build the decision tree with 
*/
Tree * DecisionTree::DTL(vector< vector<int> > examples, 
			 bool attributes[]) {

    // if all the examples have the same classification then
    // return the classification
    if (sameClass(examples, DEMOCRAT)) {
	Tree * tree = new Tree();
	tree->attribute = DEMOCRAT;
	return tree;
    } 
    if (sameClass(examples, REPUBLICAN)) {
	Tree * tree = new Tree();
	tree->attribute = REPUBLICAN;
	return tree;
    }
    // if the attributes is empty, return the most common lable
    bool empty = true;
    for (int i = 1; i < 17; ++i) {
	if (attributes[i] == true) {
	    flag = false;
	}
    }
    if (empty) {
	Tree *tree = new Tree();
	tree->attribute = mostCommon(examples);
	return tree;
    }
    // else choose the best attributes to split the examples
    // creat a new subtree
    int best = ChooseAttribute(examples, attributes);
    Tree * tree = new Tree();
    tree->attribute = best;
    attributes[best] = false;

    vector<vector<int> > new_examples;
    for (int i = 1; i < 4; ++i) {
	// for each value of the attribute update the example set
	for (int j = 1; j < examples.size(); ++j) {
	    if (examples[j][best] == i)
		new_examples.push_back(examples[j]);
	}
	
	// recurisive get the subtree
	Tree * subtree = new Tree();
	if (new_examples.size() == 0) {
	    subtree->attribute = mostCommon(examples);
	} else {
	    subtree = DTL(new_examples, attributes);
	}

	// add the branch with value i to the tree
	if (i == 1) {
	    tree->yea = subtree;
	} else if (i == 2) {
	    tree->nay = subtree;
	} else {
	    tree->no_vote = subtree;
	}
	return tree;
    }
}

/*
 * if the remain the examples is the same classification
 * return true else return false
*/
bool DecisionTree:: sameClass(vector< vector<int> > examples, int className) {
    
    int counter = 0;
    for (int i = 0; i < examples.size(); ++i) {
	if (examples[i][0] == className) {
	    counter ++;
	}
    }
    if (counter == examples.size()) {
	return true;
    } else {
	return false;
    }
}
/*
 *  return most common class name of the remain example
*/
int DecisionTree:: mostCommon(vector< vector<int> > examples) {

    int counter_dem = 0;
    int counter_rep = 0;

    for (int i = 0; i < examples.size(); ++i) {
	if (examples[i][0] == -1) {
	    counter_dem++;
	} else {
	    counter_rep++;
	}
    }

    if (counter_dem > counter_rep) {
	return DEMOCRAT;
    } else {
	return REPUBLICAN;
    }
}
