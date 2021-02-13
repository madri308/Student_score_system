#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include "Model.h"

using namespace std;

map<string, vector<string>> students; //Students list username:data
map<string, vector<string>> teachers; //Teachers list username:data
map<string, vector<string>> subjects; //Subjects list subject:data
map<string, vector<vector<string>>> scores; //score list username:data

vector<map<string, vector<string>>> structures{ students,teachers,subjects };
vector<string> Model::checkUser(string username, string password) {
    if (!(structures[0].find(username) == structures[0].end())) {
        if (structures[0][username][0] == password) {
            return { structures[0][username][1], "1"}; //Student
        }
        else {
            return {"Wrong password", "-2" }; //Wrong password
        }
    }
    else if (!(structures[1].find(username) == structures[1].end())) {
        if (structures[1][username][0] == password) {
            return { structures[1][username][1], "2" }; //Teacher
        }
        else {
            return { "Wrong password", "-2" }; //Wrong password
        }
    }
    return { "User not found ","0" };
}
void Model::insertSubject(string subjectName, string credits) {
    structures[2][subjectName] = { credits };
    saveData();
}
void Model::modifySubject(string subjectName, string newCredits) {
    structures[2][subjectName] = { newCredits };
    saveData();
}
void Model::deleteSubject(string subjectName) {
    structures[2].erase(subjectName);
    saveData();
}
string Model::getSubject(string subjectName) {
    vector<string> data = structures[2][subjectName];
    string stringData = "";
    for (string element : data) {
        stringData += element + ",";
    }
    stringData.pop_back();
    return stringData;
}
void Model::insertScore(string subjectName, string studentName, string score) {
    scores[studentName].push_back({ subjectName,score });
    saveData();
}
void Model::modifyScore(string subjectName, string studentName, string score) {
    vector<vector<string>> *data = &scores[studentName];
    for (vector<string> &subjectData : *data) {
        if (subjectData[0] == subjectName) {
            subjectData[1] = score;
            break;
        }
    }
    saveData();
}
void Model::deleteScore(string subjectName, string studentName) {
    for (int index = 0; index < scores[studentName].size(); index++) {
        vector<string> subjectData = scores[studentName][index];
        if (subjectData[0] == subjectName) {
            scores[studentName].erase(scores[studentName].begin() + index);
            break;
        }
    }
    saveData();
}
string Model::getSubjects() {
    string stuctureData = ""; //String to save
    map<string, vector<string>>::iterator in1;
    for (in1 = structures[2].begin(); in1 != structures[2].end(); in1++) {
        vector<string> data = in1->second; //students data
        string object = (in1->first) + ": ";  //write the key
        for (string element : data) {     //saves each element from students data  
            object += element + ", ";        //splitted by ,
        }
        object.pop_back(); //Delete the last ,
        object.pop_back(); //Delete the last ,
        object += "\n"; //All students splitted by ;
        stuctureData += object;
    }
    return stuctureData;
}
string Model::getStudentsScores() {
    string scoresData = ""; //String to save
    map<string, vector<vector<string>>>::iterator in4;
    for (in4 = scores.begin(); in4 != scores.end(); in4++) {
        vector<vector<string>> data = in4->second;  //teachers data
        string score = (in4->first) + ":";          //write the key
        for (vector<string> element : data) {       //saves each element from teachers data  
            score += "\n   "+element[0] + "-" + element[1];    //splitted by ,
        }
        score += "\n";       //All students splitted by ;
        scoresData += score;
    }
    return scoresData;
}
//Save all the structures in a txt file
void Model::saveData() {
    ofstream newFile("data.txt");

    for (int datas = 0; datas < 3; datas++) {
        //Save all
        string stuctureData = ""; //String to save
        map<string, vector<string>>::iterator in1;
        for (in1 = structures[datas].begin(); in1 != structures[datas].end(); in1++) {
            vector<string> data = in1->second; //students data
            string object = (in1->first) + ":";  //write the key
            for (string element : data) {     //saves each element from students data  
                object += element + ",";        //splitted by ,
            }
            object.pop_back(); //Delete the last ,
            object += ";"; //All students splitted by ;
            stuctureData += object;
        }
        newFile << stuctureData << endl; //write in the file
    }

    //Save scores
    string scoresData = ""; //String to save
    map<string, vector<vector<string>>>::iterator in4;
    for (in4 = scores.begin(); in4 != scores.end(); in4++) {
        vector<vector<string>> data = in4->second;  //teachers data
        string score = (in4->first) + ":";          //write the key
        for (vector<string> element : data) {       //saves each element from teachers data  
            score += element[0] + "-" + element[1] + ",";    //splitted by ,
        }
        score.pop_back();   //Delete the last then
        score += ";";       //All students splitted by ;
        scoresData += score;
    }
    newFile << scoresData << endl; //write in the file
    newFile.close();    //close the file
}

//Fill all the structures with data from the txt file
void Model::getData() {
    std::ifstream infile("data.txt");
    string tp;
    string msg;
    int line = 0;
    while (getline(infile, tp)) {
        if (line != 3) {
            string label = "", word = "";
            bool labelDone = false;
            vector<string> data = {};
            for (char element : tp) {
                if (element == ';') { //All elements of the object done then
                    data.push_back(word);
                    structures[line][label] = data; //Saves data and restart all
                    label = word = ""; 
                    data = {}; 
                    labelDone = false;
                }
                else if (element == ':'){ //Label done
                    labelDone = true;
                }
                else if (element == ',') { //New word to save
                    data.push_back(word);
                    word = "";
                }
                else if (!labelDone) { //If label not done yet
                    label += element;  //keep writing the label
                }
                else {//If label already written then
                    word += element;//Write the word
                }
            }
        }
        else {
            string label = "", word = "";
            bool labelDone = false;
            vector<vector<string>> data = {};
            vector<string> scoreAndSubject = {};
            for (char element : tp) {
                if (element == ';') { //All elements of the object are done then
                    scoreAndSubject.push_back(word);
                    data.push_back(scoreAndSubject);
                    scores[label] = data; //Saves data and restart all
                    label = word =  "";
                    data = {};
                    scoreAndSubject = {};
                    labelDone = false;
                }
                else if (element == ':') { //Label done
                    labelDone = true;
                }
                else if (element == ',') { //New word to save
                    scoreAndSubject.push_back(word);
                    data.push_back(scoreAndSubject);
                    scoreAndSubject = {};
                    word = "";
                }
                else if (element == '-') {
                    scoreAndSubject.push_back(word);
                    word = "";
                }
                else if (!labelDone) { //If label not done yet
                    label += element;  //keep writing the label
                }
                else {//If label already written then
                    word += element;//Write the word
                }
            }
        }
        line++;
    }
    infile.close();
}
