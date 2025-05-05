#include <iostream>
#include<string>
#include <league_management/structs_and_functions.h>
#include <algorithm>
using namespace std;
int Fridays[20] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19 };

//defining structs:

void ViewTable(League league)
{
	TableRecord table[MAX_TEAMS_IN_LEAGUE];
	for (int i = 0;i < MAX_TEAMS_IN_LEAGUE;i++)
	{
		table[i] = league.table[i];

	}
	int nums[20]={};
	sort(table, table+MAX_TEAMS_IN_LEAGUE, cmp);

	cout << "RANK  NAME       MP         POINTS" << endl;
	for(int i=1; i<=MAX_TEAMS_IN_LEAGUE; i++){
		TableRecord record = table[i-1];
		cout << i << " " << record.team.name << " " << record.matchesPlayed << " " << record.points << endl;
	}
	
}



// user 