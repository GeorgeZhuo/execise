#include "BPL.h"

using namespace std;

int main() {
  
  BPL bpl("train.csv", "test.csv");

  cout << "training ...." << endl;
  bpl.train();
  
  cout << "testing...." << endl;
  bpl.test();

  return 0;
}
