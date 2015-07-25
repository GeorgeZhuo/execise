#define DEMOCRAT -1
#define REPUBLICAN -2
#define YEA 1
#define NAY 2
#define NO_VOTE 3
#define N 350

#include <vector>
#include <string>

using namespace std;

struct Tree {
  // -1 means democrat,  -2 means republican.
  // k (1...16) means we use attribute k 
  // for the next decision.
  int attribute;
  Tree *yea;
  Tree *nay;
  Tree *no_vote;
};

class DecisionTree {
 public:
  // set all attributes unvisited.
  DecisionTree();

  Tree* DTL(vector< vector<int> > examples, bool attributes[]);
  bool TestDTL();

 private:
  vector< vector<int> > learning_examples;
  vector< vector<int> > testing_examples;
  bool attributes[16];

  // read file and record learing_examples and testing_examples.
  bool ReadFile(string file_name);

  // choose the best attribute which splits the examples.
  int ChooseAttribute(vector< vector<int> > examples, bool attributes[]);
  bool sameClass(vector< vector<int> > examples, int className);
  int mostCommon(vector< vector<int> > examples);
  
};
