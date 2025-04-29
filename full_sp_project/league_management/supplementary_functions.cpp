#pragma once
#include<string>


// Function to get max days in a month
int daysInMonth(int month) 
{
    switch(month) 
    {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            return 31;

        case 4: case 6: case 9: case 11:
            return 30;

        case 2:
            return 28;

        default:
            return 0;
    }
}


Date stringToDate(string s){
    int day = stoi(s.substr(0, 2));
    int month = stoi(s.substr(3, 2));
    int year = stoi(s.substr(6, 4));

    return Date{
        day,
        month,
        year,
    };
}


