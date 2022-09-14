#include "../Libraries/menu.h"
#include "../Libraries/auxiliary.h"
#include <stdio.h>
#include <string.h>

void printMenu(gameState *state, Font font){
    Vector2 titlePos = {((float)SCREEN_WIDTH/3-70), 75};
    Vector2 spPos = {(float)SCREEN_WIDTH/3-20, 225};
    Vector2 mpPos = {(float)SCREEN_WIDTH/3, 325};
    Vector2 cmdPos = {(float)SCREEN_WIDTH/3+35, 425};
    Vector2 scbPos = {(float)SCREEN_WIDTH/3, 525};
    Vector2 exitBtn = {(float)SCREEN_WIDTH/3 + 110, 625};

    ClearBackground(getColor(BLACK_SWAG));

    DrawTextEx(font, "X-TETRIS", titlePos, 90, 3, getColor(RANDOM_COLOR));
    DrawTextEx(font, "SINGLEPLAYER", spPos, 40, 2, getColor(BLUETTE));
    DrawTextEx(font, "MULTIPLAYER", mpPos, 40, 2, getColor(GRENETTE));
    DrawTextEx(font, "COMMANDS", cmdPos, 40, 2, getColor(ROSETTE));
    DrawTextEx(font, "SCOREBOARD", scbPos, 40, 2, getColor(YELLOWETTE));
    DrawTextEx(font, "QUIT", exitBtn, 40, 2, getColor(UGLY_COLOR));

    if(GetMouseX() >= 313 && GetMouseX() <= 713 && GetMouseY() >= 225 && GetMouseY() <= 265){
        DrawTextEx(font, "SINGLEPLAYER", spPos, 40, 2, getColor(CREAMY_WHITE));
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            *state = CHOOSE_NAME;
        }
    }
    if(GetMouseX() >= 330 && GetMouseX() <= 685 && GetMouseY() >= 325 && GetMouseY() <= 365){
        DrawTextEx(font, "MULTIPLAYER", mpPos, 40, 2, getColor(CREAMY_WHITE));
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            *state = CHOOSE_MULTIPLAYER;
        }
    }
    if(GetMouseX() >= 365 && GetMouseX() <= 640 && GetMouseY() >= 425 && GetMouseY() <= 465){
        DrawTextEx(font, "COMMANDS", cmdPos, 40, 2, getColor(CREAMY_WHITE));
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            *state = COMMANDS;
        }
    }
    if(GetMouseX() >= 330 && GetMouseX() <= 670 && GetMouseY() >= 525 && GetMouseY() <= 565){
        DrawTextEx(font, "SCOREBOARD", scbPos, 40, 2, getColor(CREAMY_WHITE));
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            *state = SCOREBOARD;
        }
    }
    if(GetMouseX() >= 440 && GetMouseX() <= 570 && GetMouseY() >= 625 && GetMouseY() <= 665){
        DrawTextEx(font, "QUIT", exitBtn, 40, 2, getColor(CREAMY_WHITE));
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            *state = EXIT;
        }
    }

    EndDrawing();
}

void confirmExit(gameState *state, Font font){
    Vector2 textPosition = {0,0};
    char *strTmp = malloc(20);

    ClearBackground(getColor(BLACK_SWAG));
    BeginDrawing();
    strTmp = "ARE YOU SURE?";
    textPosition.x = (float)SCREEN_WIDTH/2-((float)(strlen(strTmp)*30)/2);
    textPosition.y = (float)SCREEN_HEIGHT/2-150;
    DrawTextEx(font, strTmp, textPosition, 40, 2, getColor(AZZURRO9));
    strTmp = "YES";
    textPosition.x = 350;
    textPosition.y = 350;
    DrawTextEx(font, strTmp, textPosition, 30, 2, getColor(AZZURRO4));
    if(GetMouseX() >= (int)textPosition.x && GetMouseX() <= (int)(textPosition.x + (float)strlen(strTmp)*20) && GetMouseY() >= 350 && GetMouseY() <= 380){
        DrawTextEx(font, strTmp, textPosition, 30, 2, getColor(CREAMY_WHITE));
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            exit(0);
        }
    }
    strTmp = "NO";
    textPosition.x = 575;
    textPosition.y = 350;
    DrawTextEx(font, strTmp, textPosition, 30, 2, getColor(AZZURRO4));
    if(GetMouseX() >= (int)textPosition.x && GetMouseX() <= (int)(textPosition.x + (float)strlen(strTmp)*20) && GetMouseY() >= 350 && GetMouseY() <= 380){
        DrawTextEx(font, strTmp, textPosition, 30, 2, getColor(CREAMY_WHITE));
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            *state = MENU;
    }
    EndDrawing();
}

void choose_name(gameState *state, char *nickname1, char *nickname2, int *letterCount_pl1, int *letterCount_pl2, Font Font, int is_multiplayer, Texture2D back_arrow, char *errorText, int is_pve){
    int key;
    Rectangle textBox_pl1 = { (float)SCREEN_WIDTH/3 - 250, (float)SCREEN_HEIGHT/2 - 50, 370, 50 };
    Rectangle textBox_pl2 = { (float)SCREEN_WIDTH/3 + 200, (float)SCREEN_HEIGHT/2 - 50, 370, 50 };
    Rectangle textBox = { (float)SCREEN_WIDTH/2 - 170, (float)SCREEN_HEIGHT/2 - 50, 370, 50 };

    key = GetCharPressed();
    while (key > 0){
        if(is_multiplayer && !is_pve){
            if (((key >= 32) && (key <= 125) && (*letterCount_pl1 < 13)) &&
                (GetMousePosition().x >= textBox_pl1.x && GetMousePosition().x <= textBox_pl1.x+370) &&
                (GetMousePosition().y >= textBox_pl1.y && GetMousePosition().y <= textBox_pl1.y+50)){
                nickname1[*letterCount_pl1] = (char)key;
                nickname1[*letterCount_pl1+1] = '\0';
                ++(*letterCount_pl1);
            }
            if (((key >= 32) && (key <= 125) && (*letterCount_pl2 < 13)) &&
                (GetMousePosition().x >= textBox_pl2.x && GetMousePosition().x <= textBox_pl2.x+370) &&
                (GetMousePosition().y >= textBox_pl2.y && GetMousePosition().y <= textBox_pl2.y+50)){
                nickname2[*letterCount_pl2] = (char)key;
                nickname2[*letterCount_pl2+1] = '\0';
                ++(*letterCount_pl2);
            }
            key = GetCharPressed();
        }else{
            if ((key >= 32) && (key <= 125) && (*letterCount_pl1 < 13)){
                nickname1[*letterCount_pl1] = (char)key;
                nickname1[*letterCount_pl1+1] = '\0';
                (*letterCount_pl1)++;
            }
            key = GetCharPressed();
        }
    }

    if (IsKeyPressed(KEY_BACKSPACE)){
        if(is_multiplayer) {
            if ((GetMousePosition().x >= textBox_pl1.x && GetMousePosition().x <= textBox_pl1.x + 370) &&
                (GetMousePosition().y >= textBox_pl1.y && GetMousePosition().y <= textBox_pl1.y + 50)) {
                (*letterCount_pl1)--;
                if ((*letterCount_pl1) < 0) (*letterCount_pl1) = 0;
                nickname1[*letterCount_pl1] = '\0';
            }
            if ((GetMousePosition().x >= textBox_pl2.x && GetMousePosition().x <= textBox_pl2.x + 370) &&
                (GetMousePosition().y >= textBox_pl2.y && GetMousePosition().y <= textBox_pl2.y + 50)) {
                (*letterCount_pl2)--;
                if ((*letterCount_pl2) < 0) (*letterCount_pl2) = 0;
                nickname2[*letterCount_pl2] = '\0';
            }
        }else{
            (*letterCount_pl1)--;
            if ((*letterCount_pl1) < 0) (*letterCount_pl1) = 0;
            nickname1[*letterCount_pl1] = '\0';
        }
    }
    if (IsKeyPressed(KEY_ENTER)){
        if(is_multiplayer && !is_pve){
            if(*letterCount_pl1 == 0 || *letterCount_pl2 == 0)
                sprintf(errorText, "Nickname can't be empty!");
            else
                *state = MULTIPLAYER_PVP;
        }else if(is_multiplayer){
            if(*letterCount_pl1 == 0)
                sprintf(errorText, "Nickname can't be empty!");
            else {
                *state = MULTIPLAYER_PVE;
            }
        }else{
            if(*letterCount_pl1 == 0){
                sprintf(errorText, "Nickname can't be empty!");
            }else {
                *state = SINGLEPLAYER;
            }
        }
    }

    DrawText(errorText, 385, 380, 20, getColor(AZZURRO4));

    if(is_multiplayer && !is_pve){
        BeginDrawing();

        ClearBackground(getColor(BLACK_SWAG));

        DrawText("INSERT NAME PLAYER 1", 120, 200, 25, getColor(CREAMY_WHITE));
        DrawText("INSERT NAME PLAYER 2", 560, 200, 25, getColor(CREAMY_WHITE));

        DrawRectangleRec(textBox_pl1, getColor(LIGHTGRAY));
        DrawRectangleLines((int)textBox_pl1.x, (int)textBox_pl1.y, (int)textBox_pl1.width, (int)textBox_pl1.height, getColor(RED));
        DrawText(nickname1, (int)textBox_pl1.x + 5, (int)textBox_pl1.y + 8, 40, getColor(BLACK_SWAG));

        DrawRectangleRec(textBox_pl2, getColor(LIGHTGRAY));
        DrawRectangleLines((int)textBox_pl2.x, (int)textBox_pl2.y, (int)textBox_pl2.width, (int)textBox_pl2.height, getColor(RED));
        DrawText(nickname2, (int)textBox_pl2.x + 5, (int)textBox_pl2.y + 8, 40, getColor(BLACK_SWAG));

        DrawText(TextFormat("INPUT CHARS: %i/%i", *letterCount_pl1, 13), 170, 250, 20, getColor(CREAMY_WHITE));
        DrawText(TextFormat("INPUT CHARS: %i/%i", *letterCount_pl2, 13), 610, 250, 20, getColor(CREAMY_WHITE));


        EndDrawing();
    } else{

        BeginDrawing();

        ClearBackground(getColor(BLACK_SWAG));

        DrawText("INSERT YOUR NAME", 380, 200, 25, getColor(CREAMY_WHITE));

        DrawRectangleRec(textBox, getColor(LIGHTGRAY));
        DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, getColor(RED));

        DrawText(nickname1, (int)textBox.x + 5, (int)textBox.y + 8, 40, getColor(BLACK_SWAG));

        DrawText(TextFormat("INPUT CHARS: %i/%i", *letterCount_pl1, 13), 410, 250, 20, getColor(CREAMY_WHITE));

        EndDrawing();
    }
    DrawTexture(back_arrow, 920, 660, getColor(AZZURRO3));
    if(GetMouseX() >= 920 && GetMouseX() <= 1000 && GetMouseY() >= 660 && GetMouseY() <= 740){
        DrawTexture(back_arrow, 920, 660, getColor(AZZURRO9));
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            *state = MENU;
        }
    }
}

void printCommands(Font font, Font arrowFont, Texture2D back_arrow, gameState *state){
    Vector2 textPosition = {350, 50};

    ClearBackground(getColor(BLACK_SWAG));
    BeginDrawing();
    DrawTextEx(font, "COMMANDS", textPosition, 50, 2, getColor(ROSETTE));
    textPosition.x = 180;
    textPosition.y = 150;
    DrawTextEx(font, "T                      Choose piece", textPosition, 30, 2, getColor(AZZURRO4));
    textPosition.x = 180;
    textPosition.y = 250;
    DrawTextEx(font, "R                      Rotate piece", textPosition, 30, 2, getColor(AZZURRO5));
    textPosition.x = 125;
    textPosition.y = 350;
    DrawTextEx(font, "ENTER                 Insert piece on field", textPosition, 30, 2,getColor( AZZURRO6));
    textPosition.x = 100;
    textPosition.y = 450;
    DrawTextEx(arrowFont, "o T", textPosition, 50, 2, getColor(AZZURRO7));
    textPosition.y = 460;
    DrawTextEx(font, "                                 Choose piece's position", textPosition, 30, 2, getColor(AZZURRO7));
    textPosition.x = 175;
    textPosition.y = 550;
    DrawTextEx(arrowFont, "s", textPosition, 90, 2, getColor(AZZURRO8));
    textPosition.y = 560;
    DrawTextEx(font, "                         Increase piece's speed", textPosition, 30, 2, getColor(AZZURRO8));

    DrawTexture(back_arrow, 920, 660, getColor(AZZURRO3));
    if(GetMouseX() >= 920 && GetMouseX() <= 1000 && GetMouseY() >= 660 && GetMouseY() <= 740){
        DrawTexture(back_arrow, 920, 660, getColor(AZZURRO9));
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            *state = MENU;
        }
    }
    EndDrawing();
}

void choose_multiplayer(Font font, Texture2D back_arrow, gameState *state, int *is_multiplayer, int *is_pve){
    Vector2 textPosition = {0,0};
    char *strTmp = malloc(20);

    ClearBackground(getColor(BLACK_SWAG));
    BeginDrawing();
    strTmp = "SELECT GAME MODE";
    textPosition.x = (float)SCREEN_WIDTH/2-(((float)strlen(strTmp)*37)/2);
    textPosition.y = 75;
    DrawTextEx(font, strTmp, textPosition, 50, 3, getColor());
    strTmp = "PLAYER VS PLAYER";
    textPosition.x = (float)SCREEN_WIDTH/2-(((float)strlen(strTmp)*27)/2);
    textPosition.y = (float)SCREEN_HEIGHT/2 - 100;
    DrawTextEx(font, strTmp, textPosition, 35, 3, getColor(AZZURRO4));
    if(GetMouseX() >= (int)textPosition.x && GetMouseX() <= (int)(textPosition.x + (float)strlen(strTmp)*28) && GetMouseY() >= (int)textPosition.y && GetMouseY() <= (int)textPosition.y + 35){
        DrawTextEx(font, "PLAYER VS PLAYER", textPosition, 35, 3, getColor(AZZURRO9));
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            *state = CHOOSE_NAME;
            *(is_multiplayer) = 1;
            *(is_pve) = 0;
        }
    }
    strTmp = "PLAYER VS AI";
    textPosition.x = (float)SCREEN_WIDTH/2-(((float)strlen(strTmp)*27)/2);
    textPosition.y = (float)SCREEN_HEIGHT/2 + 50;
    DrawTextEx(font, strTmp, textPosition, 35, 3, getColor(AZZURRO3));
    if(GetMouseX() >= (int)textPosition.x && GetMouseX() <= (int)(textPosition.x + (float)strlen(strTmp)*26) && GetMouseY() >= (int)textPosition.y && GetMouseY() <= (int)textPosition.y+ 35){
        DrawTextEx(font, "PLAYER VS AI", textPosition, 35, 3, getColor(AZZURRO9));
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            *state = CHOOSE_NAME;
            *(is_multiplayer) = 1;
            *(is_pve) = 1;
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
