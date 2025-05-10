#pragma once
#include <iostream>
#include "structs.cpp"
#include "navigation.cpp"
#include "../authentication.h"
#include "../supplementary/supplementary_functions.cpp"
#include "add_team_page.cpp"
#include "generate_schedule.cpp"


void viewAdminMenuLeagueNotStartedPage(){
    cout << "1.Logout\n2.Add Team\n3.Start League\nPick choice: ";
}

void adminMenuLeagueNotStartedInput(League &league){
    int choice;
    cin >> choice;
    if(choice == 1){
        // logout
        log_out();
        while(!stck.empty()) stck.pop();
        stck.push(AUTHENTICATION_PAGE);
    }
    else if(choice == 2){
        // add team
        AddTeam(league);
    }
    else if(choice == 3){
        // start league
        generateSchedule(league);
        stck.pop();
        stck.push(ADMIN_MENU_LEAGUE_STARTED);
    }
    return;
}



