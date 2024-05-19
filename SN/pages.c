#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "fxlib.h"
#include "MonochromeLib.h"
#include "images.h"
#include "funcs.h"
#include "data.h"

void page_game_draw_scoreboard(int *s1, int *s2) {
    char *s = "SN ";
    s = strcon(s, int2str(*s1));
    s = strcon(s, " - ");
    s = strcon(s, int2str(*s2));
    s = strcon(s, " ME");
    PrintXY(0, 0, s, 0);
}
void page_game_draw_word(char *w1, char *w2) {
    PrintLocated(ML_SCREEN_WIDTH / 2, ML_SCREEN_HEIGHT / 2, w1, 0);
}
void page_game_turn(int *s1, int *s2) {
    char *w1 = calloc(SN_WORDS_LENGTH + 1, sizeof(char)), *w2 = calloc(SN_WORDS_LENGTH + 1, sizeof(char));
    int file = Bfile_OpenFile(/*strcon(SN_WORDS_DIR, int2str(randint(1, SN_WORDS_COUNTS)))*/"\\\\fls0\\1.txt", _OPENMODE_READ);
    Bfile_ReadFile(file, w1, SN_WORDS_LENGTH, 0);
    Bfile_CloseFile(file);

    ML_clear_vram();
    page_game_draw_scoreboard(s1, s2);
    w1 = int2str(file);
    page_game_draw_word(w1, w2);
    ML_display_vram();
}

extern void page_game_entry() {
    int s1 = 0, s2 = 0, i = 0;

    // for (i = 0; i < SN_REGULAR_TURNS; i ++) {
        page_game_turn(&s1, &s2);
    // }
}
