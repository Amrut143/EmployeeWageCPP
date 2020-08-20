#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <unistd.h>
#include <vector>
using namespace std;

vector<vector<int> > totalWage;

void saveWageIntoFile(vector<int> wages, int empId, int numOfMonths) {

	fstream fileStream;
	fileStream.open("EmpWage.csv", ios::out | ios::app);
	fileStream.seekg(0, ios::end);

		if(fileStream.is_open())
		{
			if(fileStream.tellp() == 0)
			{
				fileStream << "Employee";
				for(int month = 0; month < 12; month++) {
					fileStream << ", Month " << (month + 1);
				}
			}

			fileStream.seekg(0, ios::beg);
			fileStream << "\n" << "Employee " << (empId + 1);
			for(int month = 0; month < numOfMonths; month++) {
				fileStream << "," << wages[month];
			}
		}
		fileStream.close();
}

int getEmpWorkingHour() {

	const int NUM_OF_WORKING_DAYS = 20;
	const int MAX_HOUR_IN_MONTH = 100;
	const int PART_TIME = 1;
	const int FULL_TIME = 2;

	int empHrs = 0;
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
		totalEmpHrs += empHrs;
	}
	return totalEmpHrs;
}

void computeEmpWage(int numOfEmp, int totalMonths) {

	const int EMP_RATE_PER_HOUR = 20;

	for(int i = 0; i < numOfEmp; i++) {

		vector<int> monthlyWage;
		for(int j = 0; j < totalMonths; j++) {

			sleep(2);
			int empWage = getEmpWorkingHour() * EMP_RATE_PER_HOUR;
			monthlyWage.push_back(empWage);
			cout << "Monthly Wage For Employee:" << (j + 1) << "Is: " << empWage << endl;
		}
		saveWageIntoFile(monthlyWage, i, totalMonths);
	}
}

int main() {

	computeEmpWage(3, 3);
	return 0;
}

