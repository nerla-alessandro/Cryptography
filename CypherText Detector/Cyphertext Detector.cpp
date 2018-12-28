#include <iostream>
#include <fstream>
#include <list>
#include <cstdlib>
#include <stdio.h>
#include <string.h>
#include <math.h>

using namespace std;

int totChar;
const char alphabet[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
const float engFreq[26] = {8.167, 1.492, 2.782, 4.253, 12.702, 2.228, 2.015, 6.094, 6.966, 0.153, 0.772, 4.025, 2.406, 6.749, 7.507, 1.929, 0.095, 5.987, 6.327, 9.056, 2.758, 0.978, 2.360, 0.150, 1.974, 0.074};
float txtFreq[26];
char fName[64];
char c;
bool plnTxtFlag;
int trsh;

float absf(float n);
bool isEqualish(char a, char b);
void getFreq();
void normFreq();
void checkFreq();
void getTreshold();

int main()
{
    plnTxtFlag = true;
    getTreshold();
    getFreq();
    normFreq();
    checkFreq();
    cout << endl << (plnTxtFlag? "The file is in Plaintext":"The file is cyphered") << endl;
}

bool isEqualish(char a, char b){
    if(a == b || (int)(a) == (int)(b+32) || (int)a == (int)(b-32))
        return true;
    return false;
}

float absf(float n){
    if(n<0)
        n+=(n*-2);
    return n;
}

void getFreq(){
    cout << "Write name of Key File:  ";
    cin>>fName;
    strcat(fName, ".txt");
    ifstream txtFile(fName);
    if(txtFile.is_open()){
        while(txtFile.get(c)){
            for(int i=0; i<26; i++)
                if(isEqualish(c, alphabet[i])){
                    txtFreq[i]++;
                    totChar++;
                }
        }
        txtFile.close();
    }
    else
        cout << "Could not open File" << endl;
    cout << endl;
}

void normFreq(){
    for(int i=0; i<26; i++){
        cout << alphabet[i] << ": " << txtFreq[i] << endl;
        txtFreq[i]=(txtFreq[i]/totChar);
        txtFreq[i]*=100;
    }
    cout << endl << "Total: " << totChar << endl << endl << endl;
}

void checkFreq(){
    float t;
    float deltaFreq;
    cout <<  "Letter: English Frequency - Text Frequency" << endl << endl;
    for(int i=0; i<26; i++){
        t = (txtFreq[i]-engFreq[i]);
        t = absf(t);
        cout <<  alphabet[i] << ": " << engFreq[i] << " - " << txtFreq[i] << endl;
        deltaFreq+=t;
        if(deltaFreq>trsh)
            plnTxtFlag=false;
    }
    cout << endl << endl << "Frequency Deviation: "<< deltaFreq << " - Treshold: " << trsh << endl;
}

void getTreshold(){
    cout << "The lower the value, the more the program has to be sure it is Plaintext" << endl << endl;
    cout << "WARNING:" << endl;
    cout << " - The program only accepts .txt files" << endl;
    cout << " - It is not advised to exceed the 20/60 range" << endl;
    cout << " - The program is made to detect english text" << endl;
    cout << " - It may not work with other languages" << endl << endl;
    cout << "Enter Plaintext treshold [20 - High / 45 - Low]:  ";
    cin >> trsh;
    cout << endl;
}
