#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <vector>
#include "Model.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK WndProc2(HWND, UINT, WPARAM, LPARAM);

//Declare GUI elements
HWND registerButton, loginButton, textField, userTextBox, passwordTextBox //Login View
, insertSubject, modifySubject, deleteSubject, searchSubject, insertScore //Teacher view
, modifyScore, deleteScore, searchScore, enquiryStudent, enquirySubject   //Teacher view
, subjectTextBox, creditTextBox, subjectTextBox2, scoreTextBox, studentTextBox //Teacher view
, subjectText, scoreText //Teacher view
, enquiryMyResult, calculateGPA, selectSubjects; //Student view


//Declare constants
//GUI
_In_ int nCmd;
HWND hWnd2;
HINSTANCE hInstance2;
//Logic
int userType;
string actualUser;
Model model;

//Main
int CALLBACK WinMain(_In_ HINSTANCE hInstance,_In_opt_ HINSTANCE hPrevInstance,_In_ LPSTR lpCmdLine,_In_ int nCmdShow){
    hInstance2 = hInstance;
    nCmd = nCmdShow;

    WNDCLASSEX wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = _T("principal");
    wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

    if (!RegisterClassEx(&wcex)){
        MessageBox(NULL,_T("Call to RegisterClassEx failed!"),_T("Windows Desktop Guided Tour"),NULL);
        return 1;
    }

    HWND hWnd = CreateWindow(
        wcex.lpszClassName,
        _T("Student score system"),
        WS_MINIMIZEBOX | WS_SYSMENU,
        CW_USEDEFAULT, CW_USEDEFAULT,
        500, 270,
        NULL, NULL, hInstance, NULL
    );

    if (!hWnd){
        MessageBox(NULL,_T("Call to CreateWindow failed!"), _T("Windows Desktop Guided Tour"), NULL);
        return 1;
    }

    ShowWindow(hWnd,nCmdShow);
    UpdateWindow(hWnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return (int)msg.wParam;
}
//Second window
void initSecondView() {
    WNDCLASSEX wcex2;
    wcex2.cbSize = sizeof(WNDCLASSEX);
    wcex2.style = CS_HREDRAW | CS_VREDRAW;
    wcex2.lpfnWndProc = WndProc2;
    wcex2.cbClsExtra = 0;
    wcex2.cbWndExtra = 0;
    wcex2.hInstance = hInstance2;
    wcex2.hIcon = LoadIcon(hInstance2, IDI_APPLICATION);
    wcex2.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex2.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex2.lpszMenuName = NULL;
    wcex2.lpszClassName = _T("Second");
    wcex2.hIconSm = LoadIcon(wcex2.hInstance, IDI_APPLICATION);

    if (!RegisterClassEx(&wcex2)) {
        MessageBox(NULL, _T("Call to RegisterClassEx failed!"), _T("Windows Desktop Guided Tour"), NULL);
    }

    hWnd2 = CreateWindow(
        wcex2.lpszClassName,
        _T("Student score system 2"),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        602, 300,
        NULL, NULL, hInstance2, NULL
    );

    if (!hWnd2) {
        MessageBox(NULL, _T("Call to CreateWindow failed!"), _T("Windows Desktop Guided Tour"), NULL);
    }
    ShowWindow(hWnd2, nCmd);
    UpdateWindow(hWnd2);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

//Function that is called after any event in the firts window
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
    PAINTSTRUCT ps;
    HDC hdc;
    TCHAR welcomeLabel[] = _T("Welcome to the student score system! please log in or register");
    TCHAR userLabel[] = _T("Enter your username:");
    TCHAR passwordLabel[] = _T("Enter your password:");
    int gwtstat = 0;
    vector<string> answer; 
    string title;
    
    switch (message){
    case WM_CREATE: //When the window is just created
        model.getData();
        //BUTTONS
        loginButton = CreateWindow(TEXT("button"), TEXT("Log in"),
            WS_VISIBLE | WS_CHILD,
            165, 180, 80, 25,
            hWnd, (HMENU) 1, NULL, NULL);
        registerButton = CreateWindow(TEXT("button"), TEXT("Register"),
            WS_VISIBLE | WS_CHILD,
            255, 180, 80, 25,
            hWnd, (HMENU) 2, NULL, NULL);

        //ENTRY BOXES
        userTextBox = CreateWindow(TEXT("Edit"), TEXT(""),
            WS_BORDER | WS_VISIBLE | WS_CHILD,
            150, 70, 200, 20,
            hWnd, NULL, NULL, NULL);
        passwordTextBox = CreateWindow(TEXT("Edit"), TEXT(""),
            WS_BORDER | WS_VISIBLE | WS_CHILD,
            150, 130, 200, 20,
            hWnd, NULL, NULL, NULL);
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);

        //LABELS
        TextOut(hdc, 35, 5, welcomeLabel, _tcslen(welcomeLabel));
        TextOut(hdc, 35, 50, userLabel, _tcslen(userLabel));
        TextOut(hdc, 35, 110, passwordLabel, _tcslen(passwordLabel));

        EndPaint(hWnd, &ps);        
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case 1://login
            //Get the username
            char userName[40];
            gwtstat = GetWindowText(userTextBox, LPSTR(&userName[0]), 40);
            if (gwtstat == 0) {
                MessageBox(NULL, _T("Can you please enter your username."), _T("Error"), NULL);
                break;
            }
            //Get the password
            char password[40];
            gwtstat = GetWindowText(passwordTextBox, LPSTR(&password[0]), 40);
            if (gwtstat == 0) {
                MessageBox(NULL, _T("Can you please enter your password."), _T("Error"), NULL);
                break;
            }

            char buff[100];
            answer = model.checkUser(userName, password);
            if (answer[1] == "1") { //Student
                sprintf_s(buff, "Bienvenido %s", answer[0].c_str());
                cout << buff;
                MessageBox(NULL, _T(buff), _T("Students portal"), NULL);
                PostMessage(hWnd, WM_CLOSE, 0, 0);
                userType = 1;
                actualUser = userName;
                initSecondView();
            }
            else if (answer[1] == "2") { //Teacher
                sprintf_s(buff, "Bienvenido %s", answer[0].c_str());
                cout << buff;
                MessageBox(NULL, _T(buff), _T("Teachers portal"), NULL);
                PostMessage(hWnd, WM_CLOSE, 0, 0);
                userType = 2;
                actualUser = userName;
                initSecondView();
            }
            else { //Error
                sprintf_s(buff, "%s", answer[0].c_str());
                cout << buff;
                MessageBox(NULL, _T(buff), _T("Error"), NULL);
            }
            break;
        case 2://Register
            PostMessage(hWnd, WM_CLOSE, 0, 0);
            userType = 1;
            actualUser = "diego28";
            initSecondView();
            break;
        }
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
        break;
    }
    return 0;
}
//Function that is called after any event in the second window
LRESULT CALLBACK WndProc2(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    PAINTSTRUCT ps;
    HDC hdc;
    int gwtstat = 0;
    string subjects;
    string scores;
    char subjectName[40];
    char student[40];
    char score[40];
    string msg;
    char buff[500];

    switch (message) {
    case WM_PAINT:

        hdc = BeginPaint(hWnd, &ps);
        TextOut(hdc, 2, 53, "Subject: credit hours", _tcslen("Subject: credit hours"));
        if (userType == 2) {
            //LABELS
            TextOut(hdc, 310, 53, "Student: Subject-Score", _tcslen("Student: Subject-Score"));
            TextOut(hdc, 2, 1, "Subject name:", _tcslen("Subject name:"));
            TextOut(hdc, 132, 1, "Credit hours:", _tcslen("Credit hours:"));
            TextOut(hdc, 310, 1, "Student:", _tcslen("Student:"));
            TextOut(hdc, 410, 1, "Subject:", _tcslen("Subject:"));
            TextOut(hdc, 510, 1, "Score:", _tcslen("Score:"));
        }
        else {
            TextOut(hdc, 197, 150, "Subjects for the next semester.", _tcslen("Subjects for the next semester."));
            TextOut(hdc, 427, 53, "Next semester subjects", _tcslen("Next semester subjects"));
        }
        EndPaint(hWnd, &ps);
        break;
    case WM_CREATE: //When the window is just created
        model.getData();
        switch (userType) {
        case 2: //Teacher

            //TEXT BOXES
            subjects = model.getSubjects();
            sprintf_s(buff, "%s", subjects.c_str());
            cout << buff;
            subjectText = CreateWindow(TEXT("STATIC"), _T(buff),
                WS_BORDER | WS_VISIBLE | WS_CHILD,
                2, 70, 150, (_tcslen(buff)/10)*17,
                hWnd, NULL, NULL, NULL);

            scores = model.getStudentsScores();
            sprintf_s(buff, "%s", scores.c_str());
            cout << buff;
            scoreText = CreateWindow(TEXT("STATIC"), _T(buff),
                WS_BORDER | WS_VISIBLE | WS_CHILD,
                310, 70, 150, (_tcslen(buff) / 10) * 15,
                hWnd, NULL, NULL, NULL);

            //ENTRY BOXES
            subjectTextBox = CreateWindow(TEXT("Edit"), TEXT(""),
                WS_BORDER | WS_VISIBLE | WS_CHILD,
                30, 20, 100, 20,
                hWnd, NULL, NULL, NULL);
            creditTextBox = CreateWindow(TEXT("Edit"), TEXT(""),
                WS_BORDER | WS_VISIBLE | WS_CHILD,
                155, 20, 100, 20,
                hWnd, NULL, NULL, NULL);

            subjectTextBox2 = CreateWindow(TEXT("Edit"), TEXT(""),
                WS_BORDER | WS_VISIBLE | WS_CHILD,
                430, 20, 70, 20,
                hWnd, NULL, NULL, NULL);
            scoreTextBox = CreateWindow(TEXT("Edit"), TEXT(""),
                WS_BORDER | WS_VISIBLE | WS_CHILD,
                530, 20, 50, 20,
                hWnd, NULL, NULL, NULL);
            studentTextBox = CreateWindow(TEXT("Edit"), TEXT(""),
                WS_BORDER | WS_VISIBLE | WS_CHILD,
                330, 20, 70, 20,
                hWnd, NULL, NULL, NULL);

            //BUTTONS
            insertSubject = CreateWindow(TEXT("button"), TEXT("Insert Subject"),
                WS_VISIBLE | WS_CHILD,
                155, 70, 120, 25,
                hWnd, (HMENU)1, NULL, NULL);
            modifySubject = CreateWindow(TEXT("button"), TEXT("Modify Subject"),
                WS_VISIBLE | WS_CHILD,
                155, 105, 120, 25,
                hWnd, (HMENU)2, NULL, NULL);
            deleteSubject = CreateWindow(TEXT("button"), TEXT("Delete Subject"),
                WS_VISIBLE | WS_CHILD,
                155, 140, 120, 25,
                hWnd, (HMENU)3, NULL, NULL);
            searchSubject = CreateWindow(TEXT("button"), TEXT("Search Subject"),
                WS_VISIBLE | WS_CHILD,
                155, 175, 120, 25,
                hWnd, (HMENU)4, NULL, NULL);
            enquirySubject = CreateWindow(TEXT("button"), TEXT("Enquiry Subject"),
                WS_VISIBLE | WS_CHILD,
                155, 210, 120, 25,
                hWnd, (HMENU)5, NULL, NULL);
            insertScore = CreateWindow(TEXT("button"), TEXT("Insert Score"),
                WS_VISIBLE | WS_CHILD,
                465, 70, 120, 25,
                hWnd, (HMENU)6, NULL, NULL);
            modifyScore = CreateWindow(TEXT("button"), TEXT("Modify Score"),
                WS_VISIBLE | WS_CHILD,
                465, 105, 120, 25,
                hWnd, (HMENU)7, NULL, NULL);
            deleteScore = CreateWindow(TEXT("button"), TEXT("Delete Score"),
                WS_VISIBLE | WS_CHILD,
                465, 140, 120, 25,
                hWnd, (HMENU)8, NULL, NULL);
            searchScore = CreateWindow(TEXT("button"), TEXT("Search Score"),
                WS_VISIBLE | WS_CHILD,
                465, 175, 120, 25,
                hWnd, (HMENU)9, NULL, NULL);
            enquiryStudent = CreateWindow(TEXT("button"), TEXT("Enquiry Student"),
                WS_VISIBLE | WS_CHILD,
                465, 210, 120, 25,
                hWnd, (HMENU)10, NULL, NULL);
            break;
        case 1: //Student
            //ENTRYBOXES
            subjectTextBox = CreateWindow(TEXT("Edit"), TEXT("Biology,English,Mathematics..."),
                WS_BORDER | WS_VISIBLE | WS_CHILD,
                200, 170, 200, 20,
                hWnd, NULL, NULL, NULL);
            //TEXT BOXES
            subjects = model.getSubjects();
            sprintf_s(buff, "%s", subjects.c_str());
            cout << buff;
            subjectText = CreateWindow(TEXT("STATIC"), _T(buff),
                WS_BORDER | WS_VISIBLE | WS_CHILD,
                2, 70, 150, (_tcslen(buff) / 10) * 17,
                hWnd, NULL, NULL, NULL);

            subjects = model.getNextSemester(actualUser);
            sprintf_s(buff, "%s", subjects.c_str());
            cout << buff;
            subjectText = CreateWindow(TEXT("STATIC"), _T(buff),
                WS_BORDER | WS_VISIBLE | WS_CHILD,
                430, 70, 150, (_tcslen(buff) / 5) * 17,
                hWnd, NULL, NULL, NULL);

            //MORE BUTTONS
            enquiryMyResult = CreateWindow(TEXT("button"), TEXT("Enquiry My Result of Subject"),
                WS_VISIBLE | WS_CHILD,
                170, 30, 250, 45,
                hWnd, (HMENU)11, NULL, NULL);
            selectSubjects = CreateWindow(TEXT("button"), TEXT("Select Subjects for next semester"),
                WS_VISIBLE | WS_CHILD,
                170, 105, 250, 45,
                hWnd, (HMENU)12, NULL, NULL);
            calculateGPA = CreateWindow(TEXT("button"), TEXT("Calculate GPA"),
                WS_VISIBLE | WS_CHILD,
                240, 200, 120, 45,
                hWnd, (HMENU)13, NULL, NULL);
            break;
        }
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case 1://insertSubject
            //Get the subject
            gwtstat = GetWindowText(subjectTextBox, LPSTR(&subjectName[0]), 40);
            if (gwtstat == 0) {
                MessageBox(NULL, _T("Can you please enter the subject name."), _T("Error"), NULL);
                break;
            }
            //Get the credits
            char credits[40];
            gwtstat = GetWindowText(creditTextBox, LPSTR(&credits[0]), 40);
            if (gwtstat == 0) {
                MessageBox(NULL, _T("Can you please enter the credits."), _T("Error"), NULL);
                break;
            }
            model.insertSubject(subjectName, credits);
            MessageBox(NULL, _T("Subject added successfully!\nRestart the app to see the changes"), _T("Subject Added"), NULL);
            break;
        case 2://modifySubject
            //Get the subject
            gwtstat = GetWindowText(subjectTextBox, LPSTR(&subjectName[0]), 40);
            if (gwtstat == 0) {
                MessageBox(NULL, _T("Can you please enter the subject name."), _T("Error"), NULL);
                break;
            }
            //Get the new credits
            char newCredits[40];
            gwtstat = GetWindowText(creditTextBox, LPSTR(&newCredits[0]), 40);
            if (gwtstat == 0) {
                MessageBox(NULL, _T("Can you please enter the new credits."), _T("Error"), NULL);
                break;
            }
            model.modifySubject(subjectName, newCredits);
            MessageBox(NULL, _T("Subject modified successfully!\nRestart the app to see the changes"), _T("Subject Modified"), NULL);
            break;
        case 3://deleteSubject
            //Get the subject
            gwtstat = GetWindowText(subjectTextBox, LPSTR(&subjectName[0]), 40);
            if (gwtstat == 0) {
                MessageBox(NULL, _T("Can you please enter the subject name."), _T("Error"), NULL);
                break;
            }
            model.deleteSubject(subjectName);
            MessageBox(NULL, _T("Subject deleted successfully!\nRestart the app to see the changes"), _T("Subject Deleted"), NULL);
            break;
        case 4://searchSubject
            //Get the subject
            gwtstat = GetWindowText(subjectTextBox, LPSTR(&subjectName[0]), 40);
            if (gwtstat == 0) {
                MessageBox(NULL, _T("Can you please enter the subject name."), _T("Error"), NULL);
                break;
            }
            sprintf_s(buff, "%s", model.getSubject(subjectName).c_str());
            cout << buff;
            MessageBox(NULL, _T(buff), _T(subjectName), NULL);
            break;
        case 5://enquirySubject
            //Get the subject
            gwtstat = GetWindowText(subjectTextBox, LPSTR(&subjectName[0]), 40);
            if (gwtstat == 0) {
                MessageBox(NULL, _T("Can you please enter the subject name."), _T("Error"), NULL);
                break;
            }
            sprintf_s(buff, "%s", model.enquirySubject(subjectName).c_str());
            cout << buff;
            MessageBox(NULL, _T(buff), _T(subjectName), NULL);
            break;
        case 6://insertScore
            //Get the subject
            gwtstat = GetWindowText(subjectTextBox2, LPSTR(&subjectName[0]), 40);
            if (gwtstat == 0) {
                MessageBox(NULL, _T("Can you please enter the subject name."), _T("Error"), NULL);
                break;
            }
            //Get the student
            gwtstat = GetWindowText(studentTextBox, LPSTR(&student[0]), 40);
            if (gwtstat == 0) {
                MessageBox(NULL, _T("Can you please enter the student name."), _T("Error"), NULL);
                break;
            }
            //Get the score
            gwtstat = GetWindowText(scoreTextBox, LPSTR(&score[0]), 40);
            if (gwtstat == 0) {
                MessageBox(NULL, _T("Can you please enter the score."), _T("Error"), NULL);
                break;
            }
            model.insertScore(subjectName, student, score);
            MessageBox(NULL, _T("Score added successfully!\nRestart the app to see the changes"), _T("Score Added"), NULL);
            break;
        case 7://modifyScore
            //Get the subject
            gwtstat = GetWindowText(subjectTextBox2, LPSTR(&subjectName[0]), 40);
            if (gwtstat == 0) {
                MessageBox(NULL, _T("Can you please enter the subject name."), _T("Error"), NULL);
                break;
            }
            //Get the student
            gwtstat = GetWindowText(studentTextBox, LPSTR(&student[0]), 40);
            if (gwtstat == 0) {
                MessageBox(NULL, _T("Can you please enter the student name."), _T("Error"), NULL);
                break;
            }
            //Get the score
            gwtstat = GetWindowText(scoreTextBox, LPSTR(&score[0]), 40);
            if (gwtstat == 0) {
                MessageBox(NULL, _T("Can you please enter the score."), _T("Error"), NULL);
                break;
            }
            model.modifyScore(subjectName, student, score);
            MessageBox(NULL, _T("Score modified successfully!\nRestart the app to see the changes"), _T("Score Modified"), NULL);
            break;
        case 8://deleteScore
            //Get the subject
            gwtstat = GetWindowText(subjectTextBox2, LPSTR(&subjectName[0]), 40);
            if (gwtstat == 0) {
                MessageBox(NULL, _T("Can you please enter the subject name."), _T("Error"), NULL);
                break;
            }
            //Get the student
            gwtstat = GetWindowText(studentTextBox, LPSTR(&student[0]), 40);
            if (gwtstat == 0) {
                MessageBox(NULL, _T("Can you please enter the student name."), _T("Error"), NULL);
                break;
            }
            model.deleteScore(subjectName, student);
            MessageBox(NULL, _T("Score deleted successfully!\nRestart the app to see the changes"), _T("Score Deleted"), NULL);
            break;
        case 9://searchScore
            //Get the subject
            gwtstat = GetWindowText(subjectTextBox2, LPSTR(&subjectName[0]), 40);
            if (gwtstat == 0) {
                MessageBox(NULL, _T("Can you please enter the subject name."), _T("Error"), NULL);
                break;
            }
            //Get the student
            gwtstat = GetWindowText(studentTextBox, LPSTR(&student[0]), 40);
            if (gwtstat == 0) {
                MessageBox(NULL, _T("Can you please enter the student name."), _T("Error"), NULL);
                break;
            }
            sprintf_s(buff, "%s", model.getScore(subjectName,student).c_str());
            cout << buff;
            MessageBox(NULL, _T(buff), _T(student), NULL);
            break;
        case 10://enquiryStudent
            //Get the student
            gwtstat = GetWindowText(studentTextBox, LPSTR(&student[0]), 40);
            if (gwtstat == 0) {
                MessageBox(NULL, _T("Can you please enter the student name."), _T("Error"), NULL);
                break;
            }
            sprintf_s(buff, "%s", model.enquiryStudent(student).c_str());
            cout << buff;
            MessageBox(NULL, _T(buff), _T(student), NULL);
            break;
        case 11://enquiryMyResult
            sprintf_s(buff, "%s", model.enquiryStudent(actualUser).c_str());
            cout << buff;
            MessageBox(NULL, _T(buff), _T("Information"), NULL);
            break;
        case 12://selectSubjects
            //Get the subject
            gwtstat = GetWindowText(subjectTextBox, LPSTR(&subjectName[0]), 40);
            if (gwtstat == 0) {
                MessageBox(NULL, _T("Can you please enter the subjects."), _T("Error"), NULL);
                break;
            }
            model.saveNextSemesterSubjects(actualUser,subjectName);
            MessageBox(NULL, _T("Subjects for next semester saved successfully"), _T(subjectName), NULL);
            break;
        case 13://calculateGPA
            sprintf_s(buff, "%s", to_string(model.calculateGPA(actualUser)).c_str());
            cout << buff;
            MessageBox(NULL, _T(buff), _T("GPA"), NULL);
            break;
        }
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
        break;
    }
    return 0;
}
