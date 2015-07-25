#include "Forest.h"
#include <iostream>

using namespace std;

int main() {
  
  Forest rdf("train.csv", "test.csv");

  rdf.train();
  
  return 0;
}
