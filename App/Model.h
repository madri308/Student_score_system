#include <iostream>
using namespace std;

class Model {
public:
    void saveData();
    void getData();
    vector<string> checkUser(string,string);
    string getSubjects();
    string getStudentsScores();
    void insertSubject(string,string);
    void modifySubject(string, string);
    void deleteSubject(string);
    string getSubject(string);
    void insertScore(string, string, string);
    void modifyScore(string, string, string);
    void deleteScore(string, string);
};