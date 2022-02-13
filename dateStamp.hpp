#pragma once

#ifndef DATESTAMP_HPP
#define DATESTAMP_HPP

#include "datetimedeps.hpp"
#include "datetimetables.hpp"

class dateStamp
{
private:
	//	Using a signed integer allows for easier AD/BC conversion
	int stamp;
	// The date stamp consists of 4 "places" each one 2 characters wide
	//  1  2  3  4
	// YY YY MM DD
	// We can access these places by multiplying or dividing by 100, which is
	// referred to as the the place offset
	// It is important to note that the first and second positions are variable
	// because A.D. 2 is a real year. This should be represented

public:
	dateStamp();
	dateStamp(int stmmp);
	dateStamp(string stmp);

	int getYear();
	int getMonth();
	int getDay();
	int getDateStamp();
	int getOrdinalDay();
	int getOrdinalDayOfYear();
	int getOrdinalDayOfYear(int date);
	int convertOrdinalDay(int days);
	int convertOrdinalDayOfYear(int days);
	string getWeekday();

	void setYear(int year);
	void setMonth(int month);
	void setDay(int day);
	void setDateStamp(int stmp);
	void setMonthByName(string month);

	int differenceInYears(dateStamp other);
	int differenceInMonths(dateStamp other);
	int differenceInDays(dateStamp other);

	void addDays(int days);
	void addMonths(int months);
	void addYears(int years);

	bool isLeap();
	bool isLeap(int year);
	int countLeapYears();
	int countLeapYears(int year);
};

dateStamp::dateStamp()
{
	//	Unix timestamp
	stamp = 19700101;
}

dateStamp::dateStamp(int otherStamp)
{
	stamp = otherStamp;
}

dateStamp::dateStamp(string otherStamp)
{

}

int dateStamp::getYear()
{
	return int(stamp / 10000);
}

int dateStamp::getMonth()
{
	return (stamp - (int(stamp / 10000) * 10000)) / 100;
}

int dateStamp::getDay()
{
	int monthDay = stamp - (int(stamp / 10000) * 10000);

	return monthDay - (int(monthDay / 100) * 100);
}

int dateStamp::getDateStamp()
{
	return stamp;
}

void dateStamp::setDay(int day)
{
	day = abs(day);
	stamp -= getDay();
	stamp += day;
}

void dateStamp::setMonth(int month)
{
	if(month > monthsInGregorian)
	{
		month = monthsInGregorian;
	}

	else if(month < 1)
	{
		month = 1;
	}

	// Save the day for later use
	int day = dateStamp::getDay();

	// Divide the stamp by two place offsets to clear everything upto the year
	stamp /= 10000;
	// Multiply the stamp by one place offset so that we can add the month
	stamp *= 100;
	// Add the month value to the stamp.
	stamp += month;
	// Multiply by a place offset so that we can add the day
	stamp *= 100;
	// Add the day to the stamp
	stamp += day;
}

void dateStamp::setYear(int year)
{
	// The year A.D. 0 does not exist. Whenever a user passes 0 to this function
	// correct the value to 1.
	if(year == 0)
	{
		year = 1;
	}

	bool isBC = false;
	stamp = abs(stamp);

	if(year < 0)
	{
		isBC = true;
		year = abs(year);
	}

	int month = dateStamp::getMonth();
	int day = dateStamp::getDay();

	// Assign the stamp to the value of year passed by the user. Then multiply
	// by two position offsets.
	stamp = year;
	stamp *= 100;
	stamp += month;
	stamp *= 100;
	stamp += day;

	if(isBC)
	{
		stamp = -stamp;
	}
}

/*
================================================================================
Inputs: int stmp, the new datestamp
Output: none
Detail: Sets the current datestamp of this instance equal to the value of the
int stmp.
================================================================================
*/
void dateStamp::setDateStamp(int stmp)
{
	stamp = stmp;
}

void dateStamp::addDays(int days)
{
	//int year = getYear();
	//int month = getMonth();
	//int day = getDay();
}

int dateStamp::differenceInYears(dateStamp other)
{
	return abs(getYear() - other.getYear());
}

int dateStamp::differenceInMonths(dateStamp other)
{
	int result = 0;
	result += abs(getMonth() - other.getMonth());
	int yearDiff = differenceInYears(other);
	result += yearDiff * monthsInGregorian;

	return abs(result);
}

int dateStamp::differenceInDays(dateStamp other)
{
	//int daysPerYear = 365;
	//int year = getYear() - 1;
	//dateStamp unixEpoch(19700101);

	return 0;
}

// The logic to determine if a year is a leap year or not:
// If a year is divisible by 4, but not also divisible by 100 then it is a leap
// If a year is divisible by 400 it is a leap year regardless of any other
// divisor. For example, 1900 was not a leap year, while 2000 was a leap year.
// 1896, 1904, 1996, 2004 were also leap years
// =============================================================================
// Before the year 8AD in the Julian calendar the following were leap years:
// 45 BC, 42 BC, 39 BC, 36 BC, 33 BC, 30 BC, 27 BC, 24 BC, 21 BC, 18 BC, 15 BC,
// 12 BC, 9 BC, 8 AD, 12 AD
// https://archive.fo/iLTqO
// It isn't clear from internet sources how the Gregorian calendar deals with
// some of these dates. Some sources will call 4AD a leap year
// https://archive.ph/Zow5C
bool dateStamp::isLeap()
{
	int year = getYear();
	if((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
	{
		return true;
	}

	return false;
}

/*
================================================================================
Inputs: int year, the year to be checked
Output: bool, is a leap or not
Detail: Returns true if year is a leap year. Returns false if year is a common
year (non-leap). Functions the same as isLeap() but with external variables
================================================================================
*/
bool dateStamp::isLeap(int year)
{
	if((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
	{
		return true;
	}

	return false;
}

/*
================================================================================
Inputs: none
Output: int count
Detail: Returns the count of leap years from 1AD to the current year. For
example, if the year is 2022 the function will return a single integer
representing the number of leap years from [1, 2022]
================================================================================
*/
int dateStamp::countLeapYears()
{
	// A) Count the number of years that are divisible by 4
	// B) Count the number of years that are divisible by 100
	// C) Count the number of years that are divisible by 400
	// Subtract B from A then add C.
	// Years that are divisible by 100 are also divisible by 4, and the same is
	// true for years that are divisible by 400. If a year is divisible by 400
	// it is also divisible by 100. If a year is divisible by 4 there still is
	// the 100 divisiblity condition to check, but any year that is divisible by
	// 400 then it is always a leap year.
	int year = getYear();
	return (year / 4) - (year / 100) + (year / 400);
}

int dateStamp::countLeapYears(int year)
{
	return (year / 4) - (year / 100) + (year / 400);
}

/*
================================================================================
Inputs: none
Output: int days
Detail: Returns the number of days since January 1st 1AD. The running count of
days referred to as the ordinal day. This is not the same as the ordinal day of
the year. The ordinal day of the year can be computed by subtracting the
difference in days from the ordinal day to the start of the to be compared.
================================================================================
*/
int dateStamp::getOrdinalDay()
{
	// This can likely be collapsed into a bitmask to avoid a condition
	int leapDay = 0;
	if(isLeap())
	{
		// For an arbitrary leap year, we need to apply a leap day for February
		// 29th and every day after for that year.
		// YYYYMMDD
		// XXXX0228 = 229
		if((getMonth() * 100 + getDay()) > 229)
		{
			leapDay = 1;
		}
	}

	int yearOffset = getYear() - 1;

	return yearOffset * 365 + countLeapYears(yearOffset) + ordinalMonths[getMonth() - 1] + (getDay() - 1) + leapDay;
}

/*
================================================================================
Inputs: int days, the number of days since January 1st, 1AD
Output: int convertedDatestamp,the value of days converted into a datestamp
Detail: Accepts an integer, days, representing the count of all days, including
leap days, starting from January 1st 1AD and returns another integer,
convertedDatestamp, which matches the format of the datestmap class.
================================================================================
*/
int dateStamp::convertOrdinalDay(int days)
{
	// This number is inclusive of leap years and common years including the
	// 4, 100, and 400 factors to determine if a year is a common or a leap year
	//cout << "Converting " << days << endl;
	int daysInFourCent = 146097;
	int daysInOneCent = 365 * 100 + 24;
	int daysInFourYears = 365 * 4 + 1;

	int cycleMultiple = days / daysInFourCent;
	days -= cycleMultiple * daysInFourCent;
	int quarterCycleMultiple = days / daysInOneCent;
	days -= quarterCycleMultiple * daysInOneCent;
	int leapMultiple = days / daysInFourYears;
	days -= leapMultiple * daysInFourYears;
	int yearMultiple = days / (365 + 0);
	days -= yearMultiple * 365;
	int daysRemaining = days + 1;
	//cout << "Leap Multiple: " << leapMultiple << " Year Multiple: " << yearMultiple << " cycleMultiple: " << cycleMultiple << " quarterCycleMultiple: " << quarterCycleMultiple << endl;
	int year = (cycleMultiple * 400) + (quarterCycleMultiple * 100) + (leapMultiple * 4) + yearMultiple + 1;

/*
	int fourCentMultiple = (days + 0) / daysInFourCent;
	int daysMinusFourMultiple = (days + 0) - (fourCentMultiple * daysInFourCent);
	int leapsInOneCent = 24;
	int daysInOneCent = 365 * 100 + leapsInOneCent;
	int centMultiple = (days + 0) / daysInOneCent;
	int daysMinusOneCentMultiple = daysMinusFourMultiple - (centMultiple * daysInOneCent);
	int daysInFourYears = 365 * 4 + 1;
	int fourYearsMultiple = daysMinusOneCentMultiple / daysInFourYears;
	int daysMinusFourYears = daysMinusOneCentMultiple - (fourYearsMultiple * daysInFourYears);
	int yearsMultiple = daysMinusFourYears / 365;
	int daysRemaining = (daysMinusFourYears - (yearsMultiple * 365)) + 1;
	// Reconstruct the date
	int year = (fourCentMultiple * 400) + (centMultiple * 100) + (fourYearsMultiple * 4) + yearsMultiple;
	++year;
*/

	// The logic for this chunk of code can probably be consolidated into
	// convertOrdinalDayOfYear

	int month = 0;
	//while(daysRemaining > 31)
	/*
	while(daysRemaining > numberOfDaysByMonth[month])
	{
		int daysForThisMonth = numberOfDaysByMonth[month];
		if(isLeap(year) && ((month + 1) * 100) + daysRemaining == 229)
		{
			daysForThisMonth = 29;
		}
		daysRemaining -= daysForThisMonth;
		++month;
	}
	++month;
	*/

	//cout << daysRemaining << endl;
	bool leap = isLeap(year);
	if(leap)
	{
		//cout << "Executes?" << endl;
		daysRemaining += 0;
	}
	int ordinalDays = 0;
	//cout << "daysRemaining: " << daysRemaining;// << ", ordinalDays: " << ordinalDays << endl;
	for(int i = 0; i <= monthsInGregorian; ++i)
	{
		/*int daysInThisMonth = ordinalMonths[i];
		if(isLeap(year) && ((month + 1) * 100) + daysRemaining == 229)
		{
			daysInThisMonth = 29;
		}

		if(daysRemaining - daysInThisMonth < 0)
		{
			month = i;
			break;
		}
		daysRemaining -= daysInThisMonth;
		month = i;*/
		//int daysForThisMonth = ordinalMonths[i];
		ordinalDays = ordinalMonths[i + 1];
		//bool leap = isLeap(year);

		if(leap)
		{
			ordinalDays = ordinalLeapMonths[i + 1];
			//daysForThisMonth = ordinalLeapMonths[i];
			//daysRemaining += 1;
		}

		if(daysRemaining - ordinalDays <= 0)
		{
			ordinalDays = ordinalMonths[i];
			if(leap)
			{
				ordinalDays = ordinalLeapMonths[i];
			}
			//daysRemaining -= ordinalDays;
			month = i + 1;
			//cout << "\t daysForThisMonth: " << daysForThisMonth << endl;
			//daysRemaining -= daysForThisMonth;
			break;
		}
	}
	//cout <<  ", ordinalDays: " << ordinalDays << endl;
	daysRemaining -= (ordinalDays);
	//cout <<  ", ordinalDays: " << ordinalDays << " " << daysRemaining << endl;

	//cout << daysRemaining << endl;

	/*
	int multipleOf400 = days / daysIn400Years;
	int daysMinus400Multiple = daysIn400Years * multipleOf400;
	int leapYearsIn100CommonYears = 24;
	int daysIn100CommonYears = 365 * 100 + leapYearsIn100CommonYears;
	int daysMinus100Multiple = daysMinus400Multiple / daysIn100CommonYears;
	int daysIn4Years = 365 * 4 + 1;
	int daysMinus4Multiple = daysIn100CommonYears
	*/

	//int leapYearsIn400CommonYears = leapYearsIn100CommonYears * 3 + 1;
	//return year;
/*
	cout << "YYYY" << year;
	year *= 10000;
	cout << "MM" << month;
	month *= 100;
	cout << "DD" << daysRemaining << endl;
*/
	if(quarterCycleMultiple == 4)
	//if(cycleMultiple == 1)
	{
		//return (year * 10000) + (month * 100) + (daysRemaining);
	}

	//if(yearMultiple == 4 && year % 400 != 0) //&& cycleMultiple == 4)
	if(yearMultiple == 4 || quarterCycleMultiple == 4) //&& cycleMultiple == 4)
	{
		//cout << "year: " << year << endl;
		return ((year - 1) * 10000) + (12 * 100) + (31);
	}

	//             yyyymmdd
	return (year * 10000) + (month * 100) + (daysRemaining);
	//return year + month + daysRemaining;
}

/*
================================================================================
Inputs: none
Output: int ordinalDay, with a value between [1,366]
Detail: Given the current datestamp, this function will return the ordinal date
of the year. This number represents the count of days from January 1st of any
arbitrary year. The function is expected to return an integer between 1 and 366
inclusively. The function is also expected to operate on a valid datestamp
================================================================================
*/
int dateStamp::getOrdinalDayOfYear()
{
	int month = getMonth();
	int days = getDay();

	int leapDay = 0;
	if((getMonth() * 100 + getDay()) > 229 && isLeap())
	{
		leapDay = 1;
	}

	return ordinalMonths[month - 1] + days + leapDay;
}


/*
================================================================================
Inputs: int date, an integer datestamp matching the format of this library
Output: int ordinalDay, with a value between [1,366]
Detail: Given an integer, date, calculate the ordinal day from January 1st of
the year in date. Functions the same as funciton without a parameter, but
accepts external variables. Datestamp integrity is not checked.
================================================================================
*/

int dateStamp::getOrdinalDayOfYear(int date)
{
	return 0;
}

#endif	//	DATESTAMP_HPP



// TODO:
// setDay should throw a warning, but not an error, when the value exceeds the
// number of days in the month.
//
//
// Replace the magic numbers with readable constants in datetimetables.hpp
//
//
