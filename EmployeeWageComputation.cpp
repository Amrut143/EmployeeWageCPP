#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
using namespace std;

int main() {
	const int EMP_RATE_PER_HOUR = 20;
	const int NUM_OF_WORKING_DAYS = 20;
	const int MAX_HOUR_IN_MONTH = 100;
	const int PART_TIME = 1;
	const int FULL_TIME = 2;

	int empHrs, empWage = 0;
	int monthlyWage = 0;
	int totalEmpHrs = 0;
	int totalWorkingDays = 0;

	cout << "Welcome to employee wage computation" << endl;

	srand(time(0));
	while(totalEmpHrs <= MAX_HOUR_IN_MONTH && totalWorkingDays < NUM_OF_WORKING_DAYS) {
			totalWorkingDays++;
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
		totalEmpHrs += empHrs;

		fstream fileStream;
		fileStream.open("EmpWage.txt", ios::out | ios::app);

		if(fileStream.is_open()) {
			fileStream << "Day: " << totalWorkingDays << "--->" << empWage << endl;
			fileStream.close();
		}
	}
	monthlyWage = totalEmpHrs * EMP_RATE_PER_HOUR;

	fstream fileStream;
	fileStream.open("EmpWage.txt", ios::out | ios::app);

	if(fileStream.is_open()) {
		fileStream << "Employee Monthly Wage Is: " << monthlyWage << endl;
		fileStream.close();
	}
	cout << "Employee Monthly Wage Is: " << monthlyWage << endl;

	return 0;
}

