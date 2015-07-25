#include "LR.h"

using namespace std;

int main() {
  
  LR lr("train_temp.csv", "test_temp.csv");

  cout << "training ...." << endl;
  lr.train();
  
  cout << "testing...." << endl;
  lr.test();

  return 0;
}
