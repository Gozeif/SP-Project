#pragma once
#include <iostream>
#include "structs.cpp"

#include "../supplementary/supplementary_functions.cpp"
#include "add_team_page.cpp"

void generateTeams(int stIndex, int& teamsCount, League &league){
    for(int i=stIndex; i<MAX_TEAMS_IN_LEAGUE; i++){
        Team team;
        team.id = teamsCount++;
        team.name = adjectives[rand()%20] + " " + nouns[rand()%20];
        generatePlayers(0, team, league.playersCount);
        league.teams[team.id]=team;
        league.table[team.id].team=team;
    }
}

// AKA START LEAGUE 
void generateSchedule(League &league){
    if(league.teamsCount < MAX_TEAMS_IN_LEAGUE){
        cout << "Not enough teams to generate leagues (only " << league.teamsCount << " are found)"  << endl;
        char choice;
        
        do
        {
            cout << "Add teams or generate Them ? (a/g): ";
            cout.flush();
            cin >> choice;
            if(choice == 'a' || choice == 'A'){
                cout << endl;
                while(league.teamsCount < MAX_TEAMS_IN_LEAGUE){
                    AddTeam(league);
                    cout << endl;
                    if(league.teamsCount < MAX_TEAMS_IN_LEAGUE){
                        cout << "generate the rest of the teams ? (y/n): ";
                        cin >> choice;
                        if(choice == 'y'){
                            generateTeams(league.teamsCount, league.teamsCount, league);
                            break;
                        }
                    }
                }
            }
            else if(choice == 'g' || choice == 'G'){
                generateTeams(league.teamsCount, league.teamsCount, league);
            }
            else{
                cout << "Invalid input!\n\n";
            }
        } while (choice != 'A' && choice != 'a' && choice != 'G' && choice != 'g');
        
    }
    string sDate;
    Date startDate;

    do
    {
        cout << "Enter start date (dd/mm/yyyy): ";
        cin >> sDate;
        startDate = stringToDate(sDate);

        if (startDate.day == -1)
        {
            cout << "Invalid Date!\n\n";
        }
        
    } while (startDate.day == -1 || startDate.month == -1 || startDate.year == -1);
    

    league.startDate = startDate;

    int matchesScheduled=0;
    // using the circle method for generating round robin tournaments schedule     
    int circle[2][MAX_TEAMS_IN_LEAGUE/2]={};
    for(int i=0; i<2; i++){
        for(int j=0; j<MAX_TEAMS_IN_LEAGUE/2; j++){
            circle[i][j] = j + i*(MAX_TEAMS_IN_LEAGUE/2);
        }
    }
    Date curDate=league.startDate;
    for(int week=1; week<=38; week++){


        for(int i=0; i<MAX_TEAMS_IN_LEAGUE/2; i++){
            Match match;
            int time;
            if(i <= 2) time = 4;
            else if(i <= 5) time = 6;
            else time = 8;
            if(week <= 19)
                match = {matchesScheduled++, league.teams[circle[0][i]], league.teams[circle[1][i]], curDate, {0, 0}, time};
            else
                match = {matchesScheduled++, league.teams[circle[1][i]], league.teams[circle[0][i]], curDate, {0, 0}, time};
            league.matches[match.id] = match;
        }

        int temp = circle[0][MAX_TEAMS_IN_LEAGUE/2-1];
        for(int i=MAX_TEAMS_IN_LEAGUE/2-1; i>0; i--){
            circle[0][i] = circle[0][i-1];
        }
        circle[0][1] = circle[1][0];
        for(int i=0; i<MAX_TEAMS_IN_LEAGUE/2 - 1; i++)
            circle[1][i] = circle[1][i+1];
        circle[1][MAX_TEAMS_IN_LEAGUE/2-1]=temp;
        curDate = getNextWeek(curDate);
    }
    // cout << matchesScheduled << endl;
    
    league.started = true;
    cout << "League started successfully!" << endl;
   
}




