/**
 * @file tetramino.h
 * @brief The following file contains all functions for the pieces
 */

#ifndef X_TETRIS_TETRAMINO_H
#define X_TETRIS_TETRAMINO_H

#include "field.h"
#include "../Libraries/palette.h"
/**
 *
 * @param piece
 * @brief set all the pieces's block to empty
 */
void initPiece(pieceType *piece);
/**
 *
 * @param infoPieces
 * @param is_multiplayer
 * @brief sets the number of playable pieces
 */
void initInfo(pieceInfo *infoPieces, int is_multiplayer);
/**
 *
 * @param pieceID
 * @param piece
 * @brief gets the pieces from ID
 */
void getTetraminoFromID(int pieceID, pieceType *piece);
/**
 *
 * @param activePiece
 * @brief turn the pieces
 */
void turnPiece(pieceType *activePiece);

#endif
