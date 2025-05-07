#pragma once
#include <iostream>
#include "structs.cpp"
#include "navigation.cpp"
#include "../authentication.h"


void viewUserMenuLeagueStarted(){
    cout << "1.Logout\n2.View Last 10 results\n3.View Teams\n4.View Next 10 matches\n5.View Table\nPick choice: ";
}


void userMenuLeagueStartedInput(){
    int choice;
    cin >> choice;
    if(choice == 1){
        log_out();
        while(!stck.empty()) stck.pop();
        stck.push(AUTHENTICATION_PAGE);
    }
    else if(choice == 2){
        stck.push(VIEW_LAST_10_RESULTS);
    }
    else if(choice == 3){
        stck.push(VIEW_TEAMS);
    }
    else if(choice == 4){
        stck.push(VIEW_SCHEDULE);
    }
    else if(choice == 5){
        stck.push(VIEW_TABLE);
    }
}