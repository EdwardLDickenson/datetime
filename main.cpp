//	Notes:
// Currently, this library only supports saturation arithmetic. Future
// versions may support modular arithmetic
//
// Because the datestamp class is a wrapper around a bitstamp represented as an
// integer, the values are not zero indexed.


#include <lazytest/lazytest.hpp>
#include "dateStamp.hpp"

void testConsts(TestGroup &group)
{
	group.equal(31, daysInJanuary);
	group.equal(28, daysInFebruary);
	group.equal(31, daysInMarch);
	group.equal(30, daysInApril);
	group.equal(31, daysInMay);
	group.equal(30, daysInJune);
	group.equal(31, daysInJuly);
	group.equal(31, daysInAugust);
	group.equal(30, daysInSeptember);
	group.equal(31, daysInOctober);
	group.equal(30, daysInNovember);
	group.equal(31, daysInDecember);

	group.equal(string("January"), january);
	group.equal(string("February"), february);
	group.equal(string("March"), march);
	group.equal(string("April"), april);
	group.equal(string("May"), may);
	group.equal(string("June"), june);
	group.equal(string("July"), july);
	group.equal(string("August"), august);
	group.equal(string("September"), september);
	group.equal(string("October"), october);
	group.equal(string("November"), november);
	group.equal(string("December"), december);

	group.equal(string("Sunday"), sunday);
	group.equal(string("Monday"), monday);
	group.equal(string("Tuesday"), tuesday);
	group.equal(string("Wednesday"), wednesday);
	group.equal(string("Thursday"), thursday);
	group.equal(string("Friday"), friday);
	group.equal(string("Saturday"), saturday);

	group.equal(31, numberOfDaysByMonth[0]);
	group.equal(28, numberOfDaysByMonth[1]);
	group.equal(31, numberOfDaysByMonth[2]);
	group.equal(30, numberOfDaysByMonth[3]);
	group.equal(31, numberOfDaysByMonth[4]);
	group.equal(30, numberOfDaysByMonth[5]);
	group.equal(31, numberOfDaysByMonth[6]);
	group.equal(31, numberOfDaysByMonth[7]);
	group.equal(30, numberOfDaysByMonth[8]);
	group.equal(31, numberOfDaysByMonth[9]);
	group.equal(30, numberOfDaysByMonth[10]);
	group.equal(31, numberOfDaysByMonth[11]);

	group.equal(string("January"), monthsByName[0]);
	group.equal(string("February"), monthsByName[1]);
	group.equal(string("March"), monthsByName[2]);
	group.equal(string("April"), monthsByName[3]);
	group.equal(string("May"), monthsByName[4]);
	group.equal(string("June"), monthsByName[5]);
	group.equal(string("July"), monthsByName[6]);
	group.equal(string("August"), monthsByName[7]);
	group.equal(string("September"), monthsByName[8]);
	group.equal(string("October"), monthsByName[9]);
	group.equal(string("November"), monthsByName[10]);
	group.equal(string("December"), monthsByName[11]);

	group.equal(string("Sunday"), weekdaysByName[0]);
	group.equal(string("Monday"), weekdaysByName[1]);
	group.equal(string("Tuesday"), weekdaysByName[2]);
	group.equal(string("Wednesday"), weekdaysByName[3]);
	group.equal(string("Thursday"), weekdaysByName[4]);
	group.equal(string("Friday"), weekdaysByName[5]);
	group.equal(string("Saturday"), weekdaysByName[6]);
}

void testDay(TestGroup &group)
{
	dateStamp stamp;

	group.equal(1, stamp.getDay());
	group.equal(19700101, stamp.getDateStamp());
	group.equal(1, stamp.getOrdinalDay());

	stamp.setDay(10);
	group.equal(19700110, stamp.getDateStamp());
	stamp.setDay(19);
	group.equal(19700119, stamp.getDateStamp());
	stamp.setDay(7);
	group.equal(19700107, stamp.getDateStamp());
	stamp.setDay(99);
	group.equal(19700199, stamp.getDateStamp());
	stamp.setDay(100);
	group.equal(19700200, stamp.getDateStamp());
}

void testMonth(TestGroup &group)
{
	dateStamp stamp;

	// Test default month value in timestamp
	group.equal(1, stamp.getMonth());

	// Check the bounds on month timestamp
	stamp.setMonth(0);
	group.equal(1, stamp.getMonth());

	for(int i = 1; i < 13; ++i)
	{
		stamp.setMonth(i);
		group.equal(i, stamp.getMonth());
	}
}

void testYear(TestGroup &group)
{
	dateStamp stamp;

	// Test the default year value in the timestamp
	group.equal(1970, stamp.getYear());

	stamp.setYear(1950);
	group.equal(1950, stamp.getYear());
	stamp.setYear(750);
	group.equal(750, stamp.getYear());
	stamp.setYear(40);
	group.equal(40, stamp.getYear());
	stamp.setYear(-40);
	group.equal(-40, stamp.getYear());
	stamp.setYear(-750);
	group.equal(-750, stamp.getYear());
	stamp.setYear(-1970);
	group.equal(-1970, stamp.getYear());
	stamp.setYear(2000);
	group.equal(2000, stamp.getYear());
	stamp.setYear(0);
	group.equal(1, stamp.getYear());
	stamp.setYear(1);
	group.equal(1, stamp.getYear());
	stamp.setYear(-1);
	group.equal(-1, stamp.getYear());
}

// This function tests the integrity of the datestamp after performing an
// operation. It does not perform detailed tests on every operation.
void testStampIntegrity(TestGroup &group)
{
	dateStamp stamp;
}

void testDifferences(TestGroup &group)
{
	dateStamp early;
	// July 4th, 1999
	dateStamp late(19990704);
	dateStamp twelveHundred(12000101);
	dateStamp twentyTwoHundred(22000101);
	// January 1st 500BC
	dateStamp fiveHundredBC(-5000101);
	// January 1st AD500
	dateStamp adFiveHundred(5000101);
	dateStamp jan(19700101);
	dateStamp mar(19700301);
	dateStamp dec(19691201);

	// Verifiy that difference is commutative
	group.equal(29, early.differenceInYears(late));
	group.equal(29, late.differenceInYears(early));
	group.equal(1000, twelveHundred.differenceInYears(twentyTwoHundred));
	group.equal(1000, twentyTwoHundred.differenceInYears(twelveHundred));
	group.equal(1000, fiveHundredBC.differenceInYears(adFiveHundred));
	group.equal(1000, adFiveHundred.differenceInYears(fiveHundredBC));
	//group.equal(0, dec.differenceInYears(jan));
	//group.equal(0, jan.differenceInYears(dec));
	//group.equal(0, jan.differenceInYears(mar));
	//group.equal(0, mar.differenceInYears(jan));

	//group.equal(2, jan.differenceInMonths(mar));
}

void testLeap(TestGroup &group)
{
	dateStamp date;

	// There is a known issue with the unit test library which causes issues
	// when comparing bools. This will be fixed in a future iteration of the
	// unit test library, but for now a work around will accomplish the goal
	//group.equal(false, date.isLeap());

	// False, True, and the value to be compared
	int f = 0;
	int t = 1;
	int val = f;

	if(!date.isLeap())
	{
		val = f;
	}
	else
	{
		val = t;
	}
	group.equal(val, f, "1970 is not a leap year");

	date.setYear(1980);
	if(!date.isLeap())
	{
		val = f;
	}
	else
	{
		val = t;
	}
	group.equal(val, t, "1980 is a leap year");

	date.setYear(2000);
	if(!date.isLeap())
	{
		val = f;
	}
	else
	{
		val = t;
	}
	group.equal(val, t, "2000 is a leap year");

	date.setYear(1900);
	if(!date.isLeap())
	{
		val = f;
	}
	else
	{
		val = t;
	}
	group.equal(val, f, "1900 is not a leap year");

	date.setYear(2022);
	group.equal(490, date.countLeapYears());

	// See the documentation for context on why the year 4AD is an important
	// year to test
	date.setYear(4);
	group.equal(1, date.countLeapYears());

	date.setYear(1);
	group.equal(0, date.countLeapYears());

	date.setYear(2020);
	group.equal(490, date.countLeapYears());

	date.setYear(2019);
	group.equal(489, date.countLeapYears());

	date.setYear(2021);
	group.equal(490, date.countLeapYears());
}

void testOrdinalDays(TestGroup &group)
{
	dateStamp date;

	// Count the number of days between January 1st 1AD and:
	// January 1st, 1970
	group.equal(719162, date.getOrdinalDay());
	// January 2nd, 1970
	date.setDay(2);
	group.equal(719163, date.getOrdinalDay());
	// February 2nd, 1970
	date.setMonth(2);
	group.equal(719194, date.getOrdinalDay());
	// December 2nd, 1970
	date.setMonth(12);
	group.equal(719497, date.getOrdinalDay());
	// December 31, 1970
	date.setDay(31);
	group.equal(719526, date.getOrdinalDay());;
	// December 31, 1972
	date.setYear(1972);
	group.equal(720257, date.getOrdinalDay());
	// December 31, 1980
	date.setYear(1980);
	group.equal(723179, date.getOrdinalDay());
	// December 31, 1999
	date.setYear(1999);
	group.equal(730118, date.getOrdinalDay());

	// The bug seems to be caused by the way that leap days are applied to leap
	// years. The leap day is currently applied to the start of the year, making
	// January 1st appear as January 2nd

	// December 31, 2000
	date.setYear(2000);
	group.equal(730484, date.getOrdinalDay());
	// January 1st, 2000
	date.setYear(2000);
	date.setMonth(1);
	date.setDay(1);
	group.equal(730119, date.getOrdinalDay());
	// March 1st, 2000
	date.setMonth(3);
	group.equal(730179, date.getOrdinalDay());

	// January 1st, 2020
	date.setYear(2020);
	date.setMonth(1);
	group.equal(737424, date.getOrdinalDay());
}

int main(int argc, char *argv[])
{
	cout << "===\tStarting Program\t===" << endl;

	TestSuite dateTimeSuite("units.csv");

	TestGroup constants("Constant values");
	TestGroup dayGroup("Day operations");
	TestGroup monthGroup("Month operations");
	TestGroup yearGroup("Year operations");
	TestGroup stampIntegrity("Stamp integrity");
	TestGroup differences("Datestamp differences");
	TestGroup leaps("Leap Year Formula");
	TestGroup ordinals("Ordinal Days");

	//	Lookup tables, constants, non-computed values, and compile time values
	//	not including TMP values.
	testConsts(constants);
	testDay(dayGroup);
	testMonth(monthGroup);
	testYear(yearGroup);
	testStampIntegrity(stampIntegrity);
	testDifferences(differences);
	testLeap(leaps);
	testOrdinalDays(ordinals);

	dateTimeSuite.addGroup(constants);
	dateTimeSuite.addGroup(dayGroup);
	dateTimeSuite.addGroup(monthGroup);
	dateTimeSuite.addGroup(yearGroup);
	dateTimeSuite.addGroup(stampIntegrity);
	dateTimeSuite.addGroup(differences);
	dateTimeSuite.addGroup(leaps);
	dateTimeSuite.addGroup(ordinals);

	dateTimeSuite.run();
	dateTimeSuite.write();

	cout << "===\tEnding Program\t\t===" << endl;
}



//	TODO:
//
//
//
