
// Problem1/main.c
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

// 5. PassOrFail �Լ�: 50 �̻��̸� 1, �ƴϸ� 0 ��ȯ
int PassOrFail(int score) {
    return score >= 50 ? 1 : 0;
}

int main(void) {
    int score;

    // 6. �ֿܼ��� ����ڷκ��� ���� ���� �Է� �ޱ�
    printf("���� ��� ������ �Է��ϼ���: ");
    if (scanf("%d", &score) != 1) {
        printf("�Է��� �ùٸ��� �ʽ��ϴ�.\n");
        return 1;
    }

    // ��� ���
    if (PassOrFail(score)) {
        printf("����� �����ϴ�!\n");
    }
    else {
        printf("�츮�� ���ߴ١� ������̴١�\n");
    }

    return 0;
}
