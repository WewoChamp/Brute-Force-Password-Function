#include <iostream>
#include <string>
#include <limits>
#include <cmath>

const int UPPER = 126; //Upper limit of the ASCII characters
const int LOWER = 32; //Lower limit of the ASCII characters

using namespace std;

//Brute Forcing Function To Try All Possible Passwords that are numOfChars long
string bruteForcer(int numOfChars){
    if(numOfChars == 0){
        return "";
    }else{
        static int storage[100][2] = { [0 ... 99] = {LOWER - 1, 1} }; //Storage for the current character and trackers to see when to increment characters at the different positions in the password
        if((storage[numOfChars - 1][0] /*The current character at that position*/ < 126) && (storage[numOfChars - 1][1]/*The tracker at that position to see if the character should be incremented*/ >= pow((UPPER - (LOWER - 1)), (numOfChars-1)))){
            storage[numOfChars - 1][0]++;
            storage[numOfChars - 1][1] = 1;
        }else if((storage[numOfChars - 1][0] >= 126) && (storage[numOfChars - 1][1] >= pow((UPPER - (LOWER - 1)), (numOfChars-1)))){
            storage[numOfChars - 1][0] = LOWER;
            storage[numOfChars - 1][1] = 1;
        }else{
            storage[numOfChars - 1][1]++;
        }
        string currPasswordString(1, (char)storage[numOfChars - 1][0]);
        currPasswordString += bruteForcer(numOfChars - 1);
        return currPasswordString;
    }
}

//Main program just simulating a log in system
int main(){
    string passwordString;
    cout << "Set a password: " << endl;
    getline(cin, passwordString);
    
    char * password = &passwordString[0];

    string trialPasswordString;
    char * trialPassword;

    bool match = false;
    bool manRetry = true;
    int tries = 0;
    while(!match){
        if(manRetry){
            cout << "Enter the password you set: " << endl;
            getline(cin, trialPasswordString);
            trialPassword = &trialPasswordString[0];

            match = true;
            int i = 0;
            while(*(password + i) != '\0'){
                if ((*(password + i) != *(trialPassword + i))){
                    match = false;
                    break;
                }
                i++;
            }

            if(*(trialPassword + i) != '\0'){
                match = false;
            }

            if (match){
                cout << "Successful Log in" << endl;
            }else{
                cout << "Incorrect Password" << endl;
                string ans = "to";
                while(ans.length() != 1 || (ans[0] != 'y' && ans[0] != 'n')){
                    cout << "Do you want to brute force? (y/n): " << endl;
                    getline(cin, ans);
                }
                (ans[0] == 'n')? manRetry = true : manRetry = false;
            }
        }else{
            ++tries; //Just to keep track of the number of tries could easily have been implemented in the bruteForcer function
            trialPasswordString = bruteForcer(3); //Trying all possible 4 character passwords, everytime function is called it generates the next password trial
            trialPassword = &trialPasswordString[0];
            cout << "Trying password: " << trialPasswordString << endl;

            match = true;
            int i = 0;
            while(*(password + i) != '\0'){
                if ((*(password + i) != *(trialPassword + i))){
                    match = false;
                    break;
                }
                i++;
            }

            if(*(trialPassword + i) != '\0'){
                match = false;
            }

            if (match){
                cout << "Successful Log in" << endl;
                cout << "Number of attempts: " << tries << endl;
            }else{
                cout << "Incorrect Password" << endl;
            }
        }
    }
    return 0;
}