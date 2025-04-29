#include <iostream>
#include <stack>
#include "authentication.h"
#include "league_management/data_pulling_logic.h"
#include "league_management/structs_and_functions.h"
#include "league_management/data_pushing_logic.h"
using namespace std;


League league;




enum Page {
    AUTHENTICATION_PAGE,
    LOGIN_PAGE,
    SIGNUP_PAGE,
    ADMIN_MENU_LEAGUE_NOT_STARTED,
    ADMIN_MENU_LEAGUE_STARTED,
    MAIN_MENU,
    EXIT
};

stack<Page> stck;


void showAuthenticationPage(){
    cout << "1.Login\n2.Signup\n3.Exit\nPick choice: ";
    
}

void showAdminMenuLeagueStarted(){
    cout << "1.Logout\n Pick choice: ";
}

void showAdminMenuLeagueNotStarted(){
    cout << "1.Logout\n2.Add Team\n3.Start League\n";
}


void getInput(Page page){
    int choice;
    switch (page)
    {
    case AUTHENTICATION_PAGE:
        cin >> choice;
        // cout << "DDDUDUDUDU" << endl;
        if(choice == 1){
            // cout << "HERE" << endl;
            stck.push(LOGIN_PAGE);
        }
        else if(choice == 2){
            stck.push(SIGNUP_PAGE);
        }
        else if(choice == 3){
            stck.push(EXIT);
        }
        break;
    case LOGIN_PAGE:
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
            //
        }
        break;
    case ADMIN_MENU_LEAGUE_NOT_STARTED:
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
        break;
    case ADMIN_MENU_LEAGUE_STARTED:
        cin >> choice;
        if(choice == 1){
            log_out();
            while(!stck.empty()) stck.pop();
            stck.push(AUTHENTICATION_PAGE);
        }
        break;
    default:
        break;
    }
}


void display(Page page){
    switch (page)
    {
    case AUTHENTICATION_PAGE:
        showAuthenticationPage();
        break;
    case ADMIN_MENU_LEAGUE_NOT_STARTED:
        showAdminMenuLeagueNotStarted();
        break;
    case ADMIN_MENU_LEAGUE_STARTED:
        showAdminMenuLeagueStarted();
    default:
        break;
    }
}


int main(){
    // loading data initially

    load_user_db();
    pullTeamsCount(league.teamsCount);
    pullTeams(league);
    pullHasStarted(league);
    
    stck.push(AUTHENTICATION_PAGE);
    while(!stck.empty() && !(stck.top() == EXIT)){
        Page currentPage=stck.top();


        display(currentPage);
        getInput(currentPage);
        // showAuthenticationPage();



    }
    
    
    
    save();
    pushTeamsCount(league.teamsCount);
    pushTeams(league);
    pushMatches(league);
    pushHasStarted(league);
    
}