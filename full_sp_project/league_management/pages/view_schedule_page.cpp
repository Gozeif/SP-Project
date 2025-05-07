#pragma once
#include "structs.cpp"
#include <iostream>
#include <algorithm>
#include "navigation.cpp"
#include "../supplementary/supplementary_functions.cpp"


void viewMatchResult(Match match)
{
	//cout << "the week :" << matches[b].week << "\n";

    cout << "Date: " << dateToString(match.date) << " " << match.time << ":00 PM" << endl;
	cout << match.id << " " << match.team_home.name << "   " << match.result.home.goals<< " " << '-' << " " << match.result.away.goals << "   " << match.team_away.name << endl;


}


void viewLast10Results(League &league){
    if(league.matchesPlayed == 0){
        cout << "League has not started yet." << endl;

    }
    else{
        for(int i=max(league.matchesPlayed-10, 0); i<league.matchesPlayed; i++){
            viewMatchResult(league.matches[i]);
        }
    }
    cout << "1.go Back\n2.View Match Details\nPick choice: ";
    
}

void showViewSchedulePage(League &league){
    if(league.matchesPlayed == MAX_MATCHES){
        cout << "No Upcoming matches" << endl;
    }
    else{
             
        for(int i=league.matchesPlayed; i<min(MAX_MATCHES, league.matchesPlayed+10); i++){
            Match match = league.matches[i];
            viewMatchResult(match);
        }
    }
    cout << "1.go Back\nPick choice: ";
}

void viewScheduleInput(){

    int choice;
    cin >> choice;
    if(choice == 1){
        stck.pop();
    }
    
    return;
}

void viewLast10ResultsInput(){
    int choice;
    cin >> choice;
    if(choice == 1){
        stck.pop();
    }
    else if(choice == 2){
        stck.push(VIEW_MATCH_STATISTICS);
    }
    return;
}