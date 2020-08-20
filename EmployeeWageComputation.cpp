#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <unistd.h>
#include <vector>
using namespace std;

struct CompanyEmpWage {

	string companyName;
	int numOfWorkingDays;
	int maxHrsInMonth;
	int empRatePerHrs;

public:
		void setCompanyDetails(string companyName, int numOfWorkingDays, int maxHrsInMonth, int empRatePerHrs) {

				this -> companyName = companyName;
				this -> numOfWorkingDays = numOfWorkingDays;
				this -> maxHrsInMonth = maxHrsInMonth;
				this -> empRatePerHrs = empRatePerHrs;
		}
};

void saveWageIntoFile(vector<int> wages, int empId, int numOfMonths, string companyName) {

	fstream fileStream;
	fileStream.open("EmpWage.csv", ios::out | ios::app);
	fileStream.seekg(0, ios::end);

		if(fileStream.is_open())
		{
			if(fileStream.tellp() == 0)
			{
				fileStream << "Company, Employee";
				for(int month = 0; month < 12; month++) {
					fileStream << ", Month " << (month + 1);
				}
			}

			fileStream.seekg(0, ios::beg);
			fileStream << "\n" << companyName << ", Employee " << (empId + 1);
			for(int month = 0; month < numOfMonths; month++) {
				fileStream << "," << wages[month];
			}
		}
		fileStream.close();
}

int getEmpWorkingHour(struct CompanyEmpWage companyEmpWage) {

	const int NUM_OF_WORKING_DAYS = companyEmpWage.numOfWorkingDays;
	const int MAX_HOUR_IN_MONTH = companyEmpWage.maxHrsInMonth;
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

void computeEmpWage(struct CompanyEmpWage companyEmpWage, int numOfEmp, int totalMonths) {

	const int EMP_RATE_PER_HOUR = companyEmpWage.empRatePerHrs;

	for(int i = 0; i < numOfEmp; i++) {

		vector<int> monthlyWage;
		for(int j = 0; j < totalMonths; j++) {

			sleep(2);
			int empWage = getEmpWorkingHour(companyEmpWage) * EMP_RATE_PER_HOUR;
			monthlyWage.push_back(empWage);
			cout << "Monthly Wage For Employee:" << (j + 1) << "Is: " << empWage << endl;
		}
		saveWageIntoFile(monthlyWage, i, totalMonths, companyEmpWage.companyName);
	}
}

int main() {

	struct CompanyEmpWage companyEmpWage;
	companyEmpWage.setCompanyDetails("Dmart", 20, 100, 20);
	computeEmpWage(companyEmpWage, 3, 3);
	companyEmpWage.setCompanyDetails("Relaince", 25, 105, 40);
	computeEmpWage(companyEmpWage, 2, 2);

	return 0;
}

