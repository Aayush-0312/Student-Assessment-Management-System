#include <iostream>
#include <vector>
#include <string>
using namespace std;


struct Question {
    string queName;
    int maxMarks;
};

struct Paper {
    string name;
    vector<Question> questions;
};

class Department {
    protected:
        string dptName;
        int rollNo;
        vector<Paper> papers;
        vector<int> obtainedMarks; // per paper
    public:
        Department(string name) { // Constructor
            dptName = name;
        }

        void setRollNo(int r) { 
            rollNo = r; 
        }

        // Virtual functions for polymorphism
        virtual void enterMarks() {
            cout << "\n ===> Enter Marks for Roll No : " <<
                rollNo  << " (" << dptName << ") \n";

            obtainedMarks.clear();

            for(auto &p : papers) {

                cout << "\nSubject : " << p.name << "\n";
                int total = 0;

                for(int i = 0; i < p.questions.size(); i++) {

                    int marks;
                    cout << "Q" << i+1 << " [" << p.questions[i].queName 
                         << "] (Max : " << p.questions[i].maxMarks << ") : ";
                    cin >> marks;

                    if(0 > marks ||  marks > p.questions[i].maxMarks) {
                        cout << "Enter mark in range of 0 - max. Re enter please.\n";
                        i--;
                    }
                    else {
                        total += marks;
                    }
                
                }
                obtainedMarks.push_back(total);
            }
        }

        virtual void displayResult() {

            cout << "\n----------- RESULT ----------\n";
            cout << "Roll No : " << rollNo << "\n";
            cout << "Department : " << dptName << "\n\n";

            int totalObtained = 0, totalMax = 0;

            for(int i = 0; i < papers.size(); i++) {

                int paperMax = 0;
                for(auto &q : papers[i].questions) {
                    paperMax += q.maxMarks;
                }

                cout << papers[i].name << ": " << obtainedMarks[i] << " / " << paperMax << "\n";
                totalObtained += obtainedMarks[i];
                totalMax += paperMax;
            }

            float percentage = (float)totalObtained / totalMax * 100.0;

            cout << "\nTotal: " << totalObtained << " / " << totalMax << "\n";
            cout << "Percentage: " << percentage << "%\n";
            cout << "-----------------------------\n";
        }

};

class Civil : public Department {
    public:
        Civil() : Department("Civil") {
            papers = {
                {"Structural Analysis", {
                    {"Question on Trusses", 20},
                    {"Question on Beams", 30},
                    {"Question on Frames", 50}
                }},
                {"Surveying", {
                    {"Chain Survey", 25},
                    {"Leveling", 25},
                    {"Theodolite", 50}
                }},
                {"Geotechnical Engg", {
                    {"Soil Classification", 40},
                    {"Bearing Capacity", 60}
                }}
            };
        }
};

class Chemical : public Department {
    public:
        Chemical() : Department("Chemical") {
            papers = {
                {"Organic Chemistry", {
                    {"Alkanes", 30},
                    {"Alcohols", 30},
                    {"Polymers", 40}
                }},
                {"Process Calculation", {
                    {"Material Balance", 50},
                    {"Energy Balance", 50}
                }}
            };
        }
};

class Mechanical : public Department {
    public:
        Mechanical() : Department("Mechanical") {
            papers = {
                {"Thermodynamics", {
                    {"First Law", 30},
                    {"Second Law", 30},
                    {"Entropy", 40}
                }},
                {"Fluid Mechanics", {
                    {"Bernoulli Equation", 25},
                    {"Flow Measurement", 25},
                    {"Turbines", 50}
                }},
                {"Machine Design", {
                    {"Shaft Design", 50},
                    {"Gear Design", 50}
                }},
                {"Kinematics", {
                    {"Velocity Analysis", 40},
                    {"Acceleration Analysis", 60}
                }}
            };
        }
};

class ComputerScience : public Department {
    public:
        ComputerScience() : Department("Computer Science") {
            papers = {
                {"Data Structures", {
                    {"Arrays", 20},
                    {"Linked List", 30},
                    {"Trees", 50}
                }},
                {"Algorithms", {
                    {"Sorting", 30},
                    {"Graph Algorithms", 70}
                }},
                {"DBMS", {
                    {"ER Diagram", 30},
                    {"Normalization", 30},
                    {"SQL Queries", 40}
                }}
            };
        }
};


int main() {
    cout << "----- University Exam Result System ----\n";

    int rollNum;
    cout << "Enter Student's Roll No : ";
    cin >> rollNum;

    cout << "\nChoose Department : \n";
    cout << "1. Civil\n2. Chemical\n3. Mechanical\n4. Computer Science\n";
    cout << "Enter choice: ";
    int choice;
    cin >> choice;

    Department* dpt = NULL;

    switch(choice) {
        case 1: 
            dpt = new Civil(); 
            break;
            
        case 2: 
            dpt = new Chemical(); 
            break;

        case 3: 
            dpt = new Mechanical(); 
            break;
            
        case 4: 
            dpt = new ComputerScience(); 
            break;

        default: 
            cout << "Invalid choice! \nPlease enter a valid choice."; return 0;
    }

    dpt->setRollNo(rollNum);
    dpt->enterMarks();
    dpt->displayResult();

    delete dpt;
    return 0;
}

