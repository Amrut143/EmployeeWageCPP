#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <unistd.h>
#include <vector>
#include <list>
using namespace std;

vector<int> dailyWage;
struct CompanyEmpWage {

	string companyName;
	int numOfWorkingDays;
	int maxHrsInMonth;
	int empRatePerHrs;
	int numOfEmployees;
	int totalMonths;

public:
		void setCompanyDetails(string companyName, int numOfWorkingDays, int maxHrsInMonth, int empRatePerHrs, int numOfEmployees, int totalMonths) {

				this -> companyName = companyName;
				this -> numOfWorkingDays = numOfWorkingDays;
				this -> maxHrsInMonth = maxHrsInMonth;
				this -> empRatePerHrs = empRatePerHrs;
				this -> numOfEmployees = numOfEmployees;
				this -> totalMonths = totalMonths;
		}

};

void saveWageIntoFile(vector<int> wages, int empName, int numOfMonths, string companyName, int wagePerHr) {

	fstream fileStream;
	fileStream.open("EmpWage.csv", ios::out | ios::app);
	fileStream.seekg(0, ios::end);

		if(fileStream.is_open())
		{
			if(fileStream.tellp() == 0)
			{
				fileStream << "Company,Employee,Day,DailyWage,WagePerHour,Month";
			}
			fileStream.seekg(0, ios::beg);
			for(int day = 0; day < wages.size(); day++) {
				fileStream << "\n" << companyName << ", Emp_" << (empName + 1) << ", " << (day + 1) << ", " << wages[day] << ", " << wagePerHr << ", " << (numOfMonths + 1);
			}
		}
		fileStream.close();
}

struct EmpWageBuilder {

	vector<CompanyEmpWage> companyWage;

	int getWorkingHour(CompanyEmpWage);

	void addCompany(string companyName, int numOfWorkingDays, int maxHrsInMonth, int empRatePerHrs, int numOfEmployees, int totalMonths) {

		CompanyEmpWage companyEmpWage;
		companyEmpWage.setCompanyDetails(companyName, numOfWorkingDays, maxHrsInMonth, empRatePerHrs, numOfEmployees, totalMonths);
		companyWage.push_back(companyEmpWage);
	}

	void searchTotalWage(string companyName) {

		vector<int> monthlyWage;
		int totalWage = 0;

		if(companyWage.size() != 0)
		{
			vector<CompanyEmpWage>::iterator itr;

			for(itr = companyWage.begin(); itr < companyWage.end(); itr++) {

				if((*itr).companyName == companyName)
				{
					for(int employee = 0; employee < (*itr).numOfEmployees; employee++) {

						for(int month = 0; month < (*itr).totalMonths; month++) {

							for(int day = 0; day < (*itr).numOfWorkingDays; day++) {

								totalWage += getWorkingHour(*itr) * (*itr).empRatePerHrs;
							}
							monthlyWage.push_back(totalWage);
							cout << "\nCompanyName: " << companyName << "\nEmployeeName: " << "Employee_" << (employee +1) << "\nMonth: " << (month + 1) << "\nMonthlyWage: " << monthlyWage[month] << endl;
						}
					}
				}
			}
		}
	}
};

int EmpWageBuilder::getWorkingHour(CompanyEmpWage companyEmpWage) {

	const int NUM_OF_WORKING_DAYS = companyEmpWage.numOfWorkingDays;
	const int MAX_HOUR_IN_MONTH = companyEmpWage.maxHrsInMonth;
	const int PART_TIME = 1;
	const int FULL_TIME = 2;

	int empHrs = 0;
	int totalEmpHrs = 0;
	int totalWorkingDays = 0;

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
		int wage = empHrs * companyEmpWage.empRatePerHrs;
		dailyWage.push_back(wage);
		totalEmpHrs += empHrs;
	}
	return totalEmpHrs;
}

void computeEmpWage(struct EmpWageBuilder empWageBuilder) {

	vector <CompanyEmpWage> :: iterator company;

	for(company = empWageBuilder.companyWage.begin(); company != empWageBuilder.companyWage.end(); company++) {

		int numOfEmployee = (*company).numOfEmployees;
		int totalMonths = (*company).totalMonths;

		for(int employee = 0; employee < numOfEmployee; employee++) {

			for(int month = 0; month < totalMonths; month++) {

				sleep(1.5);
				saveWageIntoFile(dailyWage, employee, month, (*company).companyName, (*company).empRatePerHrs);
			}
		}
	}
}

int main() {

	struct EmpWageBuilder empWageBuilder;

	empWageBuilder.addCompany("Dmart", 20, 100, 20, 3, 2);
	empWageBuilder.addCompany("Reliance", 25, 105, 50, 2, 2);

	computeEmpWage(empWageBuilder);

	empWageBuilder.searchTotalWage("Reliance");

	return 0;
}

