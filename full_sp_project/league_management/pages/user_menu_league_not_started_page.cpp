#pragma once
#include <iostream>
#include "structs.cpp"
#include "navigation.cpp"
#include "../authentication.h"



void viewUserMenuLeagueNotStarted(){
    cout << "League has not started yet.\n1.Logout\nPick choice: "; 
}


void userMenuLeagueNotStartedInput(){
    int choice;
    cin >> choice;
    if(choice == 1){
        log_out();
        while(!stck.empty()) stck.pop();
        stck.push(AUTHENTICATION_PAGE);
    }
    return;
}