#include <stdio.h>

int zeller(int day, int month, int year);

int main(){
    int day, month, year;

    printf("%d", zeller(5, 12, 2023));
    return 0;
}

int zeller(int day, int month, int year){
    int K = year % 100, J = (year / 100);
    return (day + (13 * (month + 1) / 5) + K + (K / 4) + (J / 4) - 2 * J) % 7;
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
