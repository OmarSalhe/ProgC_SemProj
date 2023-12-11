
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
