#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <cstdlib>
#include <list>
using namespace std;

list<char> keyList;
char t;
string input;
char choice;
char fName[1024];

void writeData();
void readData();
bool readKey(char n[]);
void createKeyFile();
char generateRandomChar();
char encode(char a, char b);
char decode(char a, char b);
void updateKeyFile();
int filesize(ofstream);

int main () {

        bool exitFlag=false;

        do{
        cout << "Menu: " << endl << endl;
        cout << "   1: Encrypt" << endl << endl;
        cout << "   2: Decrypt" << endl << endl;
        cout << "   3: Create new Key File" << endl << endl;
        cout << "   4: Exit" << endl << endl;

        cin >> choice;
        cout << endl;

        switch(choice){

        //Encrypt
        case '1' :
        writeData();
        break;

        //Decrypt
        case '2':
        readData();
        break;

        //New Key File
        case '3':
        createKeyFile();
        break;

        //Exit
        case '4':
        exitFlag=true;
        break;
        }

        choice=getchar();

    }while(!exitFlag);
    return 0;
}

void writeData(){
    ofstream dataFile ("Cyphertext.txt", ios::app);
    if (dataFile.is_open()){
        cout << "Write name of Key File:  ";
        cin>>fName;
        strcat(fName, ".txt");
        if(readKey(fName)){
            unsigned int tSize = keyList.size();
            cout<< endl << endl;
            cout << "Write 'ENDFILE' to exit write mode" << endl;
            cout << "Write the text to encode below:" << endl << endl;
            do{
                cin >> input;
                if(input.compare("ENDFILE")==0)
                    break;
                for(unsigned int i=0; i<input.length();i++){
                    t = keyList.front();
                    keyList.pop_front();
                    input[i] = encode(input[i], t);
                }
                if(tSize >= input.length())
                    dataFile << input;
                else{
                    cout << endl << "ERROR: End of Key File - Could not encode" << endl << endl;
                    break;
                }
                t = keyList.front();
                keyList.pop_front();
                dataFile << encode(' ', t);
            }while(1);
            dataFile.close();
            updateKeyFile();
        }
    }
    else cout << "Unable to open file";
}

void readData(){
    ifstream dataFile("Cyphertext.txt");
    ofstream plainFile("Plaintext.txt", ios::app);
    char c;
    if(dataFile.is_open()){
        cout << "Write name of Key File:  ";
        cin>>fName;
        strcat(fName, ".txt");
        if(readKey(fName)){
            cout<< endl << endl;
            cout << "Decoded Text:  ";
            while(dataFile.get(c)){
                t = keyList.front();
                keyList.pop_front();
                if(keyList.size() >= 0)
                    c = decode(c, t);
                else{
                    cout << endl << "ERROR: End of Key File - Could not decode" << endl << endl;
                    break;
                }
                plainFile << c;
                cout << c;
            }
            plainFile << endl;
            updateKeyFile();
            dataFile.close();
            ofstream dataFile("Cyphertext.txt", ios::trunc);
            dataFile.close();
            plainFile.close();
        }
    }
    else cout << "Unable to open file";
}


bool readKey(char n[]){
    ifstream keyFile(n);
    if(keyFile.is_open()){
        char c;
        while(keyFile.get(c))
            keyList.push_back(c);
        keyFile.close();
        return true;
    }
    else
        cout << endl << "No Key File found" << endl << endl;
    keyFile.close();
    return false;
}


void createKeyFile(){
    cout << "Insert ID of Key File to create:  ";
    cin >> fName;
    cout << endl << endl;
    strcat(fName, ".txt");
    ofstream keyFile (fName, ios::app);
    cout << "Insert length of Key File to create:  ";
    unsigned long int itmp;
    cin >> itmp;
    cout << endl << endl;
    srand(time(NULL));
    for(unsigned long int i=0; i<itmp; i++){
        keyFile << generateRandomChar();
    }


}

char generateRandomChar(){
    int t = rand() % 95 + 32;
    return (char)t;
}

char encode(char a, char b){
    for (int i = 0; i < (int)(b-32); i++){
        if (a == '~'){
            a = ' ';
        }
        else {
            a++;
        }
    }
    return a;
}

char decode(char a, char b){
    for (int i = 0; i < (int)(b-32); i++){
        if (a == ' '){
            a = '~';
        }
        else {
            a--;
        }
    }
    return a;
}

void updateKeyFile(){
    ofstream dataFile(fName, ios::trunc);
    do{
        dataFile << keyList.front();
        keyList.pop_front();
    }while(keyList.size()>0);
}

