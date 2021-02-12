#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <vector>
#include "Model.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK WndProc2(HWND, UINT, WPARAM, LPARAM);
void initSecondView();


HWND registerButton, loginButton, textField, userTextBox, passwordTextBox //Login View
, insertSubject, modifySubject, deleteSubject, searchSubject, insertScore, modifyScore, deleteScore, searchScore, enquiryStudent, enquirySubject //Teacher view
, enquiryMyResult, calculateGPA, selectSubjects; //Student view

Model model;
_In_ int nCmd;
HWND hWnd2;
int userType;
HINSTANCE hInstance2;
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
            if (answer[1] == "1") {
                sprintf_s(buff, "Bienvenido %s", answer[0].c_str());
                cout << buff;
                MessageBox(NULL, _T(buff), _T("Students portal"), NULL);
                ShowWindow(hWnd2, nCmd);
            }
            else if (answer[1] == "2") {
                sprintf_s(buff, "Bienvenido %s", answer[0].c_str());
                cout << buff;
                MessageBox(NULL, _T(buff), _T("Teachers portal"), NULL);
                ShowWindow(hWnd2, nCmd);
            }
            else {
                sprintf_s(buff, "%s", answer[0].c_str());
                cout << buff;
                MessageBox(NULL, _T(buff), _T("Error"), NULL);
            }
            break;
        case 2://Register
            PostMessage(hWnd, WM_CLOSE, 0, 0);
            userType = 2;
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

LRESULT CALLBACK WndProc2(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    PAINTSTRUCT ps;
    HDC hdc;
    TCHAR welcomeLabel[] = _T("Welcome to the student score system! please log in or register");
    int gwtstat = 0;

    switch (message) {
    case WM_CREATE: //When the window is just created
        switch (userType) {
        case 1:
            //BUTTONS
            insertSubject = CreateWindow(TEXT("button"), TEXT("Insert Subject"),
                WS_VISIBLE | WS_CHILD,
                125, 10, 120, 25,
                hWnd, (HMENU)1, NULL, NULL);
            modifySubject = CreateWindow(TEXT("button"), TEXT("Modify Subject"),
                WS_VISIBLE | WS_CHILD,
                125, 45, 120, 25,
                hWnd, (HMENU)2, NULL, NULL);
            deleteSubject = CreateWindow(TEXT("button"), TEXT("Delete Subject"),
                WS_VISIBLE | WS_CHILD,
                125, 80, 120, 25,
                hWnd, (HMENU)2, NULL, NULL);
            searchSubject = CreateWindow(TEXT("button"), TEXT("Search Subject"),
                WS_VISIBLE | WS_CHILD,
                125, 115, 120, 25,
                hWnd, (HMENU)2, NULL, NULL);
            deleteScore = CreateWindow(TEXT("button"), TEXT("Enquiry Subject"),
                WS_VISIBLE | WS_CHILD,
                125, 150, 120, 25,
                hWnd, (HMENU)2, NULL, NULL);
            insertScore = CreateWindow(TEXT("button"), TEXT("Insert Score"),
                WS_VISIBLE | WS_CHILD,
                255, 10, 120, 25,
                hWnd, (HMENU)2, NULL, NULL);
            modifyScore = CreateWindow(TEXT("button"), TEXT("Modify Score"),
                WS_VISIBLE | WS_CHILD,
                255, 45, 120, 25,
                hWnd, (HMENU)2, NULL, NULL);
            deleteScore = CreateWindow(TEXT("button"), TEXT("Delete Score"),
                WS_VISIBLE | WS_CHILD,
                255, 80, 120, 25,
                hWnd, (HMENU)2, NULL, NULL);
            searchScore = CreateWindow(TEXT("button"), TEXT("Search Score"),
                WS_VISIBLE | WS_CHILD,
                255, 115, 120, 25,
                hWnd, (HMENU)2, NULL, NULL);
            enquiryStudent = CreateWindow(TEXT("button"), TEXT("Enquiry Student"),
                WS_VISIBLE | WS_CHILD,
                255, 150, 120, 25,
                hWnd, (HMENU)2, NULL, NULL);
            break;
        case 2:
            enquiryMyResult = CreateWindow(TEXT("button"), TEXT("Enquiry My Result of Subject"),
                WS_VISIBLE | WS_CHILD,
                125, 10, 250, 45,
                hWnd, (HMENU)1, NULL, NULL);
            selectSubjects = CreateWindow(TEXT("button"), TEXT("Select Subjects for next semester"),
                WS_VISIBLE | WS_CHILD,
                125, 65, 250, 45,
                hWnd, (HMENU)2, NULL, NULL);
            calculateGPA = CreateWindow(TEXT("button"), TEXT("Calculate GPA"),
                WS_VISIBLE | WS_CHILD,
                190, 120, 120, 45,
                hWnd, (HMENU)2, NULL, NULL);
            break;
        }
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);

        EndPaint(hWnd, &ps);

        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_COMMAND:
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
        break;
    }
    return 0;
}
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
         WS_MINIMIZEBOX | WS_SYSMENU,
        CW_USEDEFAULT, CW_USEDEFAULT,
        500, 230,
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