// 11227154 辛宇平

#include <iostream>
#include <string>
#include <vector>
#include <sstream>  
#include <fstream>
#include <math.h>
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
    int students;
    int teachers;
    int graduates;
    string locatedCity;
    string type;
  public:
    SchoolData(int num, stringstream &inputString);
    int getNum();
    int getGraduated();
    int getStudents();
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
    int serialNum;
    int value;
  public:
    Node(int serialNum, int value);
    int getNum();
    int getValue();
};

int inLayer(int position);

class Heap {
  protected:
    vector<Node*> array;
    ~Heap();
    void maxHeapify(int start, int end);
    void minHeapify(int start, int end);
    bool isMaxLayer(int position);
  public:
    void add(int serialNum, int value);   // push_back newData onto array
    bool isEmpty();
    void clear();
    void showRoot();
    void showBottom();
    void showLeftmostBottom();
};

class MaxHeap : public Heap {
  public:
    void insert(int serialNum, int value);
    void showResult();
};

class MinMaxHeap : public Heap {
  private:
    void minMaxHeapify();  
  public:
    void insert(int serialNum, int value);
    void showResult();
};

class DEAP : public Heap {
  public:
    DEAP();
    void insert(int serialNum, int value);
    void showResult();
};


class CommandExecuter {
    SchoolList dataStorage;
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
    string temp;
    this->num = num;
    getline(inputString, this->schoolNumber, '\t');
    getline(inputString, this->schoolName, '\t');
    getline(inputString, this->departmentNumber, '\t');
    getline(inputString, this->departmentName, '\t');
    getline(inputString, this->timeSlots, '\t');
    getline(inputString, this->degree, '\t');
    getline(inputString, temp, '\t');
    this->students = stoi(stringToPureNum(temp));
    getline(inputString, temp, '\t');
    this->teachers = stoi(stringToPureNum(temp));
    getline(inputString, temp, '\t');
    this->graduates = stoi(stringToPureNum(temp));
    getline(inputString, this->locatedCity, '\t');
    getline(inputString, this->type, '\t');
}

int SchoolData::getGraduated() {
    return this->graduates;
}

int SchoolData::getStudents() {
    return this->students;
}

int SchoolData::getNum() {
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

int Node::getNum() {
    return this->serialNum;
}

int Node::getValue() {
    return this->value;
}


// Heap ***************************************************************************

int inLayer(int position) {
    return (int)log2(position+1);
}

Heap::~Heap() {
    clear();
}

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

void Heap::maxHeapify(int start, int end) {
    if (start == 0)
        start = (array.size())-1;
    int parent = (start-1)/2;
    while (parent >= end && parent != start) {
        // if child is larger than parent
        if (array[start]->getValue() > array[parent]->getValue()) {
            swap(array[start], array[parent]);    // exchange
            start = parent;
            parent = (start-1)/2;
        }
        else
            break;
    }
    return;
}

void Heap::minHeapify(int start, int end) {
    if (start == 0)
        start = (array.size())-1;
    int parent = (start-1)/2;
    while (parent >= end && parent != start) {
        // if child is smaller than parent
        if (array[start]->getValue() < array[parent]->getValue()) {
            swap(array[start], array[parent]); 
            start = parent;
            parent = (start-1)/2;
        }
        else
            break;
    }
    return;
}

bool Heap::isMaxLayer(int position) {
    if ((inLayer(position))%2 == 1)
        return true;
    return false;
}

void Heap::showRoot() {
    Node* root = this->array.at(0);
    cout << "root: [" << root->getNum() << "] " << root->getValue() << endl;
}

void Heap::showBottom() {
    Node* bottom = array.at(array.size()-1);
    cout << "bottom: [" << bottom->getNum() 
         << "] " << bottom->getValue() << endl;
}

void Heap::showLeftmostBottom() {
    int layers = (int)log2(array.size());
    int leftmostPosition = exp2(layers)-1;
    Node* leftmostBottom = array.at(leftmostPosition);
    cout << "leftmost bottom: [" << leftmostBottom->getNum() 
         << "] " << leftmostBottom->getValue() << endl;
}

void Heap::clear() {
    this->array.clear();
}

// MaxHeap ***************************************************************************

void MaxHeap::insert(int serialNum, int value) {
    add(serialNum, value);
    maxHeapify(array.size()-1, 0);
}

void MaxHeap::showResult() {
    showRoot();
    showBottom();
    showLeftmostBottom();
}

// MinMaxHeap ************************************************************************

void MinMaxHeap::minMaxHeapify() {
    int index = (array.size())-1;
    int parent = (index-1)/2;
    int grandparent = (parent-1)/2;
    while (parent != index) {
        // if parent's layer is max and child is larger than parent
        if ((isMaxLayer(parent) && array[index]->getValue() > array[parent]->getValue()) ||
            (!isMaxLayer(parent) && array[index]->getValue() < array[parent]->getValue())) {
            swap(array[index], array[parent]);    // exchange
        }  
        else if ((isMaxLayer(grandparent) && array[index]->getValue() > array[grandparent]->getValue()) ||
                 (!isMaxLayer(grandparent) && array[index]->getValue() < array[grandparent]->getValue())) {
            swap(array[index], array[grandparent]);    // exchange
        }
        index = parent;
        parent = (index-1)/2;
        grandparent = (parent-1)/2;     
    }
    return;
}

void MinMaxHeap::insert(int serialNum, int value) {
    add(serialNum, value);
    minMaxHeapify();
}

void MinMaxHeap::showResult() {
    showRoot();
    showBottom();
    showLeftmostBottom();
}

// DEAP ******************************************************************************

DEAP::DEAP() {
    array.push_back(nullptr);
}

void DEAP::insert(int serialNum, int value) {
    add(serialNum, value);
    
    if (array.size() < 3)
        return;
    int newIndex = array.size()-1;
    int layers = (int)log2(array.size());
    int leftmostPosition = exp2(layers)-1;
    int inLayerPos = newIndex - leftmostPosition;
    int halfLayerSpace = exp2(layers-1);
    bool inMin = (inLayerPos/halfLayerSpace == 0);
    int comparePosMin, comparePosMax;
    
    if (inMin) {
        minHeapify(0, 1);
        comparePosMin = newIndex;
        comparePosMax = (newIndex + halfLayerSpace-1)/2;
    }
    else {
        maxHeapify(0, 2);
        comparePosMin = newIndex - halfLayerSpace;
        comparePosMax = newIndex;
    }

    if (array[comparePosMin]->getValue() > array[comparePosMax]->getValue()) {
        swap(array[comparePosMin], array[comparePosMax]);
        minHeapify(comparePosMin, 1);
        maxHeapify(comparePosMax, 2);
    }
    
}

void DEAP::showResult() {
    showBottom();
    showLeftmostBottom();
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
    MaxHeap maxHeap;
    SchoolData* dataPtr;
    for (int i = 0;i < dataStorage.size();i++) {
        dataPtr = dataStorage.returnData(i);
        maxHeap.insert(dataPtr->getNum(), dataPtr->getGraduated());
    }
    cout << "<max heap>" << endl;
    maxHeap.showResult();
}

void CommandExecuter::buildMinMaxHeap() {
    MinMaxHeap minMaxHeap;
    SchoolData* dataPtr;
    for (int i = 0;i < dataStorage.size();i++) {
        dataPtr = dataStorage.returnData(i);
        minMaxHeap.insert(dataPtr->getNum(), dataPtr->getStudents());
    }
    cout << "<min-max heap>" << endl;
    minMaxHeap.showResult();
}

void CommandExecuter::buildDEAP() {
    DEAP *deap = new DEAP();
    SchoolData* dataPtr;
    for (int i = 0;i < dataStorage.size();i++) {
        dataPtr = dataStorage.returnData(i);
        deap->insert(dataPtr->getNum(), dataPtr->getGraduated());
    }
    cout << "<DEAP>" << endl;
    deap->showResult();
}

