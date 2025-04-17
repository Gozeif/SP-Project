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
	char ch = _getch(); // Hide password input
	while (ch != 13) { // Enter key is pressed
		password.push_back(ch);
		cout << "*";
		ch = _getch();
	}
	cout << endl << password;
}

bool log_in(string username, string password) {
	return true;
}

int main() {
	sign_up();











	return 0;
}