/**
 * @file field.h
 * @brief The following file contains all functions concerning the playing field
 */
#ifndef X_TETRIS_FIELD_H
#define X_TETRIS_FIELD_H

#include "../Libraries/raylib.h"
#include "../Libraries/dataStructure.h"
#include "../Libraries/palette.h"

/**
 * @brief print the game interface on single player
 * @param matrixField
 * @param font
 * @param pieceID
 * @param color
 * @param infoPieces
 * @param points
 * @param back_arrow
 */
void printField(const fieldType *matrixField, Font font, int pieceID, Color color, pieceInfo *infoPieces, const int *points, Texture2D back_arrow);

/**
 * @brief print the game interface on multiplayer
 * @param field_1
 * @param field_2
 * @param font
 * @param pieceID
 * @param color
 * @param infoPieces
 * @param points_pl1
 * @param points_pl2
 * @param nickname1
 * @param nickname2
 * @param turn
 * @param back_arrow
 */
void printField_multiplayer(const fieldType *field_1, const fieldType *field_2, Font font, int pieceID, Color color, pieceInfo *infoPieces, const int *points_pl1, const int *points_pl2, char *nickname1, char *nickname2, int turn, Texture2D back_arrow);

/**
 * @brief initialises the playing field to EMPTY
 * @param field
 */
void initField(fieldType *field);

/**
 * @brief at each frame, assign the moving piece to the playing field matrix
 * @param field
 * @param tetramino
 */
void assignPieceToField(fieldType *field, pieceType *tetramino);

#endif
