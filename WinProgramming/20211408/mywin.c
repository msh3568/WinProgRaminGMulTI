#define _CRT_SECURE_NO_WARNINGS
#include "mywin.h"
#include <stdio.h>
#include <string.h>

// �ܼ� �ʺ�(�÷�)
int getConsoleWidth() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        return csbi.srWindow.Right - csbi.srWindow.Left + 1;
    }
    return -1;
}

// �ܼ� ����(��)
int getConsoleHeight() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        return csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    }
    return -1;
}

// WinAPI Ŀ�� �̵�
void move_cursor(int row, int col) {
    COORD pos = { (SHORT)(col - 1), (SHORT)(row - 1) };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// ����/��� �Ӽ� ����
void set_color(WORD attr) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), attr);
}
void reset_color() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
        FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

// ���� ����� �簢�� ä���
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

// ������ �׸��� (ASCII �ڽ�)
void DrawWin(MyWin* w) {
    if (w->isMin) return;  // �ּ�ȭ ���¸� �׸��� ����

    int x = w->x, y = w->y;
    int W = w->width, H = w->height;
    WORD bg = w->color;
    WORD fg = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;

    // +-----+
    set_color(fg | bg);
    move_cursor(y, x);       printf("+");
    for (int i = 0; i < W - 2; i++) printf("-");
    printf("+");

    // ���� + �ܡܡ� ��ư
    move_cursor(y, x + 2);     printf("%s", w->name);
    // �ݱ�(����)
    set_color(FOREGROUND_RED | bg);
    move_cursor(y, x + W - 6); printf("��");
    // �ּ�ȭ(���)
    set_color(FOREGROUND_RED | FOREGROUND_GREEN | bg);
    move_cursor(y, x + W - 4); printf("��");
    // �ִ�ȭ(�ʷ�)
    set_color(FOREGROUND_GREEN | bg);
    move_cursor(y, x + W - 2); printf("��");

    // ����
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

// �۾�ǥ���� (�ϴ� 2��)
void DrawTaskbar() {
    int w = getConsoleWidth(), h = getConsoleHeight();
    WORD attr = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE; // ȸ��
    set_color(attr);
    for (int r = h - 2; r < h; r++) {
        for (int c = 0; c < w; c++) {
            move_cursor(r + 1, c + 1);
            putchar(' ');
        }
    }
    reset_color();
}
