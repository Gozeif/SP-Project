#pragma once
#include<string> 
#include<iostream>
const int MAX_TEAMS_IN_LEAGUE = 20;
const int MAX_MATCHES = 380;
const int MAX_PLAYERS = 34;


using namespace std;


struct Date
{
	int day, month, year;
};



struct Player
{
	int id;
	string name;
	Date birthDate;
	string nationality;
};

struct Team
{
	int id = 0;
	string name;
	Player Players[MAX_PLAYERS];
}team[MAX_TEAMS_IN_LEAGUE];

//enum Result {
//	HasNotStarted,
//	Home,
//	Away,
//	Draw,
//};

struct Result {
	int home_score;
	int away_score;
};



struct Match {
	int id;
	Team team_home;
	Team team_away;
	int week;
	Result result;
}matches[380];














void viewTeamInfo(int numberofteam)
{
	const int Y = numberofteam - 1; // y Because the array starts at position 0
	cout << "Id =" << team[Y].id << "\n"; 
	cout << "Name =" << team[Y].name << "\n";
	cout << "players :\n";
	int f = 1;
	for (int i = 0;i < 34; i++)
	{
		cout << f << "-" << team[Y].Players[i].name << "\n";
		f++;
	}


}


void viewPlayerInfo(int numberofteam, int numberofplayer)
{
	const int h = numberofteam - 1; // h Because the array starts at position 0
	const int g = numberofplayer - 1; // g Because the array starts at position 0
	cout << "id = " << team[h].Players[g].id << "\n";
	cout << "name = " << team[h].Players[g].name << "\n";
	Date birthDate = team[h].Players[g].birthDate;
	cout << "birthdate = " << birthDate.day << '/' << birthDate.month << '/' << birthDate.year << "\n";
	cout << "nationality = " << team[h].Players[g].nationality << "\n";
}



