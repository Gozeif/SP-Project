#include <iostream>
#include <string>

using namespace std;
const int MAX_USERS =100;
struct user 
{
string username ;
string password ;
};

user users[MAX_USERS];
int usercount = 0;

void sign_up (){
    string username, password;
    cout << "Enter new username: ";
    cin >> username;


    for (int i = 0; i < usercount; i++) {
        if (users[i].username == username) {
            cout << "Username already exists!\n";
            return;
        }
    }

    cout << "Enter new password: ";
    cin >> password;

    users[usercount].username = username;
    users[usercount].password = password;
    usercount++;

    cout << "Sign up successful!\n";
}

int main() {


sign_up ();









	return 0;
}
