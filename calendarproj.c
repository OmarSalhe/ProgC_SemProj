#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// Function to check if a year is a leap year
bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

// Function to get the number of days in a month
int getDaysInMonth(int year, int month) {
    int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Adjust February for leap years
    if (month == 2 && isLeapYear(year)) {
        return 29;
    } else {
        return daysInMonth[month];
    }
}

// Function to get the day of the week for a given date
int getDayOfWeek(int year, int month, int day) {
    if (month < 3) {
        month += 12;
        year--;
    }

    int k = year % 100;
    int j = year / 100;

    int dayOfWeek = (day + 13 * (month + 1) / 5 + k + k / 4 + j / 4 + 5 * j) % 7;

    return (dayOfWeek + 5) % 7; // Adjust for the known day of October 15, 1582 (Friday)
}

// Function to print a calendar for a given month and year
void printCalendar(int year, int month) {
    printf("\n");

    // Print the month and year
    printf("    %d - %d\n", month, year);

    // Print the days of the week
    printf("Sat Sun Mon Tues Wed Thu Fri \n");

    // Get the day of the week for the first day of the month
    int dayOfWeek = getDayOfWeek(year, month, 1);

    // Print leading spaces to align the first day properly
    for (int i = 0; i < dayOfWeek; i++) {
        printf("    ");
    }

    // Print the dates of the month
    int daysInMonth = getDaysInMonth(year, month);
    for (int day = 1; day <= daysInMonth; day++) {
        printf("%3d ", day);

        // Move to the next line after Saturday
        if ((dayOfWeek + day) % 7 == 0) {
            printf("\n");
        }
    }

    printf("\n");
}

int main() {
    int year, month;

    // Get input for year
    printf("Enter the year (since 15 October 1582): ");
    while (scanf("%d", &year) != 1 || year < 1582) {
        printf("Invalid input. Please enter a valid year: ");
        while (getchar() != '\n'); // Clear input buffer
    }

    // Get input for month
    printf("Enter the month (as an integer or word, 'all' for entire year): ");
    while (true) {
        if (scanf("%d", &month) == 1) {
            if (month >= 1 && month <= 12) {
                break; // Valid numeric input
            }
        } else {
            char input[10];
            scanf("%s", input);
            if (strcmp(input, "all") == 0) {
                // Print calendar for the entire year
                for (int i = 1; i <= 12; i++) {
                    printCalendar(year, i);
                }
                return 0;
            }
            printf("Invalid input. Please enter a valid month (as an integer or 'all'): ");
        }
        printf("Invalid input. Please enter a valid month (as an integer or 'all'): ");
        while (getchar() != '\n'); // Clear input buffer
    }

    // Print the calendar for the specified month and year
    printCalendar(year, month);

    return 0;
}


/*
#include <stdio.h>

#define week 7
#define num_of_months 12
#define days_in_year 365

int dayMonthStarts(int start_day, int start_month, int start_year);
int zeller(int start_day, int start_month, int start_year);
int isLeapYear(int year);
int numOfLeap(int start_year, int end_year);
int numOfDaysApart(int start_day, int start_month, int start_year, int end_year, int end_month);
int daysIntoYear(int month, int day);
int firstDayOfMonth(int start_day, int start_month, int start_year, int end_month, int end_year);

const int monthDays[num_of_months] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int main(){
    return 0;
}

int firstDayOfMonth(int start_day, int start_month, int start_year, int end_month, int end_year){
    int daysApart = numOfDaysApart(start_day, start_month, start_year, end_year, end_month);
    int startDay = zeller(start_day, start_month, start_year);

    // daysApart + startDay calculates the target day. modulo week (7) confines this value to a day in the week.
    return (daysApart + startDay) % week; 
}


int zeller(int start_day, int start_month, int start_year){
    int K = start_year % 100, J = (start_year / 100);
    //zeller's congruence considers Jan and Feb the last two months starting from March = 3
    if (start_month < 3){
        start_month += 12;
        start_year--;
    }
    //returns a value between 0-6 -> 0 = Saturday, 1 = Sunday ...
    return (start_day + (13 * (start_month + 1) / 5) + K + (K / 4) + (J / 4) - 2 * J) % week;
}

int isLeapYear(int year){
    //return true or false, depending on if leap year or not
    return ((year % 4 && year % 100) != 0) || ((year % 400) == 0);
}

int numOfLeap(int start_year, int end_year){
    //# of days added due to a leap year
    int leapDays = 0;
    //iterates over every year between start and target year checking for leap years
    for (int i = 0, diff_year = end_year - start_year; i < diff_year + 1; i++){ 
        //adds 1 day for every leap year
        if (isLeapYear(start_year + i)){
            leapDays++;
        }
    }
    return leapDays;
}

int numOfDaysApart(int start_day, int start_month, int start_year, int end_year, int end_month){
    //accounts for additional days due to leap years
    int leapDays = numOfLeap(start_year, end_year);
    //# of full years elapsed between start and target date
    int yearAhead = (end_year - start_year - 1) * days_in_year;
    //calculates remaining days withiin starting year
    int daysLeftStart = days_in_year - daysIntoYear(start_month, start_day);    //subtracts remaining days in the year for the starting date
    //accounts for potential leap year on start
    if (isLeapYear(start_year)){ 
        daysLeftStart--;
    }
    //calculates # of days into target year
    int daysIntoCurrent = daysIntoYear(end_month, 0); //day = 0 b/c start of month

    //returns total # of days elapesed between start and end date
    return yearAhead + leapDays + daysIntoCurrent - daysLeftStart;  //total # of days between entered month and starting date
}

int daysIntoYear(int month, int day){
    int numOfDays = 0;
    //adds values of each full month passed 
    for (int i = 0; i < month; i++){ 
        numOfDays += monthDays[i];
    }
    //adds # of days into current month
    numOfDays += day;

    return numOfDays;
}
*/
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
