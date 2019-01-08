#pragma once

#ifndef DATESTAMP_HPP
#define DATESTAMP_HPP

#include "DateTimeDependencies.hpp"
#include "DateTimeTables.hpp"

class DateStamp
{
private:
	int stamp;

public:
	DateStamp();
	DateStamp(int stmmp);
	DateStamp(string stmp);
	DateStamp(DateStamp &stmp);

	int getYear();
	int getMonth();
	int getDay();
	int getDateStamp();
	string getWeekday();
	string getMonthName();

	void setYear(int year);
	void setMonth(int month);
	void setDay(int day);
	void setYear(string year);
	void setMonth(string month);
	void setDay(string day);
	void setYear(DateStamp &year);
	void setMonth(DateStamp &month);
	void setDay(DateStamp &day);
	void setMonthName(string month);
	void setWeekday(string day);

	void setYearMonth(int year, int month);
	void setYearMonthDay(int year, int month, int day);

	DateStamp addDays(int days);
	DateStamp addMonths(int months);
	DateStamp addYears(int years);
};

DateStamp::DateStamp()
{
	stamp = 19700101;
}

DateStamp::DateStamp(int otherStamp)
{
	stamp = otherStamp;
}

DateStamp::DateStamp(string otherStamp)
{

}

int DateStamp::getYear()
{
	return int(stamp / 10000);
}

int DateStamp::getMonth()
{	
	return (stamp - (int(stamp / 10000) * 10000)) / 100;
}

int DateStamp::getDay()
{
	int monthDay = stamp - (int(stamp / 10000) * 10000);

	return monthDay - (int(monthDay / 100) * 100);
}

int DateStamp::getDateStamp()
{
	return stamp;
}

void DateStamp::setDay(int day)
{

}

#endif	//	DATESTAMP_HPP


