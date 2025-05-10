#include <iostream>
#include <fstream>
#include "../supplementary/supplementary_functions.cpp"

using namespace std;


void pullTeamsCount(int &curTeamsCount){
    ifstream inputFile("league_management/data/counts/teams_count.txt"); // Open the file

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
    ifstream inputFile("league_management/data/counts/matches_played.txt"); // Open the file

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

void pullMatches(League& league){
    string myPath = "league_management/data/matches/matches.txt";
    ifstream inputFile(myPath);
    if(!inputFile){
        cout << "Couldn't find file" << endl;
        return;
    }
    for(int i=0; i<MAX_MATCHES; i++){
        
        
        string matchS;
        getline(inputFile, matchS);
        istringstream iss(matchS);
        string id, team1, homeGoals, homePossession, homeShots, homeYellow, homeRed, homeFouls;
        string team2, homeGoals2, homePossession2, homeShots2, homeYellow2, homeRed2, homeFouls2;
        string date, time;
        iss >> id;
        iss >> team1;
        iss >> homeGoals;
        iss >> homePossession;
        iss >> homeShots;
        iss >> homeYellow;
        iss >> homeRed;
        iss >> homeFouls;
        iss >> team2;
        iss >> homeGoals2;
        iss >> homePossession2;
        iss >> homeShots2;
        iss >> homeYellow2;
        iss >> homeRed2;
        iss >> homeFouls2;
        iss >> date;
        iss >> time;
        TeamStat homeRes = {stoi(homeGoals), stoi(homePossession), stoi(homeShots), stoi(homeYellow), stoi(homeRed), stoi(homeFouls)};
        TeamStat awayRes = {stoi(homeGoals2), stoi(homePossession2), stoi(homeShots2), stoi(homeYellow2), stoi(homeRed2), stoi(homeFouls2)};
        //cout << id << " " << team1 << "  " << homeGoals << " " << awayGoals << " " << team2 << " " << date << endl;
        Match match = {stoi(id), league.teams[stoi(team1)], league.teams[stoi(team2)], stringToDate(date), {homeRes, awayRes}, stoi(time)};
        league.matches[i] = match;
    }
}


void pullTeams(League& league){
    // cout << "TEAMS COUNT " << league.teamsCount << endl;
    for(int i=0; i<league.teamsCount; i++){
        string myPath = "league_management/data/system_teams/team";
        myPath += to_string(i);
        myPath += ".txt";
        // cout << myPath << endl;
        ifstream inputFile(myPath);
        if(!inputFile){
            cout << "Couldn't find file";
            continue;
        }
        string id, name, matchesPlayed, points;
        getline(inputFile, id);
        getline(inputFile, name);
        getline(inputFile, matchesPlayed);
        getline(inputFile, points);
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
        league.table[i].team = league.teams[i];
        league.table[i].matchesPlayed = stoi(matchesPlayed);
        league.table[i].points = stoi(points);
    }
}

void pullHasStarted(League &league){
    ifstream inputFile("league_management/data/counts/started_league.txt"); // Open the file

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