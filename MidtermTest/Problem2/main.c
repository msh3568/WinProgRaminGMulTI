
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <windows.h>

#define TOP_MARGIN    1
#define BOTTOM_MARGIN 1   // 작업표시줄 높이
#define LEFT_MARGIN   2
#define RIGHT_MARGIN  2

// ANSI 헬퍼
static void move_cursor(int row, int col) { printf("\x1b[%d;%dH", row, col); }
static void set_bg(int c) { printf("\x1b[%dm", 40 + c); }
static void set_fg(int c) { printf("\x1b[%dm", 30 + c); }
static void reset_color(void) { printf("\x1b[0m"); }

// 배경＋작업표시줄 (여백 제외 영역만)
void DrawBG(int W, int H) {
    printf("\x1b[2J");  // 전체 클리어
    // 파란 배경
    for (int r = TOP_MARGIN + 1; r <= H - BOTTOM_MARGIN; ++r) {
        move_cursor(r, LEFT_MARGIN + 1);
        set_bg(4);
        for (int c = 0; c < W - LEFT_MARGIN - RIGHT_MARGIN; ++c) putchar(' ');
        reset_color();
    }
    // 회색 작업표시줄
    move_cursor(H, LEFT_MARGIN + 1);
    set_bg(7);
    for (int c = 0; c < W - LEFT_MARGIN - RIGHT_MARGIN; ++c) putchar(' ');
    reset_color();
}

// 콘솔 윈도우 그리기
// startX/startY: 좌상단, width/height: 테두리 포함 전체 크기
// title: 창 제목, color: ANSI 배경색(0~7)
void drawConsoleWindow(int startX, int startY, int width, int height,
    const char* title, int color)
{
    int innerW = width - 2;    // 내부 폭
    int tlen = (int)strlen(title);

    // 1) 상단 테두리
    move_cursor(startY, startX);
    set_bg(color);
    putchar('|');
    for (int i = 0; i < innerW; ++i) putchar('-');
    putchar('|');
    reset_color();

    // 2) 제목줄 (전체 노란색, 오른쪽에 X)
    move_cursor(startY + 1, startX);
    set_bg(color);
    putchar('|');
    // 내부 전체 노란으로 채우기
    for (int i = 0; i < innerW; ++i) putchar(' ');
    putchar('|');
    reset_color();

    // 제목 덮어쓰기 (들여쓰기 2칸)
    move_cursor(startY + 1, startX + 2);
    set_bg(color); set_fg(7);
    printf("%s", title);
    reset_color();

    // X 버튼 (오른쪽에서 한 칸 전)
    move_cursor(startY + 1, startX + width - 2);
    set_bg(1); set_fg(7);
    putchar('X');
    reset_color();

    // 3) 내부
    for (int r = 2; r < height - 1; ++r) {
        move_cursor(startY + r, startX);
        set_bg(color); putchar('|');
        for (int i = 0; i < innerW; ++i) putchar(' ');
        putchar('|');
        reset_color();
    }

    // 4) 하단 테두리
    move_cursor(startY + height - 1, startX);
    set_bg(color);
    putchar('|');
    for (int i = 0; i < innerW; ++i) putchar('-');
    putchar('|');
    reset_color();
}

int main(void) {
    const int W = 80, H = 25;
    DrawBG(W, H);
    drawConsoleWindow(15, 5, 52, 15, "나의 멋진 윈도우 프로그래밍", 3);

    // 이번에 추가된 부분: 종료 안내 메시지
    move_cursor(H, 1);
    printf("\n\n프로그램이 정상적으로 종료되었습니다. 아래 메시지를 확인하세요.\n");

    // 커서 숨기기
    printf("\x1b[?25l");
    return 0;
}

