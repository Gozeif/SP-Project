#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <conio.h>

using namespace std;

struct user {
	string username;
	string password;
	int id;
};

user users[100]{};

void load_user_db() {
	string user_data[3];
	ifstream credentials("credentials.txt");
	if (!credentials.is_open()) {
		cout << "Error: Unable to open credentials file." << endl;
	}

	string temp_user_arr[100];
	for (int i = 0; i < 100 && credentials.good(); i++) {
		getline(credentials, temp_user_arr[i], '\n');
		if (temp_user_arr[i].empty()) {
			break;
		}
		else if (temp_user_arr[i][0] == '[')
		{
			continue;
		}
		stringstream ss(temp_user_arr[i]);
		for (int j = 0; j < 3; j++) {
			getline(ss, user_data[i], '@'); // Split username, password and id
		}

		// Store the data in the user struct
		users[i].username = user_data[0];
		users[i].password = user_data[1];
		users[i].id = stoi(user_data[2]); // Converts string to int
	}
}

void sign_up() {
	string username, password;
	bool valid_username = true;
	cout << "Username: ";
	do  // Loop until a valid username is entered
	{
		cin >> username;
		if (username.find(',') || username.find('[') || username.find(']')) {
			cout << "Username cannot contain commas or square brackets. Please try again." << endl;
			valid_username = false;
			continue;
		}
		// Check if username already exists
		for (int i = 0; i < 100; i++) {
			if (users[i].username == username) {
				cout << "Username already exists. Please choose another one." << endl;
				valid_username = false;
				break;
			}
			else
			{
				valid_username = true;
			}
		}

	} while (!valid_username);
	

	cout << "Password: ";
	char ch = _getch(); // Hide password input
	while (ch != 13) { // Enter key is pressed
		if (ch == 8) { // Backspace key is pressed
			password.pop_back();
			cout << "\b \b"; // Erase the last character
		}
		else {
			password.push_back(ch);
			cout << "*"; // Print asterisk for each character
		}
		ch = _getch();
	}
	for (int i = 0; i < 100; i++) {
		if (users[i].username.empty()) {
			users[i].username = username;
			users[i].password = password;
			users[i].id = i;
			break;
		}
		else if (i == 100) {
			cout << "Error: User limit reached." << endl;
			return;
		}
	}
	//this should be refactored into save()
	// 
	// 
	//ofstream file("credentials.txt", ios::app); // Open file in append mode
	//if (file.is_open()) {
	//	file << username << "@" << password << endl;
	//	file.close();
	//}
	//else {
	//	cout << "Error: Unable to open file." << endl;
	//}
}

void log_in() {
	string username, password;
	int user_id;
	bool valid_username = false;
	cout << "Username: ";
	do	{
		cin >> username;
		// Check if username actually exists
		for (int i = 0; i < 100; i++) {
			if (users[i].username == username) {
				user_id = users[i].id;
				valid_username = true;
				break;
			}
			else
			{
				valid_username = false;
			}
		}
		if (!valid_username) {
			cout << "Username not found. Please try again." << endl;
		}
	} while (!valid_username);

	cout << "Password: ";
	char ch = _getch(); // Hide password input

	while (ch == 13) { // Enter key is pressed
		cout << endl << "Please enter your password." << endl;
		ch = _getch();
	}
	while (ch != 13) {
		if (ch == 8) { // Backspace key is pressed
			password.pop_back();
			cout << "\b \b"; // Erase the last character
		}
		else {
			password.push_back(ch);
			cout << "*"; // Print asterisk for each character
		}
		ch = _getch();
	}
	if (users[user_id].password == password) {
		cout << "\nLogin successful!" << endl;
		return;
	}
	else {
		cout << "\nIncorrect password." << endl;
		return;
	}
}
void log_out() {

}
int main() {
	load_user_db();
	sign_up();
	return 0;
}