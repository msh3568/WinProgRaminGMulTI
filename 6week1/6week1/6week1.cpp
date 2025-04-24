#include <stdio.h>
#include <conio.h>
#include <Windows.h>

int main() {
    // 배경을 노란색으로 설정 (E는 밝은 노란색 배경, 0은 검정색 글자)
    system("color E0");

    int x = 10; // 캐릭터 초기 x 좌표
    int y = 10; // 캐릭터 초기 y 좌표
    char ch;    // 입력받을 키

    printf("w,a,s,d로 캐릭터 A를 움직이세요. 종료하려면 q를 누르세요.\n");

    while (1) {
        // 화면 지우기
        system("cls");

        // 캐릭터 위치로 커서 이동
        for (int i = 0; i < y; i++) printf("\n"); // y축 이동
        for (int i = 0; i < x; i++) printf(" ");  // x축 이동
        printf("A"); // 캐릭터 출력

        // 키 입력이 있을 때까지 기다림
        if (_kbhit()) {
            ch = _getch(); // 키 입력 받기

            // w, a, s, d에 따라 캐릭터 이동
            if (ch == 'w' && y > 0) y--;      // 위로
            else if (ch == 'a' && x > 0) x--; // 왼쪽으로
            else if (ch == 's') y++;          // 아래로
            else if (ch == 'd') x++;          // 오른쪽으로
            else if (ch == 'q') break;        // q로 종료
        }
    }

    printf("\n프로그램 종료!\n");
    return 0;
}