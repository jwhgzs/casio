#define FONT_WIDTH 5
#define FONT_GAP 1
#define FONT_HEIGHT 6

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "fxlib.h"
#include "MonochromeLib.h"
#include "syscall.h"

extern int time() {
    return RTC_GetTicks();
}

extern int intlen(int n) {
    return n > 0 ? ((int) log10(n)) + 1 : 1;
}
extern char* int2str(int n) {
    char *s = calloc(intlen(n) + 1, sizeof(char));
    int i, j, sign;
    char c;

    if ((sign = n) < 0)
        n = - n;
    i = 0;
    do {
        s[i ++] = n % 10 + '0';
    } while ((n /= 10) > 0);
    if (sign < 0)
        s[i ++] = '-';
    s[i] = '\0';
    for (i = 0, j = strlen(s) - 1; i < j; i ++, j --) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }

    return s;
}
extern char* strcon(char *a, char *b) {
    char *s = calloc(strlen(a) + strlen(b) + 1, sizeof(char));
    strcat(s, a);
    strcat(s, b);
    return s;
}
extern double randraw() {
    srand(time(0));
    return ((double) rand()) / RAND_MAX;
}
extern int randint(int a, int b) {
    srand(time(0));
    return a + rand() % (b - a + 1);
}

extern void PrintLocated(int x, int y, char *s, int type) {
    int len = strlen(s);
    PrintXY(x - len * FONT_WIDTH / 2 - (len - 1) * FONT_GAP, y - FONT_HEIGHT / 2, s, type);
}
extern void WaitAnyKey() {
    unsigned int keygot;
    while (1)
        if (GetKey(&keygot))
            break;
}
extern void WaitKey(unsigned int keycode) {
    unsigned int keygot;
    while (1)
        if (GetKey(&keygot) && keygot == keycode)
            break;
}
