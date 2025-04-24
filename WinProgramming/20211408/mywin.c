#define _CRT_SECURE_NO_WARNINGS
#include "mywin.h"
#include <stdio.h>
#include <string.h>

// 콘솔 너비(컬럼)
int getConsoleWidth() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        return csbi.srWindow.Right - csbi.srWindow.Left + 1;
    }
    return -1;
}

// 콘솔 높이(줄)
int getConsoleHeight() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        return csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    }
    return -1;
}

// WinAPI 커서 이동
void move_cursor(int row, int col) {
    COORD pos = { (SHORT)(col - 1), (SHORT)(row - 1) };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// 글자/배경 속성 설정
void set_color(WORD attr) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), attr);
}
void reset_color() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
        FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

// 여백 남기고 사각형 채우기
void fill_background_with_margin(int left, int right, int top, int bottom, WORD attr) {
    int w = getConsoleWidth();
    int h = getConsoleHeight();
    set_color(attr);
    for (int r = top; r < h - bottom; r++) {
        for (int c = left; c < w - right; c++) {
            move_cursor(r + 1, c + 1);
            putchar(' ');
        }
    }
    reset_color();
}

// 윈도우 그리기 (ASCII 박스)
void DrawWin(MyWin* w) {
    if (w->isMin) return;  // 최소화 상태면 그리지 않음

    int x = w->x, y = w->y;
    int W = w->width, H = w->height;
    WORD bg = w->color;
    WORD fg = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;

    // +-----+
    set_color(fg | bg);
    move_cursor(y, x);       printf("+");
    for (int i = 0; i < W - 2; i++) printf("-");
    printf("+");

    // 제목 + ●●● 버튼
    move_cursor(y, x + 2);     printf("%s", w->name);
    // 닫기(빨강)
    set_color(FOREGROUND_RED | bg);
    move_cursor(y, x + W - 6); printf("●");
    // 최소화(노랑)
    set_color(FOREGROUND_RED | FOREGROUND_GREEN | bg);
    move_cursor(y, x + W - 4); printf("●");
    // 최대화(초록)
    set_color(FOREGROUND_GREEN | bg);
    move_cursor(y, x + W - 2); printf("●");

    // 내부
    for (int r = 1; r < H - 1; r++) {
        set_color(fg | bg);
        move_cursor(y + r, x);   printf("|");
        reset_color();
        for (int i = 0; i < W - 2; i++) putchar(' ');
        set_color(fg | bg);
        printf("|");
    }

    // +-----+
    set_color(fg | bg);
    move_cursor(y + H - 1, x); printf("+");
    for (int i = 0; i < W - 2; i++) printf("-");
    printf("+");
    reset_color();
}

// 작업표시줄 (하단 2줄)
void DrawTaskbar() {
    int w = getConsoleWidth(), h = getConsoleHeight();
    WORD attr = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE; // 회색
    set_color(attr);
    for (int r = h - 2; r < h; r++) {
        for (int c = 0; c < w; c++) {
            move_cursor(r + 1, c + 1);
            putchar(' ');
        }
    }
    reset_color();
}
