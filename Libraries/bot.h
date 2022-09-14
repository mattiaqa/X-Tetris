/**
 * @file bot.h
 * @brief The following file contains all functions for the bot
 */

#ifndef X_TETRIS_BOT_H
#define X_TETRIS_BOT_H

#include "../Libraries/dataStructure.h"

typedef struct{
    int pieceID;
    int points;
    int coords_x;
    int rotations;
    int blankPos;
}evaluatedMove;

/**
 * @brief find the best piece to place for the bot
 * @param field
 * @param infoPieces
 * @return
 */
evaluatedMove findPieceToMove(const fieldType *field, const pieceInfo *infoPieces);

#endif //X_TETRIS_BOT_H
