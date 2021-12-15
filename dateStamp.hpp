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
	bool isLeap(int other);
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


#endif	//	DATESTAMP_HPP



//	TODO:
//	setDay should throw a warning, but not an error, when the value exceeds the
//	number of days in the month.
//
//
