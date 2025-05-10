#pragma once
#include <iostream>
#include "structs.cpp"
#include "navigation.cpp"

void viewTeamsPage(League &league){
    for(int i=0; i<league.teamsCount; i++){
        cout << league.teams[i].id << " " << league.teams[i].name << endl;
    }

    cout << "1.Go back\n2.View one of the teams\nPick choice: ";
}

void viewTeamsInput(){
    int choice;
    cin >> choice;
    if(choice == 1){
        stck.pop();
    }
    else if(choice == 2){
        stck.push(VIEW_TEAM_INFO);
    }
    return;
}