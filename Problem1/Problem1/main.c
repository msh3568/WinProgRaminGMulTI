#include <stdio.h>

// ����(score)�� �޾� 50�� �̻��̸� 1, �ƴϸ� 0�� ��ȯ
int PassOrFail(int score) {
    if (score >= 50)
        return 1;
    else
        return 0;
}

int main() {
    // ������ ���������� �Է��ϼ���
    int myScore = 40;  // ��: 75��

    if (PassOrFail(myScore))
        printf("����� �����ϴ�!\n");
    else
        printf("�츮�� ���ߴ�... ������̴�...\n");

    return 0;
}
