// Fri Jan  9 11:34:37 2015

#include <iostream>
#include <string>
#include <stdio.h>
using namespace std;

struct key {
    int number;
    string str[10];
} keywords = {3, "int", "main", "return"};

struct op {
    int number;
    string str[10];
} operators = {5, "+", "*", "=", "+=", "*="};

struct bound {
    int number;
    string str[10];
} boundaries {6, "(",")", "{","}", ",", ";"};

struct id {
    int number;
    string str[100];
} identifieres {0};

struct integer {
    int number;
    string str[100];
} unsigned_integer {0};

bool isDigit(char c) {

    if (c >= '0' && c <= '9')
	return true;
    else
	return false;
}

bool isLetter (char c) {
    
    if ((c >= 'a' && c <= 'z') ||
	(c >= 'A' && c <= 'Z')) 
	return true;
    else
	return false;
}

int main(int argc, char *argv[])
{
    char peek;

    while (true){
	if (!isLetter(peek) && !isLetter(peek))
	    peek = getchar();

	if (isLetter(peek)) {
	    char buf[100];
	    int index = 0;
	    buf[index++] = peek;
	    while (peek = getchar()) {
		
		if (isLetter(peek)) {
		    buf[index++] = peek;
		} else {
		    break;
		}
	    }

	    buf[index] = '\0';

	    if (buf == keywords.str[0]) {
		cout << "<1,0>";
	    } else if (buf == keywords.str[1]) {
		cout << "<1,1>";
	    } else if (buf == keywords.str[2]) {
		cout << "<1,2>";
	    } else {
		
		int counter = 0;

		for (int i = 0; i < identifieres.number; ++i) {
		    if (identifieres.str[i] != buf)
			counter++;
		}
		if (counter == identifieres.number) {
		    identifieres.str[identifieres.number++] = buf;
		}
		for (int i = 0; i < identifieres.number; ++i) {
		    if (identifieres.str[i] == buf)
			cout << "<4,"<< i << ">";
		}
	    }
	    
	} 
	if (isDigit(peek)) {
	    char buf[100];
	    int index = 0;
	    buf[index++] = peek;
	    while (peek = getchar()) {
		
		if (isDigit(peek)) {
		    buf[index++] = peek;
		} else {
		    break;
		}
	    }

	    buf[index] = '\0';

	    int counter = 0;
	    for (int i = 0; i < unsigned_integer.number; ++i) {
		if (unsigned_integer.str[i] != buf)
		    counter++;

	    }
	    if (counter == unsigned_integer.number)
		unsigned_integer.str[unsigned_integer.number++] = buf;
	    
	    for (int i = 0; i < unsigned_integer.number; ++i) {
		if (unsigned_integer.str[i] == buf)
		    cout << "<5," << i << ">";

	    }
	    
	    
	} 
	if (peek == '+') {
	    peek = getchar();
	    if (peek == '=') {
		cout << "<2,3>";
	    } else {
		cout << "<2,0>";
	    }
	    
	}
	if (peek == '*') {
	    
	    peek = getchar();
	    if (peek == '=') {
		cout << "<2,4>";
	    } else {
		cout << "<2,1>";
	    }

	} 
	if (peek == '=') {
	    cout << "<2,2>";

	} else if (peek == '(') {
	    cout << "<3,0>";

	} else if (peek == ')') {
	    cout << "<3,1>";

	} else if (peek == '{') {
	    cout << "<3,2>";

	} else if (peek == '}') {
	    cout << "<3,3>";

	} else if (peek == ',') {
	    cout << "<3,4>";

	} else if (peek == ';') {
	    cout << "<3,5>";

	} else if (peek == '#') {
	    break;
	} else {

	    continue;
	}

    }
    cout << "\nidentifieres:" ;
    for (int i = 0; i < identifieres.number - 1; ++i) {
	cout << identifieres.str[i] << " ";
    }
    cout << identifieres.str[identifieres.number -1] << endl;
    cout << "Unsigned_integer:";
    for (int i = 0; i < unsigned_integer.number -1; ++i) {
	cout << unsigned_integer.str[i] << " ";
    }
    cout << unsigned_integer.str[unsigned_integer.number -1] << endl;
    return 0;
}

