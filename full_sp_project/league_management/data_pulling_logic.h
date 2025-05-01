#include <iostream>
#include <fstream>
#include "league.cpp"

using namespace std;


void pullTeamsCount(int &curTeamsCount){
    ifstream inputFile("league_management/counts/teams_count.txt"); // Open the file

    if (!inputFile) { // Check if the file opened successfully
        cout << "Couldn't find file dummy";
        return ;
    }
    string num;
    getline(inputFile, num);
    
    curTeamsCount = stoi(num);

    inputFile.close(); // Close the file
    return;
}

void pullMatchesPlayed(int &matchesPlayed){
    ifstream inputFile("league_management/counts/matches_played.txt"); // Open the file

    if (!inputFile) { // Check if the file opened successfully
        cout << "Couldn't find file dummy";
        return ;
    }
    string num;
    getline(inputFile, num);
    
    matchesPlayed = stoi(num);

    inputFile.close(); // Close the file
    return;
}


void pullTeams(League& league){
    // cout << "TEAMS COUNT " << league.teamsCount << endl;
    for(int i=0; i<league.teamsCount; i++){
        string myPath = "league_management/system_teams/team";
        myPath += to_string(i);
        myPath += ".txt";
        // cout << myPath << endl;
        ifstream inputFile(myPath);
        if(!inputFile){
            cout << "Couldn't find file";
            continue;
        }
        string id, name;
        getline(inputFile, id);
        getline(inputFile, name);
        league.teams[i].id=stoi(id);
        league.teams[i].name = name;
        for(int j=0; j<MAX_PLAYERS; j++){
            string playerId, playerName, birthDateDay, birthDateMonth, birthDateYear, playerNationality;
            getline(inputFile, playerId);
            getline(inputFile, playerName);
            getline(inputFile, birthDateDay);
            getline(inputFile, birthDateMonth);
            getline(inputFile, birthDateYear);
            getline(inputFile, playerNationality);
            //cout << playerId << endl << playerName << endl << birthDateDay << endl << birthDateMonth << endl << birthDateYear << endl << playerNationality << endl;
            league.teams[i].players[j].id = stoi(playerId);
            league.teams[i].players[j].name = playerName;
            league.teams[i].players[j].birthDate.day = stoi(birthDateDay);
            league.teams[i].players[j].birthDate.month = stoi(birthDateMonth);
            league.teams[i].players[j].birthDate.year = stoi(birthDateYear);
            league.teams[i].players[j].nationality = playerNationality;
        }
    }
}

void pullHasStarted(League &league){
    ifstream inputFile("league_management/counts/started_league.txt"); // Open the file

    if (!inputFile) { // Check if the file opened successfully
        cout << "Couldn't find file";
        return ;
    }

    string num;
    getline(inputFile, num);
    
    league.started = stoi(num);

    inputFile.close(); // Close the file
    return;
}