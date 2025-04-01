#include <stdio.h>
#include <stdlib.h>

int game() {
    int length = 25;
    int pos = length / 2;
    char input[10];
    char move;

    while (1) {
        system("cls");

        for (int i = 0; i < length; i++) {
            if (i == pos)
                printf("0");
            else
                printf("_");
        }
        printf("\nA: 왼쪽, D: 오른쪽, Q: 종료\n");

        fgets(input, sizeof(input), stdin);
        move = input[0];

        if (move == 'a' || move == 'A') {
            if (pos > 0)
                pos--;
        }
        else if (move == 'd' || move == 'D') {
            if (pos < length - 1)
                pos++;
        }
        else if (move == 'q' || move == 'Q') {
            break;
        }
    }

    return 0;
}

int main() {
    game();  
    return 0;
}
