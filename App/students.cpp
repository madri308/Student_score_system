#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>

static TCHAR szWindowClass[] = _T("DesktopApp");
static TCHAR szTitle[] = _T("Student score system");

HINSTANCE hInst;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

HWND registerButton
    ,loginButton
    ,textField
    ,userTextBox
    ,passwordTextBox;

int CALLBACK WinMain(_In_ HINSTANCE hInstance,_In_opt_ HINSTANCE hPrevInstance,_In_ LPSTR lpCmdLine,_In_ int nCmdShow){
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
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

    if (!RegisterClassEx(&wcex)){
        MessageBox(NULL,_T("Call to RegisterClassEx failed!"),_T("Windows Desktop Guided Tour"),NULL);
        return 1;
    }

    hInst = hInstance;
    HWND hWnd = CreateWindow(
        szWindowClass,
        szTitle,
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


    switch (message){
    case WM_CREATE: //When the window is just created
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
            char userName[40];
            gwtstat = GetWindowText(userTextBox, LPWSTR(&userName[0]), 40);
            if (gwtstat == 0) {
                MessageBox(NULL, _T("Can you please enter your username."), _T("Error"), NULL);
                break;
            }

            char password[40];
            gwtstat = GetWindowText(passwordTextBox, LPWSTR(&password[0]), 40);
            if (gwtstat == 0) {
                MessageBox(NULL, _T("Can you please enter your password."), _T("Error"), NULL);
                break;
            }
            break;
        case 2://Register
            
            break;
        }
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
        break;
    }
    return 0;
}