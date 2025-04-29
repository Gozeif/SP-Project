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



struct Player
{
	int id;
	string name;
	Date birthDate;
	string nationality;
};

struct Team
{
	int id=0;
	string name;
	Player players[MAX_PLAYERS];
};

enum Result{
    HasNotStarted,
    Home,
    Away,
    Draw,
};

struct Match {
    int id;
    Team team_home;
    Team team_away;
    int week;
    Result result;
};

// Team instance that is in a league




struct League {
    int id;
    bool started=false;
    int teamsCount=0;
    int playersCount=0;
    Date startDate;
    Team teams[MAX_TEAMS_IN_LEAGUE];
    Match matches[MAX_MATCHES];
};



// lets make a function that generates the rest of the teams
// so basically we need 20 initial teams