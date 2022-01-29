#ifndef DATETIMETABLES_HPP
#define DATETIMETABLES_HPP

#include "datetimedeps.hpp"

static const int monthsInGregorian = 12;

static const int daysInJanuary = 31;
static const int daysInFebruary = 28;	//	Leap year not accounted for yet
static const int daysInMarch = 31;
static const int daysInApril = 30;
static const int daysInMay = 31;
static const int daysInJune = 30;
static const int daysInJuly = 31;
static const int daysInAugust = 31;
static const int daysInSeptember = 30;
static const int daysInOctober = 31;
static const int daysInNovember = 30;
static const int daysInDecember = 31;

static const int numberOfDaysByMonth[12] = {
	daysInJanuary, daysInFebruary, daysInMarch,
	daysInApril, daysInMay, daysInJune,
	daysInJuly, daysInAugust, daysInSeptember,
	daysInOctober, daysInNovember, daysInDecember
};

// Acts like a look up table of the ordinal dates in the year, calculated
// for each month. An ordinal date is like a running count of the number of
// days. This count is not zero indexed. January 1st is represented as 1
static const int ordinalJanuary = 0;
static const int ordinalFebruary = 31;
static const int ordinalMarch = 59;
static const int ordinalApril = 90;
static const int ordinalMay = 120;
static const int ordinalJune = 151;
static const int ordinalJuly = 181;
static const int ordinalAugust = 212;
static const int ordinalSeptember = 243;
static const int ordinalOctober = 273;
static const int ordinalNovember = 304;
static const int ordinalDecember = 334;

static const int ordinalMonths[13] = {
	ordinalJanuary, ordinalFebruary, ordinalMarch,
	ordinalApril, ordinalMay, ordinalJune,
	ordinalJuly, ordinalAugust, ordinalSeptember,
	ordinalOctober, ordinalNovember, ordinalDecember,
	365
};

static const int ordinalLeapMonths[13] = {
	ordinalJanuary, ordinalFebruary, ordinalMarch + 1,
	ordinalApril + 1, ordinalMay + 1, ordinalJune + 1,
	ordinalJuly + 1, ordinalAugust + 1, ordinalSeptember + 1,
	ordinalOctober + 1, ordinalNovember + 1, ordinalDecember + 1,
	366
};

// This might need adjustment when dealing with translations or abbreviated
// formats
static const string january = "January";
static const string february = "February";
static const string march = "March";
static const string april = "April";
static const string may = "May";
static const string june = "June";
static const string july = "July";
static const string august = "August";
static const string september = "September";
static const string october = "October";
static const string november = "November";
static const string december = "December";

static const string monthsByName[12] = {
	january, february, march,
	april, may, june,
	july, august, september,
	october, november, december
};

// Also might need to be adjusted for abbrevations and translations
string sunday = "Sunday";
string monday = "Monday";
string tuesday = "Tuesday";
string wednesday = "Wednesday";
string thursday = "Thursday";
string friday = "Friday";
string saturday = "Saturday";

static const string weekdaysByName[7] = {
	sunday, monday, tuesday,
	wednesday, thursday, friday,
	saturday
};

#endif	//	DATETIMETABLES_HPP



//	TODO:
//
//
//
