#include <windows.h>
#include <stdio.h>

int main() {
    system("color E0");

    int x = 20; // 캐릭터 초기 x 좌표
    int y = 10; // 캐릭터 초기 y 좌표

    //초반 간단한 튜토리얼..? 비슷한거 어떻게 움직이는지, 나가는 방법
    printf("곧 게임이 시작됩니다 \nw,a,s,d로 캐릭터 A를 움직이세요.\n종료하려면 q를 누르세요.\n");

    Sleep(3000);
    system("cls");

    printf("5초뒤 게임이 시작됩니다");
    Sleep(1000);

    system("cls");
    printf("5");
    Sleep(1000);

    system("cls");
    printf("4");
    Sleep(1000);

    system("cls");
    printf("3");
    Sleep(1000);

    system("cls");
    printf("2");
    Sleep(1000);

    system("cls");
    printf("1");
    Sleep(1000);

    while (1) {
        system("cls");

        for (int i = 0; i < y; i++) printf("\n"); // y축 이동
        for (int i = 0; i < x; i++) printf(" ");  // x축 이동
        printf("O"); // 캐릭터 출력

        // 키 입력 처리
        if (GetAsyncKeyState('W') & 0x8000 && y > 0) y--;      // 위로
        if (GetAsyncKeyState('A') & 0x8000 && x > 0) x--;      // 왼쪽으로
        if (GetAsyncKeyState('S') & 0x8000) y++;               // 아래로
        if (GetAsyncKeyState('D') & 0x8000) x++;               // 오른쪽으로
        if (GetAsyncKeyState('Q') & 0x8000) {                  // 종료
            printf("\n게임 종료\n");
            break;
        }

        // CPU 사용량 줄이기 위한 대기
        Sleep(15);
    }

    return 0;
}