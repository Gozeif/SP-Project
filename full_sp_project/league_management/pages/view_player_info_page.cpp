#pragma once
#include<iostream>
#include "structs.cpp"
#include "navigation.cpp"

void viewPlayerInfoPage(League& league, Team team){
    cout << "Type Player id: ";
    int playerId;
    cin >> playerId;
    // between 0, 679
    // to get index between [0, 19]
    playerId -= team.players[0].id;
    Player selectedPlayer = team.players[playerId];
    cout << "ID: " << selectedPlayer.id << endl;
    cout << "Name: " << selectedPlayer.name << endl;
    cout << "Nationality: " << selectedPlayer.nationality << endl;
    cout << "Birthdate: " << selectedPlayer.birthDate.day << "/" << selectedPlayer.birthDate.month << "/" << selectedPlayer.birthDate.year << endl;

    cout << "1.Go back\nPick choice: ";
    int choice;
    cin >> choice;
    if(choice == 1){
        stck.pop();
        stck.pop();
    }
    return;
}
