#include <stdio.h>

#define TOP_MARGIN    1
#define BOTTOM_MARGIN 1   // �۾�ǥ���� ���� ����
#define LEFT_MARGIN   2
#define RIGHT_MARGIN  2

// width��height �ػ�, ������ ���� 1ĭ, �¿� 2ĭ
void DrawBG(int width, int height) {
    // 1) ȭ�� ��ü �����
    printf("\x1b[2J");

    // 2) ����ȭ��(�Ķ�) �׸���: row = TOP_MARGIN+1 �� height-BOTTOM_MARGIN
    for (int row = TOP_MARGIN + 1; row <= height - BOTTOM_MARGIN; ++row) {
        // �÷� ���� = LEFT_MARGIN + 1
        printf("\x1b[%d;%dH", row, LEFT_MARGIN + 1);
        printf("\x1b[44m");  // ��� �Ķ�
        for (int col = 0; col < width - LEFT_MARGIN - RIGHT_MARGIN; ++col) {
            putchar(' ');
        }
        printf("\x1b[0m");  // �� ����
    }

    // 3) �۾�ǥ����(�ϴ� 1��) �׸���: row = height
    // �¿� ���� ���ʸ� ä���
    printf("\x1b[%d;%dH", height, LEFT_MARGIN + 1);
    printf("\x1b[47m");  // ���� ȸ��
    for (int col = 0; col < width - LEFT_MARGIN - RIGHT_MARGIN; ++col) {
        putchar(' ');
    }
    printf("\x1b[0m");

    // 4) Ŀ�� ��ġ ���� (����)
    printf("\x1b[%d;1H", height + 1);
}

int main(void) {
    // ����: 80��25 �ػ�
    DrawBG(80, 25);
    return 0;
}
