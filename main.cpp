
#include <iostream>
using namespace std;


struct PlayerDetails {
	int id;
	string name;
	int date;
	string nationality;
};




struct TeamDetails {
	int id;
	string name;
	PlayerDetails players[34];
};
TeamDetails team[20];

void viewTeamInfo(int numberofteam)
{
	const int Y = numberofteam - 1;
	cout << "Id =" << team[Y].id << "\n";
	cout << "Name =" << team[Y].name << "\n";
	cout << "players :\n";
	int f = 1;
	for (int i = 0;i < 34; i++)
	{
		cout << f << "-" << team[Y].players[i].name << "\n";
		f++;
	}


}


void viewPlayerInfo(int numberofteam, int numberofplayer)
{
	const int h = numberofteam - 1;
	const int g = numberofplayer - 1;
	cout << "id = " << team[h].players[g].id << "\n";
	cout << "name = " << team[h].players[g].name << "\n";
	cout << "birthdate = " << team[h].players[g].date << "\n";
	cout << "nationality = " << team[h].players[g].nationality << "\n";
}



int main()
{

	return 0;
}