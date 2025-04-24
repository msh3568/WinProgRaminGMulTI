
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <windows.h>

#define TOP_MARGIN    1
#define BOTTOM_MARGIN 1   // �۾�ǥ���� ����
#define LEFT_MARGIN   2
#define RIGHT_MARGIN  2

// ANSI ����
static void move_cursor(int row, int col) { printf("\x1b[%d;%dH", row, col); }
static void set_bg(int c) { printf("\x1b[%dm", 40 + c); }
static void set_fg(int c) { printf("\x1b[%dm", 30 + c); }
static void reset_color(void) { printf("\x1b[0m"); }

// ��棫�۾�ǥ���� (���� ���� ������)
void DrawBG(int W, int H) {
    printf("\x1b[2J");  // ��ü Ŭ����
    // �Ķ� ���
    for (int r = TOP_MARGIN + 1; r <= H - BOTTOM_MARGIN; ++r) {
        move_cursor(r, LEFT_MARGIN + 1);
        set_bg(4);
        for (int c = 0; c < W - LEFT_MARGIN - RIGHT_MARGIN; ++c) putchar(' ');
        reset_color();
    }
    // ȸ�� �۾�ǥ����
    move_cursor(H, LEFT_MARGIN + 1);
    set_bg(7);
    for (int c = 0; c < W - LEFT_MARGIN - RIGHT_MARGIN; ++c) putchar(' ');
    reset_color();
}

// �ܼ� ������ �׸���
// startX/startY: �»��, width/height: �׵θ� ���� ��ü ũ��
// title: â ����, color: ANSI ����(0~7)
void drawConsoleWindow(int startX, int startY, int width, int height,
    const char* title, int color)
{
    int innerW = width - 2;    // ���� ��
    int tlen = (int)strlen(title);

    // 1) ��� �׵θ�
    move_cursor(startY, startX);
    set_bg(color);
    putchar('|');
    for (int i = 0; i < innerW; ++i) putchar('-');
    putchar('|');
    reset_color();

    // 2) ������ (��ü �����, �����ʿ� X)
    move_cursor(startY + 1, startX);
    set_bg(color);
    putchar('|');
    // ���� ��ü ������� ä���
    for (int i = 0; i < innerW; ++i) putchar(' ');
    putchar('|');
    reset_color();

    // ���� ����� (�鿩���� 2ĭ)
    move_cursor(startY + 1, startX + 2);
    set_bg(color); set_fg(7);
    printf("%s", title);
    reset_color();

    // X ��ư (�����ʿ��� �� ĭ ��)
    move_cursor(startY + 1, startX + width - 2);
    set_bg(1); set_fg(7);
    putchar('X');
    reset_color();

    // 3) ����
    for (int r = 2; r < height - 1; ++r) {
        move_cursor(startY + r, startX);
        set_bg(color); putchar('|');
        for (int i = 0; i < innerW; ++i) putchar(' ');
        putchar('|');
        reset_color();
    }

    // 4) �ϴ� �׵θ�
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
    drawConsoleWindow(15, 5, 52, 15, "���� ���� ������ ���α׷���", 3);

    // �̹��� �߰��� �κ�: ���� �ȳ� �޽���
    move_cursor(H, 1);
    printf("\n\n���α׷��� ���������� ����Ǿ����ϴ�. �Ʒ� �޽����� Ȯ���ϼ���.\n");

    // Ŀ�� �����
    printf("\x1b[?25l");
    return 0;
}

