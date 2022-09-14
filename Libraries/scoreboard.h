/**
 * @file scoreboard.h
 * @brief The following file contains all auxiliary functions for the scoreboard of the game
 */

#ifndef X_TETRIS_SCOREBOARD_H
#define X_TETRIS_SCOREBOARD_H

#include "../Libraries/raylib.h"
#include "../Libraries/dataStructure.h"
#include "../Libraries/palette.h"

typedef struct {
    int points;
    char nickname[50];
    char date[50];
}entry;
/**
 *
 * @param points
 * @param nickname
 * @brief saves the points in a file
 */
void saveToFile(int points, char *nickname);
/**
 *
 * @param font
 * @param state
 * @param scoreboardLoaded
 * @param back_arrow
 * @brief print the scoreboard
 */
void printScoreboard(Font font, gameState *state, int *scoreboardLoaded, Texture2D back_arrow);

#endif
