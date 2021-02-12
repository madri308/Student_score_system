#include <iostream>
using namespace std;

class Model {
public:
    void saveData();
    void getData();
    vector<string> checkUser(string,string);
    string getSubjects();
    string getStudentsScores();
};