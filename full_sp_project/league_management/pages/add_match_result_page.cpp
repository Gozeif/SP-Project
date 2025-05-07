#pragma once
#include <iostream>
#include "structs.cpp"
#include "navigation.cpp"
#include "../supplementary/supplementary_functions.cpp"


void generateMatchStats(Result& result) {

    TeamStat& h = result.home;
    TeamStat& a = result.away;

    srand(time(0)); 
    h.possession = 20 + rand() % 60; 
    a.possession = 100 - h.possession; 
    h.shots = result.home.goals + (rand() % 15);
    a.shots = result.away.goals + (rand() % 15);
    h.yellow_cards = rand() % 5;
    h.red_cards = rand() % 3;
    a.yellow_cards = rand() % 5;
    a.red_cards = rand() % 3;
    h.fouls = rand() % 15;
    a.fouls = rand() % 15;



}


void addMatchResult(League& league){
    cout << "Current Match: " << endl;
    Match& match = league.matches[league.matchesPlayed];

    cout << match.team_home.name << " vs " << match.team_away.name << "   " << dateToString(league.startDate) << " " << match.time << ":00 PM" << endl;


    while(true){
        cout << "Enter home team goals: ";
        string cnt;
        cin >> cnt;
        int goals;
        try {
            goals = stoi(cnt);
            if(goals < 0){
                cout << "Invalid Input" << endl;
                continue;
            }
            match.result.home.goals = goals;
        }
        catch(exception){
            cout << "Invalid Input" << endl;
            continue;
        }
        break;
    } 

    while(true){
        cout << "Enter away team goals: ";

        string cnt;
        cin >> cnt;
        int goals;
        try {
            goals = stoi(cnt);
            if(goals < 0){
                cout << "Invalid Input" << endl;
                continue;
            }
            match.result.away.goals = goals;
        }
        catch(exception){
            cout << "Invalid Input" << endl;
            continue;
        }
        break;
    } 
    
    int homePoints, awayPoints;
    if(match.result.home.goals > match.result.away.goals){
        homePoints=3;
        awayPoints=0;
    }
    else if(match.result.home.goals < match.result.away.goals){
        homePoints=0;
        awayPoints=3;
    }
    else{
        homePoints=1;
        awayPoints=1;
    }
    generateMatchStats(match.result);

    // generateStatistics()
    league.table[match.team_home.id].points += homePoints;
    league.table[match.team_away.id].points += awayPoints;
    league.table[match.team_away.id].matchesPlayed++;
    league.table[match.team_home.id].matchesPlayed++;
    league.matchesPlayed++;
    cout << "Result added successfully!" << endl;
    
}


