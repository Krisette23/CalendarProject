/*
* *File:   calendar.c
* ----------------------------------
* this program is used to generate a calendar for a year
* entered by the user
*/

#include <stdio.h>
#include "simpio.h"
#include "genlib.h"


/* define constants
*---------------------------------
* Days of the week are represented by numbers 0-6
* Months of the year are identified by the integers 1-12
* because this numeric representation for months is in
* common use, no special constants are defined.
*/


#define SUNDAY 0
#define MONDAY 1
#define TUESDAY 2
#define WEDNESDAY 3
#define THURSDAY 4
#define FRIDAY 5
#define SATURDAY 6

/* function prototypes */


void GiveInstructions(void);
int GetYearFromUser(void);
void PrintCalendar(int year);
void PrintCalendarMonth(int month, int year);
void IndentFirstLine(int weekday);
int MonthDays(int month, int year);
int FirstDayOfMonth(int month, int year);
string MonthName(int month);
bool IsLeapYear(int year);


/* main program */

main()
{
	int year;
	string monthName;
	GiveInstructions();
	year = GetYearFromUser();
	PrintCalendar(year);
}

/*
* Function: GiveInstructions
* Usage: GiveInstructions();
* ---------------------------------
*
* This function gives instructions to the user.
*/

void GiveInstructions(void)
{
	printf("This program displays a calendar for a full year.\n");
	printf("Year. The year must not be before 1900.\n");

}

/*
* Function: GetYearFromUser
* Usage: year = GetYearFromUser();
* ---------------------------------
*
* This function prompts the user for a year and reads the
* response. If the user enters a year less than 1900, the
* program gives the user another chance.
*/

int GetYearFromUser(void)
{
	int year;
	while (TRUE)
	{
		printf("Which year ");
		year = GetInteger();
		if (year >= 1900) return (year);
		printf("The year must be at least 1900.\n");
	}
}

/*
*Function: PrintCalendar
* USage: PrintCalendar(year);
* ---------------------------------
* This procedure prints a calendar for the year specified

*/

void PrintCalendar(int year)
{
	int month;

	for (month = 1; month <= 12; month++) {
		PrintCalendarMonth(month, year);
		printf("\n");
	}
}

/*
* Function: PrintCalendarMonth
* Usage: PrintCalendarMonth(month, year);
* ---------------------------------
* This procedure prints a calendar for the given month and year
*/


void PrintCalendarMonth(int month, int year)
{
	int weekday, nDays;

	printf("\n\n");
	printf("  %s %d\n", MonthName(month), year);
	printf(" Su Mo Tu We Th Fr Sa\n");

	weekday = FirstDayOfMonth(month, year);
	IndentFirstLine(weekday);

	nDays = MonthDays(month, year);
	for (int day = 1; day <= nDays; day++) {
		printf("%3d", day);
		if (weekday == SATURDAY) printf("\n");
		weekday = (weekday + 1) % 7;
	}
	if (weekday != SUNDAY)	printf("\n");
}


/*
* Function: IndentFirstLine
* Usage: IndentFirstLine(weekday);
* ---------------------------------
* This procedure prints spaces up to the position of the first
*
* day of the month on the calendar.
*/

void IndentFirstLine(int weekday)
{
	int i;

	for (i = 0; i < weekday; i++) {
		printf("   ");
	}
}

/*
* Function: MonthDays
* Usage: ndays = MonthDays(month, year);
*	---------------------------------
* This function returns the number of days in the specified
* month and year.
*/

int MonthDays(int month, int year)
{
	switch (month) {
	case 2:
		if (IsLeapYear(year)) return (29);
		else return (28);
	case 4: case 6: case 9: case 11: return (30);
	default:

		return (0);
	}
}

/*
* Function: FirstDayOfMonth
* Usage: weekday = FirstDayOfMonth(month, year);
* ---------------------------------
* This function returns the day of the week on which the
* specified month begins. The function uses Zeller's congruence,
* which is a mathematical formula for calculating the day of the
* week for any date in the past, present, or future.
*/


int FirstDayOfMonth(int month, int year)
{
	int adjustment, century, yrInCentury, dayInMonth;

	if (month < 3) {
		month += 12;
		year--;
	}
	adjustment = (13 * (month + 1)) / 5;
	century = year / 100;
	yrInCentury = year % 100;
	dayInMonth = (yrInCentury + (yrInCentury / 4) + (century / 4) + adjustment + 1) % 7;
	return (dayInMonth);
}

/*
* Function: MonthName
* Usage: name = MonthName(month);
* ---------------------------------
* This function returns the name of the specified month.
*/

string MonthName(int month)
{
	switch (month)
	{
	case 1: return ("January");
	case 2: return ("February");
	case 3: return ("March");
	case 4: return ("April");
	case 5:  return ("May");
	case 6:  return ("June");
	case 7:  return ("July");
	case 8:  return ("August");
	case 9:  return ("September");
	case 10:  return ("October");
	case 11:  return ("November");
	case 12:  return ("December");
	default: return ("Illegal Month");
	}
}

/*
* Function: isLeapYear
* Usage: if (isLeapYear(year)) . . .
* ---------------------------------
* This function returns TRUE if year is a leap year.
*/

bool IsLeapYear(int year)
{
	return ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0);
}