#include <stdio.h>

enum days {Saturday, Sunday, Monday, Tuesday, Wednesday, Thursday, Friday};

int zeller(int day, int month, int year);
int isLeapYear(int year);
int numOfLeap(int, int);

int main(){
    int day, month, year;

    printf("%d", zeller(5, 12, 2023));
    return 0;
}

int zeller(int day, int month, int year){
    int K = year % 100, J = (year / 100);
    if (month < 3){     //in zeller jan = 13 and feb = 14 -> it is the end of the previous year
        month += 12;
        year--;
    }
    return (day + (13 * (month + 1) / 5) + K + (K / 4) + (J / 4) - 2 * J) % 7;  //return 0-6 signifying the day of the week
}

int isLeapYear(int year){
    return ((year % 4 && year % 100) != 0) || ((year % 400) == 0);
}

int numOfLeap(int start_year, int end_year){
    int leapDays = 0;   //num of days added due to leap year
    for (int i = 0, diff_year = end_year - start_year; i < diff_year + 1; i++){     //adds a year from start year until end year and finds # of leap years in between
        if (isLeapYear(start_year + i)){
            leapDays++;
        }
    }
    return leapDays;
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
