// 11227154 辛宇平

#include <iostream>
#include <string>
#include <vector>
#include <sstream>  // for string separating
#include <fstream>  // for file reading
#include <math.h>   // for log2()
using namespace std;

// *******************************************************************************
// Declaration of Class & Function  
// (use Ctrl+F search "::functionName" to find implementation of function quickly)
// *******************************************************************************

string stringToPureNum(string &str);

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
    bool isEmpty();
    int size();
    void clear();
};


class Node {
  public:
    int serialNum;
    int value;
    Node(int serialNum, int value);
};


class Heap {
  public:
    vector<Node*> array;
    void add(int num, int value);   // push_back newData onto array
    bool isEmpty();
    int fullLayers();
    int returnValue(int position);  // return the value of the node
    void showRoot();
    void showBottom();
    void showLeftmostBottom();
    void maxHeapify(int index);
    void minHeapify(int index);
    bool isMaxLayer(int position);
    void minMaxHeapify();
};

class DEAP {
    Heap minHeap;
    Heap maxHeap;
    public:
    void insert(int serialNum, int value);
    void showBottom();
    void showLeftmostBottom();
    void clear();
};


class CommandExecuter {
    SchoolList dataStorage;
    Heap maxHeap;
    Heap minMaxHeap;
    DEAP deap;
    
  public:
    bool read();    // read the input file and store into dataStorage
    void buildMaxHeap();
    void buildMinMaxHeap();
    void buildDEAP();
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
        cout << endl << "* 3. Build a DEAP          *";
        cout << endl << "****************************";
        cout << endl << "Input a choice(0, 1, 2, 3): ";
        cin >> command;                  				
        if (command == "1")	{
            if (controller.read())
                controller.buildMaxHeap();  
        }     
        else if (command == "2") {
            if (controller.read()) 
                controller.buildMinMaxHeap();
        }
        else if (command == "3") {
            if (controller.read()) 
                controller.buildDEAP();
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

int SchoolData::returnGraduated() {
    return stoi(stringToPureNum(this->graduates));
    return 0;
}

int SchoolData::returnStudents() {
    return stoi(stringToPureNum(this->students));
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

Node::Node(int serialNum, int value) {
    this->serialNum = serialNum;
    this->value = value;
    return;
}


// Heap ***************************************************************************

void Heap::add(int num, int value) {
    Node* newNode = new Node(num, value);
    this->array.push_back(newNode);
    return;
}

bool Heap::isEmpty() {
    if (this->array.empty())
        return true;
    return false;
}

int Heap::returnValue(int position) {
    if (position >= array.size())
        return -1;
    return this->array.at(position)->value;
}

void Heap::maxHeapify(int index) {
    if (index == 0)
        index = (array.size())-1;
    int parent = (index-1)/2;
    while (parent != index) {
        // if child is larger than parent
        if (array[index]->value > array[parent]->value) {
            swap(array[index], array[parent]);    // exchange
            index = parent;
            parent = (index-1)/2;
        }
        else
            break;
    }
    return;
}

void Heap::minHeapify(int index) {
    if (index == 0)
        index = (array.size())-1;
    int parent = (index-1)/2;
    while (parent != index) {
        // if child is larger than parent
        if (array[index]->value < array[parent]->value) {
            swap(array[index], array[parent]);   // exchange
            index = parent;
            parent = (index-1)/2;
        }
        else
            break;
    }
    return;
}

bool Heap::isMaxLayer(int position) {
    if (((int)log2(position+1))%2 == 1)
        return true;
    return false;
}

void Heap::minMaxHeapify() {
    int index = (array.size())-1;
    int parent = (index-1)/2;
    int grandparent = (parent-1)/2;
    while (parent != index) {
        // if parent's layer is max and child is larger than parent
        if ((isMaxLayer(parent) && array[index]->value > array[parent]->value) ||
            (!isMaxLayer(parent) && array[index]->value < array[parent]->value)) {
            swap(array[index], array[parent]);    // exchange
        }  
        else if ((isMaxLayer(grandparent) && array[index]->value > array[grandparent]->value) ||
                 (!isMaxLayer(grandparent) && array[index]->value < array[grandparent]->value)) {
            swap(array[index], array[grandparent]);    // exchange
        }
        index = parent;
        parent = (index-1)/2;
        grandparent = (parent-1)/2;     
    }
    return;
}

int Heap::fullLayers() {
    return (int)log2(this->array.size()+1);
}

void Heap::showRoot() {
    Node* root = this->array.at(0);
    cout << "root: [" << root->serialNum << "] " << root->value << endl;
}

void Heap::showBottom() {
    Node* bottom = array.at(array.size()-1);
    cout << "bottom: [" << bottom->serialNum << "] " << bottom->value << endl;
}

void Heap::showLeftmostBottom() {
    int layers = (int)log2(array.size());
    int leftmostPosition = exp2(layers)-1;
    Node* leftmostBottom = array.at(leftmostPosition);
    cout << "leftmost bottom: [" << leftmostBottom->serialNum << "] " << leftmostBottom->value << endl;
}

// DEAP ******************************************************************************

void DEAP::insert(int serialNum, int value) {
    int comparePosMin, comparePosMax;

    // determine which heap to insert
    if (minHeap.fullLayers() <= maxHeap.fullLayers()) {
        minHeap.add(serialNum, value);
        minHeap.minHeapify(0);
        comparePosMin = minHeap.array.size()-1;
        comparePosMax = (comparePosMin-1)/2; 
    }
    else {
        maxHeap.add(serialNum, value);
        maxHeap.maxHeapify(0);
        comparePosMax = maxHeap.array.size()-1;
        comparePosMin = comparePosMax;
    }

    // minHeap connect to maxHeap
    if (maxHeap.array.size() >= 1 &&
        minHeap.array[comparePosMin]->value > maxHeap.array[comparePosMax]->value) {
        swap(minHeap.array[comparePosMin], maxHeap.array[comparePosMax]);
        minHeap.minHeapify(comparePosMin);
        maxHeap.maxHeapify(comparePosMax);
    }
    
}

void DEAP::showBottom() {
    int layers = exp2((int)log2(maxHeap.array.size()+1))-1;
    if (maxHeap.array.size() - layers > 0)
        maxHeap.showBottom();
    else
        minHeap.showBottom();
}

void DEAP::showLeftmostBottom() {
    minHeap.showLeftmostBottom();
} 

void DEAP::clear() {
    minHeap.array.clear();
    maxHeap.array.clear();
}

// CommandExecuter *******************************************************************


string stringToPureNum(string &str) {
    string pureNum;
    for (int i = 0; i < str.size(); i++)
        if (str[i] >= '0' && str[i] <= '9')  
            pureNum += str[i];
    return pureNum;
}

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
    maxHeap.array.clear();
    SchoolData* dataPtr;
    for (int i = 0;i < dataStorage.size();i++) {
        dataPtr = dataStorage.returnData(i);
        maxHeap.add(dataPtr->returnNum(), dataPtr->returnGraduated());
        maxHeap.maxHeapify(0);
    }
    cout << "<max heap>" << endl;
    maxHeap.showRoot();
    maxHeap.showBottom();
    maxHeap.showLeftmostBottom();
}

void CommandExecuter::buildMinMaxHeap() {
    minMaxHeap.array.clear();
    SchoolData* dataPtr;
    for (int i = 0;i < dataStorage.size();i++) {
        dataPtr = dataStorage.returnData(i);
        minMaxHeap.add(dataPtr->returnNum(), dataPtr->returnStudents());
        minMaxHeap.minMaxHeapify();
    }
    cout << "<min-max heap>" << endl;
    minMaxHeap.showRoot();
    minMaxHeap.showBottom();
    minMaxHeap.showLeftmostBottom();
}

void CommandExecuter::buildDEAP() {
    deap.clear();
    SchoolData* dataPtr;
    for (int i = 0;i < dataStorage.size();i++) {
        dataPtr = dataStorage.returnData(i);
        deap.insert(dataPtr->returnNum(), dataPtr->returnGraduated());
    }
    cout << "<DEAP>" << endl;
    deap.showBottom();
    deap.showLeftmostBottom();
    // minMaxHeap.showAll("2");
}
