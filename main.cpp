//	This library requires LazyTest for unit testing
#include <lazytest.hpp>

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

void testDate(TestGroup &group)
{
	dateStamp stamp;

	group.equal(1970, stamp.getYear());
	group.equal(1, stamp.getMonth());
	group.equal(1, stamp.getDay());
	group.equal(19700101, stamp.getDateStamp());

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

int main(int argc, char *argv[])
{
	cout << "===\tStarting Program\t===" << endl;

	dateStamp date;

	TestSuite dateTimeSuite("units.csv");
	TestGroup dateGroup("Date Stamp");
	TestGroup constants("Constant Values");

	//	Lookup tables, constants, non-computed values, and compile time values
	//	not including TMP values.
	testConsts(constants);
	testDate(dateGroup);

	dateTimeSuite.addGroup(constants);
	dateTimeSuite.addGroup(dateGroup);
	dateTimeSuite.run();
	dateTimeSuite.write();

	cout << "===\tEnding Program\t\t===" << endl;
}



//	TODO:
//
//
//
