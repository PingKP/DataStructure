// 11227154 辛宇平

#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <sstream>  
#include <fstream>
#include <math.h>
using namespace std;

// ## unfinished function ##

// *******************************************************************************
// Declaration of Class & Function  
// (use Ctrl+F search "::functionName" to find implementation of function quickly)
// *******************************************************************************

class sData{
    char *sid;
    char *sname;
    unsigned char score[6];
    float average;
  public:
    sData();
    sData(stringstream &inputLine);
    void read(stringstream &inputLine);
    void writeBin(ofstream &outputFile);
};


class cmdRunner {
    vector<sData*> sDatas;
    bool readBin(string fileCode);
    bool readTxtToBin(string fileCode);
  public:
    bool read();
};

// *******************************************************************************
// Main Function
// *******************************************************************************

int main(void) {
    string command;
    cmdRunner controller;
    do
    {   cout << endl << "******** Hash Table *****";
        cout << endl << "* 0. QUIT               *";
        cout << endl << "* 1. Linear probing     *";
        cout << endl << "* 2. Double hashing     *";
        cout << endl << "*************************";
        cout << endl << "Input a choice(0, 1, 2): ";
        cin >> command;                  				
        if (command == "1")	{
            if (controller.read())
                cout << "hello\n";
        }     
        else if (command == "2") {
            if (controller.read())
                cout << "hello\n";
            
        }
        else if (command != "0")
            cout << endl << "Command does not exist!" << endl;
    } while (command != "0");
    return 0;
}

// *******************************************************************************
// Implementation of Function
// (functions below aren't arranged by declaration sequence)
// *******************************************************************************

// cmdRunner (Command Execute)

bool cmdRunner::read() {
    string fileCode;
    do {
        cout << "\nInput a file number ([0] Quit): ";
        cin >> fileCode;
        if (fileCode == "0")
            return false;
        if (!readBin(fileCode)) {
            if (readTxtToBin(fileCode)) {
                readBin(fileCode);
                return true;
            }
        }
    } while (fileCode != "0");
    return false;
}

bool cmdRunner::readBin(string fileCode) {
    string inputFileName = "input" + fileCode + ".bin";
    ifstream inputFile;
    inputFile.open(inputFileName, ios_base::binary);
    if (inputFile.is_open()) {
        
        // ## unfinished function ##
        // read data function here

        return true;
    }

    cout << "\n### " << inputFileName << " does not exist! ###\n";
    return false;
}

bool cmdRunner::readTxtToBin(string fileCode) {
    string inputFileName = "input" + fileCode ;
    ifstream txtFile;
    txtFile.open(inputFileName + ".txt");

    if (txtFile.is_open()) {
        string temp;
        stringstream inputLine;
        sData tempData;
        ofstream binFile;
        binFile.open(inputFileName + ".bin", ios_base::binary | ios_base::trunc);
        while (getline(txtFile, temp)) {
            inputLine.clear();
            inputLine << temp;
            tempData.read(inputLine);
            tempData.writeBin(binFile);
        }
        
        cout << "\n---" << inputFileName + ".bin" << " has been created ---\n";
        return true;
    }

    cout << "\n### " << inputFileName << " does not exist! ###\n";
    return false;
}

// sData

sData::sData() {
    sid = new char[10];
    sname = new char[10];
}


sData::sData(stringstream &inputLine) {
    sid = new char[10];
    sname = new char[10];
    read(inputLine);
}

void sData::read(stringstream &inputLine) {
    string temp;
    int tempNum;

    getline(inputLine, temp, '\t');
    strcpy(sid, temp.data());
    
    getline(inputLine, temp, '\t');
    strcpy(sname, temp.data());

    for (int i = 0; i < 6; i++) {
        getline(inputLine, temp, '\t');
        tempNum = stoi(temp);
        score[i] = (unsigned char)tempNum;
    }
    getline(inputLine, temp, '\t');
    average = stof(temp);
}

void sData::writeBin(ofstream &outputFile) {
    outputFile.write(sid, sizeof(sid));
    outputFile << '\t';
    outputFile.write(sname, sizeof(sname));
    outputFile << '\t';
    for (int i = 0; i < 6; i++) {
        outputFile << score[i];
        outputFile << '\t';
    }
    outputFile << average << '\n';
}