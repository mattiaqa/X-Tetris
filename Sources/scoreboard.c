#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "../Libraries/scoreboard.h"
#include "../Libraries/auxiliary.h"

Color getColorScoreboard(int pos){
    Color color;
    switch (pos) {
        case 0:
            color.r = 158;
            color.g = 1;
            color.b = 66;
            break;
        case 1:
            color.r = 213;
            color.g = 62;
            color.b = 79;
            break;
        case 2:
            color.r = 244;
            color.g = 109;
            color.b = 67;
            break;
        case 3:
            color.r = 253;
            color.g = 174;
            color.b = 97;
            break;
        case 4:
            color.r = 254;
            color.g = 224;
            color.b = 139;
            break;
        case 5:
            color.r = 230;
            color.g = 245;
            color.b = 152;
            break;
        case 6:
            color.r = 171;
            color.g = 221;
            color.b = 164;
            break;
        case 7:
            color.r = 102;
            color.g = 194;
            color.b = 165;
            break;
        case 8:
            color.r = 50;
            color.g = 136;
            color.b = 189;
            break;
        case 9:
            color.r = 94;
            color.g = 79;
            color.b = 162;
            break;
        default:
            return getColor(CREAMY_WHITE);
    }
    color.a = 255;
    return color;
}

void sortEntries(entry *entries, int lines){
    size_t i, j;

    for(i = 0; i < (lines - 1); i++){
        for (j=(i + 1); j < lines; j++){
            if (entries[i].points < entries[j].points){
                entry temp = entries[i];
                entries[i] = entries[j];
                entries[j] = temp;
            }
        }
    }
}

int countLines(){
    FILE *fp = fopen("../Savings/scoreboard.txt","r");
    char ch;
    int lines = 0;

    if (fp == NULL)
        return 0;

    while(!feof(fp)){
        ch = (char)fgetc(fp);
        if(ch == '\n')
            lines++;
    }

    fclose(fp);
    return lines;
}

entry *loadFile(){
    int lines = countLines(), t;
    FILE *fptr;
    char str[50];
    size_t i;
    char *token;
    entry *entries;

    if(lines > 0){
        entries = malloc(sizeof(entry) * lines);
        fptr = fopen("../Savings/scoreboard.txt","r");

        for(i = 0; i < lines; i++){
            if(fgets(str, 50, fptr) != NULL){
                token = strtok(str, ";");
                strcpy(entries[i].nickname, token);

                token = strtok(NULL, ";");
                t = atoi(token);
                entries[i].points = t;

                token = strtok(NULL, ";");
                strcpy(entries[i].date, token);
            }
        }
        fclose(fptr);

        sortEntries(entries, lines);
        return entries;
    }

    return NULL;
}

void saveToFile(int points, char *nickname){
    FILE *fptr = fopen("../Savings/scoreboard.txt", "a");

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    fprintf(fptr, "%s;%d;%d-%d-%d\n", nickname, points, tm.tm_mday, tm.tm_mon+1, tm.tm_year+1900);

    fclose(fptr);
}

void printScoreboard(Font font, gameState *state, int *scoreboardLoaded, Texture2D back_arrow){
    int i, lines;
    entry *entries;
    Vector2 textOffset = {140, 100};
    char *strTmp = malloc(10);
    if(!(*scoreboardLoaded)){
        entries = loadFile();
        *scoreboardLoaded = 1;
    }

    lines = countLines();

    BeginDrawing();
    ClearBackground(getColor(BLACK_SWAG));

    DrawTextEx(font, "Nickname", textOffset, 25, 3, getColor(CREAMY_WHITE));
    textOffset.x += 320;
    DrawTextEx(font, "Score", textOffset, 25, 3, getColor(CREAMY_WHITE));
    textOffset.x += 300;
    DrawTextEx(font, "Date", textOffset, 25, 3, getColor(CREAMY_WHITE));

    textOffset.y += 50;

    if(lines > 0){
        for(i = 0; i < lines && i < 10; i++){
            textOffset.x = 110;

            sprintf(strTmp, "%d.", (i+1));
            DrawTextEx(font, strTmp, textOffset, 20, 2, getColorScoreboard(i));
            textOffset.x += 60;

            DrawTextEx(font, entries[i].nickname, textOffset, 20, 2, getColorScoreboard(i));
            textOffset.x += 325;

            sprintf(strTmp, "%d", entries[i].points);
            DrawTextEx(font, strTmp, textOffset, 20, 2, getColorScoreboard(i));
            textOffset.x += 225;

            DrawTextEx(font, entries[i].date, textOffset, 20, 2, getColorScoreboard(i));
            textOffset.y += 50;
        }
    }
    DrawTexture(back_arrow, 920, 660, getColor(AZZURRO3));
    if(GetMouseX() >= 920 && GetMouseX() <= 1000 && GetMouseY() >= 660 && GetMouseY() <= 740){
        DrawTexture(back_arrow, 920, 660, getColor(AZZURRO9));
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            *state = MENU;
        }
    }
    EndDrawing();
}
