#include <iostream>
#include <vector>
#include <string>
using namespace std;


class Student{
private:
    string name; //name of student
    vector<int> attendance; //list of grades/attendance
public:
    Student(const string& inName) : name(inName) {
        //initialized as 14 slots of absences
        for (int i = 0; i < 14; ++i){ attendance.push_back(-1); }
    }
    string getName() const { return name; }
    int getGrades(const int& i) const { return attendance[i]; }
    void setGrade(const int& grade, const int& session){
        attendance[session-1] = grade;
    }
};

class Section{
private:
    string sect;
    string day;
    int time;
    vector<Student*> students;

public:
    Section(const string& inSect, const string& inDay, const int& inTime)
        : sect(inSect), day(inDay), time(inTime) {}
    vector<Student*> getStudents() const { return students; }
    void display() const {
        cout << "Section: " << sect << ", Time slot: [Day: "
             << day << ", Start time: ";
        if (time > 12){ cout << (time-12) << "pm], Students: "; }
        else {cout << time << "am], Students: "; }

        if (students.size() == 0){ cout << "None"; }
        else{
            cout << endl;
            for (Student* student : students){
                cout << "Name: " << student->getName() << ", Grades: ";
                for (int i = 0; i < 14 ; ++i){ cout << student->getGrades(i) << " "; }
                cout << endl;
            }
        }
    }

    void addStudent(const string& newName){ //create a student within method????
        Student* student = new Student(newName);
        students.push_back(student);
    }

    //copy constructor
    Section(const Section& rhs) : sect(rhs.sect), day(rhs.day), time(rhs.time) {
        for (size_t i = 0; i < rhs.students.size(); ++i){
            students.push_back(rhs.students[i]);
        }
    }

    ~Section(){
        cout << "Section " << sect << " is being deleted" << endl;
        for (Student* student : students){
                cout << "Deleting " << student->getName() << endl;
                delete student;
        }
    }
};

class LabWorker{ //assume labworker can hold one section
private:
    string name;
    Section* section = nullptr;
public:
    LabWorker(string inName) : name(inName){}
    void addSection(Section& sect){
        if (section == nullptr){ section = &sect; }
        else { cout << "Already has a section. Could not add." << endl; }
    }
    void display() const {
        if (section == nullptr){
            cout << name << " does not have a section" << endl;
        } else{
            cout << name << " has ";
            section->display();
        }
    }
    void addGrade(const string& inName, const int& grade, const int& session){
        for (Student* student : section->getStudents()){
            if (student->getName() == inName){
                student->setGrade(grade, session);
            }
        }
    }
};



//---DRIVER-----

int main() {

    cout << "Test 1: Defining a section\n";
    Section secA2("A2", "Tuesday", 16);
    secA2.display();

    cout << "\nTest 2: Adding students to a section\n";
    secA2.addStudent("John");
    secA2.addStudent("George");
    secA2.addStudent("Paul");
    secA2.addStudent("Ringo");
    secA2.display();

    cout << "\nTest 3: Defining a lab worker.\n";
    LabWorker moe( "Moe" );
    moe.display();

    cout << "\nTest 4: Adding a section to a lab worker.\n";
    moe.addSection( secA2 );
    moe.display();

    cout << "\nTest 5: Adding a second section and lab worker.\n";
    LabWorker jane( "Jane" );
    Section secB3( "B3", "Thursday", 11 );
    secB3.addStudent("Thorin");
    secB3.addStudent("Dwalin");
    secB3.addStudent("Balin");
    secB3.addStudent("Kili");
    secB3.addStudent("Fili");
    secB3.addStudent("Dori");
    secB3.addStudent("Nori");
    secB3.addStudent("Ori");
    secB3.addStudent("Oin");
    secB3.addStudent("Gloin");
    secB3.addStudent("Bifur");
    secB3.addStudent("Bofur");
    secB3.addStudent("Bombur");
    jane.addSection( secB3 );
    jane.display();

    cout << "\nTest 6: Adding some grades for week one\n";
    moe.addGrade("John", 17, 1);
    moe.addGrade("Paul", 19, 1);
    moe.addGrade("George", 16, 1);
    moe.addGrade("Ringo", 7, 1);
    moe.display();

    cout << "\nTest 7: Adding some grades for week three (skipping week 2)\n";
    moe.addGrade("John", 15, 3);
    moe.addGrade("Paul", 20, 3);
    moe.addGrade("Ringo", 0, 3);
    moe.addGrade("George", 16, 3);
    moe.display();

}
