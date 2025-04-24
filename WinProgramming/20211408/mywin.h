#ifndef MYWIN_H
#define MYWIN_H

#include <windows.h>

// 윈도우 창 구조체
typedef struct {
    int  x, y;          // 윈도우 시작 좌표(1-based)
    int  width, height; // 윈도우 크기
    char name[100];     // 제목
    WORD color;         // 배경색 속성 (BACKGROUND_* | FOREGROUND_*)
    int  isMax;         // 최대화 플래그
    int  isMin;         // 최소화 플래그
    // 최대화 전 복원용
    int prevX, prevY, prevW, prevH;
} MyWin;

// 콘솔 정보 & 커서 조작
int  getConsoleWidth();
int  getConsoleHeight();
void move_cursor(int row, int col);

// 색상 제어
void set_color(WORD attr);
void reset_color();

// 배경 채우기 (여백 남기고)
void fill_background_with_margin(int left, int right, int top, int bottom, WORD attr);

// 윈도우 및 작업표시줄 그리기
void DrawWin(MyWin* w);
void DrawTaskbar();

#endif // MYWIN_H
