#include <Windows.h>
#include <stdio.h>

void gotoxy(int x, int y)
{
      COORD Cur; //short형을 두개 가지고ㅓ 있는 자료구조형임
      Cur.X = x;
      Cur.Y = y;

      HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);

      SetConsoleCursorPosition(output, Cur); // 핸들이라는게 조종하는 컨트롤러 요 핸들같은 경우 받아온다 이런게os의 제어건을 받아온다 어떤 걸 가져오냐 콘솔 핸들에 관한 정보를 가져온다 Output커서 포지션을 커서 라고 하는곳에 x,y를 저장함 
}


int main()
{
    gotoxy(19,19);
    puts("으악ㄱ아아");
    return 0;
}