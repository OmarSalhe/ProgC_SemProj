
#include <stdio.h>
#include <string.h> // for strcmp

#define week 7
#define months_in_year 12
#define full_year 365

int zeller();
int isLeapYear(int year);
int numberOfLeapYears(int target_year);
int numberOfDaysApart(int target_year, int target_month);
int totalDaysIntoYear(int month, int day);
int firstDayOfMonth(int target_month, int target_year);
void printCalendar(int year, int month);
void printAllCalendars(int year);

//starting date for the calendar is October 15, 1582 or 15/10/1582
const int start_day = 15, start_month = 10, start_year = 1582;

const int monthDays[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

const char* dayNames[] = {
    "Sun",
    "Mon",
    "Tue",
    "Wed",
    "Thu",
    "Fri",
    "Sat"
};
const char* monthNames[] = {   
    "January",
    "February",
    "March",
    "April",
    "May",
    "June",
    "July",
    "August",
    "September",
    "October",
    "November",
    "December"
};

int main(){
    int year;
    char input_month[12];

    printf("Enter year: ");
    scanf("%d", &year);

    printf("Enter month ('all' or 1-12): ");
    scanf("%s", input_month);

    if (strcmp(input_month, "all") == 0) {
        printAllCalendars(year);
    } else {
        int month = atoi(input_month); //atoi is to convert int to str

        if (month < 1 || month > 12) {
            printf("Invalid month input. Please enter 'all' or a number between 1 and 12.\n");
            return 1;
        }

        printCalendar(year, month);
    }

    return 0;
}

void printAllCalendars(int year) {
    for (int month = 1; month <= months_in_year; month++) {
        printCalendar(year, month);
        printf("\n");
    }
}

void printCalendar(int year, int month){
    printf("Calendar for %s %d:\n", monthNames[month - 1], year);

    // Print the top grid line
    for (int i = 0; i < week; i++) {
        printf("+---");
    }
    printf("+\n");

    // Print day names
    for (int i = 0; i < week; i++) {
        printf("|%s ", dayNames[i]);
    }
    printf("|\n");

    // Print the middle grid line
    for (int i = 0; i < week; i++) {
        printf("+---");
    }
    printf("+\n");

    // Calculate the first day of the month
    int firstDay = firstDayOfMonth(month - 1, year);

    // Print leading spaces
    for (int i = 0; i < firstDay; i++) {
        printf("|   ");
    }

    // Print the days of the month
    int daysInMonth = monthDays[month - 1];
    for (int day = 1; day <= daysInMonth; day++) {
        printf("|%3d", day);
        if ((firstDay + day) % week == 0) {
            printf("|\n");

            // Print the grid line after each week
            for (int i = 0; i < week; i++) {
                printf("+---");
            }
            printf("+\n");
        }
    }

    // If the last day of the month is not the end of the week, print the remaining spaces
    if ((firstDay + daysInMonth) % week != 0) {
        for (int i = (firstDay + daysInMonth) % week; i < week; i++) {
            printf("|     ");
        }
        printf("|\n");

        // Print the bottom grid line
        for (int i = (firstDay + daysInMonth) % week; i < week; i++) {
            printf("+---");
        }
        printf("+\n");
    }

    // Display additional information after printing the calendar
    int leapDays = numberOfLeapYears(year);
    int daysIntoCurrent = totalDaysIntoYear(month - 1, 1);
    int daysLeftStart = full_year - totalDaysIntoYear(start_month, start_day);

    printf("Years Ahead: %d, Leap Days: %d, Days Into Current: %d, Days Left Start: %d\n",
           year - start_year, leapDays, daysIntoCurrent, daysLeftStart);
}


int firstDayOfMonth(int target_month, int target_year) {
    int daysApart = numberOfDaysApart(target_year, target_month);

    // what day of the week the starting day is
    int firstDay = zeller();

    // daysApart + firstDay calculates the target day. modulo week (7) confines this value to a day in the week.
    return (daysApart + firstDay) % week; 
}

int zeller() {
    // K = last two year digits, J = first two year digits
    int K = start_year % 100, J = (start_year / 100);

    // returns a value between 0-6 -> 0 = Saturday, 1 = Sunday ...
    int zellerDay = (start_day + (13 * (start_month + 1) / 5) + K + (K / 4) + (J / 4) - 2 * J) % week;

    // adjusts zeller values to traditional calendar values sunday = 0, monday = 1, ...
    return (zellerDay + 6 + week) % 7; // + week ensures return is positive
}

int isLeapYear(int year) {
    // return true or false, depending on if leap year or not
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int numberOfLeapYears(int target_year) {
    // # of days added due to leap years
    int leapDays = 0;
    // iterates over every year between start and target year checking for leap years
    for (int i = start_year; i < target_year + 1; i++) { 
        // adds 1 day for every leap year
        if (isLeapYear(i)) {
            leapDays++;         
        }
    }
    return leapDays;
}

int numberOfDaysApart(int target_year, int target_month) {
    // accounts for additional days due to leap years
    int leapDays = numberOfLeapYears(target_year);

    // the # of full years, in days, elapsed between start and target date
    int yearAhead = (target_year - start_year - 1) * full_year;

    // calculates remaining days within starting year
    int daysLeftStart = full_year - totalDaysIntoYear(start_month, start_day);    // subtracts remaining days in the year for the starting date

    // accounts for a potential leap year on start
    if (isLeapYear(start_year)) { 
        daysLeftStart--;
    }

    // calculates # of days into the target year
    int daysIntoCurrent = 0;
    if (target_month == 0)
         daysIntoCurrent = totalDaysIntoYear(target_month, 0); // day = 0 because start of month
    else
         daysIntoCurrent = totalDaysIntoYear(target_month, 1);

    // returns the total # of days elapsed between the start and end date
    return yearAhead + leapDays + daysIntoCurrent + daysLeftStart;  // total # of days between entered month and starting date
}

int totalDaysIntoYear(int month, int day) {
    int numOfDays = 0;

    // adds values of each full month passed 
    for (int i = 0; i < month - 1; i++) { 
        numOfDays += monthDays[i];
    }

    // adds # of days into the current month
    numOfDays += day;

    return numOfDays;
}


#include <stdio.h>

#define week 7
#define months_in_year 12
#define full_year 365

int zeller();
int isLeapYear(int year);
int numberOfLeapYears(int target_year);
int numberOfDaysApart(int target_year, int target_month);
int totalDaysIntoYear(int month, int day);
int firstDayOfMonth(int target_month, int target_year);

//starting date for the calendar is October 15, 1582 or 15/10/1582
const int start_day = 15, start_month = 10, start_year = 1582;


const int monthDays[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

const char* dayNames[] = {
    "Sunday",
    "Monday",
    "Tuesday",
    "Wednesday",
    "Thursday",
    "Friday",
    "Saturday"
};
const char* monthNames[] = {   
    "January",
    "February",
    "March",
    "April",
    "May",
    "June",
    "July",
    "August",
    "September",
    "October",
    "November",
    "December"
};

int main(){
    int month = 1, year = 2023;
    printf("%s", dayNames[firstDayOfMonth(month, year)]);
    return 0;
}

int firstDayOfMonth(int target_month, int target_year){
    int daysApart = numberOfDaysApart(target_year, target_month);
    
    //what day of the week the starting day is
    int firstDay = zeller();

    // daysApart + firstDay calculates the target day. modulo week (7) confines this value to a day in the week.
    return (daysApart + firstDay) % week; 
}

int zeller(){
    // K = last two year digits, J = first two year digits
    int K = start_year % 100, J = (start_year / 100);

    //returns a value between 0-6 -> 0 = Saturday, 1 = Sunday ...
    int zellerDay = (start_day + (13 * (start_month + 1) / 5) + K + (K / 4) + (J / 4) - 2 * J) % week;

    //adjusts zeller values to traditional calendar values sunday = 0, monday = 1, ...
    return (zellerDay + 6 + week) % 7; // + week ensures return is positive
}

int isLeapYear(int year){
    //return true or false, depending on if leap year or not
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int numberOfLeapYears(int target_year){
    //# of days added due to leap years
    int leapDays = 0;
    //iterates over every year between start and target year checking for leap years
    for (int i = start_year; i < target_year + 1; i++){ 
        //adds 1 day for every leap year
        if (isLeapYear(i)){
            leapDays++;         
        }
    }
    return leapDays;
}

int numberOfDaysApart(int target_year, int target_month){
    //accounts for additional days due to leap years
    int leapDays = numberOfLeapYears(target_year);
    
    //the # of full years, in days, elapsed between start and target date
    int yearAhead = (target_year - start_year - 1) * full_year;
    
    //calculates remaining days withiin starting year
    int daysLeftStart = full_year - totalDaysIntoYear(start_month, start_day);    //subtracts remaining days in the year for the starting date
    
    //accounts for potential leap year on start
    if (isLeapYear(start_year)){ 
        daysLeftStart--;
    }

    //calculates # of days into target year
    int daysIntoCurrent = 0;
    if (target_month == 0)
         daysIntoCurrent = totalDaysIntoYear(target_month, 0); //day = 0 b/c start of month
    else
         daysIntoCurrent = totalDaysIntoYear(target_month, 1); //day = 0 b/c start of month

    printf("Year Ahead: %d, Leap Days: %d, Days Into Current: %d, Days Left Start: %d\n", yearAhead, leapDays, daysIntoCurrent, daysLeftStart);

    //returns total # of days elapesed between start and end date
    return yearAhead + leapDays + daysIntoCurrent + daysLeftStart;  //total # of days between entered month and starting date
}

int totalDaysIntoYear(int month, int day){
    int numOfDays = 0;

    //adds values of each full month passed 
    for (int i = 0; i < month - 1; i++){ 
        numOfDays += monthDays[i];
    }

    //adds # of days into current month
    numOfDays += day;

    return numOfDays;
}




/*
int day;
    printf("pick a num from 1 to 30");
    scanf("%d", &day);

    printf("Month       Year\n");
    printf("Sun     Mon     Tue     Wed    Thu    Fri    Sat\n");

    for(int i = 0; i < 30; i++){
        if ((i % 7) == 0 && i != 0)
            printf("|\n __________________________________________\n\n");
        if ((i + 1) == day){
            if ((i + 1) < 10)
            printf("|%d  UwU", i + 1);
            else
            printf("|%d UwU", i + 1);
        }
        else{
            if ((i + 1) < 10)
            printf("| %d    ", i + 1);
            else
            printf("| %d   ", i + 1);
        }
        
    }
*/
