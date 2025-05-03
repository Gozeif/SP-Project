#include <iostream>
#include <string>
#include <fstream>
#include "supplementary_functions.cpp"
#include "generation_data.cpp"
#include "league.cpp"

using namespace std;


const int MAX_Players = 34;






Player AddPlayer(int& curPlayersCount){

    Player pl;
	// cout << "Player ID : " ;
	// cin >> pl.id ;
    cin.ignore() ;
    pl.id = curPlayersCount++;
	
	cout << "Player Name : " ;
	getline(cin , pl.name) ; // to get spaces as a char and not end the input when encountering a space 

	cout << "Player date of birth : \n" ;

	do 
    {
        cout << "Year --> ";
        cin >> pl.birthDate.year;

    } while(pl.birthDate.year < 0 || pl.birthDate.year > 2025); // to ensure that the user enters a valid year 
	
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

	cout << "Player Nationality : " ;
	getline(cin , pl.nationality) ;


    return pl;


}


void generatePlayers(int stIndex, Team& team, int& curPlayersCount){
    for(int i=stIndex; i<MAX_Players; i++){
        Player player;
        player.id = curPlayersCount++;
        player.name = arabicMaleNames[rand()%20] + " " + arabicMaleNames[rand()%20];
        player.birthDate.day = days[rand()%28];
        player.birthDate.month = days[rand()%12];
        player.birthDate.year = days[rand()%27];
        team.players[i] = player;
    }   
}

void generateTeams(int stIndex, int& teamsCount, League &league){
    for(int i=stIndex; i<MAX_TEAMS_IN_LEAGUE; i++){
        Team team;
        team.id = teamsCount++;
        team.name = adjectives[rand()%20] + " " + nouns[rand()%20];
        generatePlayers(0, team, league.playersCount);
        league.teams[team.id]=team;
    }
}


void AddTeam(League& league)
{
    Team team;
    if(league.teamsCount == 20){
        cout << "There are already 20 teams" << endl;
        return;
    }
    team.id = league.teamsCount++;


	cout << "Enter Team Name : " ;
    cout.flush();
    cin.ignore();
	getline(cin , team.name) ;
    // cin.ignore();
    cout << endl ;

    cout << "Generate Players ? (y/n): ";
    // cout.flush();
    char choice;
    cin >> choice;

    if(choice == 'y'){
        generatePlayers(0, team, league.playersCount);
    }
    else {
        for(int i = 0 ; i < MAX_Players ; i++){
            cout << "Enter Player #" << i+1 << " info. " << endl; // "Enter Player #1 info."
            team.players[i] = AddPlayer(league.playersCount);
            cout << endl ;
            cout << "Generate The rest of the players ? (y/n): ";
            cin >> choice;
            if(choice == 'y'){
                generatePlayers(i+1, team, league.playersCount);
                break;
            }
        }
    }
    league.teams[team.id] = team;
    return;

}


void generateSchedule(League &league){
    if(league.teamsCount < MAX_TEAMS_IN_LEAGUE){
        cout << "Not enough teams to generate leagues" << endl;
        cout << "Add teams or generate Them ? (a/g): ";
        cout.flush();
        char choice;
        cin >> choice;
        if(choice == 'a'){
            cout << endl;
            while(league.teamsCount < MAX_TEAMS_IN_LEAGUE){
                cout << "LOL" << endl;
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
        else if(choice == 'g'){
            generateTeams(league.teamsCount, league.teamsCount, league);
        }
    }
    int matchesScheduled=0;
    // using the circle method for generating round robin tournaments schedule
    int circle[2][MAX_TEAMS_IN_LEAGUE/2]={};
    for(int i=0; i<2; i++){
        for(int j=0; j<MAX_TEAMS_IN_LEAGUE/2; j++){
            circle[i][j] = j + i*(MAX_TEAMS_IN_LEAGUE/2);
        }
    }
    for(int week=1; week<=38; week++){
        // for(int i=0; i<2; i++){
        //     for(int j=0; j<MAX_TEAMS_IN_LEAGUE/2; j++){
        //         cout << circle[i][j] << " ";
        //     }
        //     cout << endl;
        // }
        // cout << endl;
        for(int i=0; i<MAX_TEAMS_IN_LEAGUE/2; i++){
            Match match;
            if(week <= 19)
                match = {matchesScheduled++, league.teams[circle[0][i]], league.teams[circle[1][i]], week, HasNotStarted};
            else
                match = {matchesScheduled++, league.teams[circle[1][i]], league.teams[circle[0][i]], week, HasNotStarted};
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

    }
    cout << matchesScheduled << endl;
   
}

void addMatchResult(int matchId, Result result, League& league){
    league.matches[matchId].result = result;
}

// we want to make a function that