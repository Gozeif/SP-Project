#include <iostream>
#include <fstream>
#include <string>

using namespace std;
const int MAX_USERS =100;
struct user 
{
string username ;
string password ;
};

user users = [MAX_USERS];
int usercount = 0;

void sign_up (){
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

    users[userCount].username = username;
    users[userCount].password = password;
    userCount++;

    cout << "Sign up successful!\n";
}

int main() {












	return 0
}
