
// Problem1/main.c
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

// 5. PassOrFail 함수: 50 이상이면 1, 아니면 0 반환
int PassOrFail(int score) {
    return score >= 50 ? 1 : 0;
}

int main(void) {
    int score;

    // 6. 콘솔에서 사용자로부터 예상 점수 입력 받기
    printf("예상 평균 점수를 입력하세요: ");
    if (scanf("%d", &score) != 1) {
        printf("입력이 올바르지 않습니다.\n");
        return 1;
    }

    // 결과 출력
    if (PassOrFail(score)) {
        printf("재시험 없습니다!\n");
    }
    else {
        printf("우리는 망했다… 재시험이다…\n");
    }

    return 0;
}
