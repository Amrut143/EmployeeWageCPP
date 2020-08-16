#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {

	const int EMP_RATE_PER_HOUR = 20;
	const int NUM_OF_WORKING_DAYS = 20;
	const int PART_TIME = 1;
	const int FULL_TIME = 2;

	int empHrs, empWage = 0;
	int monthlyWage = 0;

	cout << "Welcome to employee wage computation" << endl;

	srand(time(0));
	for(int day = 0; day < NUM_OF_WORKING_DAYS; day++) {
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
		monthlyWage += empWage;
	}
	cout << "Employee Monthly Wage Is: " << monthlyWage << endl;

	return 0;
}
