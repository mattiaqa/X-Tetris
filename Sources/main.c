#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../Libraries/dataStructure.h"
#include "../Libraries/field.h"
#include "../Libraries/tetramino.h"
#include "../Libraries/auxiliary.h"
#include "../Libraries/scoreboard.h"
#include "../Libraries/menu.h"
#include "../Libraries/bot.h"

int main() {
    fieldType *field_player1 = malloc(sizeof(fieldType) * FIELD_ROW * FIELD_COLS);
    fieldType *field_player2 = malloc(sizeof(fieldType) * FIELD_ROW * FIELD_COLS);
    fieldType *field = field_player1;
    pieceType *activePiece = malloc(sizeof(pieceType));
    pieceInfo *infoPieces = malloc(sizeof(pieceInfo) * 7);

    gameState state = MENU;

    int frameCounter = 0, isPieceMoving = 0, pieceID = 0, speed = 25, points_pl1 = 0, points_pl2 = 0;
    int saved = 0, letterCount_pl1 = 0, letterCount_pl2 = 0, scoreboardLoaded = 0, gameStarted = 0, turn = 0;
    int isWin = 0, is_pve = 0, rotation, gameInitiated = 0, gameOver = 0, is_multiplayer = 0, pieceSaved = 1;

    char *nickname1 = malloc(sizeof(char) * 13);
    char *nickname2 = malloc(sizeof(char) * 13);
    char *errorText = malloc(sizeof(char) * 50);

    Image leftArrow_img, trofeo_img;
    Texture2D backArrow_texture, trofeo_texture;

    Font karmaticArcade, followTheArrow;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "X-Tetris");
    SetWindowPosition(220, 0);

    SetTargetFPS(60);

    leftArrow_img = LoadImage("../Image/curved-left-arrow.png");
    ImageResize(&leftArrow_img, 80, 80);
    backArrow_texture = LoadTextureFromImage(leftArrow_img);
    UnloadImage(leftArrow_img);
    trofeo_img = LoadImage("../Image/trofeo.png");
    ImageResize(&trofeo_img, 100, 100);
    trofeo_texture = LoadTextureFromImage(trofeo_img);
    UnloadImage(trofeo_img);

    karmaticArcade = LoadFontEx("../Fonts/karmatic_arcade.ttf", 300, 0, 250);
    followTheArrow = LoadFontEx("../Fonts/FollowTheArrow.ttf", 300, 0, 250);

    srand(time(0));

    while(!WindowShouldClose()) {
        switch (state) {
            case MENU:
                gameInitiated = 0;
                memset(nickname1, 0, sizeof(*nickname1));
                memset(errorText, 0, sizeof(*errorText));
                memset(nickname2, 0, sizeof(*nickname2));
                letterCount_pl1 = 0;
                letterCount_pl2 = 0;
                is_multiplayer = 0;
                is_pve = 0;
                scoreboardLoaded = 0;
                printMenu(&state, karmaticArcade);
                break;
            case CHOOSE_NAME:
                choose_name(&state, nickname1, nickname2, &letterCount_pl1, &letterCount_pl2, karmaticArcade,
                            is_multiplayer, backArrow_texture, errorText, is_pve);
                break;
            case COMMANDS:
                printCommands(karmaticArcade, followTheArrow, backArrow_texture, &state);
                break;
            case SINGLEPLAYER:
                if (!gameInitiated) {
                    SetWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
                    SetWindowPosition(220, 0);

                    initInfo(infoPieces, is_multiplayer);

                    initGame(&isPieceMoving, &pieceID, &points_pl1,
                             &points_pl2, &gameOver, &saved, &gameStarted,
                             &turn, &isWin, field_player1, field_player2, activePiece);

                    gameInitiated = 1;
                }

                if (!gameOver) {
                    if (frameCounter % speed == 0) {
                        frameCounter = 0;
                        if (isPieceMoving) {
                            activePiece->piecePosition.y++;
                            if(bottomCollision(field_player1, activePiece)){
                                speed = 25;
                                activePiece->piecePosition.y--;
                                isPieceMoving = 0;
                                pieceSaved = 0;

                                if (win(infoPieces)) {
                                    gameOver = 1;
                                    isWin = 1;
                                }

                                if (activePiece->piecePosition.y == 0) {
                                    gameOver = 1;
                                    isWin = 0;
                                }
                            }
                        }
                    }

                    if (!isPieceMoving) {
                        if (IsKeyPressed(KEY_ENTER)) {
                            if (infoPieces[pieceID].remaining > 0) {
                                if(!pieceSaved){
                                    savePiece(field_player1, activePiece);
                                    pieceSaved = 1;
                                }
                                getTetraminoFromID(pieceID, activePiece);
                                isPieceMoving = 1;
                                infoPieces[pieceID].remaining--;
                            }
                        }
                    }

                    if (IsKeyPressed(KEY_LEFT) && isPieceMoving) {
                        if(!leftCollision(activePiece, field_player1))
                            --activePiece->piecePosition.x;
                    }
                    if (IsKeyPressed(KEY_RIGHT) && isPieceMoving) {
                        if(!rightCollision(activePiece, field_player1))
                            ++activePiece->piecePosition.x;
                    }
                    if (IsKeyPressed(KEY_R) && isPieceMoving) {
                        turnPiece(activePiece);
                        if(bottomCollision(field_player1, activePiece))
                            activePiece->piecePosition.y += (FIELD_COLS - activePiece->piecePosition.y);
                    }

                    if (IsKeyPressed(KEY_T)) {
                        if (pieceID++ == 6)
                            pieceID = 0;
                    }

                    if (IsKeyPressed(KEY_DOWN))
                        speed = 3;

                    if (GetMouseX() >= 920 && GetMouseX() <= 1000 && GetMouseY() >= 660 && GetMouseY() <= 740) {
                        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                            state = MENU;
                        }
                    }

                    assignPieceToField(field_player1, activePiece);

                    checkFullRow(field_player1, NULL, &points_pl1, &points_pl2, is_multiplayer, turn);

                    printField(field_player1, karmaticArcade, pieceID, activePiece->color, infoPieces, &points_pl1,
                               backArrow_texture);

                } else {
                    if (!saved) {
                        saveToFile(points_pl1, nickname1);
                        saved = 1;
                    }
                    if (isWin) {
                        printWin(karmaticArcade, points_pl1, points_pl2, turn, is_multiplayer, nickname1, nickname2,
                                 trofeo_texture, backArrow_texture);
                        if (GetMouseX() >= 920 && GetMouseX() <= 1000 && GetMouseY() >= 660 && GetMouseY() <= 740) {
                            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                                state = MENU;
                            }
                        }
                    } else {
                        printGameOver(karmaticArcade, points_pl1, points_pl2, turn, is_multiplayer, nickname1,
                                      nickname2, backArrow_texture);
                        if (GetMouseX() >= 920 && GetMouseX() <= 1000 && GetMouseY() >= 660 && GetMouseY() <= 740) {
                            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                                state = MENU;
                            }
                        }
                    }
                }
                frameCounter++;
                break;
            case CHOOSE_MULTIPLAYER:
                choose_multiplayer(karmaticArcade, backArrow_texture, &state, &is_multiplayer, &is_pve);
                initInfo(infoPieces, 1);
                break;
            case MULTIPLAYER_PVP:
                if (!gameInitiated) {
                    SetWindowSize(SCREEN_WIDTH_MULTI, SCREEN_HEIGHT_MULTI);
                    SetWindowPosition(0, 0);

                    initInfo(infoPieces, is_multiplayer);

                    initGame(&isPieceMoving, &pieceID, &points_pl1,
                             &points_pl2, &gameOver, &saved, &gameStarted,
                             &turn, &isWin, field_player1, field_player2, activePiece);

                    gameInitiated = 1;
                }

                if (!gameOver) {
                    if (frameCounter % speed == 0) {
                        frameCounter = 0;
                        if (isPieceMoving) {
                            activePiece->piecePosition.y++;
                            if(bottomCollision(field, activePiece)){
                                speed = 25;
                                activePiece->piecePosition.y--;

                                pieceSaved = 0;

                                isPieceMoving = 0;

                                if (activePiece->piecePosition.y == 0){
                                    isWin = 1;
                                    gameOver = 1;
                                }

                                if(win(infoPieces)){
                                    gameOver = 1;
                                    isWin = 1;
                                }

                                ++turn;
                            }
                        }
                    }
                    if (!isPieceMoving) {
                        if (IsKeyPressed(KEY_ENTER)) {
                            if (infoPieces[pieceID].remaining > 0) {
                                if(!pieceSaved){
                                    savePiece(field, activePiece);

                                    if (turn % 2 == 0)
                                        field = field_player1;
                                    else
                                        field = field_player2;

                                    pieceSaved = 1;
                                }

                                getTetraminoFromID(pieceID, activePiece);
                                isPieceMoving = 1;
                                infoPieces[pieceID].remaining--;
                            }
                        }
                    }

                    if (IsKeyPressed(KEY_LEFT) && isPieceMoving) {
                        if(!leftCollision(activePiece, field_player1))
                            --activePiece->piecePosition.x;
                    }
                    if (IsKeyPressed(KEY_RIGHT) && isPieceMoving) {
                        if(!rightCollision(activePiece, field_player1))
                            ++activePiece->piecePosition.x;
                    }
                    if (IsKeyPressed(KEY_R) && isPieceMoving) {
                        turnPiece(activePiece);
                        if(bottomCollision(field, activePiece))
                            activePiece->piecePosition.y += (FIELD_COLS - activePiece->piecePosition.y);
                    }

                    if (IsKeyPressed(KEY_T)) {
                        if (pieceID++ == 6)
                            pieceID = 0;
                    }

                    if (IsKeyPressed(KEY_DOWN))
                        speed = 3;

                    if (GetMouseX() >= SCREEN_WIDTH_MULTI / 2 - 40 && GetMouseX() <= SCREEN_WIDTH_MULTI / 2 + 40 &&
                        GetMouseY() >= 650 && GetMouseY() <= 730) {
                        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                            SetWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
                            SetWindowPosition(220, 0);
                            state = MENU;

                        }
                    }

                    assignPieceToField(field, activePiece);

                    checkFullRow(field_player1, field_player2, &points_pl1, &points_pl2, is_multiplayer, turn);
                    checkFullRow(field_player2, field_player1, &points_pl1, &points_pl2, is_multiplayer, turn);

                    printField_multiplayer(field_player1, field_player2, karmaticArcade, pieceID, activePiece->color,
                                           infoPieces, &points_pl1, &points_pl2, nickname1, nickname2, turn,
                                           backArrow_texture);

                    frameCounter++;
                } else {
                    if (!saved) {
                        saveToFile(points_pl1, nickname1);
                        saved = 1;
                        SetWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
                        SetWindowPosition(220, 0);
                    }
                    if(isWin){
                        printWin(karmaticArcade, points_pl1, points_pl2, turn, is_multiplayer, nickname1, nickname2,
                                 trofeo_texture, backArrow_texture);
                    }else{
                        printGameOver(karmaticArcade, points_pl1, points_pl2, turn, is_multiplayer, nickname1, nickname2, backArrow_texture);
                    }
                    if (GetMouseX() >= 920 && GetMouseX() <= 1000 && GetMouseY() >= 660 && GetMouseY() <= 740) {
                        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                            state = MENU;
                        }
                    }
                }
                break;
            case MULTIPLAYER_PVE:
                if (!gameInitiated) {
                    SetWindowSize(SCREEN_WIDTH_MULTI, SCREEN_HEIGHT_MULTI);
                    SetWindowPosition(0, 0);

                    initInfo(infoPieces, is_multiplayer);

                    initGame(&isPieceMoving, &pieceID, &points_pl1,
                             &points_pl2, &gameOver, &saved, &gameStarted,
                             &turn, &isWin, field_player1, field_player2, activePiece);

                    gameInitiated = 1;
                }

                if (!gameOver) {
                    if (frameCounter % speed == 0) {
                        frameCounter = 0;
                        if (isPieceMoving) {
                            if(rotation > 0 && turn % 2 == 1){
                                --rotation;
                                turnPiece(activePiece);
                            }
                            activePiece->piecePosition.y++;
                            if(bottomCollision(field, activePiece)){
                                speed = 25;
                                activePiece->piecePosition.y--;
                                isPieceMoving = 0;

                                if (activePiece->piecePosition.y == 0){
                                    isWin = 1;
                                    gameOver = 1;
                                }

                                if(win(infoPieces)){
                                    gameOver = 1;
                                    isWin = 1;
                                }
                                ++turn;
                                pieceSaved = 0;
                            }
                        }
                    }
                    if (!isPieceMoving) {
                        if (turn % 2 == 0) {
                            if (IsKeyPressed(KEY_ENTER)) {
                                if(!pieceSaved){
                                    if(turn != 0){
                                        savePiece(field_player2, activePiece);
                                        checkFullRow(field_player2, field_player1, &points_pl1, &points_pl2, is_multiplayer, turn);
                                    }
                                    pieceSaved = 1;
                                    field = field_player1;
                                    initPiece(activePiece);
                                }
                                if (infoPieces[pieceID].remaining > 0) {
                                    getTetraminoFromID(pieceID, activePiece);
                                    isPieceMoving = 1;
                                    infoPieces[pieceID].remaining--;
                                    pieceSaved = 0;
                                }
                            }
                        } else {
                            evaluatedMove pieceToMove = findPieceToMove(field_player2, infoPieces);
                            if(!pieceSaved){
                                savePiece(field_player1, activePiece);
                                checkFullRow(field_player1, field_player2, &points_pl1, &points_pl2, is_multiplayer, turn);
                                pieceSaved = 1;
                                field = field_player2;
                                initPiece(activePiece);
                            }
                            if (infoPieces[pieceToMove.pieceID].remaining > 0) {
                                getTetraminoFromID(pieceToMove.pieceID, activePiece);
                                rotation = pieceToMove.rotations;
                                activePiece->piecePosition.x = (float)pieceToMove.coords_x;
                                isPieceMoving = 1;
                                infoPieces[pieceToMove.pieceID].remaining--;
                                pieceSaved = 0;
                            }
                        }
                    }
                    if (turn % 2 == 0) {
                        if (IsKeyPressed(KEY_LEFT) && isPieceMoving) {
                            if(!leftCollision(activePiece, field_player1))
                                --activePiece->piecePosition.x;
                        }
                        if (IsKeyPressed(KEY_RIGHT) && isPieceMoving) {
                            if(!rightCollision(activePiece, field_player1))
                                ++activePiece->piecePosition.x;
                        }
                        if (IsKeyPressed(KEY_R) && isPieceMoving) {
                            turnPiece(activePiece);
                            if(bottomCollision(field, activePiece))
                                activePiece->piecePosition.y += (FIELD_COLS - activePiece->piecePosition.y);
                        }

                        if (IsKeyPressed(KEY_DOWN))
                            speed = 3;
                    }

                    if (IsKeyPressed(KEY_T)) {
                        if (pieceID++ == 6)
                            pieceID = 0;
                    }

                    if(turn % 2 == 1)
                        speed = 18;

                    if (GetMouseX() >= SCREEN_WIDTH_MULTI / 2 - 40 && GetMouseX() <= SCREEN_WIDTH_MULTI / 2 + 40 &&
                        GetMouseY() >= 650 && GetMouseY() <= 730) {

                        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                            SetWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
                            SetWindowPosition(220, 0);
                            state = MENU;
                        }
                    }

                    assignPieceToField(field, activePiece);

                    printField_multiplayer(field_player1, field_player2, karmaticArcade, pieceID,
                                           activePiece->color, infoPieces, &points_pl1, &points_pl2, nickname1,
                                           "ALEXA", turn, backArrow_texture);

                    frameCounter++;
                } else {
                    if (!saved) {
                        saveToFile(points_pl1, nickname1);
                        saved = 1;
                        SetWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
                        SetWindowPosition(220, 0);
                    }
                    if(isWin){
                        printWin(karmaticArcade, points_pl1, points_pl2, turn, is_multiplayer, nickname1, nickname2,
                                 trofeo_texture, backArrow_texture);
                    }else{
                        printGameOver(karmaticArcade, points_pl1, points_pl2, turn, is_multiplayer, nickname1, nickname2, backArrow_texture);
                    }
                    if (GetMouseX() >= 920 && GetMouseX() <= 1000 && GetMouseY() >= 660 && GetMouseY() <= 740) {
                        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                            state = MENU;
                        }
                    }
                }
                break;
            case SCOREBOARD:
                printScoreboard(karmaticArcade, &state, &scoreboardLoaded, backArrow_texture);
            break;
            case EXIT:
                confirmExit(&state, karmaticArcade);
            break;
        }
    }

    free(field_player1);
    free(field_player2);
    free(activePiece);
    free(infoPieces);
    free(nickname1);
    free(nickname2);
    free(errorText);
}
