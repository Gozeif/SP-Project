#pragma once
#include <iostream>
#include "structs.cpp"
#include "navigation.cpp"
#include "view_player_info_page.cpp"

void viewTeamPage(League &league){
    cout << "Type team id: ";
    int teamId;
    cin >> teamId;
    TableRecord record = league.table[teamId];
    cout << "Matches Played: " << record.matchesPlayed << endl;
    cout << "Points: " << record.points << endl;
    Team team = record.team;
    for(int i=0; i<MAX_PLAYERS; i++){
        Player player = team.players[i];
        cout << player.id << " " << player.name << " " << player.nationality << endl;
    }
    cout << "1.Go back\n2.View player info\nPick choice: ";
    int choice;
    cin >> choice;
    if(choice == 1){
        stck.pop();
    }
    else if(choice == 2){
        viewPlayerInfoPage(league, team);
    }
    return;
}