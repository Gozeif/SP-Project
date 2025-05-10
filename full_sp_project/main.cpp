
#include <iostream>
#include <stack>
#include "league_management/pages/view_match_statistics_page.cpp"

#include "league_management/pages/user_menu_league_started_page.cpp"
#include "league_management/pages/user_menu_league_not_started_page.cpp"
#include "league_management/pages/add_match_result_page.cpp"
#include "league_management/pages/authentication_page.cpp"
#include "league_management/pages/admin_menu_league_started_page.cpp"
#include "league_management/pages/login_page.cpp"
#include "league_management/pages/admin_menu_league_not_started_page.cpp"
#include "league_management/pages/view_table_page.cpp"
#include "league_management/pages/view_team_page.cpp"
#include "league_management/pages/view_teams_page.cpp"
#include "league_management/pages/view_player_info_page.cpp"
#include "league_management/pages/view_schedule_page.cpp"
#include "league_management/io/data_pulling_logic.h"
#include "league_management/io/data_pushing_logic.h"

using namespace std;

League league;






void getInput(Page page){
    switch (page)
    {
    case VIEW_MATCH_STATISTICS:
        viewMatchStatisticsPage(league);
        break;
    case VIEW_TABLE:
        viewTableInput();
        break;
    case VIEW_SCHEDULE:
        viewScheduleInput();
        break;
    case VIEW_TEAM_INFO:
        viewTeamPage(league);
        break;
    case VIEW_TEAMS:
        viewTeamsInput();
        break;
    case VIEW_LAST_10_RESULTS:
        viewLast10ResultsInput();
        break;
    case USER_MENU_LEAGUE_NOT_STARTED:
        userMenuLeagueNotStartedInput();
        break;
    case USER_MENU_LEAGUE_STARTED:
        userMenuLeagueStartedInput();
        break;  
    case AUTHENTICATION_PAGE:
        authenticationPageInput();
        break;
    case LOGIN_PAGE:
        viewLoginPage(league);
        break;
    case ADMIN_MENU_LEAGUE_NOT_STARTED:
        adminMenuLeagueNotStartedInput(league);
        break;
    case ADMIN_MENU_LEAGUE_STARTED:
        adminMenuLeagueStartedInput(league);
        break;

    case SIGNUP_PAGE:
        sign_up();
        while(!stck.empty()) stck.pop();
        stck.push(AUTHENTICATION_PAGE);
        break;
    default:
        break;
    }
}


void display(Page page){
    cout << endl;
    switch (page)
    {
    case VIEW_TABLE:
        showViewTablePage(league);
        break;
    case VIEW_SCHEDULE:
        showViewSchedulePage(league);
        break;
    case VIEW_TEAMS:
        viewTeamsPage(league);
        break;
    case VIEW_LAST_10_RESULTS:
        viewLast10Results(league);
        break;
    case USER_MENU_LEAGUE_NOT_STARTED:
        viewUserMenuLeagueNotStarted();
        break;
    case USER_MENU_LEAGUE_STARTED:
        viewUserMenuLeagueStarted();
        break;
    case AUTHENTICATION_PAGE:
        viewAuthenticationPage();
        break;
    case ADMIN_MENU_LEAGUE_NOT_STARTED:
        viewAdminMenuLeagueNotStartedPage();
        break;
    case ADMIN_MENU_LEAGUE_STARTED:
        viewAdminMenuLeagueStartedPage();
        break;
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
    pullMatchesPlayed(league.matchesPlayed);
    if(league.started)
        pullMatches(league);


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
    pushMatchesPlayed(league.matchesPlayed);
    
}

