#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define TRUE 1
#define FALSE 0
#define week 7              //days in a week
#define months_in_year 12   //months in a year
#define full_year 365       //days in a (non-leap) year
#define max_name 747        //based on the longest ever recorded name
#define char_lim 256        //character limit on inputted and updated event
#define date_and_time 17    //number of characters within the format of MM//DD/YYYY 00:00 (including spaces and '/')
#define max_event 50        //max number of event for one day

const int start_day = 15, start_month = 10, start_year = 1582;  //Calendar starts on October 15, 1582

const int monthDays[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; //Days in each month

const char* dayNames[] = {
    "Sunday", "Monday", "Tuesday", "Wednesday",
    "Thursday", "Friday", "Saturday"
};

const char* monthNames[] = {   
    "January", "February", "March", "April", "May", "June", "July",
    "August", "September", "October", "November", "December"
};

void clearInputBuffer();    //clears user input buffer

//Calendar Visuals functions
void calendarChoice();                  //where decision on type of calendar occurs (month or year)
                                        //finds events for specific month and year
void date_read(char relevantEvents[max_event][char_lim], char* fileName, int target_month, int target_day, int target_year);

void printAllCalendars(int year);       //prints calendar for the yar

//Event functions
int returnUser(const char* fileName);   //searches users disk for existing event file
int addEvent(char* fileName);           //creates user specific event file for event storage 
int modifyEvent(const char* fileName);  //changes saved event based on event date and time

//Calendar Logic functions
int zeller();
int isLeapYear(int year);
int numberOfLeapYears(int target_year);
int numberOfDaysApart(int target_year, int target_month);
int totalDaysIntoYear(int month, int day);
int firstDayOfMonth(int target_month, int target_year);

void date_read(char relevantEvents[max_event][char_lim], char* fileName, int target_month, int target_day, int target_year){
    int month, day, year;
    FILE* file;
    file = fopen(fileName, "r");
    int i = 0;

    char event[char_lim];

    while (fgets(event, char_lim, file) != NULL && i < max_event){
       if ((sscanf(event, "%d %d %d", &month, &day, &year)) != 1){
            clearInputBuffer();
            printf("Could not read event date");
            return;
        }

        if (month == target_month && year == target_year){
            strcpy(relevantEvents[i], event);
            i++;
        }
    }
    fclose(file);
}

//Done
int main() {
    char username[max_name];
    char txt[] = {".txt"};
    char* fileName;
    char choice;

    printf("Enter your name: ");
    scanf("%s", username);
    clearInputBuffer();

    fileName = malloc(sizeof(char) * (strlen(username) + strlen(txt) + 1)); // + 1 for '\0'
    if (fileName == NULL){
        printf("failed to make pointer");
        return -1;
    }
    strcpy(fileName, username);
    strcat(fileName, txt);  // = "username.txt"

    if (returnUser(fileName)){
        printf("Would you like to add or make changes to your event (Y or N): ");
        scanf(" %c", &choice);
        clearInputBuffer();

        if (toupper(choice) == 'Y'){
            printf("Add event or change event (A or C)");
            scanf(" %c", &choice);
            clearInputBuffer();

                if (toupper(choice) == 'A'){
                    addEvent(fileName);
                }
                else if (toupper(choice) == 'C'){
                    modifyEvent(fileName);
                }
        }
        else if (toupper(choice) == 'N'){
            printf("Ok\n");
        }
    }
    else{
        addEvent(fileName);
    }
    calendarChoice();

    free(fileName);
    return 0;
}

//Done
void clearInputBuffer(){
    char c;
    while ((c = getchar()) != '\n' && c != EOF);
}

//Done
int returnUser(const char* fileName){
    FILE* file;
    file = fopen(fileName, "r");
    if (file != NULL){
        printf("Welcome back: %.*s! You have saved event \n",strlen(fileName) - 4, fileName); //prints only the user name (4  = .txt)
        fclose(file);
        return TRUE;
    }
    else{ 
        printf("Welcome new user: %.*s! You have no saved event \n", strlen(fileName) - 4, fileName);
        return FALSE;
    }
}

//Done
void calendarChoice(){
    int year, month;
    char user_input[4]; // 4 = 'all' + '\0'

    printf("Enter year: ");
    if ((scanf("%d", &year)) != 1){
        clearInputBuffer();
        printf("Failed to scan year");
        return;
    }
    clearInputBuffer();

    if (year == 1582){
        printf("Calendar does not support year calendars on %d and month calendars on or before October (10) ", 1582);
        printf("Either 11 or 12, Enter a month: ");
        if ((scanf("%d", &month)) != 1){
            clearInputBuffer();
            printf("Failed to scan month\n");
        }
        clearInputBuffer();

        if (month < 0 || month > 12) {
            printf("Invalid input. Either 11 or 12\n");
            return;
        }
        printCalendar(year, month);
    }
    else if (year < 1582){
        printf("Year calendar does not support years before %d", 1582);
        return;
    }
    else{
        printf("Enter month ('all' or 1-12): ");
        if((scanf("%3s", user_input)) != 1){
            clearInputBuffer();
            printf("Failed to scan user input\n");
        }
        clearInputBuffer();

        if (strcmp(user_input, "all") == 0) {
            printAllCalendars(year);
        }
        else {
            if ((sscanf(user_input, "%d", &month)) != 1){   //for cases where a string besides 'all' is inputted
                clearInputBuffer();
                printf("Invalid input. Enter 1 - 12 or 'all'.\n");
                return;
            }
            printCalendar(year, month);
        }
    }
}

void printAllCalendars(int year) {
  if (year == 1582) {
        // Print only months 10 through 12
        printf("Invalid input please input a month past October 1582\n");
        for (int month = 11; month <= months_in_year; month++) {
        printf("\n");
    }
  } else {
    // Print all months for other years
    for (int month = 1; month <= months_in_year; month++) {
      printCalendar(year, month);
      printf("\n");
    }
  }
}

//Done
int addEvent(char* fileName){
    char input, event[char_lim];

    FILE* ptr;
    ptr = fopen(fileName, "a");

    if (ptr == NULL){
        perror("Error opening the file");
        return -1;
    }
    do{
        printf("Do you want to add an event (enter Y for yes and N for No): ");
        input = getchar();

        clearInputBuffer();

        if (toupper(input) == 'Y'){
            printf("Input the date (MM/DD/YYYY), the time, following a 24-hour clock (00:00), of the event and the event (all separated by space): \n");
            printf("Example: 12/34/5678 23:59 'Lorem Ipsum' \n");

            fgets(event, sizeof(event), stdin);
            clearInputBuffer();

            if (fprintf(ptr, "%s\n", event) < 0) { //if no lines printed onto file, quit
                perror("Error writing to the file\n");
                fclose(ptr);
                return 1;
            }

            if (fflush(ptr) != 0) { //ensures event is printed onto file, quits if fails
                perror("Error flushing the file\n");
                fclose(ptr);
                return 1;
            }
        }
        else if (toupper(input) == 'N'){
            printf("Ok\n");
        }
        else{
            printf("Invalid input. Y or N\n");
        }
    }
    while (toupper(input) != 'N');
    fclose(ptr);
    return 0;
}

//Done
int modifyEvent(const char* fileName){
    FILE* ptr;
    char lineEdit[date_and_time], event[char_lim];
    ptr = fopen(fileName, "r+");
    if (ptr == NULL){
        perror("Error opening the file\n");
        return 1;
    }

    printf("Input the date (MM/DD/YYYY), the time, following a 24-hour clock (00:00), of the event being changed (separated by a space):\n");
    printf("And press enter twice: once to save and one extra time to submit\n");

    fgets(lineEdit, sizeof(lineEdit), stdin);
    clearInputBuffer();
    
    while (fgets(event, sizeof(event), ptr) != NULL){  //Keeps scanning until EOF reached
            if (strncmp(event, lineEdit, strlen(lineEdit)) == 0){
                printf("Enter the new event: ");
                fgets(lineEdit, sizeof(char) * char_lim, stdin);
                clearInputBuffer();

                fseek(ptr, -strlen(event), SEEK_CUR);

                if (fprintf(ptr, "%s\n", lineEdit) < 0) {
                perror("Error writing to the file\n");
                fclose(ptr);
                return 1;
                }

            if (fflush(ptr) != 0) {
                perror("Error flushing the file\n");
                fclose(ptr);
                return 1;
                }
        
                printf("edited successfully.\n");
                break;
            }
        }
    fclose(ptr);
    return 0;
}


/* Calendar Logic Portion */

//Done
int firstDayOfMonth(int target_month, int target_year){
    int daysApart = numberOfDaysApart(target_year, target_month);
    
    //what day of the week the starting day is
    int firstDay = zeller();

    // daysApart + firstDay calculates the target day. modulo week (7) confines this value to a day in the week.
    return (daysApart + firstDay) % week; 
}

//Done
int zeller(){
    // K = last two year digits, J = first two year digits
    int K = start_year % 100, J = (start_year / 100);

    //returns a value between 0-6 -> 0 = Saturday, 1 = Sunday ...
    int zellerDay = (start_day + (13 * (start_month + 1) / 5) + K + (K / 4) + (J / 4) - 2 * J) % week;

    //adjusts zeller values to traditional calendar values sunday = 0, monday = 1, ...
    return (zellerDay + 6 + week) % 7; // + week ensures return is positive
}

//Done
int isLeapYear(int year){
    //return true or false, depending on if leap year or not
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

//Done
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

//Done
int numberOfDaysApart(int target_year, int target_month){
    //accounts for additional days due to leap years
    int leapDays = numberOfLeapYears(target_year);
    
    //the # of full years, in days, elapsed between start and target date
    int yearAhead = (target_year - start_year - 1) * full_year;
    
    //accounts for if target year = 1582
    if (yearAhead < 0){
        yearAhead = 0;
    }
    
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

    //returns total # of days elapsed between start and end date
    return yearAhead + leapDays + daysIntoCurrent + daysLeftStart;  //total # of days between entered month and starting date
}

//Done
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
