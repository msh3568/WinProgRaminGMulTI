#include <stdio.h>

// 점수(score)를 받아 50점 이상이면 1, 아니면 0을 반환
int PassOrFail(int score) {
    if (score >= 50)
        return 1;
    else
        return 0;
}

int main() {
    // 본인의 예상점수를 입력하세요
    int myScore = 40;  // 예: 75점

    if (PassOrFail(myScore))
        printf("재시험 없습니다!\n");
    else
        printf("우리는 망했다... 재시험이다...\n");

    return 0;
}
