#include <iostream>
#include <algorithm>

int f(int x) {

    int s = 0;
    while(x-- > 0) {
	s += f(x);
    }

    return s;

}

int main(int argc, char *argv[])
{
    f(35);
    return 0;
}
