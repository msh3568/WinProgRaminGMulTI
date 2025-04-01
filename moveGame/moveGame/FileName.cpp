#include <stdio.h>
#include <conio.h>

int dislayMenu() {

	puts("********************************");
	puts("*         이것 뭐에요?         *");
	puts("********************************");
}

int moveCh() {
	char land[30];
	int chara = 0;

	for (int i = 0; i < 30; i++)
	{
		if ( i == chara){print}
	}
}

int main() {

	dislayMenu();

		char choice;
		choice = _getch();

		if (choice == '1') {
			moveCh();
		}

		else if (choice == '2')
		{
			puts("종료해벌임");
		}

		else
		{
			puts("다시 시도 ㄱㄱ");
		}

		return 0;
}