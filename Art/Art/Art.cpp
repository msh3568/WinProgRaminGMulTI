#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <windows.h>

#define MOVE_CURSOR(x, y) printf("\033[%d;%dH", (y), (x))

typedef struct {
    int x, y;
    int width, height;
    char title[32];
    char color[16];
    char art[3][30]; 
} Window;

void draw_window(Window* win) {
    printf("%s", win->color);

    MOVE_CURSOR(win->x, win->y);
    for (int i = 0; i < win->width; i++) printf("*");

    MOVE_CURSOR(win->x, win->y + 1);
    printf("[");
    for (int i = 0; i < win->width - 2; i++) printf(" ");
    printf("]");

    MOVE_CURSOR(win->x, win->y + 2);
    for (int i = 0; i < win->width; i++) printf("*");

    for (int i = 0; i < 3; i++) {
        MOVE_CURSOR(win->x, win->y + 3 + i);
        printf("[%-*s]", win->width - 2, win->art[i]);
    }

    MOVE_CURSOR(win->x, win->y + 6);
    for (int i = 0; i < win->width; i++) printf("*");

    printf("\033[0m");
}

void draw_desktop() {
    system("cls");
    printf("\033[42m");
    for (int y = 0; y < 20; y++) {
        for (int x = 0; x < 60; x++) {
            printf(" ");
        }
        printf("\n");
    }
    printf("\033[0m");
}

int main() {
    draw_desktop();

    Window base = {
        0, 0, 28, 7,
        "흠..냐륑~",
        "\033[36m",
        {
            "  /\\_/\\   /\\_/\\  ",
            " ( o.o ) ( o.o ) ",
            "  > ^ <   > ^ <  "
        }
    };

    Window win1 = base;
    Window* pWin1 = &win1;
    pWin1->x = 5;
    pWin1->y = 3;
    draw_window(pWin1);

    Window win2 = base;
    Window* pWin2 = &win2;
    pWin2->x = 30;
    pWin2->y = 10;
    strcpy(pWin2->color, "\033[34m");
    draw_window(pWin2);

    (void)getchar();
    return 0;
}
