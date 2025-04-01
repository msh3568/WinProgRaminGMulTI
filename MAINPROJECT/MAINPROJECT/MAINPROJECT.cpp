#include <stdio.h>
#include <windows.h>

// 커서 위치 설정 함수를 입력받음
void gotoxy(int x, int y) {
    COORD Cur;
    Cur.X = x;
    Cur.Y = y;
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(output, Cur);
} 

int main() {
    int width, height; //가로와 높이의 입력값을 받아버림

    // 유효한 입력 받을 때까지 반복
    while (1) {
        printf("원하는 가로 사이즈를 입력하세요 : "); // 첫 번째 입력 받는건 가로 사이즈
        scanf_s("%d", &width);
        printf("원하는 세로 사이즈를 입력하세요 : "); // 두 번째 입력 받는건 세로 사이즈
        scanf_s("%d", &height);

        system("cls"); // 입력 받았으니까 ㅇㅇ 위에있는거 지우셈

        if (width >= 2 && height >= 2) break;
        printf("너무 작아요 ;;; 가로랑 세로는 무조건 2 2 이상인데용;;;; .\n\n"); //2 미만으로 나올 경우 생성이 불가능하니까 이렇게 출력함
    }

    int middle = 2; // 두 번째 줄에서는 무조건 *이 나오게 하기 위해 입력 됨 약간 칸나누기 느낌스

    // 상단 테두리 출력
    gotoxy(0, 0); // 맨 위에 부터 출력이 되어야 합니다.
    for (int i = 0; i < width; i++) printf("*"); //첫 줄 테두리 입력

    // 중간 줄 출력
    for (int i = 1; i < height - 1; i++) {
        gotoxy(0, i); //중간부터니까 0, i임

        // 중간 위치에 '*' 테두리 출력
        if (i == middle) {
            for (int j = 0; j < width; j++) printf("*");
        }
        else {
            printf("[");
            for (int j = 1; j < width - 1; j++) printf(" ");
            printf("]");
        }
    }

    // 하단 테두리 출력
    gotoxy(0, height - 1); // 마지막 줄에서 * 출력함
    for (int i = 0; i < width; i++) printf("*");

    gotoxy(0, height + 1); // 커서 박스를 아래로 내리기
    return 0;
}