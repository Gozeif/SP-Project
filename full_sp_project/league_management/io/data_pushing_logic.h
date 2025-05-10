#include <iostream>
#include <fstream>
#include "../pages/structs.cpp"



void pushHasStarted(League& league){
    string path="league_management/data/counts/started_league.txt";
    std::fstream file(path, std::ios::in | std::ios::out | std::ios::trunc);
    if(!file){
        cout << "Couldn't open file";
        return;
    }
    file << league.started;
}


void pushMatches(League& league){
    string path="league_management/data/matches/matches.txt";
    std::fstream file(path, std::ios::in | std::ios::out | std::ios::trunc);
    if(!file){
        cout << "Couldn't open file";
        return;
    }
    for(int match=0; match<MAX_MATCHES; match++){
        // NEED TO ADD RESULT AS WELL
        file << league.matches[match].id << " ";
        file << league.matches[match].team_home.id << " ";
        file << league.matches[match].result.home.goals << " ";
        file << league.matches[match].result.home.possession << " ";
        file << league.matches[match].result.home.shots << " ";
        file << league.matches[match].result.home.yellow_cards << " ";
        file << league.matches[match].result.home.red_cards << " ";
        file << league.matches[match].result.home.fouls << " ";
        file << league.matches[match].team_away.id << " ";
        file << league.matches[match].result.away.goals << " ";
        file << league.matches[match].result.away.possession << " ";
        file << league.matches[match].result.away.shots << " ";
        file << league.matches[match].result.away.yellow_cards << " ";
        file << league.matches[match].result.away.red_cards << " ";
        file << league.matches[match].result.away.fouls << " ";
        file << dateToString(league.matches[match].date) << " ";
        file << league.matches[match].time << '\n';

    }
}


void pushTeamsCount(int &teamsCount){
    string path="league_management/data/counts/teams_count.txt";
    std::fstream file(path, std::ios::in | std::ios::out | std::ios::trunc);
    if(!file){
        cout << "Couldn't open file";
        return;
    }
    file << teamsCount;
}


void pushMatchesPlayed(int &matchesPlayed){
    string path="league_management/data/counts/matches_played.txt";
    std::fstream file(path, std::ios::in | std::ios::out | std::ios::trunc);
    if(!file){
        cout << "Couldn't open file";
        return;
    }
    file << matchesPlayed;

}

void pushTeam(TableRecord& record){
    string path="league_management/data/system_teams/team" + to_string(record.team.id) + ".txt";

    std::fstream file(path, std::ios::in | std::ios::out | std::ios::trunc);
    if(!file){
        cout << "Couldn't open file";
        return;
    }
    Team tm = record.team;
    file << tm.id << '\n' << tm.name << '\n' << record.matchesPlayed << '\n' << record.points << '\n';
    for(int i=0; i<MAX_PLAYERS; i++){
        auto player = tm.players[i];
        file << player.id << "\n" << player.name << "\n" << player.birthDate.day << '\n' << player.birthDate.month << '\n' << player.birthDate.year << "\n" << player.nationality << '\n';
    }
    // cout << '\n';
}

void pushTeams(League &league){
    for(int i=0; i<league.teamsCount; i++){
        pushTeam(league.table[i]);
    }
}




// void pushMatches()


// 