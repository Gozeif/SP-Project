#pragma once
#include <iostream>
#include "structs.cpp"
#include "navigation.cpp"
#include "../authentication.h"



void viewLoginPage(League& league){
    log_in();
    stck.pop();
    if(current_user_info.admin){
        if(league.started){
            stck.push(ADMIN_MENU_LEAGUE_STARTED);
        }
        else{

            stck.push(ADMIN_MENU_LEAGUE_NOT_STARTED);
            // showAdminMenuLeagueNotStarted();
            // cin >> choice;
    
        }
    }
    else{
        if(league.started){
            stck.push(USER_MENU_LEAGUE_STARTED);
        }
        else{
            stck.push(USER_MENU_LEAGUE_NOT_STARTED);
        }
    }
}