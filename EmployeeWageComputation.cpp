#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {

	cout << "Welcome to employee wage computation" << endl;
	srand(time(0));
	int empCheck = rand() % 2;

	if(empCheck == 1) {
		cout << "Employee is present" << endl;
	}
	else {
		cout << "Employee is abscent" << endl;
	}
	return 0;
}
