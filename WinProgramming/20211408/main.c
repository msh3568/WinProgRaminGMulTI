// main.c
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include "mywin.h"

#define LEFT_MARGIN   5
#define RIGHT_MARGIN  5
#define TOP_MARGIN    1
#define BOTTOM_MARGIN 3
#define MAX_WINDOWS   3

// 화면 전체를 다시 그리는 함수
void RedrawAll(MyWin wins[]) {
    fill_background_with_margin(LEFT_MARGIN, RIGHT_MARGIN, TOP_MARGIN, BOTTOM_MARGIN, BACKGROUND_BLUE);
    DrawTaskbar();
    for (int i = 0; i < MAX_WINDOWS; i++) {
        DrawWin(&wins[i]);
    }
}

int main() {
    // 1) 콘솔 VT 모드 켜기
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD outMode;
    GetConsoleMode(hOut, &outMode);
    SetConsoleMode(hOut, outMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);

    // 2) 마우스 입력 모드 설정
    HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
    DWORD inMode;
    GetConsoleMode(hIn, &inMode);
    inMode &= ~(ENABLE_QUICK_EDIT_MODE | ENABLE_INSERT_MODE);
    inMode |= (ENABLE_MOUSE_INPUT | ENABLE_WINDOW_INPUT);
    SetConsoleMode(hIn, inMode);

    // 3) 초기 화면 구성
    system("cls");
    MyWin wins[MAX_WINDOWS] = { 0 };

    // 첫 번째 윈도우 (cyan)
    strcpy(wins[0].name, "First");
    wins[0].x = 10; wins[0].y = 3;
    wins[0].width = 40; wins[0].height = 12;
    wins[0].color = BACKGROUND_BLUE | BACKGROUND_GREEN;

    // 두 번째 윈도우 (magenta)
    strcpy(wins[1].name, "Second");
    wins[1].x = 20; wins[1].y = 6;
    wins[1].width = 50; wins[1].height = 10;
    wins[1].color = BACKGROUND_RED | BACKGROUND_BLUE;

    // 세 번째 윈도우 (brown → yellow)
    strcpy(wins[2].name, "Third");
    wins[2].x = 30; wins[2].y = 9;
    wins[2].width = 45; wins[2].height = 11;
    wins[2].color = BACKGROUND_RED | BACKGROUND_GREEN;

    RedrawAll(wins);

    INPUT_RECORD rec;
    DWORD cnt;
    COORD lastPos = { -1, -1 };

    while (1) {
        ReadConsoleInput(hIn, &rec, 1, &cnt);

        if (rec.EventType != MOUSE_EVENT)
            continue;

        MOUSE_EVENT_RECORD m = rec.Event.MouseEvent;
        COORD pos = m.dwMousePosition;

        // 마우스 이동 또는 클릭 중 하나라도 발생하면
        if ((m.dwEventFlags & MOUSE_MOVED) ||
            (m.dwEventFlags == 0 && (m.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)))
        {
            lastPos = pos;                  // 최신 위치 저장
            RedrawAll(wins);                // 화면 전체 재그리기

            // 좌클릭 처리 (닫기/최대화/최상위/복원)
            if (m.dwEventFlags == 0 && (m.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)) {
                // 제목바 클릭 검사
                for (int i = 0; i < MAX_WINDOWS; i++) {
                    MyWin* w = &wins[i];
                    if (w->isMin) continue;
                    if (pos.Y + 1 == w->y) {
                        int lx = pos.X + 1 - w->x;
                        if (lx == w->width - 6) {
                            w->isMin = 1;  // 닫기(최소화)
                        }
                        else if (lx == w->width - 2) {
                            // 최대화/복원 토글
                            if (!w->isMax) {
                                w->prevX = w->x; w->prevY = w->y;
                                w->prevW = w->width; w->prevH = w->height;
                                w->x = LEFT_MARGIN + 1; w->y = TOP_MARGIN + 1;
                                w->width = getConsoleWidth() - LEFT_MARGIN - RIGHT_MARGIN - 2;
                                w->height = getConsoleHeight() - TOP_MARGIN - BOTTOM_MARGIN - 2;
                                w->isMax = 1;
                            }
                            else {
                                w->x = w->prevX; w->y = w->prevY;
                                w->width = w->prevW; w->height = w->prevH;
                                w->isMax = 0;
                            }
                        }
                        // 최상위 순서로 이동
                        MyWin tmp = *w;
                        for (int j = i; j < MAX_WINDOWS - 1; j++)
                            wins[j] = wins[j + 1];
                        wins[MAX_WINDOWS - 1] = tmp;
                        break;
                    }
                }
                // 작업표시줄 클릭 → 최소화된 윈도우 복원
                int tbY = getConsoleHeight() - 1;
                if (pos.Y == tbY) {
                    for (int i = 0; i < MAX_WINDOWS; i++) {
                        int iconX = 1 + i * 12;
                        if (pos.X + 1 >= iconX
                            && pos.X + 1 < iconX + (int)strlen(wins[i].name) + 2
                            && wins[i].isMin) {
                            wins[i].isMin = 0;
                            break;
                        }
                    }
                }
                // 다시 전체 그리기
                RedrawAll(wins);
            }

            // 커서(+) 그리기
            if (pos.X >= LEFT_MARGIN
                && pos.X < getConsoleWidth() - RIGHT_MARGIN
                && pos.Y >= TOP_MARGIN
                && pos.Y < getConsoleHeight() - BOTTOM_MARGIN)
            {
                set_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                move_cursor(pos.Y + 1, pos.X + 1);
                putchar('+');
                reset_color();
            }
        }
    }

    return 0;
}
