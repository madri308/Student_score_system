#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include "Model.h"

using namespace std;

std::map<string, vector<string>> students; //Students list username:data
std::map<string, vector<string>> teachers; //Teachers list username:data
std::map<string, vector<string>> subjects; //Subjects list subject:data
std::map<string, vector<vector<string>>> scores; //score list username:data

void Model::saveData() {
    ofstream newFile("data.txt");

    students["madri20"] = { "pass123", "Esteban Madrigal Marin" };
    students["josh22"] = { "pass345", "Josh Bird" };
    students["maria33"] = { "code987", "Maria Gonzalez" };
    students["diego28"] = { "easy654", "Diego Maradona" };

    teachers["jp123"] = { "pass123", "Jean Paul Gord" };
    teachers["mark34"] = { "pass345", "Mark Mendes" };
    teachers["bell32"] = { "code987", "Bernard Lincoln" };
    teachers["drake72"] = { "easy654", "Drake Nichols" };

    subjects["Math"] = { "jp123", "Monday" };
    subjects["Science"] = { "mark34", "Friday" };
    subjects["Art"] = { "bell32", "Monday" };
    subjects["Physics"] = { "drake72", "Tuesday" };

    scores["madri20"] = { {"Math", "20"},{ "Science", "100" } };
    scores["josh22"] = { {"Math", "40"},{ "Science", "100" } };
    scores["diego28"] = { {"Physics", "90"},{ "Science", "100" } };

    //Save students
    string studentsData = ""; //String to save
    map<string, vector<string>>::iterator in1;
    for (in1 = students.begin(); in1 != students.end(); in1++){
        vector<string> data = in1->second; //students data
        string student = (in1->first) + ":";  //write the key
        for (string element : data) {     //saves each element from students data  
            student += element + ",";        //splitted by ,
        }
        student.pop_back(); //Delete the last ,
        student += ";"; //All students splitted by ;
        studentsData += student;
    }
    newFile << studentsData << endl; //write in the file

    //Save teachers
    string teachersData = ""; //String to save
    map<string, vector<string>>::iterator in2;
    for (in2 = teachers.begin(); in2 != teachers.end(); in2++) {
        vector<string> data = in2->second; //teachers data
        string teacher = (in2->first) + ":";  //write the key
        for (string element : data) {     //saves each element from teachers data  
            teacher += element + ",";    //splitted by ,
        }
        teacher.pop_back(); //Delete the last ,
        teacher += ";"; //All students splitted by ;
        teachersData += teacher;
    }
    newFile << teachersData << endl; //write in the file

    //Save subjects
    string subjectsData = ""; //String to save
    map<string, vector<string>>::iterator in3;
    for (in3 = subjects.begin(); in3 != subjects.end(); in3++) {
        vector<string> data = in3->second; //teachers data
        string subject = (in3->first) + ":";  //write the key
        for (string element : data) {     //saves each element from teachers data  
            subject += element + ",";    //splitted by ,
        }
        subject.pop_back(); //Delete the last ,
        subject += ";"; //All students splitted by ;
        subjectsData += subject;
    }
    newFile << subjectsData << endl; //write in the file

    //Save scores
    string scoresData = ""; //String to save
    map<string, vector<vector<string>>>::iterator in4;
    for (in4 = scores.begin(); in4 != scores.end(); in4++) {
        vector<vector<string>> data = in4->second; //teachers data
        string score = (in4->first) + ":";  //write the key
        for (vector<string> element : data) {     //saves each element from teachers data  
            score += element[0] + "-" + element[1] + ",";    //splitted by ,
        }
        score.pop_back(); //Delete the last ,
        score += ";"; //All students splitted by ;
        scoresData += score;
    }
    newFile << scoresData << endl; //write in the file

    newFile.close();    //close the file
}
string Model::getData(int label) {
    std::ifstream infile("data.txt");
    string tp;
    string msg;

    for (int numberLine = 0; numberLine != label; numberLine++) {
        getline(infile, tp);
    }
    getline(infile, tp);

    msg = tp;
    infile.close();
    return msg;
}
