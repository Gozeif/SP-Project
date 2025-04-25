
#include "data_pulling_logic.cpp"
#include "data_pushing_logic.cpp"
#include "structs_and_functions.cpp"


using namespace std;







int main(){

    League league;
    pullTeamsCount(league.teamsCount);
    // cout.flush();
    pullTeams(league);
    // cout.flush();
    generateSchedule(league);

    // // need to push team
    // // for(int i=0; i<MAX_MATCHES; i++){
    // //     cout << league.matches[i].team_home.name << " " << league.matches[i].team_away.name << endl;
    // // }
    pushTeamsCount(league.teamsCount);
    pushTeams(league);

    for(int i=0; i<380; i++){
        cout << league.matches[i].team_away.id << " " << league.matches[i].team_home.id << endl;
    }




    // Team team = league.teams[0];
    // cout << team.id << " " << team.name << endl;
    // for(int i=0; i<34; i++){
    //     cout << team.players[i].name << " " << team.players[i].id << " " << team.players[i].nationality << endl;
    // }
    return 0;
}