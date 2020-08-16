#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {

	const int EMP_RATE_PER_HOUR = 20;
	const int PART_TIME = 1;
	const int FULL_TIME = 2;

	int empHrs, empWage = 0;

	cout << "Welcome to employee wage computation" << endl;

	srand(time(0));
	int empCheck = rand() % 3;

	switch(empCheck) {
		case PART_TIME:
			empHrs = 4;
			break;
		case FULL_TIME:
			empHrs = 8;
			break;
		default:
			empHrs = 0;
	}
	empWage = empHrs * EMP_RATE_PER_HOUR;
	cout << "Employee Daily Wage Is: " << empWage << endl;

	return 0;
}

