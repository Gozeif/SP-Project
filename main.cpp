#include "authentication.h"

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