#pragma once
#include <iostream>
#include "structs.cpp"
#include "navigation.cpp"
#include "../authentication.h"
#include "../supplementary/supplementary_functions.cpp"
#include "add_player_page.cpp"
#include "../supplementary/generation_data.cpp"



const int MAX_PLAYERS_IN_TEAM = 34;



void generatePlayers(int stIndex, Team& team, int& curPlayersCount){
    for(int i=stIndex; i<MAX_PLAYERS_IN_TEAM; i++){
        Player player;
        player.id = curPlayersCount++;
        player.name = arabicMaleNames[rand()%20] + " " + arabicMaleNames[rand()%20];
        player.birthDate.day = days[rand()%28];
        player.birthDate.month = months[rand()%12];
        player.birthDate.year = years[rand()%27];
        player.nationality = nationalities[rand()%20];
        team.players[i] = player;
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


    cin.ignore();
    cout.flush();
    while(team.name.empty()){
        	cout << "Enter Team Name : " ;
            getline(cin , team.name) ;
    }

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
            for(int i = 0 ; i < MAX_PLAYERS_IN_TEAM ; i++){
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
