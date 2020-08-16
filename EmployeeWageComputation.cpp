#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {

	int EMP_RATE_PER_HOUR = 20;

	int empHrs, empWage = 0;

	cout << "Welcome to employee wage computation" << endl;

	srand(time(0));
	int empCheck = rand() % 2;

	if(empCheck == 1) {
		cout << "Employee is present" << endl;
		empHrs = 8;
	}
	else {
		cout << "Employee is abscent" << endl;
		empHrs = 0;
	}
	empWage = empHrs * EMP_RATE_PER_HOUR;
	cout << "Employee Daily Wage Is: " << empWage << endl;

	return 0;
}
