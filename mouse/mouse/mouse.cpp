#include <windows.h>
#include <stdio.h>

// 콘솔 좌표 이동 함수
void gotoxy(int x, int y) {
    COORD pos = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// 콘솔 커서 숨기기
void hideCursor() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

// 콘솔 글꼴 크기 안전하게 가져오기
COORD getFontSizeSafe() {
    CONSOLE_FONT_INFO fontInfo;
    COORD fontSize = { 8, 16 };  // 기본값
    if (GetCurrentConsoleFont(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &fontInfo)) {
        if (fontInfo.dwFontSize.X > 0) fontSize.X = fontInfo.dwFontSize.X;
        if (fontInfo.dwFontSize.Y > 0) fontSize.Y = fontInfo.dwFontSize.Y;
    }
    return fontSize;
}

// 콘솔 클라이언트 영역의 좌측 상단 위치 (텍스트 영역 기준)
POINT getConsoleOriginInScreen() {
    HWND consoleWindow = GetConsoleWindow();
    RECT rect;
    GetClientRect(consoleWindow, &rect);

    POINT origin = { 0, 0 };
    ClientToScreen(consoleWindow, &origin); // 좌측 상단 픽셀 위치
    return origin;
}

int main() {
    POINT pt;
    int letterX = 10, letterY = 5;
    int isDragging = 0;

    hideCursor();
    system("cls");

    COORD fontSize = getFontSizeSafe();  // 글꼴 크기
    int fontWidth = fontSize.X;
    int fontHeight = fontSize.Y;

    POINT consoleOrigin = getConsoleOriginInScreen(); // 보정 기준점

    while (1) {
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
            break;

        GetCursorPos(&pt);

        // 보정: 콘솔 내부 텍스트 좌표 기준으로 계산
        int mouseX = (pt.x - consoleOrigin.x) / fontWidth;
        int mouseY = (pt.y - consoleOrigin.y) / fontHeight;

        // 클릭 → 드래그
        if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
            if (!isDragging && mouseX == letterX && mouseY == letterY) {
                isDragging = 1;
            }
            if (isDragging) {
                letterX = mouseX;
                letterY = mouseY;
            }
        }
        else {
            isDragging = 0;
        }

        system("cls");

        // A 출력
        gotoxy(letterX, letterY);
        printf("A");

        // 디버그 정보
        gotoxy(0, 0);
        printf("마우스: (%d, %d) | A 위치: (%d, %d)", mouseX, mouseY, letterX, letterY);

        Sleep(30);
    }

    return 0;
}
