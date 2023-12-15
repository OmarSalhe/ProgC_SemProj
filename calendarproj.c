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
    "Sun", "Mon", "Tue", "Wed",
    "Thu", "Fri", "Sat"
};

const char* monthNames[] = {   
    "January", "February", "March", "April", "May", "June", "July",
    "August", "September", "October", "November", "December"
};

void clearInputBuffer();    //clears user input buffer

//Calendar Visuals functions
void calendarChoice(char* fileName);                  //where decision on type of calendar occurs (month or year)
                                        //finds events for specific month and year
void date_read(char relevantEvents[max_event][char_lim], char* fileName, int target_month, int target_year);
void printCalendar(int year, int month);
void printAllCalendars(int year);
void printEvents(char relevantEvents[max_event][char_lim], int numEvents);

//Event functions
int returnUser(char* fileName);   //searches users disk for existing event file
int addEvent(char* fileName);           //creates user specific event file for event storage 
int modifyEvent(char* fileName);  //changes saved event based on event date and time
int deleteEvent(char* fileName);

//Calendar Logic functions
int zeller();                           //finds day of week October 15, 1582 is 
int isLeapYear(int year); 
int numberOfLeapYears(int target_year);
int numberOfDaysApart(int target_year, int target_month);
int totalDaysIntoYear(int month, int day);
int firstDayOfMonth(int target_month, int target_year);

//Done
int main(){
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
    calendarChoice(fileName);

    free(fileName);
    return 0;
}

void clearInputBuffer(){
    char c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/*  Calendar Visual */

void date_read(char relevantEvents[max_event][char_lim], char* fileName, int target_month, int target_year){
    int month, day, year;
    FILE* file;
    file = fopen(fileName, "r");
    int i = 0;

    char event[char_lim];

    while (fgets(event, char_lim, file) != NULL && i < max_event){
        sscanf(event, "%d/%d/%d", &month, &day, &year);

        if (month == target_month && year == target_year){
            strcpy(relevantEvents[i], event);
            i++;
        }
    }
    fclose(file);

    printEvents(relevantEvents, i);
}

void calendarChoice(char* fileName){
    int year, month;
    char user_input[4]; // 4 = 'all' + '\0'
    char relevantEvents[max_event][char_lim];

    printf("Enter year: ");
    if ((scanf("%d", &year)) != 1){
        clearInputBuffer();
        printf("Failed to scan year");
        return;
    }
    clearInputBuffer();

    if (year == start_year){
        printf("Calendar does not support year calendars on %d and month calendars on or before October (10)", start_year);
        printf("Either 11 or 12, Enter a month: ");
        if ((scanf("%d", &month)) != 1){
            clearInputBuffer();
            printf("Failed to scan month\n");
        }
        clearInputBuffer();

        if (month == 11 || month == 12) {
            printCalendar(year, month);
            return;
    
        }
        else{
            printf("Invalid input. Either 11 or 12\n");
            return;
        }
    }
    else if (year < 1582){
        printf("Calendar does not support years before %d", start_year);
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
            date_read(relevantEvents, fileName, month, year);
        }
    }
}

void printCalendar(int year, int month) {
  printf("Calendar for %s %d:\n", monthNames[month - 1], year);

  // Print the top grid line
  for (int i = 0; i < week; i++) {
    printf("+---");
  }
  printf("+\n");

  // Print day names
  for (int i = 0; i < week; i++) {
    printf("|%s", dayNames[i]);
  }
  printf("|\n");

  // Print the middle grid line
  for (int i = 0; i < week; i++) {
    printf("+---");
  }
  printf("+\n");

  // Calculate the first day of the month
  int firstDay = firstDayOfMonth(month, year);

  // Print leading spaces
  for (int i = 0; i < firstDay; i++) {
    printf("|   ");
  }

  // Print the days of the month
  int daysInMonth = monthDays[month - 1];
    for (int day = 0; day < daysInMonth; day++) {
        printf("|%3d", day + 1);
        if ((firstDay + 1 + day) % week == 0) {
        printf("|\n");

        // Print the grid line after each week
        for (int i = 0; i < week; i++) {
            printf("+---");
        }
        printf("+\n");
        }
    }

    // If the last day of the month is not the end of the week, print the
    // remaining spaces
    if ((firstDay + daysInMonth) % week != 0) {
        for (int i = (firstDay + daysInMonth) % week; i < week; i++) {
            printf("|   ");
        }
        printf("|\n");

        // Print the bottom grid line
        for (int i = (firstDay + daysInMonth) % week; i < week; i++) {
      
        }
        printf("+---+---+---+---+---+---+---+\n");
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

void printEvents(char relevantEvents[max_event][char_lim], int numEvents) {
    
    printf("\nEvents for the selected month:\n");
    for (int i = 0; i < numEvents; ++i) {
    printf("%s\n", relevantEvents[i]);
    }
}

/* Event Making */

int returnUser(char* fileName){
    FILE* file;
    file = fopen(fileName, "r");
    if (file != NULL){
        printf("Welcome back: %.*s! You have saved event \n", (int)strlen(fileName) - 4, fileName); //prints only the user name (4  = .txt)
        fclose(file);
        return TRUE;
    }
    else{ 
        printf("Welcome new user: %.*s! You have no saved event \n", (int)strlen(fileName) - 4, fileName);
        return FALSE;
    }
}

int modifyEvent(char* fileName){
    FILE* ptr;
    char eventdate[date_and_time], event[char_lim], lineEdit[char_lim], input, quit[5]; //quit is 4 letters plus '/0'
    ptr = fopen(fileName, "r+");
    if (ptr == NULL){
        perror("Error opening the file\n");
        return 1;
    }
        
    do {
        printf("Input the date (MM/DD/YYYY), the time, following a 24-hour clock (00:00), of the event being changed (separated by a space):\n");
        fgets(eventdate, sizeof(eventdate), stdin);
        clearInputBuffer();
    
        while (fgets(event, sizeof(event), ptr) != NULL){  //Keeps scanning until EOF reached
            if (strncmp(event, eventdate, strlen(eventdate)) == 0){
                printf("Enter the new events date, time, and description/title: ");
                fgets(lineEdit, sizeof(char) * char_lim, stdin);
                clearInputBuffer();

                fseek(ptr, -strlen(event), SEEK_CUR);

                fprintf(ptr, "%s", lineEdit);
                fflush(ptr);

                printf("edited successfully.\n");

                fseek(ptr, 0, SEEK_SET);
                break;
            }
        }
        printf("To quit enter 'quit' ");
        scanf("%4s", quit);
        clearInputBuffer();

        if (strcasecmp(quit, "quit") == 0){
            break;
        }
    }
    while(TRUE);
  
    fclose(ptr);

    printf("Would you like to add or delete any events (A or D) or quit (anything else)");
    scanf(" %c", &input);
    clearInputBuffer();

    if (toupper(input) == 'A'){
        addEvent(fileName);
    }
    else if (toupper(input) == 'D'){
        deleteEvent(fileName);
    }
    return 0;
}

int addEvent(char* fileName){
    char input, event[char_lim], quit[5];

    FILE* ptr;
    ptr = fopen(fileName, "a");

    if (ptr == NULL){
        perror("Error opening the file");
        return -1;
    }
    do{
        printf("Input the date (MM/DD/YYYY), the time, following a 24-hour clock (00:00), of the event and the event (all separated by space): \n");
        printf("Example: 12/34/5678 23:59 'Lorem Ipsum' \n");
        fgets(event, sizeof(event), stdin);
        clearInputBuffer();

        if ((fprintf(ptr, "%s", event)) > 0){   //
            fflush(ptr);
            printf("Sucessfully added\n");
        }

        printf("To quit enter 'quit' ");
        scanf("%4s", quit);
        clearInputBuffer();

        if (strcasecmp(quit, "quit") == 0)
            break;
    }
    while (TRUE);

    fclose(ptr);

    printf("Would you like to edit or delete any events (E or D) or quit (anything else)\n");
    scanf(" %c", &input);
    clearInputBuffer();

    if (toupper(input) == 'E' ){
        modifyEvent(fileName);
    }
    else if (toupper(input) == 'D' ){
        deleteEvent(fileName);
    }

    return 0;
}

int deleteEvent(char* fileName){
    char lineDelete[date_and_time], line[char_lim], filler[char_lim], decision, quit[5];
    int found = 0;
    FILE* ptr;
    FILE* tmp;

    ptr = fopen(fileName, "r");
    tmp = fopen("tmp.txt", "w");

    if (ptr == NULL || tmp == NULL){
        perror("Error opening the file\n");
        return 1;
    }

    do {
        printf("Input the date (MM/DD/YYYY), the time, following a 24-hour clock (00:00), of the event being deleted (separated by a space): ");
        fgets(lineDelete, sizeof(lineDelete), stdin);
        clearInputBuffer();
        while (fgets(line, sizeof(line), ptr) != NULL) {
            if (strncmp(line, lineDelete, strlen(lineDelete)) == 0){
                found = 1;
                printf("Event found and deleted successfully.\n");
            }
            else {
                fprintf(tmp, "%s", line);
            }
        }

        if (!found){
            printf("Event not found\n");
        }
        fseek(ptr, 0, SEEK_SET);

        printf("Enter 'quit' to quit: ");
        scanf("%4s", quit);
        clearInputBuffer();

        if (strcasecmp(quit, "quit") == 0){
            break;
        }
    }
    while (TRUE);

    fclose(ptr);
    fclose(tmp);

    remove(fileName);
    rename("tmp.txt", fileName);

    printf("Would you like to edit or add any events (E or A) or quit (anything else)\n");
    scanf(" %c", &decision);
    clearInputBuffer();

    if (toupper(decision) == 'E' ){
        modifyEvent(fileName);
    }
    else if (toupper(decision) == 'A' ){
        deleteEvent(fileName);
    }

    return 0;
}

/* Calendar Logic Portion */

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
