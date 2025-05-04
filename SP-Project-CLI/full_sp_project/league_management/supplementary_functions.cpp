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

    int maxday = daysInMonth(month);

    if (day > maxday || day < 1)
    {
        return {-1,-1,-1};
    }
    if (month > 12 || month < 1)
    {
        return {-1,-1,-1};
    }
    if (year > 2025 || year < 0)
    {
        return {-1,-1,-1};
    }
    

    return Date{
        day,
        month,
        year,
    };
}

string dateToString(Date date){
    string res = "";
    string day = to_string(date.day);
    string month = to_string(date.month);
    string year = to_string(date.year);
    if(day.size() == 1) day.insert(day.begin(), '0');
    if(month.size() == 1) month.insert(month.begin(), '0');
    res = day + '/' + month + '/' + year;
    return res;
}


Date getNextWeek(Date date){
    date.day += 7;
    if(date.day > daysInMonth(date.month)){
        date.day -= daysInMonth(date.month);
        date.month++;
        if(date.month > 12){
            date.month -= 12;
            date.year++;
        }
    }
    return date;
}

bool cmp(TableRecord Record1, TableRecord Record2)
{
	return (Record1.points > Record2.points);
}
