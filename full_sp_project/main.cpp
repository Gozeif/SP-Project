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
    ADD_MATCH_RESULT,
    VIEW_SCHEDULE,
    VIEW_TEAMS,
    VIEW_TEAM_INFO,
    VIEW_PLAYER_INFO,
    VIEW_TABLE,
    ADMIN_MENU_LEAGUE_NOT_STARTED,
    ADMIN_MENU_LEAGUE_STARTED,
    USER_MENU_LEAGUE_STARTED,
    USER_MENU_LEAGUE_NOT_STARTED,
    VIEW_LAST_10_RESULTS,
    MAIN_MENU,
    EXIT
};

stack<Page> stck;


void showAuthenticationPage(){
    cout << "1.Login\n2.Signup\n3.Exit\nPick choice: ";
    
}


void showViewTablePage(){
    TableRecord table[MAX_TEAMS_IN_LEAGUE];
	for (int i = 0;i < MAX_TEAMS_IN_LEAGUE;i++)
	{
		table[i] = league.table[i];

	}
	int nums[20]={};
	sort(table, table+MAX_TEAMS_IN_LEAGUE, cmp);

	cout << "RANK  NAME    MP      POINTS" << endl;
	for(int i=1; i<=MAX_TEAMS_IN_LEAGUE; i++){
		TableRecord record = table[i-1];
		cout << i << " " << record.team.name << " " << record.matchesPlayed << " " << record.points << endl;
	}
    cout << "1.Go back\nPick choice: ";
}

void showViewSchedulePage(){
    if(league.matchesPlayed == MAX_MATCHES){
        cout << "No Upcoming matches" << endl;
    }
    else{                                                                      //11
        for(int i=league.matchesPlayed; i<min(MAX_MATCHES, league.matchesPlayed+10); i++){
            Match match = league.matches[i];
            viewMatchResult(match);
        }
    }
    cout << "1.go Back\nPick choice: ";
}

void showAdminMenuLeagueStarted(){                                                         //11
    cout << "1.Logout\n2.Add Match Result\n3.View last 10 results\n4.View Teams\n5.View Next 10 matches\n6.View Table\nPick choice: ";
}

void showAdminMenuLeagueNotStarted(){
    cout << "1.Logout\n2.Add Team\n3.Start League\nPick choice: ";
}

void showUserMenuLeagueNOTStarted(){
    cout << "League has not started yet.\n1.Logout\nPick choice: "; 
}

void showUserMenuLeagueStarted(){
    cout << "1.Logout\n2.View Last 10 results\n3.View Teams\n4.View Next 10 matches\n5.View Table\nPick choice: ";
}

void ViewTeam(){
    cout << "Type team id: ";
    int teamId;
    cin >> teamId;
    TableRecord record = league.table[teamId];
    cout << "Matches Played: " << record.matchesPlayed << endl;
    cout << "Points: " << record.points << endl;
    Team team = record.team;
    cout << "LOL" << endl;
    for(int i=0; i<MAX_PLAYERS; i++){
        Player player = team.players[i];
        cout << player.id << " " << player.name << " " << player.nationality << endl;
    }
    cout << "1.Go back\n2.View player info\nPick choice: ";
}


void ViewPlayerInfo(){
    cout << "Type Player id: ";
    int playerId;
    cin >> playerId;
    Player selectedPlayer = league.teams->players[playerId];
    cout << "ID: " << selectedPlayer.id << endl;
    cout << "Name: " << selectedPlayer.name << endl;
    cout << "Nationality: " << selectedPlayer.nationality << endl;
    cout << "Birthdate: " << selectedPlayer.birthDate.day << "/" << selectedPlayer.birthDate.month << "/" << selectedPlayer.birthDate.year << endl;

    cout << "1.Go back\nPick choice: ";
}


void showTeams(){
    for(int i=0; i<league.teamsCount; i++){
        cout << league.teams[i].id << " " << league.teams[i].name << endl;
    }

    cout << "1.Go back\n2.View one of the teams\nPick choice: ";
}


void showLast10Results(){
    if(league.matchesPlayed == 0){
        cout << "League has not started yet." << endl;
    }
    else{
        for(int i=max(league.matchesPlayed-10, 0); i<league.matchesPlayed; i++){
            viewMatchResult(league.matches[i]);
        }
    }
    
    cout << "1.go Back\nPick choice: ";
}


void getInput(Page page){
    int choice;
    switch (page)
    {
    case VIEW_TABLE:
        cin >> choice;
        if(choice == 1){
            stck.pop();
        }
        break;
    case VIEW_SCHEDULE:
        cin >> choice;
        if(choice == 1){
            stck.pop();
        }
        break;
    case VIEW_TEAM_INFO:
        ViewTeam();
        cin >> choice;
        if(choice == 1){
            stck.pop();
        }
        else if(choice == 2){
            stck.push(VIEW_PLAYER_INFO);
        }
        break;
    case VIEW_PLAYER_INFO:
        ViewPlayerInfo();
        cin >> choice;
        if(choice == 1){
            stck.pop();
        }
        break;
    case VIEW_TEAMS:
        cin >> choice;
        if(choice == 1){
            stck.pop();
        }
        else if(choice == 2){
            stck.push(VIEW_TEAM_INFO);
        }
        break;
    case VIEW_LAST_10_RESULTS:
        cin >> choice;
        if(choice == 1){
            stck.pop();
        }
        break;
    case USER_MENU_LEAGUE_NOT_STARTED:
        cin >> choice;
        if(choice == 1){
            log_out();
            while(!stck.empty()) stck.pop();
            stck.push(AUTHENTICATION_PAGE);
        }
        break;
    case USER_MENU_LEAGUE_STARTED:
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
        break;
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
            if(league.started){
                stck.push(USER_MENU_LEAGUE_STARTED);
            }
            else{
                stck.push(USER_MENU_LEAGUE_NOT_STARTED);
            }
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
        showViewTablePage();
        break;
    case VIEW_SCHEDULE:
        showViewSchedulePage();
        break;
    case VIEW_TEAMS:
        showTeams();
        break;
    case VIEW_LAST_10_RESULTS:
        showLast10Results();
        break;
    case USER_MENU_LEAGUE_NOT_STARTED:
        showUserMenuLeagueNOTStarted();
        break;
    case USER_MENU_LEAGUE_STARTED:
        showUserMenuLeagueStarted();
        break;
    case AUTHENTICATION_PAGE:
        showAuthenticationPage();
        break;
    case ADMIN_MENU_LEAGUE_NOT_STARTED:
        showAdminMenuLeagueNotStarted();
        break;
    case ADMIN_MENU_LEAGUE_STARTED:
        showAdminMenuLeagueStarted();
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
    // pull & push table
    
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


// user menu (literally copy paste from admin) --> done


// view player info --> done

// validate data (saving/pulling) logic, pushing matches is missing results 