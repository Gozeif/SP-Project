#include <iostream>
#include <fstream>
#include "league.cpp"


void pushTeamsCount(int &teamsCount){
    string path="counts/teams_count.txt";
    std::fstream file(path, std::ios::in | std::ios::out | std::ios::trunc);
    if(!file){
        cout << "Couldn't open file";
        return;
    }
    file << teamsCount;
}


void pushTeam(Team tm){
    string path="system_teams/team" + to_string(tm.id) + ".txt";

    std::fstream file(path, std::ios::in | std::ios::out | std::ios::trunc);
    if(!file){
        cout << "Couldn't open file";
        return;
    }
    file << tm.id << '\n' << tm.name << '\n';
    for(int i=0; i<MAX_PLAYERS; i++){
        auto player = tm.players[i];
        file << player.id << "\n" << player.name << "\n" << player.birthDate.day << '\n' << player.birthDate.month << '\n' << player.birthDate.year << "\n" << player.nationality << '\n';
    }
    // cout << '\n';
}

void pushTeams(League league){
    for(int i=0; i<league.teamsCount; i++){
        pushTeam(league.teams[i]);
    }
}


// void pushMatches()
