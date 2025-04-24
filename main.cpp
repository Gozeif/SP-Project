#include <iostream>
#include <fstream>
#include <string>
#include <sstream> // For stringstream
#include <conio.h> // For _getch()
#include <algorithm> // For transform()

using namespace std;

fstream credentials;

struct user {
	string username = "";
	string password = "";
	int id = 0;
}current_user_info;


const int MAX_USERS = 101;
user users[MAX_USERS]{};


void load_user_db() {
	string user_data[3];
	credentials.open("credentials.txt", ios::in);
	if (!credentials.is_open()) {
		cout << "Error: Unable to open credentials file." << endl;
	}
	string temp_user_arr[MAX_USERS];
	for (int i = 0; i < MAX_USERS && credentials.good(); i++) {
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
		for (int i = 0; i < MAX_USERS; i++) {
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
	cout << username << endl;

	bool invalid_password = true;
	while (invalid_password) {
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
	cout << "Confirm Password: ";

	for (int i = 1; i < MAX_USERS; i++) {
		if (users[i].username.empty()) {
			users[i].username = username;
			users[i].password = password;
			users[i].id = i;
			current_user_info.id = users[i].id;
			break;
		}
		else if (i == MAX_USERS - 1) {
			cout << "Error: User limit reached." << endl;
			return;
		}
	}
	current_user_info.username = username;
	current_user_info.password = password;
}

void log_in() {
	string username, password;
	int user_id;
	bool valid_username = false;
	cout << "Username: ";
	do	{
		cin >> username;
		// Check if username actually exists
		for (int i = 0; i < MAX_USERS; i++) {
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
		cout << "Welcome, " << users[user_id].username << "!" << endl;
		current_user_info.username = users[user_id].username;
		current_user_info.id = users[user_id].id;
		return;
	}
	else {
		cout << "\nIncorrect password." << endl;
		return;
	}
}

void log_out() {
	cout << "Logging out..." << endl;
	current_user_info.username = "";
	current_user_info.id = 0;
}

void save() {
	credentials.open("credentials.txt", ios::out | ios::in);
	credentials.seekg(0, ios::beg); // Move to the beginning of the file
	char ch;
	for (int i = 1; i < MAX_USERS && users[i].id != 0; i++) {
		do
		{
			ch = credentials.get(); // Read character by character
			credentials.seekg(1, ios::cur);
		} while (ch != '\n' && not credentials.eof());
		string line;
		streampos pos = credentials.tellg();
		getline(credentials, line);
		if (line[0] != '[' && line[0] != ']') { // Skip the line if it starts with '[' or ']'
			credentials.seekp(pos); // Move back to the previous position
			credentials << users[i].id << "," << users[i].username << "," << users[i].password << endl;
		}
		/*if (users[i+1].id == 0) {
			break;
		}*/
		credentials.seekg(pos);
	}
}

int main() {
	load_user_db();
	sign_up();
	save();
	return 0;
}