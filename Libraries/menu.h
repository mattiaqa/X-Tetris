/**
 * @file menu.h
 * @brief The following file contains all auxiliary functions for the menu of the game
 */

#ifndef X_TETRIS_MENU_H
#define X_TETRIS_MENU_H

#include "../Libraries/dataStructure.h"
#include "../Libraries/palette.h"
#include <stdlib.h>
/**
 *
 * @param state
 * @param font
 * @brief print the menù
 */
void printMenu(gameState *state, Font font);
/**
 *
 * @param state
 * @param font
 * @brief print the exit confirmation screen
 */
void confirmExit(gameState *state, Font font);
/**
 *
 * @param state
 * @param nickname1
 * @param nickname2
 * @param letterCount_pl1
 * @param letterCount_pl2
 * @param font
 * @param is_multiplayer
 * @param back_arrow
 * @param errorText
 * @param is_pve
 * @brief print the name choice screen according to the game mode
 */
void choose_name(gameState *state, char *nickname1, char *nickname2, int *letterCount_pl1, int *letterCount_pl2, Font font, int is_multiplayer, Texture2D back_arrow, char *errorText, int is_pve);
/**
 *
 * @param font
 * @param arrowFont
 * @param back_arrow
 * @param state
 * @brief print the command screen
 */
void printCommands(Font font, Font arrowFont, Texture2D back_arrow, gameState *state);
/**
 *
 * @param font
 * @param back_arrow
 * @param state
 * @param is_multiplayer
 * @param is_pve
 * @brief print the multiplayer mode selection screen
 */
void choose_multiplayer(Font font, Texture2D back_arrow, gameState *state, int *is_multiplayer, int *is_pve);

#endif
