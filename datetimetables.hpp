#ifndef DATETIMETABLES_HPP
#define DATETIMETABLES_HPP

#include "datetimedeps.hpp"

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

static const int numberOfDaysByMonth[12] =
													{
														daysInJanuary, daysInFebruary, daysInMarch,
														daysInApril, daysInMay, daysInJune,
														daysInJuly, daysInAugust, daysInSeptember,
														daysInOctober, daysInNovember, daysInDecember
													};

//	This might need adjustment when dealing with translations or abbreviated formats
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

static const string monthsByName[12] =
									{
										january, february, march,
										april, may, june,
										july, august, september,
										october, november, december
									};

//	Also might need to be adjusted for abbrevations and translations
string sunday = "Sunday";
string monday = "Monday";
string tuesday = "Tuesday";
string wednesday = "Wednesday";
string thursday = "Thursday";
string friday = "Friday";
string saturday = "Saturday";

static const string weekdaysByName[7] =
									{
										sunday, monday, tuesday, wednesday, thursday, friday, saturday
									};



#endif	//	DATETIMETABLES_HPP



//	TODO:
//
//
//
