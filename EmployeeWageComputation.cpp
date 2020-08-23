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

	if(fileStream.is_open()) {

		if(fileStream.tellp() == 0) {

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

	int getEmpWage(CompanyEmpWage company) {

		return getWorkingHour(company) *  company.empRatePerHrs;
	}

	void addCompany(string companyName, int numOfWorkingDays, int maxHrsInMonth, int empRatePerHrs, int numOfEmployees, int totalMonths) {

		CompanyEmpWage companyEmpWage;
		companyEmpWage.setCompanyDetails(companyName, numOfWorkingDays, maxHrsInMonth, empRatePerHrs, numOfEmployees, totalMonths);
		companyWage.push_back(companyEmpWage);
	}

	void getTotalWageBasedOnCompany(string companyName) {

		vector<CompanyEmpWage>::iterator company;
		int totalWage = 0;

		for(company = companyWage.begin(); company < companyWage.end(); company++) {

			if((*company).companyName == companyName) {

				for(int employee = 0; employee < (*company).numOfEmployees; employee++) {

					for(int month = 0; month < (*company).totalMonths; month++) {

						for(int day = 0; day < (*company).numOfWorkingDays; day++) {

							totalWage += getWorkingHour(*company) * (*company).empRatePerHrs;
						}
					}
				}
				cout << "\n\nTotal Wage of company " << companyName << " Is: " << totalWage << endl;
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
	}
	return empHrs;
}

void sortByWages(int *, int);
void displaySortedData(int *, int);

void computeEmpWage(struct EmpWageBuilder empWageBuilder) {

	vector <CompanyEmpWage> :: iterator company;
	CompanyEmpWage companyEmpWage;
	int totalWage = 0;
	vector<int> dailyWage;

	for(company = empWageBuilder.companyWage.begin(); company != empWageBuilder.companyWage.end(); company++) {

		int numOfEmployee = (*company).numOfEmployees;
		int totalMonths = (*company).totalMonths;
		int month = (*company).totalMonths * (*company).numOfEmployees;
		int monthCount = 0;
		int monthArray[month];
		int days = totalMonths * numOfEmployee * (*company).numOfWorkingDays;
		int dayCount = 0;
		int dayArray[days];

		for(int employee = 0; employee < numOfEmployee; employee++) {

			for(int month = 0; month < totalMonths; month++) {

				for(int day = 0; day < (*company).numOfWorkingDays; day++) {

					int wage = empWageBuilder.getEmpWage(*company);
					dailyWage.push_back(wage);
					dayArray[dayCount] = wage;
					dayCount++;

					totalWage += wage;
					sleep(1.5);
				}
				cout << "**********************" << endl;
				cout << "Monthly Wage For Employee:" << (month + 1) << " Is: " << totalWage << endl;

				monthArray[monthCount] = totalWage;
				monthCount++;
				totalWage = 0;

				saveWageIntoFile(dailyWage, employee, month, (*company).companyName, (*company).empRatePerHrs);
			}
		}
		cout << endl;
		cout << "\n\nBefore sorting the monthly wages are " << endl;

		displaySortedData(monthArray, month);
		sortByWages(monthArray, month);

		cout << "\n\nAfter sorting the monthly wages are" << endl;
		displaySortedData(monthArray, month);

		cout << "\n\nBefore sorting daily wage" << endl;
		displaySortedData(dayArray, month);

		sortByWages(dayArray, month);
		cout << "\n\nAfter sorting daily wage" << endl;
		displaySortedData(dayArray, month);
	}
}

void displaySortedData(int *arrayElement, int size) {

	for(int count = 0; count < size; count++) {

		cout << arrayElement[count] << " ";
		cout << endl;
	}
}

void sortByWages(int *wage, int size) {

	int tempWage;

	for(int i = 0; i < size; i++ ) {

		for(int j = i + 1; j < size; j++) {

			if(wage[i] > wage[j]) {
				tempWage = wage[i];
				wage[i] = wage[j];
				wage[j] = tempWage;
			}
		}
	}
}

int main() {

	struct EmpWageBuilder empWageBuilder;

	empWageBuilder.addCompany("Dmart", 20, 100, 20, 2, 2);
	empWageBuilder.addCompany("Reliance", 25, 105, 50, 2, 2);
	computeEmpWage(empWageBuilder);

	empWageBuilder.getTotalWageBasedOnCompany("Reliance");

	return 0;
}

