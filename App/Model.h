#include <iostream>
#include <iostream> 
#include <sstream> 
using namespace std;

class Model {
public:
    void saveData();
    void getData();
    vector<string> checkUser(string,string);
    string getNextSemester(string);
    string getSubjects();
    string getStudentsScores();
    void insertSubject(string,string);
    void modifySubject(string, string);
    void deleteSubject(string);
    string getSubject(string);
    void insertScore(string, string, string);
    void modifyScore(string, string, string);
    void deleteScore(string, string);
    string getScore(string,string);
    string enquirySubject(string);
    string enquiryStudent(string);
    float calculateGPA(string);
    void saveNextSemesterSubjects(string,string);
};