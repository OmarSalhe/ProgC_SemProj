#include <stdio.h>
#include <string.h>

#define week 7

const char *dayNames[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

const char *monthNames[] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

int isLeapYear(int year);
int numberOfLeapYears(int target_year);
int numberOfDaysApart(int target_year, int target_month);
int totalDaysIntoYear(int month, int day, int target_year);
int firstDayOfMonth(int target_month, int target_year);
void printCalendar(int year, int month);
int daysAfter(int month, int year);

// starting date for the calendar is October 15, 1582, or 15/10/1582
const int start_day = 15, start_month = 10, start_year = 1582;
const int monthDays[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int main()
{
    int year, month;

    // Prompt the user to enter the year and ensure it is valid
    printf("Enter the year: ");
    while (scanf("%d", &year) != 1 || year < start_year)
    {
        // Handle invalid input
        printf("Invalid input. Please enter a valid year (since 15 October 1582): ");
        while (getchar() != '\n')
            ;
    }

    // Prompt the user to enter the month and ensure it is valid
    printf("Enter the month (as an integer or 'all'): ");
    char input[10];
    while (scanf("%s", input) == 1)
    {
        if (strcmp(input, "all") == 0)
        {
            // Print the calendar for the entire next year
            for (int i = 1; i <= 12; i++)
            {
                // Print only October to December for the year 1582
                if (year == 1582 && i < 10)
                    continue;

                printCalendar(year, i);
            }
            return 0;
        }
        else
        {
            // Convert the input to an integer
            sscanf(input, "%d", &month);
            if (month >= 1 && month <= 12)
            {
                // Print the calendar for the specified month and year
                printCalendar(year, month);
                return 0;
            }
        }

        // Handle invalid input
        printf("Invalid input. Please enter a valid month (as an integer or 'all'): ");
        while (getchar() != '\n')
            ;
    }

    return 0;
}

void printCalendar(int year, int month)
{
    printf("\n");

    // Print the month and year header
    printf("    %s - %d\n", monthNames[month - 1], year);

    // Print the days of the week header
    printf("+---+---+---+---+---+---+---+\n");
    printf("|Sun|Mon|Tue|Wed|Thu|Fri|Sat|\n");
    printf("+---+---+---+---+---+---+---+\n");

    // Calculate the day of the week for the first day of the month
    int firstDay = firstDayOfMonth(month, year);

    // Adjust the spacing for the first day
    int spacing = (firstDay + 6) % 7; // Add 6 to ensure positive result

    // Print leading spaces to align the first day properly
    for (int i = 0; i < spacing; i++)
    {
        printf("|   ");
    }

    // Initialize variables to keep track of the current day and week day
    int daysInMonth = monthDays[month - 1];
    int weekDay = spacing;

    // Loop through each day in the month
    for (int day = 1; day <= daysInMonth; day++)
    {
        // Print the day with proper formatting
        printf("|%3d", day);

        // Update the week day
        weekDay = (weekDay + 1) % week;

        // Move to the next line after Saturday and start a new row
        if (weekDay == 0)
        {
            printf("|\n");
            if (day < daysInMonth)
            {
                printf("+---+---+---+---+---+---+---+\n");
            }
        }
    }

    // Fill in any remaining cells with spaces
    while (weekDay != 0)
    {
        printf("|    ");
        weekDay = (weekDay + 1) % week;
    }

    // Close the grid
    printf("|\n");
    printf("+---+---+---+---+---+---+---+\n");
}

int firstDayOfMonth(int target_month, int target_year)
{
    int daysApart = numberOfDaysApart(target_year, target_month);

    // what day of the week the starting day is
    int firstDay = daysAfter(target_month, target_year);

    // daysApart + firstDay calculates the target day. modulo week (7) confines this value to a day in the week.
    return (daysApart + firstDay) % week;
}

int daysAfter(int month, int year)
{
    int K = year % 100, J = (year / 100);
    return ((1 + (13 * (month + 1) / 5) + K + (K / 4) + (J / 4) - 2 * J) % 7) + 1;
}

int isLeapYear(int year)
{
    // return true or false, depending on if leap year or not
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int numberOfLeapYears(int target_year)
{
    // # of days added due to leap years
    int leapDays = 0;
    // iterates over every year between start and target year checking for leap years
    for (int i = start_year; i < target_year + 1; i++)
    {
        // adds 1 day for every leap year
        if (isLeapYear(i))
        {
            leapDays++;
        }
    }
    return leapDays;
}

int numberOfDaysApart(int target_year, int target_month)
{
    // accounts for additional days due to leap years
    int leapDays = numberOfLeapYears(target_year);

    // the # of full years, in days, elapsed between start and target date
    int yearAhead = (target_year - start_year - 1) * 365 + leapDays;

    // calculates remaining days within starting year
    int daysLeftStart = 365 - totalDaysIntoYear(start_month, start_day, start_year); // subtracts remaining days in the year for the starting date

    // accounts for a potential leap year on start
    if (isLeapYear(start_year))
    {
        daysLeftStart--;
    }

    // calculates # of days into the target year
    int daysIntoCurrent = totalDaysIntoYear(target_month, 1, target_year); // day = 1 because it's the start of the month

    // returns total # of days elapsed between start and end date
    return yearAhead + daysIntoCurrent + daysLeftStart; // total # of days between entered month and starting date
}

int totalDaysIntoYear(int month, int day, int target_year)
{
    int numOfDays = 0;

    // adds values of each full month passed
    for (int i = 0; i < month - 1; i++)
    {
        numOfDays += monthDays[i];
    }

    // adds # of days into the current month
    numOfDays += day;

    // accounts for an additional day in February for a leap year
    if (month > 2 && isLeapYear(target_year))
    {
        numOfDays++;
    }

    return numOfDays;
}


/*

// Zeller's Congruence algorithm to determine the day of the week
int zeller(int month, int year) {
    int K = year % 100, J = (year / 100);
    return (1 + (13 * (month + 1) / 5) + K + (K / 4) + (J / 4) - 2 * J) % 7;
}

// Function to print the calendar for a given month and year
void printCalendar(int year, int month) {
    printf("\n");

    // Array of month names
    const char *monthNames[] = {"January", "February", "March", "April", "May", "June",
                                "July", "August", "September", "October", "November", "December"};

    // Print the month and year
    printf("    %s - %d\n", monthNames[month - 1], year);

    // Print the header for the days of the week
    printf("+---+---+---+---+---+---+---+\n");
    printf("|Sun|Mon|Tue|Wed|Thu|Fri|Sat|\n");
    printf("+---+---+---+---+---+---+---+\n");

    // Calculate the day of the week for the first day of the month
    int dayOfWeek = zeller(month, year);

    // Print leading spaces to align the first day properly
    for (int i = 0; i < dayOfWeek; i++) {
        printf("|   ");
    }

    // Initialize variables to keep track of the current day and week day
    int daysInMonth = getDaysInMonth(year, month);
    int weekDay = dayOfWeek;

    // Loop through each day in the month
    for (int day = 1; day <= daysInMonth; day++) {
        // Print the day with proper formatting
        printf("|%3d", day);

        // Update the week day
        weekDay = (weekDay + 1) % 7;

        // Move to the next line after Saturday and start a new row
        if (weekDay == 0) {
            printf("|\n");
            if (day < daysInMonth) {
                printf("+---+---+---+---+---+---+---+\n");
            }
        }
    }

    // Fill in any remaining cells with spaces
    while (weekDay != 0) {
        printf("|   ");
        weekDay = (weekDay + 1) % 7;
    }

    // Close the grid
    printf("|\n");
    printf("+---+---+---+---+---+---+---+\n");
}

// Main function
int main() {
    int year, month;

    // Prompt the user to enter the year (since October 15, 1582)
    printf("Enter the year (since 15 October 1582): ");
    while (scanf("%d", &year) != 1 || year < 1582) {
        // Handle invalid input
        printf("Invalid input. Please enter a valid year: ");
        while (getchar() != '\n');
    }

    // Prompt the user to enter the month or choose 'all' for the entire year
    printf("Enter the month (as an integer or word, 'all' for entire year): ");
    while (true) {
        if (scanf("%d", &month) == 1) {
            if (month >= 1 && month <= 12) {
                break;
            }
        } else {
            char input[10];
            scanf("%s", input);
            if (strcmp(input, "all") == 0) {
                // Print the calendar for the entire year and exit
                for (int i = 1; i <= 12; i++) {
                    printCalendar(year, i);
                }
                return 0;
            }
            // Handle invalid input
            printf("Invalid input. Please enter a valid month (as an integer or 'all'): ");
        }
        // Handle invalid input
        printf("Invalid input. Please enter a valid month (as an integer or 'all'): ");
        while (getchar() != '\n');
    }

    // Print the calendar for the specified month
    printCalendar(year, month);

    return 0;
}

*/
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


/*
 * #include <stdio.h>
 
 int zeller( int month, int year){
    int K = year % 100, J = (year / 100);
    return (1 + (13 * (month + 1) / 5) + K + (K / 4) + (J / 4) - 2 * J) % 7;
} //replaced day with 1 in the equation, so that we know what day of the week the month
  //will start with and go from there.

int main() {                        //Haven't actually tested the code out. Just something I wrote - Yaoxin
    int month, year;
    printf("Enter Month and Year: ");
    scanf("%d %d", &month, &year);
    int day_of_week = zeller(month, year);
    for (int i = 1; i <= 7; i++) {
        if (day_of_week == i)
        {
            
            break;
        }
        else printf(" ");
    }
    return 0;
} 

//Also messed around with arrays of structs
#include <stdio.h>       
#include <string.h>

struct months
{
    char monthName[50];
    int dayInMonth;
};

int main(void)
{
    struct months months[50];
    strcpy(months[3].monthName, "March");
    months[3].dayInMonth = 31;

    strcpy(months[4].monthName, "April");
    months[4].dayInMonth = 30;

    strcpy(months[5].monthName, "May");
    months[5].dayInMonth = 31; 
    
    strcpy(months[6].monthName, "June"); 
    months[6].dayInMonth = 30;

    strcpy(months[7].monthName, "July");
    months[7].dayInMonth = 31;

    strcpy(months[8].monthName, "August");
    months[7].dayInMonth = 31;

    strcpy(months[9].monthName, "September");
    months[7].dayInMonth = 30;
    
    strcpy(months[10].monthName, "October");
    months[7].dayInMonth = 31;

    strcpy(months[11].monthName, "November");
    months[11].dayInMonth = 30;

    strcpy(months[12].monthName, "December");
    months[12].dayInMonth = 31;

    strcpy(months[13].monthName, "January");
    months[13].dayInMonth = 31;

    strcpy(months[14].monthName, "February");
    months[14].dayInMonth = 28;
}
*/
