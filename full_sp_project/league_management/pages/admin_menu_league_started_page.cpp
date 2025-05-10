#pragma once
#include <iostream>
#include "structs.cpp"
#include "navigation.cpp"


void viewAdminMenuLeagueStartedPage(){                                                         //11
    cout << "1.Logout\n2.Add Match Result\n3.View last 10 results\n4.View Teams\n5.View Next 10 matches\n6.View Table\nPick choice: ";
}

void adminMenuLeagueStartedInput(League &league){
    int choice;
    cin >> choice;
    if(choice == 1){
        log_out();
        while(!stck.empty()) stck.pop();
        stck.push(AUTHENTICATION_PAGE);
    }
    else if(choice == 2){
        addMatchResult(league);
    }
    else if(choice == 3){
        stck.push(VIEW_LAST_10_RESULTS);
    }
    else if(choice == 4){
        stck.push(VIEW_TEAMS);
    }
    else if(choice == 5){
        stck.push(VIEW_SCHEDULE);
    }
    else if(choice == 6){
        stck.push(VIEW_TABLE);
    }
    return;
}

