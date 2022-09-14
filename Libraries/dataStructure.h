#ifndef X_TETRIS_DATASTRUCTURE_H
#define X_TETRIS_DATASTRUCTURE_H

#include "raylib.h"
#include "../Libraries/palette.h"

#define TETRAMINO_DIM 4

#define FIELD_COLS 10
#define FIELD_ROW 15

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 740

#define SCREEN_WIDTH_MULTI 1440
#define SCREEN_HEIGHT_MULTI 800

typedef enum{
    TETRAMINO,
    MOVING,
    EMPTY,
    INTERNAL_EMPTY
} fieldType;

typedef enum{
    MENU,
    SINGLEPLAYER,
    COMMANDS,
    CHOOSE_NAME,
    CHOOSE_MULTIPLAYER,
    MULTIPLAYER_PVP,
    MULTIPLAYER_PVE,
    SCOREBOARD,
    EXIT
} gameState;

typedef struct {
    int pieceID;
    int remaining;
}pieceInfo;

typedef struct{
    fieldType structure[16];
    Color color;
    Vector2 piecePosition;
}pieceType;

#endif
