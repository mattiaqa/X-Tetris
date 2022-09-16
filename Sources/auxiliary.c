#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../Libraries/dataStructure.h"
#include "../Libraries/auxiliary.h"
#include "../Libraries/field.h"
#include "../Libraries/tetramino.h"

void invertRow(fieldType *field, int deletedRow){
    size_t i, j;
    for(i = FIELD_ROW - 1; i > FIELD_ROW - deletedRow - 1; --i){
        for(j = 0; j < FIELD_COLS; ++j) {
            if (field[i * FIELD_COLS + j] == TETRAMINO)
                field[i * FIELD_COLS + j] = EMPTY;
            else if (field[i * FIELD_COLS + j] == EMPTY)
                field[i * FIELD_COLS + j] = TETRAMINO;
        }
    }
}

Color getColor(int idColor){
    int r, g, b;
    Color color;

    switch(idColor){
        case RANDOM_COLOR:
        {
            r = rand() % 255;
            g = rand() % 255;
            b = rand() % 255;
            break;
        }
        case BLACK_SWAG:
        {
            r = 32;
            g = 32;
            b = 32;
            break;
        }
        case CREAMY_WHITE:
        {
            r = 255;
            g = 253;
            b = 228;
            break;
        }
        case BLUETTE:
        {
            r = 102;
            g = 140;
            b = 255;
            break;
        }
        case GRENETTE:
        {
            r = 0;
            g = 128;
            b = 0;
            break;
        }
        case ROSETTE:
        {
            r = 255;
            g = 102;
            b = 102;
            break;
        }
        case YELLOWETTE:
        {
            r = 255;
            g = 191;
            b = 0;
            break;
        }
        case UGLY_COLOR:
        {
            r = 164;
            g = 191;
            b = 0;
            break;
        }
        case ULTRA_SWAG_GRAY:
        {
            r = 75;
            g = 75;
            b = 75;
            break;
        }
        case SEAGREEN:
        {
            r = 88;
            g = 239;
            b = 236;
            break;
        }
        case DARK_SEAGREEN:
        {
            r = 112;
            g = 215;
            b = 221;
            break;
        }
        case VERYDARK_SEAGREEN:
        {
            r = 136;
            g = 190;
            b = 205;
            break;
        }
        case AZZURRO3:
        {
            r = 0;
            g = 119;
            b = 182;
            break;
        }
        case AZZURRO4:
        {
            r = 0;
            g = 150;
            b = 199;
            break;
        }
        case AZZURRO5:
        {
            r = 0;
            g = 180;
            b = 216;
            break;
        }
        case AZZURRO6:
        {
            r = 72;
            g = 202;
            b = 228;
            break;
        }
        case AZZURRO7:
        {
            r = 144;
            g = 224;
            b = 239;
            break;
        }
        case AZZURRO8:
        {
            r = 173;
            g = 224;
            b = 239;
            break;
        }
        case AZZURRO9:
        {
            r = 202;
            g = 240;
            b = 240;
            break;
        }
        case BLACK_SWAG_LIGHT:
        {
            r = 55;
            g = 55;
            b = 55;
            break;
        }
        case BLACK_SWAG_L:
        {
            r = 39;
            g = 39;
            b = 39;
            break;
        }
        case YELLOW:
        {
            r = 253;
            g = 249;
            b = 0;
            break;
        }
        case LIGHTGRAY:
        {
            r = 200;
            g = 200;
            b = 200;
            break;
        }
        case GRAY:
        {
            r = 130;
            g = 130;
            b = 130;
            break;
        }
        case RED:
        {
            r = 230;
            g = 42;
            b = 55;
            break;
        }
    }
    color.r = r;
    color.g = g;
    color.b = b;
    color.a = 255;

    return color;
}

int bottomCollision(const fieldType *field, pieceType *piece){
    size_t i, j;
    size_t yTetramino = (size_t)piece->piecePosition.y;
    size_t xTetramino;

    for(i = 0; i < TETRAMINO_DIM; i++){
        xTetramino = (size_t)piece->piecePosition.x;
        for(j = 0; j < TETRAMINO_DIM ; j++){
            if(piece->structure[i * TETRAMINO_DIM + j] == TETRAMINO) {
                if(yTetramino == FIELD_ROW || field[yTetramino * FIELD_COLS + xTetramino] == TETRAMINO) {
                    return 1;
                }
                ++xTetramino;
            }else if(piece->structure[i * TETRAMINO_DIM + j] == INTERNAL_EMPTY){
                ++xTetramino;
            }
        }
        ++yTetramino;
    }
    return 0;
}

void savePiece(fieldType *field, pieceType *piece){
    size_t i, j;
    size_t yTetramino = (size_t)piece->piecePosition.y;
    size_t xTetramino;

    for(i = 0; i < TETRAMINO_DIM; i++){
        xTetramino = (size_t)piece->piecePosition.x;
        for(j = 0; j < TETRAMINO_DIM ; j++){
            if(piece->structure[i * TETRAMINO_DIM + j] == TETRAMINO) {
                field[yTetramino * FIELD_COLS + xTetramino] = TETRAMINO;
                ++xTetramino;
            }else if(piece->structure[i * TETRAMINO_DIM + j] == INTERNAL_EMPTY)
                ++xTetramino;
        }
        ++yTetramino;
    }
}

void blockLowering(fieldType *field, int deletedRow, int startRow){
    size_t i, j, k;
    for(k = 0; k < deletedRow; ++k){
        for(i = startRow; i > 0; i--){
            for(j = 0; j < FIELD_COLS; ++j){
                field[i * FIELD_COLS + j] = field[(i - 1) * FIELD_COLS + j];
            }
        }
    }
}

void checkFullRow(fieldType *field_player1, fieldType *field_player2, int *points_pl1, int *points_pl2, int is_multiplayer, int turn){
    size_t i, j, k, blocks, deletedRow = 0, start, set = 0;

    for(i = FIELD_ROW - 1; i > 0; i--){
        blocks = 0;
        for(j = 0; j < FIELD_COLS; ++j){
            if(field_player1[i * FIELD_COLS + j] == TETRAMINO)
                blocks++;
        }
        if(blocks == FIELD_COLS) {
            for(k = i; k < FIELD_COLS; ++k)
                field_player1[i * FIELD_COLS + j] = EMPTY;
            if(!set) {
                start = i;
                set = 1;
            }
            deletedRow++;
        }
    }

    if(deletedRow > 0)
        blockLowering(field_player1, (int)deletedRow, (int)start);

    if(is_multiplayer && deletedRow > 2){
        invertRow(field_player2, (int)deletedRow);
    }

    if(deletedRow == 2)
        (is_multiplayer) ? ( (turn % 2 != 0) ? (*points_pl1 += 3) : (*points_pl2 += 3)) : (*points_pl1 +=3);
    else if(deletedRow == 3)
        (is_multiplayer) ? ( (turn % 2 != 0) ? (*points_pl1 += 6) : (*points_pl2 += 6)) : (*points_pl1 +=6);
    else if(deletedRow == 1)
        (is_multiplayer) ? ((turn % 2 != 0) ? (*points_pl1)++ : (*points_pl2)++) : (*points_pl1)++;
    else if(deletedRow >= 4)
        (is_multiplayer) ? ( (turn % 2 != 0) ? (*points_pl1 += 12) : (*points_pl2 += 12)) : (*points_pl1 += 12);

}

void printGameOver(Font font, int points_pl1, int points_pl2, int turn, int is_multiplayer, char *nickname1, char *nickname2, Texture2D back_arrow){
    char *strTmp = malloc(20);
    Vector2 textOffset = {270, 150};

    sprintf(strTmp, "You gained %d points", (is_multiplayer) ? ((turn % 2 != 0) ? points_pl1 : points_pl2) : points_pl1);

    BeginDrawing();

    ClearBackground(getColor(BLACK_SWAG));
    DrawTextEx(font, "Game Over!", textOffset, 60, 3, getColor(AZZURRO5));

    textOffset.x = (float)SCREEN_WIDTH/2-((float)strlen(nickname1)/2)*40;
    textOffset.y = 300;

    DrawTextEx(font, (is_multiplayer) ? ((turn % 2 != 0) ? nickname1 : nickname2) : nickname1, textOffset, 40, 3, getColor(SEAGREEN));

    textOffset.x = 220;
    textOffset.y = 420;

    DrawTextEx(font, strTmp, textOffset, 40, 3, getColor(RANDOM_COLOR));

    textOffset.x = 330;
    textOffset.y = 670;

    DrawTexture(back_arrow, 920, 660, getColor(AZZURRO3));
    if(GetMouseX() >= 920 && GetMouseX() <= 1000 && GetMouseY() >= 660 && GetMouseY() <= 740){
        DrawTexture(back_arrow, 920, 660, getColor(AZZURRO9));
    }
    EndDrawing();
}

void printWin(Font font, int points_pl1, int points_pl2, int turn, int is_multiplayer, char *nickname1, char *nickname2, Texture2D trofeo, Texture2D back_arrow) {
    Vector2 textOffset = {0, 0};
    char *strTmp = malloc(20);
    ClearBackground(getColor(BLACK_SWAG));
    BeginDrawing();
    if (points_pl1 == points_pl2) {
        strTmp = "DRAW!";
        textOffset.x = ((float) SCREEN_WIDTH / 2) - ((float) (strlen(strTmp) * 50) / 2);
        textOffset.y = 300;
        DrawTextEx(font, strTmp, textOffset, 80, 2, getColor(RANDOM_COLOR));
    } else {
        sprintf(strTmp, "THE WINNER IS %s",
                (is_multiplayer) ? ((points_pl1 > points_pl2) ? nickname1 : nickname2) : nickname1);
        DrawTexture(trofeo, SCREEN_WIDTH / 2 - 50, 100, getColor(YELLOW));
        textOffset.x = ((float) SCREEN_WIDTH / 2) - ((float) (strlen(strTmp) * 23) / 2);
        textOffset.y = 300;
        DrawTextEx(font, strTmp, textOffset, 40, 1, getColor(RANDOM_COLOR));
        sprintf(strTmp, "You gained %d points",
                (is_multiplayer) ? ((points_pl1 > points_pl2) ? points_pl1 : points_pl2) : points_pl1);
        textOffset.x = ((float) SCREEN_WIDTH / 2) - ((float) (strlen(strTmp) * 23) / 2);
        textOffset.y = 450;
        DrawTextEx(font, strTmp, textOffset, 40, 1, getColor(AZZURRO5));
    }
    DrawTexture(back_arrow, 920, 660, getColor(AZZURRO3));
    if(GetMouseX() >= 920 && GetMouseX() <= 1000 && GetMouseY() >= 660 && GetMouseY() <= 740){
        DrawTexture(back_arrow, 920, 660, getColor(AZZURRO9));
    }
    EndDrawing();
}

void initGame(int *isPieceMoving, int *pieceID, int *points_pl1, int *points_pl2, int *gameOver,
              int *saved, int *gameStarted, int *turn, int *isWin, fieldType *field_player1, fieldType *field_player2,
              pieceType *activePiece){
    *isPieceMoving = 0;
    *pieceID = 0;
    *points_pl1 = 0;
    *points_pl2 = 0;
    *gameOver = 0;
    *saved = 0;
    *gameStarted = 0;
    *turn = 0;
    *isWin = 0;
    initField(field_player1);
    initField(field_player2);
    initPiece(activePiece);
}

int win(pieceInfo *infoPieces){
    size_t i;

    for(i = 0; i < 7; ++i){
        if(infoPieces[i].remaining != 0)
            return 0;
    }
    return 1;
}

int leftCollision(pieceType *piece, const fieldType *field){
    int yPiece = (int)piece->piecePosition.y;
    int xPiece = (int)piece->piecePosition.x;

    if(xPiece - 1 < 0 || field[yPiece * FIELD_COLS + xPiece - 1] == TETRAMINO)
        return 1;
    return 0;
}

int rightCollision(pieceType *piece, const fieldType *field){
    size_t i, j;
    size_t yPiece = (size_t)piece->piecePosition.y;
    size_t xPiece;

    for(i = 0; i < TETRAMINO_DIM; ++i){
        xPiece = (size_t)piece->piecePosition.x;
        for(j = 0; j < TETRAMINO_DIM; ++j){
            if(piece->structure[i * TETRAMINO_DIM + j] == TETRAMINO){
                if(xPiece + 1 > 9 || field[yPiece * FIELD_COLS + xPiece + 1] == TETRAMINO)
                    return 1;
                ++xPiece;
            }else if(piece->structure[i * TETRAMINO_DIM + j] == INTERNAL_EMPTY){
                ++xPiece;
            }
        }
        ++yPiece;
    }
    return 0;
}

