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

    } while(pl.birthDate.year < 0 || pl.birthDate.year > 2010); // to ensure that the user enters a valid year and apropiate age to player
	
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
        player.nationality = nationalities[rand()%20];
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
        league.table[team.id].team=team;
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

    char choice;

    do
    {
        cout << "Generate Players ? (y/n): ";
        // cout.flush();
        cin >> choice;

        if(choice == 'y' || choice == 'Y'){
            generatePlayers(0, team, league.playersCount);
        }
        else if(choice == 'n' || choice == 'N') {
            for(int i = 0 ; i < MAX_Players ; i++){
                cout << "Enter Player #" << i+1 << " info. " << endl; // "Enter Player #1 info."
                team.players[i] = AddPlayer(league.playersCount);
                cout << endl ;

                bool generated = false;

                do
                {
                    cout << "Generate The rest of the players ? (y/n): ";
                    cin >> choice;

                    if(choice == 'y' || choice == 'Y'){
                        generatePlayers(i+1, team, league.playersCount);
                        generated = true;
                    }
                    else if(choice == 'n' || choice == 'N'){
                    }
                    else{
                        cout << "Invalid input!\n\n";
                    }

                } while (choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n');

                if (generated)
                {
                    break;
                }
                
                
            }
        }
        else{
            cout << "Invalid input!\n\n";
        }

    } while (choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n');
    
    league.teams[team.id] = team;
    league.table[team.id].team = team;
    return;

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
            else if(choice == 'g' || choice == 'G'){
                cout << "LOL" << endl;
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
            if(week <= 19)
                match = {matchesScheduled++, league.teams[circle[0][i]], league.teams[circle[1][i]], curDate, {0, 0}};
            else
                match = {matchesScheduled++, league.teams[circle[1][i]], league.teams[circle[0][i]], curDate, {0, 0}};
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

void addMatchResult(League& league){
    cout << "Current Match: " << endl;
    Match& match = league.matches[league.matchesPlayed];

    cout << match.team_home.name << " vs " << match.team_away.name << "   " << dateToString(league.startDate) << endl;


    do
    {
        cout << "Enter home team goals: ";
        cin >> match.result.homeGoals;
    } while (match.result.homeGoals < 0);
    
    do
    {
        cout << "Enter away team goals: ";
        cin >> match.result.awayGoals;
    } while (match.result.awayGoals < 0);
    
    
    int homePoints, awayPoints;
    if(match.result.homeGoals > match.result.awayGoals){
        homePoints=3;
        awayPoints=0;
    }
    else if(match.result.homeGoals < match.result.awayGoals){
        homePoints=0;
        awayPoints=3;
    }
    else{
        homePoints=1;
        awayPoints=1;
    }

    league.table[match.team_home.id].points += homePoints;
    league.table[match.team_away.id].points += awayPoints;
    league.table[match.team_away.id].matchesPlayed++;
    league.table[match.team_home.id].matchesPlayed++;
    league.matchesPlayed++;
    cout << "Result added successfully!" << endl;

}

void viewMatchResult(Match match)
{
	//cout << "the week :" << matches[b].week << "\n";

    cout << "Date: " << dateToString(match.date) << endl;
	cout << match.team_home.name << "   " << match.result.homeGoals<< " " << '-' << " " << match.result.awayGoals << "   " << match.team_away.name << endl;


}

// we want to make a function that