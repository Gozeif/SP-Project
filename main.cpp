#include <iostream>
#include <fstream>
#include <string>
#include <sstream> // For stringstream,  
#include <conio.h> // For _getch(), hide password input
#include <algorithm> // For transform(), convert string to uppercase for case-insensitive username comparison
using namespace std;

fstream credentials;

const int MAX_USERS = 101;
int save_index = 1; // Int to track what index to save new users to


struct user {
	string username = "";
	string password = "";
	int id = 0;
}current_user_info;
user users[MAX_USERS]{};


void load_user_db() {
	string user_data[3];
	credentials.open("credentials.txt", ios::in);
	if (!credentials.is_open()) {
		cout << "Error: Unable to open credentials file." << endl;
	}
	string temp_user_arr[MAX_USERS];
	for (int i = 1; i < MAX_USERS && credentials.good(); i++) {
		getline(credentials, temp_user_arr[i]);
		if (temp_user_arr[i].empty()) {
			break;
		}
		stringstream ss(temp_user_arr[i]); // Create a stringstream object to parse the line
		for (int j = 0; j < 3; j++) {
			getline(ss, user_data[j], ','); // Split username, password and id
		}

		// Store the data in the user struct
		users[i].username = user_data[1];
		users[i].password = user_data[2];
		if (!user_data[0].empty()) {
			users[i].id = stoi(user_data[0]); // Converts string to int
		}
		else {
			cout << "Error: User without id found in database" << endl; // Handle the error, e.g., log it or skip this entry
			cout << "Assigned new id: " << i+1 << endl;
			users[i].id = i + 1;
		}
		save_index = i + 1; // Update save_index to the first new signup index
	}
	credentials.close();
}

void sign_up() {
	string username, password;
	bool valid_username = true;
	cout << "Username: ";
	do  // Loop until a valid username is entered
	{
		cin >> username;
		if (username.find(',') != -1) {
			cout << "Username cannot contain commas. Please pick a different username." << endl;
			valid_username = false;
			continue;
		}
		// Check if username already exists
		for (int i = 1; i < MAX_USERS; i++) {
			string x = users[i].username;
			transform(x.begin(), x.end(), x.begin(), ::toupper); // Convert to uppercase for case-insensitive comparison
			string s = username;
			transform(s.begin(), s.end(), s.begin(), ::toupper);
			if (x == s) {
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

	bool invalid_password = true;
	while (invalid_password) {
		cout << "Password: ";
		char ch = _getch(); // Hide password input
		while (ch != 13) { // Enter key is pressed
			if (ch == 8) { // Backspace key is pressed
				if (!password.empty()) {
					password.pop_back();
					cout << "\b \b"; // Erase the last character
				}
			}
			else {
				password.push_back(ch);
				cout << "*"; // Print asterisk for each character
			}
			ch = _getch();
		}
		if (password.find(',') != -1) {
			cout << "\nPassword cannot contain commas. Please pick a different password." << endl;
			password.clear();
		}
		else if (password.length() < 8) {
			cout << "\nPassword must be at least 8 characters long. Please pick a different password." << endl;
			password.clear();
		}
		else if (password.find(username) != string::npos) {
			cout << "\nPassword cannot contain the username. Please pick a different password." << endl;
			password.clear();
		}
		else {
			invalid_password = false;
		}
	}
	cout << "\nPassword accepted." << endl;

	for (int i = 1; i < MAX_USERS; i++) {
		if (users[i].username.empty()) {
			users[i].username = username;
			users[i].password = password;
			users[i].id = i;
			break;
		}
		else if (i == MAX_USERS - 1) {
			cout << "Error: User limit reached." << endl;
			return;
		}
	}
	cout << "New user created: " << username << endl;
}

void log_in() {
	string username, password;
	int user_id;
	bool valid_username = false;
	cout << "Username: ";
	do	{
		cin >> username;
		// Check if username actually exists
		for (int i = 1; i < MAX_USERS; i++) {
			string x = users[i].username;
			transform(x.begin(), x.end(), x.begin(), ::toupper); // Convert to uppercase for case-insensitive comparison
			string s = username;
			transform(s.begin(), s.end(), s.begin(), ::toupper);
			// Search if the input matches a username in the database
			if (x == s) {
				current_user_info.id = users[i].id;
				valid_username = true;
				user_id = users[i].id; // Store the index of the found user
				break;
			}
			else
			{
				valid_username = false;
			}
			if (users[i].username.empty()) {
				break; // Stop searching if an empty username is found
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
		current_user_info.username = users[user_id].username;
		current_user_info.id = users[user_id].id;
		cout << "\nLogin successful!" << endl;
		cout << "Welcome, " << current_user_info.username << "!" << endl;
	}
	else {
		cout << "\nIncorrect password." << endl;
	}
}

void log_out() {
	cout << "Logging out..." << endl;
	current_user_info.username = "";
	current_user_info.id = 0;
}

void save() {
	credentials.open("credentials.txt", ios::app);
	if (!credentials.is_open()) {
		cout << "Error: Unable to open credentials file." << endl;
	}
	for (int i = 0; i < MAX_USERS; i++) {
		if (users[save_index + i].id == 0) {
			break; // Stop saving if an empty username is found
		}
		credentials << users[save_index + i].id << "," << users[save_index + i].username << "," << users[save_index + i].password << endl;
	}
	credentials.close();
}

int main() {
	load_user_db();
	sign_up();
	cout << "Log-in" << endl;
	log_in();
	cout << "Current user: " << current_user_info.username << endl;
	log_out();
	cout << "Current user: " << current_user_info.username << endl;
	cout << "Saving user data..." << endl;
	save();
	cout << "User data saved." << endl;
	return 0;
}