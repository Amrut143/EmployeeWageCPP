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
					fileStream << ", Month_" << (month + 1);
				}
			}

			fileStream.seekg(0, ios::beg);
			fileStream << "\n" << companyName << ", Employee" << (empId + 1);
			for(int month = 0; month < numOfMonths; month++) {
				fileStream << "," << wages[month];
			}
		}
		fileStream.close();
}

struct EmpWageBuilder {

	vector<CompanyEmpWage> companyWage;
	int getEmpWorkingHour(CompanyEmpWage);
	int getEmpWage(CompanyEmpWage company) {

		return getEmpWorkingHour(company) *  company.empRatePerHrs;
	}

	void addCompany(CompanyEmpWage companyEmpWage) {

		companyWage.push_back(companyEmpWage);
	}
};

int EmpWageBuilder::getEmpWorkingHour(CompanyEmpWage companyEmpWage) {

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

void computeEmpWage(CompanyEmpWage companyEmpWage, int numOfEmp, int totalMonths) {

	struct EmpWageBuilder empWageBuilder;
	int numOfCompany = 2;


		for(int employee = 0; employee < numOfEmp; employee++) {

			vector<int> monthlyWage;
			for(int month = 0; month < totalMonths; month++) {

				sleep(2);
				int empWage = empWageBuilder.getEmpWage(companyEmpWage);
				monthlyWage.push_back(empWage);
				cout << "Monthly Wage For Employee:" << (month + 1) << "Is: " << empWage << endl;
			}
			saveWageIntoFile(monthlyWage, employee, totalMonths, companyEmpWage.companyName);
		}
		empWageBuilder.addCompany(companyEmpWage);
}

int main() {

	struct CompanyEmpWage companyEmpWage[2];

	companyEmpWage[0].setCompanyDetails("Dmart", 20, 100, 20);
	companyEmpWage[1].setCompanyDetails("Relaince", 25, 105, 40);
	computeEmpWage(companyEmpWage[0], 2, 2);
	computeEmpWage(companyEmpWage[1], 2, 3);

	return 0;
}

