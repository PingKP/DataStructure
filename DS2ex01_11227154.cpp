// 11227154 辛宇平

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
using namespace std;

// *******************************************************************************
// Declaration of Class & Function  
// (use Ctrl+F search "::functionName" to find implementation of function quickly)
// *******************************************************************************

bool isDigit(string &str);

class SchoolData{
    int num;
    string schoolNumber;
    string schoolName;
    string departmentNumber;
    string departmentName;
    string timeSlots;
    string degree;
    string students;
    string teachers;
    string graduates;
    string locatedCity;
    string type;
  public:
    SchoolData(int num, stringstream &inputString);
    void print();
    int returnNum();
    int returnGraduated();
    int returnStudents();
};


class SchoolList {
    vector<SchoolData*> list;
  public:
    SchoolList();
    void read(ifstream &inputFile);
    SchoolData* returnData(int position);
    void print();
    bool isEmpty();
    int size();
    void clear();
};


class Node {
  public:
    SchoolData* storedData;
    int value;
    Node(int value, SchoolData* newData);
};


class Heap {
    vector<Node*> array;
  public:
    void add(int value, SchoolData* newData);
    bool isEmpty();
    void swapNode(int positionA, int positionB);
    int returnValue(int position);
    Node* returnRoot();
    Node* returnBottom();
    Node* returnLeftmostBottom();
    void maxHeapify(int startPosition);
    void minHeapify(int startPosition);
    void maxMinHeapify(int startPosition);
    void minMaxHeapify(int startPosition);
    void clear();
    void showAll();     //print all node in the array (for debug)
};


class CommandExecuter {
    SchoolList dataStorage;
    Heap maxHeap;
    Heap minMaxHeap;
    void showResult(Heap &theHeap);
  public:
    bool read();
    void buildMaxHeap();
    void buildMinMaxHeap();
   
};

// *******************************************************************************
// Main Function
// *******************************************************************************

int main(void) {
    string command;
    CommandExecuter controller;
    do
    {   cout << endl << "**** Heap Construction *****";
        cout << endl << "* 0. QUIT                  *";
        cout << endl << "* 1. Build a max heap      *";
        cout << endl << "* 2. Build a min-max heap  *";
        cout << endl << "****************************";
        cout << endl << "Input a choice(0, 1, 2): ";
        cin >> command;                  				
        if (command == "1")	{
            if (controller.read())
                controller.buildMaxHeap();  
        }     
        else if (command == "2") {
            if (controller.read()) 
                controller.buildMinMaxHeap();
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


// SchoolData *********************************************************************

SchoolData::SchoolData(int num, stringstream &inputString) {
    this->num = num;
    getline(inputString, this->schoolNumber, '\t');
    getline(inputString, this->schoolName, '\t');
    getline(inputString, this->departmentNumber, '\t');
    getline(inputString, this->departmentName, '\t');
    getline(inputString, this->timeSlots, '\t');
    getline(inputString, this->degree, '\t');
    getline(inputString, this->students, '\t');
    getline(inputString, this->teachers, '\t');
    getline(inputString, this->graduates, '\t');
    getline(inputString, this->locatedCity, '\t');
    getline(inputString, this->type, '\t');
}

void SchoolData::print() {
    cout << "[" << num << "] ";
    cout << schoolNumber << "\t" << schoolName;
    cout << "\t" << departmentNumber << "\t" << departmentName;
    cout << "\t" << timeSlots << "\t" << degree;
    cout << "\t" << students << "\t" << teachers << "\t" << graduates;
    cout << "\t" << locatedCity << "\t" << type << endl;
}

int SchoolData::returnGraduated() {
    if (isDigit(this->graduates))
        return stoi(this->graduates);
    return 0;
}

int SchoolData::returnStudents() {
    if (isDigit(this->students))
        return stoi(this->students);
    return 0;
}

int SchoolData::returnNum() {
    return this->num;
}

// SchoolList **********************************************************************

SchoolList::SchoolList() {
    this->list.resize(0);
    return;
}

void SchoolList::read(ifstream &inputFile) {
    string temp;
    stringstream inputString;
    getline(inputFile, temp);
    getline(inputFile, temp);
    getline(inputFile, temp);
    for (int num = 1;getline(inputFile, temp); num++) {
        inputString.clear();
        inputString << temp;
        SchoolData *newData = new SchoolData(num, inputString);
        this->list.push_back(newData);
    }
    return;
}

void SchoolList::print() {
    for (int i= 0;i < list.size(); i++) {
        list[i]->print();
    }
    return;
}


bool SchoolList::isEmpty() {
    if (this->list.empty())
        return true;
    return false;
}

SchoolData* SchoolList::returnData(int position) {
    return this->list.at(position);
}

int SchoolList::size() {
    return this->list.size();
}

void SchoolList::clear() {
    this->list.clear();
}

// Node ****************************************************************************

Node::Node(int value, SchoolData* newData) {
    this->storedData = newData;
    this->value = value;
    return;
}


// Heap ***************************************************************************

void Heap::add(int value, SchoolData* newData) {
    Node* newNode = new Node(value, newData);
    this->array.push_back(newNode);
    return;
}

bool Heap::isEmpty() {
    if (this->array.empty())
        return true;
    return false;
}

Node* Heap::returnRoot() {
    if (this->array.empty())
        return nullptr;
    return this->array.at(0);
}

Node* Heap::returnBottom() {
    if (this->array.empty())
        return nullptr;
    return this->array.at(this->array.size()-1);
}

Node* Heap::returnLeftmostBottom() {
    if (this->array.empty())
        return nullptr;
    for (int position = 0;position < this->array.size();position = position*2 + 1)
        if ((position*2 + 1) >= this->array.size())
            return this->array.at(position);
    return nullptr;
}

void Heap::swapNode(int positionA, int positionB) {
    Node* tempNode = this->array.at(positionA);
    this->array.at(positionA) = this->array.at(positionB);
    this->array.at(positionB) = tempNode;
    return;
}

int Heap::returnValue(int position) {
    return this->array.at(position)->value;
}

void Heap::clear() {
    this->array.clear();
}

// using recrusion?
void Heap::maxHeapify(int startPosition) {
    if (startPosition >= this->array.size())
        return;
    int left = startPosition*2 + 1;
    int right = left + 1;
    if (left >= this->array.size())     // if current node has no left Node && no right node
        return;                         // mean it's a leaf
    maxHeapify(left);
    maxHeapify(right);

    int largestPosition = startPosition;
    if (returnValue(largestPosition) < returnValue(left)) {
            largestPosition = left;
    }
        
    if (right < this->array.size() && returnValue(largestPosition) < returnValue(right)) {
            largestPosition = right;
    }
    if (largestPosition != startPosition) {
        swapNode(largestPosition, startPosition);
        maxHeapify(largestPosition);
    }
        
    return;
}

void Heap::minHeapify(int startPosition) {
    if (startPosition >= this->array.size())
        return;
    int left = startPosition*2 + 1;
    int right = left + 1;
    if (left >= this->array.size())     // if current node has no left Node && no right node
        return;                         // mean it's a leaf
    minHeapify(left);
    minHeapify(right);

    int smallestPosition = startPosition;
    if (returnValue(smallestPosition) > returnValue(left)) {
            smallestPosition = left;
    }
    if (right < this->array.size() && returnValue(smallestPosition) > returnValue(right)) {
        smallestPosition = right;
    }
    if (smallestPosition != startPosition) {
        swapNode(smallestPosition, startPosition);
        minHeapify(smallestPosition);
    }
        
    return;
}

void Heap::maxMinHeapify(int startPosition) {
    if (startPosition >= this->array.size())
        return;
    int left = startPosition*2 + 1;
    int right = left + 1;
    maxHeapify(startPosition);
    minMaxHeapify(left);
    minMaxHeapify(right);
    return;
}

void Heap::minMaxHeapify(int startPosition) {
    if (startPosition >= this->array.size())
        return;
    int left = startPosition*2 + 1;
    int right = left + 1;
    minHeapify(startPosition);
    maxMinHeapify(left);
    maxMinHeapify(right);
    return;
}

void Heap::showAll() {
    ofstream outputFile;
    outputFile.open("debug.txt", ofstream::trunc);
    for (int i = 0; i < this->array.size(); i++) {
       outputFile << "[" << array[i]->storedData->returnNum() << "] " << array[i]->value << endl;
    }
}

// CommandExecuter *******************************************************************

bool CommandExecuter::read() {
    string fileCode;
    do {
        cout << "\nInput a file number ([0] Quit): ";
        cin >> fileCode;
        if (fileCode == "0")
            return false;
        string inputFileName = "input" + fileCode + ".txt";
        ifstream inputFile;
        inputFile.open(inputFileName);
        if (inputFile.is_open()) {
            this->dataStorage.clear();
            dataStorage.read(inputFile);
            return true;
        }
        else
            cout << "\n### " << inputFileName << " does not exist! ###\n";
    } while (fileCode != "0");
    return false;
}

void CommandExecuter::buildMaxHeap() {
    maxHeap.clear();
    SchoolData* dataPtr;
    for (int i = 0;i < dataStorage.size();i++) {
        dataPtr = dataStorage.returnData(i);
        maxHeap.add(dataPtr->returnGraduated() ,dataPtr);
        maxHeap.maxHeapify(0);
    }

    cout << "<max heap>" << endl;
    showResult(maxHeap);
    // maxHeap.showAll();
}

void CommandExecuter::buildMinMaxHeap() {
    minMaxHeap.clear();
    SchoolData* dataPtr;
    for (int i = 0;i < dataStorage.size();i++) {
        dataPtr = dataStorage.returnData(i);
        minMaxHeap.add(dataPtr->returnStudents() ,dataPtr);
        minMaxHeap.minMaxHeapify(0);
    }

    cout << "<min-max heap>" << endl;
    showResult(minMaxHeap);
    // minMaxHeap.showAll();
}

void CommandExecuter::showResult(Heap &theHeap) {
    Node* root = theHeap.returnRoot();
    Node* bottom = theHeap.returnBottom();
    Node* leftmostBottom = theHeap.returnLeftmostBottom();
    
    
    cout << "root: [" << root->storedData->returnNum() << "] " << root->value << endl;
    cout << "bottom: [" << bottom->storedData->returnNum() << "] " << bottom->value << endl;
    cout << "leftmost bottom: [" << leftmostBottom->storedData->returnNum() << "] " << leftmostBottom->value << endl;

}

bool isDigit(string &str) {
    for (int i = 0; i < str.size(); i++)
        if (str[i] < '0' || str[i] > '9')  
            return false;
    return true;
}