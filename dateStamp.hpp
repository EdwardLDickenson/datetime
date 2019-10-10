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

public:
	dateStamp();
	dateStamp(int stmmp);
	dateStamp(string stmp);
	dateStamp(dateStamp &stmp);

	int getYear();
	int getMonth();
	int getDay();
	int getDateStamp();
	string getWeekday();

	void setYear(int year);
	void setMonth(int month);
	void setDay(int day);
	void setYear(string year);
	void setMonth(string month);
	void setDay(string day);
	void setYear(dateStamp &year);
	void setMonth(dateStamp &month);
	void setDay(dateStamp &day);
	void setMonthName(string month);
	void setWeekday(string day);

	void setYearMonth(int year, int month);
	void setYearMonthDay(int year, int month, int day);

	dateStamp addDays(int days);
	dateStamp addMonths(int months);
	dateStamp addYears(int years);
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

	//	This code is more applicable for the addDays function

	/*day = math.abs(day);
	int daysInCurrentMonth = numberOfDaysByMonth[getMonth() - 1];
	int currentDay = getDay();

	if(currentDay + day > daysInCurrentMonth)
	{
		cout << "Too big, overflow into the next month(s)"
	}

	else
	{

	}*/

	day = abs(day);
	stamp -= getDay();
	stamp += day;
}



#endif	//	DATESTAMP_HPP



//	TODO:
//	setDay should throw a warning, but not an error, when the value exceeds the
//	number of days in the month.
//
//
