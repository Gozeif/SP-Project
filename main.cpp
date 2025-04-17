#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
using namespace std;



void sign_up() {
	string username, password;
	cout << "Username: ";
	cin >> username;
	cout << "Password: ";
	password = _getch();
	cout << "*";
}

bool log_in(string username, string password) {
	return true;
}

int main() {
	sign_up();











	return 0;
}