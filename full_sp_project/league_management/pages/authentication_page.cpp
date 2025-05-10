#pragma once
#include <iostream>
#include "structs.cpp"
#include "navigation.cpp"


void viewAuthenticationPage(){
    cout << "1.Login\n2.Signup\n3.Exit\nPick choice: ";
    
}

void authenticationPageInput(){
    int choice;
    cin >> choice;
    // cout << "DDDUDUDUDU" << endl;
    if(choice == 1){

        stck.push(LOGIN_PAGE);
    }
    else if(choice == 2){
        stck.push(SIGNUP_PAGE);
    }
    else if(choice == 3){
        stck.push(EXIT);
    }
}