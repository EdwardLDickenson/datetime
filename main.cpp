//	Notes:
// Currently, this library only supports saturation arithmetic. Future
// versions may support modular arithmetic
//
// Because the datestamp class is a wrapper around a bitstamp represented as an
// integer, the values are not zero indexed.
//
//

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
	//             yyyymmdd
	dateStamp late(19990704);

	// Verifiy that difference is commutative
	group.equal(29, early.differenceInYears(late));
	group.equal(29, late.differenceInYears(early));

}

int main(int argc, char *argv[])
{
	cout << "===\tStarting Program\t===" << endl;

	dateStamp date;

	TestSuite dateTimeSuite("units.csv");
	TestGroup constants("Constant Values");
	TestGroup dayGroup("Day Operations");
	TestGroup monthGroup("Month Operations");
	TestGroup yearGroup("Year operations");
	TestGroup stampIntegrity("Stamp Integrity");
	TestGroup differences("Datestamp Differences");

	//	Lookup tables, constants, non-computed values, and compile time values
	//	not including TMP values.
	testConsts(constants);
	testDay(dayGroup);
	testMonth(monthGroup);
	testYear(yearGroup);
	testStampIntegrity(stampIntegrity);
	testDifferences(differences);

	dateTimeSuite.addGroup(constants);
	dateTimeSuite.addGroup(dayGroup);
	dateTimeSuite.addGroup(monthGroup);
	dateTimeSuite.addGroup(yearGroup);
	dateTimeSuite.addGroup(stampIntegrity);
	dateTimeSuite.addGroup(differences);
	dateTimeSuite.run();
	dateTimeSuite.write();

	cout << "===\tEnding Program\t\t===" << endl;
}



//	TODO:
//
//
//