#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <stdio.h>
#include <string.h>

// 콘솔 레이아웃 상수
#define SCREEN_W     80
#define SCREEN_H     25
#define TOP_MARGIN    1
#define BOTTOM_MARGIN 1
#define LEFT_MARGIN   2
#define RIGHT_MARGIN  2

// 윈도우 개수
#define MAX_WINDOWS 3

// 윈도우 구조체
typedef struct {
    int x, y;         // 좌상단 위치 (1-based)
    int w, h;         // 크기 (테두리 포함)
    int color;        // ANSI 배경색 (0–7)
    int open;         // 열림 여부
    char title[32];   // 제목
} Window;

// 세 개의 윈도우 정의
Window wins[MAX_WINDOWS] = {
    {  5,  3, 20,  8, 3, 1, "Window1" },
    { 30,  3, 20,  8, 2, 1, "Window2" },
    { 55,  3, 20,  8, 5, 1, "Window3" }
};

// ANSI 헬퍼
static void move_cursor(int r, int c) { printf("\x1b[%d;%dH", r, c); }
static void set_bg(int c) { printf("\x1b[%dm", 40 + c); }
static void set_fg(int c) { printf("\x1b[%dm", 30 + c); }
static void reset_color() { printf("\x1b[0m"); }

// 바탕화면 + 작업표시줄
void DrawBG() {
    printf("\x1b[2J");
    for (int r = TOP_MARGIN + 1; r <= SCREEN_H - BOTTOM_MARGIN; ++r) {
        move_cursor(r, LEFT_MARGIN + 1);
        set_bg(4);
        for (int c = 0; c < SCREEN_W - LEFT_MARGIN - RIGHT_MARGIN; ++c) putchar(' ');
        reset_color();
    }
    move_cursor(SCREEN_H, LEFT_MARGIN + 1);
    set_bg(7);
    for (int c = 0; c < SCREEN_W - LEFT_MARGIN - RIGHT_MARGIN; ++c) putchar(' ');
    reset_color();
}

// 하나의 윈도우 그리기
void drawWindow(const Window* w) {
    int innerW = w->w - 2;
    int tlen = (int)strlen(w->title);
    if (tlen > innerW - 4) tlen = innerW - 4;

    // 상단 테두리
    move_cursor(w->y, w->x);
    set_bg(w->color); putchar('|');
    for (int i = 0; i < innerW; ++i) putchar('-');
    putchar('|'); reset_color();

    // 제목줄 배경
    move_cursor(w->y + 1, w->x);
    set_bg(w->color); putchar('|');
    for (int i = 0; i < innerW; ++i) putchar(' ');
    putchar('|'); reset_color();

    // 제목 텍스트
    move_cursor(w->y + 1, w->x + 2);
    set_fg(7); set_bg(w->color);
    fwrite(w->title, 1, tlen, stdout);
    reset_color();

    // X 버튼
    move_cursor(w->y, w->x + w->w - 3);
    set_bg(1); set_fg(7); putchar('X'); reset_color();

    // 내부
    for (int dy = 2; dy < w->h - 1; ++dy) {
        move_cursor(w->y + dy, w->x);
        set_bg(w->color); putchar('|');
        for (int i = 0; i < innerW; ++i) putchar(' ');
        putchar('|'); reset_color();
    }

    // 하단 테두리
    move_cursor(w->y + w->h - 1, w->x);
    set_bg(w->color); putchar('|');
    for (int i = 0; i < innerW; ++i) putchar('-');
    putchar('|'); reset_color();
}

// 이전 커서 자리 복원
void restore_cell(COORD p) {
    int row = p.Y + 1, col = p.X + 1;
    // Z-order: 뒤에서부터 검사
    for (int i = MAX_WINDOWS - 1; i >= 0; --i) {
        Window* w = &wins[i];
        if (!w->open) continue;
        if (row >= w->y && row < w->y + w->h &&
            col >= w->x && col < w->x + w->w)
        {
            int ry = row - w->y, rx = col - w->x;
            // 테두리/내부 모두 배경색으로 복원
            set_bg(w->color);
            move_cursor(row, col);
            if (ry == 0 || ry == w->h - 1) putchar('-');
            else if (rx == 0 || rx == w->w - 1) putchar('|');
            else putchar(' ');
            reset_color();
            return;
        }
    }
    // 작업표시줄
    if (row == SCREEN_H && col > LEFT_MARGIN && col <= SCREEN_W - RIGHT_MARGIN) {
        set_bg(7);
        move_cursor(row, col);
        putchar(' ');
        reset_color();
        return;
    }
    // 나머지 데스크탑
    if (row > TOP_MARGIN && row < SCREEN_H) {
        set_bg(4);
        move_cursor(row, col);
        putchar(' ');
        reset_color();
    }
}

int main(void) {
    // VT & 마우스 설정
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE), hIn = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode;
    GetConsoleMode(hOut, &mode);
    SetConsoleMode(hOut, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
    GetConsoleMode(hIn, &mode);
    mode &= ~(ENABLE_QUICK_EDIT_MODE | ENABLE_INSERT_MODE);
    mode |= ENABLE_MOUSE_INPUT | ENABLE_WINDOW_INPUT;
    SetConsoleMode(hIn, mode);
    printf("\x1b[?25l");

    // 초기 그리기
    DrawBG();
    for (int i = 0; i < MAX_WINDOWS; ++i)
        if (wins[i].open) drawWindow(&wins[i]);

    // 이벤트 루프
    COORD prev = { -1,-1 };
    INPUT_RECORD ir; DWORD cnt;
    while (1) {
        ReadConsoleInput(hIn, &ir, 1, &cnt);
        if (ir.EventType != MOUSE_EVENT) continue;
        MOUSE_EVENT_RECORD m = ir.Event.MouseEvent;
        int row = m.dwMousePosition.Y + 1, col = m.dwMousePosition.X + 1;

        // 클릭: 먼저 Close
        if (m.dwEventFlags == 0 && (m.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)) {
            // X 버튼 클릭
            for (int i = 0; i < MAX_WINDOWS; ++i) {
                Window* w = &wins[i];
                if (!w->open) continue;
                if (row == w->y && col == w->x + w->w - 3) {
                    w->open = 0;
                    // 덮어쓰기
                    for (int ry = 0; ry < w->h; ++ry) {
                        move_cursor(w->y + ry, w->x);
                        for (int cx = 0; cx < w->w; ++cx) {
                            set_bg((ry == SCREEN_H) ? 7 : 4);
                            putchar(' ');
                        }
                        reset_color();
                    }
                }
            }
            // 내부 클릭 → 최상위로 이동
            for (int i = 0; i < MAX_WINDOWS; ++i) {
                Window w = wins[i];
                if (!w.open) continue;
                if (row >= w.y && row < w.y + w.h &&
                    col >= w.x && col < w.x + w.w)
                {
                    // 단, X 클릭은 이미 처리됨
                    if (!(row == w.y && col == w.x + w.w - 3)) {
                        // reorder
                        for (int j = i; j < MAX_WINDOWS - 1; ++j) wins[j] = wins[j + 1];
                        wins[MAX_WINDOWS - 1] = w;
                        // 전체 재그리기
                        DrawBG();
                        for (int k = 0; k < MAX_WINDOWS; ++k)
                            if (wins[k].open) drawWindow(&wins[k]);
                    }
                    break;
                }
            }
        }

        // 이동: 커서 갱신
        if (m.dwEventFlags & MOUSE_MOVED) {
            COORD cur = m.dwMousePosition;
            if (prev.X != -1) restore_cell(prev);
            if (cur.X >= LEFT_MARGIN && cur.X < SCREEN_W - RIGHT_MARGIN &&
                cur.Y >= TOP_MARGIN && cur.Y < SCREEN_H - BOTTOM_MARGIN)
            {
                move_cursor(cur.Y + 1, cur.X + 1);
                set_fg(7); putchar('<'); reset_color();
                prev = cur;
            }
        }
    }

    return 0;
}
