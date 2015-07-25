// Sat Mar 21 17:18:48 2015
// george@NOSPAM.Phycles

#include <iostream>

using namespace std;

int entry[10];
int count;

void insert_heap(int cur, int low, int high) {

    int large = low * 2 + 1;
    while(large <= high) {
	if (large < high && entry[large] < entry[large +1])
	    large++;
	if (cur >= large)
	    break;
	else {
	    entry[low] = entry[large];
	    low = large;
	    large = low * 2 + 1;
	}
    }
    entry[low] = cur;

}
void buid_heap() {
    int low;
    for (low = count/2 - 1; low >= 0; low--) {
	int cur = entry[low];
	insert_heap(cur, low, count -1);

    }
}

int main(int argc, char *argv[]) {

    int last_unsorted;
    int current;

    cin >> count;
    for (int i = 0; i < count; ++i) {
	cin >> entry[i];
    }

    buid_heap();
    for (last_unsorted = count - 1; last_unsorted > 0; last_unsorted--) {
	current = entry[last_unsorted -1];
	entry[last_unsorted] = entry[0];
	insert_heap(current, 0, last_unsorted -1);
    }
    for (int i = 0; i < count; ++i) {
	cout << entry[i] << endl;
    }
    return 0;
}
