#include <iostream>
#include <fstream>
#include <string>

using namespace std ;

const int MAX_USERS = 100;
const int MAX_TEAMS = 20;
const int MAX_PLAYERS = 34;
const int MAX_MATCHES = 190;

struct User {
	int ID;
	string username;
	string password;
	string Role;
};

struct Player {
	int ID;
	string Name;
	string BirthDate;
	string Nationality;
};

struct Team {
	int ID;
	string Name;
	Player Players[MAX_PLAYERS];
	int playerCount = 0;
};

struct Match {
	int ID;
	int TeamHome;
	int TeamAway;
	string StartDate;
	int ResultID = -1;
};

struct Result {
	int ID;
	int TeamHomeGoals;
	int TeamAwayGoals;
};

struct TableRecord {
	int ID;
	int No;
	string TeamName;
	int Points = 0;
};


User users[MAX_USERS];
int userCount = 0;
User currentUser;

Team teams[MAX_TEAMS];
int teamCount = 0;

Match matches[MAX_MATCHES];
int matchCount = 0;

Result results[MAX_MATCHES];
int resultCount = 0;

TableRecord table[MAX_TEAMS];

 
void sign_up() {
	string username, password;
	cout << "Enter new username: ";
	cin >> username;

	for (int i = 0; i < userCount; i++) {
		if (users[i].username == username) {
			cout << "Username already exists!\n";
			return;
		}
	}

	cout << "Enter new password: ";
	cin >> password;

	users[userCount].ID = userCount + 1;
	users[userCount].username = username;
	users[userCount].password = password;
	users[userCount].Role = "User"; 
	userCount++;

	cout << "Sign up successful!\n";
}


bool login(string username, string password) {
	for (int i = 0; i < userCount; i++) {
		if (users[i].username == username && users[i].password == password) {
			currentUser = users[i];
			return true;
		}
	}
	return false;
}
int main ()
{
	return 0;
	
}
