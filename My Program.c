#include <stdio.h>
int main(){
    int totalDays, years, months, days;
    printf("Enter total days: ");
    scanf("%d", &totalDays);
    years = totalDays / 365;
    totalDays = totalDays % 365;
    months = totalDays / 30;
    days = totalDays % 30;
    printf("Years = %d\n", years);
    printf("Months = %d\n", months);
    printf("Days = %d\n", days);
    return 0;
}
