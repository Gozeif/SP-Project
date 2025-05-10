#pragma once
#include <iostream>
#include <cstdlib>
#include "structs.cpp"
#include "navigation.cpp"
#include "view_schedule_page.cpp"





void viewMatchStats(Match match) {
    TeamStat h = match.result.home;
    TeamStat a = match.result.away;
    //cout << "           HomeTeam" << " " << 5 << " - " << 6 << " " << "AwayTeam" << endl;
    cout<<"------------------------------------------"<< endl;
    cout << "Possession:    |" << h.possession << "%"<< "   -   "<< a.possession<< "%" << " |"<< endl;
    cout << "Yellow Cards:  |" << h.yellow_cards  << "     -   " << a.yellow_cards << "   |"<< endl;
    cout << "Red Cards:     |" << h.red_cards  << "     -   " << a.red_cards <<  "   |"<< endl;

    string homeShots = to_string(h.shots);
    string homeFouls = to_string(h.fouls);
    string awayFouls = to_string(a.fouls);
    string awayShots = to_string(a.shots);
    if(homeShots.size() == 1) homeShots += " ";
    if(awayShots.size() == 1) awayShots += " ";
    if(homeFouls.size() == 1) homeFouls += " ";
    if(awayFouls.size() == 1) awayFouls += " ";

    cout << "Shots:         |" << homeShots << "    -   " << awayShots << "  |" << endl;
    cout << "Fouls:         |" << homeFouls << "    -   " << awayFouls << "  |" << endl;


    cout << "------------------------------------------" << endl;

}


void viewMatchStatisticsPage(League &league){
    cout << "Enter match id: ";
    int id;
    cin >> id;
    Match match = league.matches[id];
    viewMatchResult(match);
    cout << endl;
    viewMatchStats(match);

    // 
    cout << "1.go Back\nPick choice: ";
    int choice;
    cin >> choice;
    if(choice == 1){
        stck.pop();
    }
    return;
}


// view last 10 results

// /

// /

// 






// select one 

