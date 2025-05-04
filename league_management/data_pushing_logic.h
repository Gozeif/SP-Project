#include <iostream>
#include <fstream>
#include "league.cpp"



void pushHasStarted(League& league){
    string path="league_management/counts/started_league.txt";
    std::fstream file(path, std::ios::in | std::ios::out | std::ios::trunc);
    if(!file){
        cout << "Couldn't open file";
        return;
    }
    file << league.started;
}


void pushMatches(League& league){
    string path="league_management/matches/matches.txt";
    std::fstream file(path, std::ios::in | std::ios::out | std::ios::trunc);
    if(!file){
        cout << "Couldn't open file";
        return;
    }
    for(int match=0; match<MAX_MATCHES; match++){
        // NEED TO ADD RESULT AS WELL
        file << league.matches[match].id << " " << league.matches[match].team_home.id << " " << league.matches[match].result.homeGoals << " " << league.matches[match].result.awayGoals << "  " << league.matches[match].team_away.id << " " << dateToString(league.matches[match].date) << '\n';
    }
}


void pushTeamsCount(int &teamsCount){
    string path="league_management/counts/teams_count.txt";
    std::fstream file(path, std::ios::in | std::ios::out | std::ios::trunc);
    if(!file){
        cout << "Couldn't open file";
        return;
    }
    file << teamsCount;
}


void pushMatchesPlayed(int &matchesPlayed){
    string path="league_management/counts/matches_played.txt";
    std::fstream file(path, std::ios::in | std::ios::out | std::ios::trunc);
    if(!file){
        cout << "Couldn't open file";
        return;
    }
    file << matchesPlayed;

}

void pushTeam(Team tm){
    string path="league_management/system_teams/team" + to_string(tm.id) + ".txt";

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
