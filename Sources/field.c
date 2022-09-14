#include <stdlib.h>
#include <stdio.h>

#include "../Libraries/dataStructure.h"
#include "../Libraries/field.h"
#include "../Libraries/tetramino.h"
#include "../Libraries/auxiliary.h"

void printField(const fieldType *field, Font font, int pieceID, Color color, pieceInfo *infoPieces, const int *points, Texture2D back_arrow){
    size_t i, j;
    Vector2 fieldOffset = {80, 70}, textOffset = {660, 130}, tmpOffset = {600, 155};
    char *strTmp = malloc(20);
    pieceType *tmp = malloc(sizeof(pieceType));
    Color BlackSwag = {32, 32, 32, 255};
    BeginDrawing();
    ClearBackground(BlackSwag);

    DrawRectangle((int)fieldOffset.x - 5, (int)fieldOffset.y - 5, 410, 610, getColor(CREAMY_WHITE));

    for(i = 0; i < FIELD_ROW; ++i){
        for(j = 0; j < FIELD_COLS; ++j){
            if(field[i * FIELD_COLS + j] == EMPTY){
                DrawRectangle((int)fieldOffset.x, (int)fieldOffset.y, 40, 40, getColor(BLACK_SWAG_LIGHT));
                DrawLine((int)fieldOffset.x, (int)fieldOffset.y, (int)fieldOffset.x + 40, (int)fieldOffset.y, getColor(CREAMY_WHITE ));
                DrawLine((int)fieldOffset.x, (int)fieldOffset.y, (int)fieldOffset.x, (int)fieldOffset.y + 40, getColor(CREAMY_WHITE ));
                DrawLine((int)fieldOffset.x + 40, (int)fieldOffset.y, (int)fieldOffset.x + 40, (int)fieldOffset.y + 40, getColor(CREAMY_WHITE ));
                DrawLine((int)fieldOffset.x, (int)fieldOffset.y + 40 , (int)fieldOffset.x + 40, (int)fieldOffset.y + 40, getColor(CREAMY_WHITE ));
            }
            if(field[i * FIELD_COLS + j] == MOVING){
                DrawRectangle((int)fieldOffset.x, (int)fieldOffset.y, 40, 40, color);
            }
            if(field[i * FIELD_COLS + j] == TETRAMINO){
                DrawRectangle((int)fieldOffset.x, (int)fieldOffset.y, 40, 40, getColor(GRAY));
            }

            fieldOffset.x += 40;
        }
        fieldOffset.y += 40;
        fieldOffset.x = 80;
    }

    DrawRectangle(550, 0, 450, 740, getColor(BLACK_SWAG_L));

    sprintf(strTmp, "Remaining piece %d", infoPieces[pieceID].remaining);

    DrawTextEx(font, "Choose your piece", textOffset, 15, 3, getColor(CREAMY_WHITE));
    DrawRectangle(595, 150, 370, 250, getColor(AZZURRO9));

    textOffset.x = 660;
    textOffset.y = 420;
    DrawTextEx(font, strTmp, textOffset, 17, 2, getColor(CREAMY_WHITE));

    for(i = 0; i < 4; i++){
        for(j = 0; j < 6; j++){
            DrawRectangle((int)tmpOffset.x, (int)tmpOffset.y, 60, 60, getColor(BLACK_SWAG_LIGHT));
            DrawLine((int)tmpOffset.x, (int)tmpOffset.y, (int)tmpOffset.x + 60, (int)tmpOffset.y, getColor(CREAMY_WHITE ));
            DrawLine((int)tmpOffset.x, (int)tmpOffset.y, (int)tmpOffset.x, (int)tmpOffset.y + 60, getColor(CREAMY_WHITE ));
            DrawLine((int)tmpOffset.x + 60, (int)tmpOffset.y, (int)tmpOffset.x + 60, (int)tmpOffset.y + 60, getColor(CREAMY_WHITE ));
            DrawLine((int)tmpOffset.x, (int)tmpOffset.y + 60 , (int)tmpOffset.x + 60, (int)tmpOffset.y + 60, getColor(CREAMY_WHITE ));
            tmpOffset.x += 60;
        }
        tmpOffset.y += 60;
        tmpOffset.x = 600;
    }

    fieldOffset.x = 660;
    fieldOffset.y = 215;

    getTetraminoFromID(pieceID, tmp);
    for(i = 0; i < TETRAMINO_DIM; i++){
        for(j = 0; j < TETRAMINO_DIM; j++){
            if(tmp->structure[i * TETRAMINO_DIM + j] == TETRAMINO)
                DrawRectangle((int)fieldOffset.x, (int)fieldOffset.y, 60, 60, getColor(AZZURRO3));
            fieldOffset.x += 60;
        }
        fieldOffset.y += 60;
        fieldOffset.x = 660;
    }

    sprintf(strTmp, "Points %d", *points);
    textOffset.x = 660;
    textOffset.y = 500;
    DrawTextEx(font, strTmp, textOffset, 40, 2, getColor(AZZURRO6));

    textOffset.x = 605;
    textOffset.y = 10;
    DrawTextEx(font, "X-Tetris", textOffset, 60, 3, getColor(AZZURRO8));

    DrawTexture(back_arrow, 920, 660, getColor(AZZURRO3));
    if(GetMouseX() >= 920 && GetMouseX() <= 1000 && GetMouseY() >= 660 && GetMouseY() <= 740){
        DrawTexture(back_arrow, 920, 660, getColor(AZZURRO9));
    }
    EndDrawing();
}

void printField_multiplayer(const fieldType *field_1, const fieldType *field_2, Font font, int pieceID, Color color, pieceInfo *infoPieces, const int *points_pl1, const int *points_pl2, char *nickname1, char *nickname2, int turn, Texture2D back_arrow){
    size_t i, j;
    Vector2 fieldOffset = {40, 100}, textOffset = {580, 105}, tmpOffset = {540, 155};
    char *strTmp = malloc(20);
    pieceType *tmp = malloc(sizeof(pieceType));

    BeginDrawing();
    ClearBackground(getColor(BLACK_SWAG));

    DrawRectangle((int)fieldOffset.x - 5, (int)fieldOffset.y - 5, 410, 610, (turn % 2 != 0) ? getColor(ULTRA_SWAG_GRAY) : getColor(VERYDARK_SEAGREEN));

    for(i = 0; i < FIELD_ROW; ++i){
        for(j = 0; j < FIELD_COLS; ++j){
            if(field_1[i * FIELD_COLS + j] == EMPTY){
                DrawRectangle((int)fieldOffset.x, (int)fieldOffset.y, 40, 40, (turn % 2 != 0) ? getColor(BLACK_SWAG) : getColor(BLACK_SWAG_LIGHT));
                DrawLine((int)fieldOffset.x, (int)fieldOffset.y, (int)fieldOffset.x + 40, (int)fieldOffset.y, (turn % 2 != 0) ? getColor(ULTRA_SWAG_GRAY) : getColor(CREAMY_WHITE));
                DrawLine((int)fieldOffset.x, (int)fieldOffset.y, (int)fieldOffset.x, (int)fieldOffset.y + 40, (turn % 2 != 0) ? getColor(ULTRA_SWAG_GRAY) : getColor(CREAMY_WHITE));
                DrawLine((int)fieldOffset.x + 40, (int)fieldOffset.y, (int)fieldOffset.x + 40, (int)fieldOffset.y + 40, (turn % 2 != 0) ? getColor(ULTRA_SWAG_GRAY) : getColor(CREAMY_WHITE));
                DrawLine((int)fieldOffset.x, (int)fieldOffset.y + 40 , (int)fieldOffset.x + 40, (int)fieldOffset.y + 40, (turn % 2 != 0) ? getColor(ULTRA_SWAG_GRAY) : getColor(CREAMY_WHITE));
            }
            if(field_1[i * FIELD_COLS + j] == MOVING){
                DrawRectangle((int)fieldOffset.x, (int)fieldOffset.y, 40, 40, color);
            }
            if(field_1[i * FIELD_COLS + j] == TETRAMINO){
                DrawRectangle((int)fieldOffset.x, (int)fieldOffset.y, 40, 40, getColor(GRAY));
            }

            fieldOffset.x += 40;
        }
        fieldOffset.y += 40;
        fieldOffset.x = 40;
    }

    fieldOffset.x = 1000;
    fieldOffset.y = 100;

    DrawRectangle((int)fieldOffset.x - 5, (int)fieldOffset.y - 5, 410, 610, (turn % 2 == 0) ? getColor(ULTRA_SWAG_GRAY) : getColor(VERYDARK_SEAGREEN));

    for(i = 0; i < FIELD_ROW; ++i){
        for(j = 0; j < FIELD_COLS; ++j){
            if(field_2[i * FIELD_COLS + j] == EMPTY){
                DrawRectangle((int)fieldOffset.x, (int)fieldOffset.y, 40, 40, (turn % 2 == 0) ? getColor(BLACK_SWAG) : getColor(BLACK_SWAG_LIGHT));
                DrawLine((int)fieldOffset.x, (int)fieldOffset.y, (int)fieldOffset.x + 40, (int)fieldOffset.y, (turn % 2 == 0) ? getColor(ULTRA_SWAG_GRAY) : getColor(CREAMY_WHITE));
                DrawLine((int)fieldOffset.x, (int)fieldOffset.y, (int)fieldOffset.x, (int)fieldOffset.y + 40, (turn % 2 == 0) ? getColor(ULTRA_SWAG_GRAY) : getColor(CREAMY_WHITE));
                DrawLine((int)fieldOffset.x + 40, (int)fieldOffset.y, (int)fieldOffset.x + 40, (int)fieldOffset.y + 40, (turn % 2 == 0) ? getColor(ULTRA_SWAG_GRAY) : getColor(CREAMY_WHITE));
                DrawLine((int)fieldOffset.x, (int)fieldOffset.y + 40 , (int)fieldOffset.x + 40, (int)fieldOffset.y + 40, (turn % 2 == 0) ? getColor(ULTRA_SWAG_GRAY) : getColor(CREAMY_WHITE));
            }
            if(field_2[i * FIELD_COLS + j] == MOVING){
                DrawRectangle((int)fieldOffset.x, (int)fieldOffset.y, 40, 40, color);
            }
            if(field_2[i * FIELD_COLS + j] == TETRAMINO){
                DrawRectangle((int)fieldOffset.x, (int)fieldOffset.y, 40, 40, getColor(GRAY));
            }

            fieldOffset.x += 40;
        }
        fieldOffset.y += 40;
        fieldOffset.x = 1000;
    }

    DrawRectangle(500, 0, 440, 800, getColor(BLACK_SWAG_L));

    sprintf(strTmp, "Remaining piece %d", infoPieces[pieceID].remaining);

    DrawTextEx(font, "Choose your piece", textOffset, 20, 3, getColor(CREAMY_WHITE));
    DrawRectangle(535, 150, 370, 250, getColor(AZZURRO9));

    textOffset.x = 600;
    textOffset.y = 410;
    DrawTextEx(font, strTmp, textOffset, 17, 2, getColor(CREAMY_WHITE));

    for(i = 0; i < 4; i++){
        for(j = 0; j < 6; j++){
            DrawRectangle((int)tmpOffset.x, (int)tmpOffset.y, 60, 60, getColor(BLACK_SWAG_LIGHT));
            DrawLine((int)tmpOffset.x, (int)tmpOffset.y, (int)tmpOffset.x + 60, (int)tmpOffset.y, getColor(CREAMY_WHITE));
            DrawLine((int)tmpOffset.x, (int)tmpOffset.y, (int)tmpOffset.x, (int)tmpOffset.y + 60, getColor(CREAMY_WHITE));
            DrawLine((int)tmpOffset.x + 60, (int)tmpOffset.y, (int)tmpOffset.x + 60, (int)tmpOffset.y + 60, getColor(CREAMY_WHITE));
            DrawLine((int)tmpOffset.x, (int)tmpOffset.y + 60 , (int)tmpOffset.x + 60, (int)tmpOffset.y + 60, getColor(CREAMY_WHITE));
            tmpOffset.x += 60;
        }
        tmpOffset.y += 60;
        tmpOffset.x = 540;
    }

    fieldOffset.x = 600;
    fieldOffset.y = 215;

    getTetraminoFromID(pieceID, tmp);
    for(i = 0; i < TETRAMINO_DIM; i++){
        for(j = 0; j < TETRAMINO_DIM; j++){
            if(tmp->structure[i * TETRAMINO_DIM + j] == TETRAMINO)
                DrawRectangle((int)fieldOffset.x, (int)fieldOffset.y, 60, 60, getColor(AZZURRO3));
            fieldOffset.x += 60;
        }
        fieldOffset.y += 60;
        fieldOffset.x = 600;
    }

    sprintf(strTmp, "%s", nickname1);
    textOffset.x = 50;
    textOffset.y = 50;
    DrawTextEx(font, strTmp , textOffset, 30, 2, (turn % 2 != 0) ? getColor(ULTRA_SWAG_GRAY) : getColor(DARK_SEAGREEN));
    sprintf(strTmp, "%s", nickname2);
    textOffset.x = 1010;
    textOffset.y = 50;
    DrawTextEx(font, strTmp , textOffset, 30, 2, (turn % 2 == 0) ? getColor(ULTRA_SWAG_GRAY) : getColor(DARK_SEAGREEN));

    sprintf(strTmp, "Points %d", *points_pl1);
    textOffset.x = 610;
    textOffset.y = 500;
    DrawTextEx(font, strTmp, textOffset, 40, 2, (turn % 2 != 0) ? getColor(ULTRA_SWAG_GRAY) : getColor(DARK_SEAGREEN));
    sprintf(strTmp, "Points %d", *points_pl2);
    textOffset.x = 610;
    textOffset.y = 570;
    DrawTextEx(font, strTmp, textOffset, 40, 2, (turn % 2 == 0) ? getColor(ULTRA_SWAG_GRAY) : getColor(DARK_SEAGREEN));

    DrawTexture(back_arrow, SCREEN_WIDTH_MULTI/2-40, 650, getColor(AZZURRO3));
    if(GetMouseX() >= SCREEN_WIDTH_MULTI/2-40 && GetMouseX() <= SCREEN_WIDTH_MULTI/2+40 && GetMouseY() >= 650 && GetMouseY() <= 730){
        DrawTexture(back_arrow, SCREEN_WIDTH_MULTI/2-40, 650, getColor(AZZURRO9));
    }

    EndDrawing();
}

void initField(fieldType *field){
    size_t i, j;

    for(i = 0; i < FIELD_ROW; i++){
        for(j = 0; j < FIELD_COLS; j++){
            field[i * FIELD_COLS + j] = EMPTY;
        }
    }
}

void updateField(fieldType *field){
    size_t i, j;

    for(i = 0; i < FIELD_ROW; i++){
        for(j = 0; j < FIELD_COLS; j++){
            if(field[i * FIELD_COLS + j] != TETRAMINO){
                field[i * FIELD_COLS + j] = EMPTY;
            }
        }
    }
}

void assignPieceToField(fieldType *field, pieceType *piece){
    size_t i, j;
    size_t yPiece = (size_t)piece->piecePosition.y;
    size_t yPieceOld = (size_t)piece->piecePosition.y-1;
    size_t xPiece;

    for(i = 0; i < TETRAMINO_DIM; i++){
        xPiece = (size_t)piece->piecePosition.x;
        for(j = 0; j < TETRAMINO_DIM ; j++){
            if(piece->structure[i * TETRAMINO_DIM + j] == TETRAMINO) {
                field[yPiece * FIELD_COLS + xPiece] = EMPTY;
                ++xPiece;
            }else if(piece->structure[i * TETRAMINO_DIM + j] == INTERNAL_EMPTY)
                ++xPiece;
        }
        ++yPieceOld;
    }

    updateField(field);

    for(i = 0; i < TETRAMINO_DIM; i++){
        xPiece = (size_t)piece->piecePosition.x;
        for(j = 0; j < TETRAMINO_DIM ; j++){
            if(piece->structure[i * TETRAMINO_DIM + j] == TETRAMINO) {
                field[yPiece * FIELD_COLS + xPiece] = MOVING;
                ++xPiece;
            }else if(piece->structure[i * TETRAMINO_DIM + j] == INTERNAL_EMPTY)
                ++xPiece;
        }
        ++yPiece;
    }
}
