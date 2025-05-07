#pragma once
#include<string> 
const int MAX_TEAMS_IN_LEAGUE=20;
const int MAX_MATCHES=380;
const int MAX_PLAYERS=34;


using namespace std;


struct Date
{
	int day , month , year ;
};

//  dd/mm/year



struct Player
{
	int id;
	string name="";
	Date birthDate;
	string nationality="";
};

struct Team
{
	int id=0;
	string name="";
	Player players[MAX_PLAYERS];
};

struct TeamStat {
    int goals=0;
    int possession=0; 
    int shots=0;
    int yellow_cards=0;
    int red_cards=0;
    int fouls = 0;
};

struct Result{
    TeamStat home;
    TeamStat away;
};


struct Match {
    int id;
    Team team_home;
    Team team_away;
    Date date;
    Result result;
    int time;



};


struct TableRecord
{
	int matchesPlayed=0, points=0;
    // goal difference
    // etc.
    Team team;
};




struct League {
    int id;
    bool started=false;
    int teamsCount=0;
    int playersCount=0;
    int matchesPlayed=0;
    Date startDate;
    Team teams[MAX_TEAMS_IN_LEAGUE];
    Match matches[MAX_MATCHES];
    TableRecord table[MAX_TEAMS_IN_LEAGUE];
};



// lets make a function that generates the rest of the teams
// so basically we need 20 initial teams



// league.table

// print table sorted

// copy 
// sort lel copy
// print el copy

// id 1 -> id 1