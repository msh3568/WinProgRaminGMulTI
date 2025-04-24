#ifndef MYWIN_H
#define MYWIN_H

#include <windows.h>

// ������ â ����ü
typedef struct {
    int  x, y;          // ������ ���� ��ǥ(1-based)
    int  width, height; // ������ ũ��
    char name[100];     // ����
    WORD color;         // ���� �Ӽ� (BACKGROUND_* | FOREGROUND_*)
    int  isMax;         // �ִ�ȭ �÷���
    int  isMin;         // �ּ�ȭ �÷���
    // �ִ�ȭ �� ������
    int prevX, prevY, prevW, prevH;
} MyWin;

// �ܼ� ���� & Ŀ�� ����
int  getConsoleWidth();
int  getConsoleHeight();
void move_cursor(int row, int col);

// ���� ����
void set_color(WORD attr);
void reset_color();

// ��� ä��� (���� �����)
void fill_background_with_margin(int left, int right, int top, int bottom, WORD attr);

// ������ �� �۾�ǥ���� �׸���
void DrawWin(MyWin* w);
void DrawTaskbar();

#endif // MYWIN_H
