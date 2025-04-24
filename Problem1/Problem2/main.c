#include <stdio.h>

#define TOP_MARGIN    1
#define BOTTOM_MARGIN 1   // 작업표시줄 영역 포함
#define LEFT_MARGIN   2
#define RIGHT_MARGIN  2

// width×height 해상도, 여백은 상하 1칸, 좌우 2칸
void DrawBG(int width, int height) {
    // 1) 화면 전체 지우기
    printf("\x1b[2J");

    // 2) 바탕화면(파랑) 그리기: row = TOP_MARGIN+1 … height-BOTTOM_MARGIN
    for (int row = TOP_MARGIN + 1; row <= height - BOTTOM_MARGIN; ++row) {
        // 컬럼 시작 = LEFT_MARGIN + 1
        printf("\x1b[%d;%dH", row, LEFT_MARGIN + 1);
        printf("\x1b[44m");  // 배경 파랑
        for (int col = 0; col < width - LEFT_MARGIN - RIGHT_MARGIN; ++col) {
            putchar(' ');
        }
        printf("\x1b[0m");  // 색 리셋
    }

    // 3) 작업표시줄(하단 1줄) 그리기: row = height
    // 좌우 여백 안쪽만 채우기
    printf("\x1b[%d;%dH", height, LEFT_MARGIN + 1);
    printf("\x1b[47m");  // 밝은 회색
    for (int col = 0; col < width - LEFT_MARGIN - RIGHT_MARGIN; ++col) {
        putchar(' ');
    }
    printf("\x1b[0m");

    // 4) 커서 위치 고정 (선택)
    printf("\x1b[%d;1H", height + 1);
}

int main(void) {
    // 예제: 80×25 해상도
    DrawBG(80, 25);
    return 0;
}
