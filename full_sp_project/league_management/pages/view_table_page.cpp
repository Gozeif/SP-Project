#pragma once
#include "structs.cpp"
#include <iostream>
#include <algorithm>
#include "navigation.cpp"


bool cmp(TableRecord Record1, TableRecord Record2)
// if function return true
// first element has ore priority than second element;
// 1 0
{
	return (Record1.points > Record2.points);
}


// display()
void showViewTablePage(League &league){
    TableRecord table[MAX_TEAMS_IN_LEAGUE];
	for (int i = 0;i < MAX_TEAMS_IN_LEAGUE;i++)
	{
		table[i] = league.table[i];

	}

	sort(table, table+MAX_TEAMS_IN_LEAGUE, cmp);

    // command line interface
	cout << "RANK       NAME             MP  POINTS" << endl;
	for(int i=1; i<=MAX_TEAMS_IN_LEAGUE; i++){
		TableRecord record = table[i-1];
        string rank = to_string(i);
        if(rank.size() == 1) rank += " ";
        string name = record.team.name;
        while(name.size() < 22) name += " ";
		cout << rank << "    " << name << record.matchesPlayed << "     " << record.points << endl;
	}
    cout << "1.Go back\nPick choice: ";
}


// input()
void viewTableInput(){
	int choice;
	cin >> choice;
	if(choice == 1){
		stck.pop();
	}
	return;
}
