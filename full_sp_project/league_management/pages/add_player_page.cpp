#pragma once
#include "structs.cpp"
#include <iostream>
#include "../supplementary/supplementary_functions.cpp"



Player AddPlayer(int& curPlayersCount){

    Player pl;
	// cout << "Player ID : " ;
	// cin >> pl.id ;
    cin.ignore() ;
    pl.id = curPlayersCount++;
	
    while(pl.name.empty()){
        cout << "Player Name : " ;
        getline(cin , pl.name) ; // to get spaces as a char and not end the input when encountering a space 

    }

	cout << "Player date of birth : \n" ;

	do 
    {
        cout << "Year --> ";
        cin >> pl.birthDate.year;

    } while(pl.birthDate.year < 0 || pl.birthDate.year > 2010); // to ensure that the user enters a valid year and apropiate age to player
	
    do 
    {
        cout << "Month --> ";
        cin >> pl.birthDate.month;

    } while(pl.birthDate.month < 1 || pl.birthDate.month > 12); // to ensure that the user enters a valid month 
	
    int maxDay = daysInMonth(pl.birthDate.month); // get the maximum days in a certain month
    do 
    {
        cout << "Day --> ";
        cin >> pl.birthDate.day;

    } while(pl.birthDate.day < 1 || pl.birthDate.day > maxDay); // to ensure that the user enters a valid day depending on the month

    cin.ignore() ;

    while(pl.nationality.empty()){
        cout << "Player Nationality : " ;
        getline(cin , pl.nationality) ;
    }
	


    return pl;


}