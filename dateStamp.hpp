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
	int convertOrdinalDay(int days);
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
		// YYYYMMDD
		// XXXX0228 = 228
		if((getMonth() * 100 + getDay()) > 228)
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
int dateStamp::convertOrdinalDay(int day)
{
	return 0;
}

#endif	//	DATESTAMP_HPP



//	TODO:
//	setDay should throw a warning, but not an error, when the value exceeds the
//	number of days in the month.
//
//
