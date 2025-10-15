#include <stdio.h>
#include <locale.h>

enum month {January, February, March, April, May, June, July, August, September, October, November, December};

int leap_year(int year){
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)){
        return 1;
    } else {
        return 0;
    }
}

int mount_day(int year, enum month m){
    switch (m)
    {
    case January: case March: case May: case July: case August: case October: case December:
        return 31;
    case April : case June: case September: case November:
        return 30;
    case February:
        if (leap_year(year) == 1){
            return 29;
        }
        return 28;
    default:
        return 0;
    }
}

int answer(int day, int mounth, int year){
    enum month current_month = (enum month)(mounth - 1);
    int m_day = mount_day(year, current_month);
    
    if ((day == 31) && (mounth == 12)){
        printf("%d.%d.%d",1,1,year+1);
        return 1; 
    }
    if (m_day == day){
        printf("%d.%d.%d",1,mounth+1,year);
        return 1;
    }
    printf("%d.%d.%d",day+1,mounth,year);
    return 1;
}

int main(){
    setlocale(LC_ALL, "Rus");
    int day, mounth, year;
    printf("Введите день: ");
    scanf_s("%d", &day);
    printf("Введите месяц: ");
    scanf_s("%d", &mounth);
    printf("Введите год: ");
    scanf_s("%d", &year);
    answer(day, mounth, year);
}