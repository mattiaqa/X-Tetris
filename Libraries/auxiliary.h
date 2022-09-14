/**
 * @file auxiliary.h
 * @brief The following file contains all auxiliary functions for the operation of the game
 */

#ifndef X_TETRIS_AUXILIARY_H
#define X_TETRIS_AUXILIARY_H

#include "../Libraries/raylib.h"
#include "../Libraries/palette.h"

/**
 * @brief returns a colour based on the id
 * @param idColor
 * @return RGB color
 */
Color getColor();

/**
 * @brief check whether a collision occurs in the bottom with the edge or with another piece
 * @param field player's field
 * @param piece piece to be checked if it collides
 * @return 1 if there is a collision, 0 otherwise
 */
int bottomCollision(const fieldType *field, pieceType *piece);

/**
 * @brief check whether the piece can be moved to the left
 * @param piece piece to be checked if it collides
 * @param field player's field
 * @return 1 if there is a collision, 0 otherwise
 */
int leftCollision(pieceType *piece, const fieldType *field);

/**
 * @brief check whether the piece can be moved to the right
 * @param piece piece to be checked if it collides
 * @param field player's field
 * @return 1 if there is a collision, 0 otherwise
 */
int rightCollision(pieceType *piece, const fieldType *field);

/**
 * @brief saves the current piece in the field matrix
 * @param field player's field
 * @param piece piece to be saved
 */
void savePiece(fieldType *field, pieceType *piece);

/**
 * @brief checks whether one or more rows have been completed, if so, points are awarded to the player who is playing
 * @param field_player1
 * @param field_player2 if is not multiplayer, this parameter can be NULL
 * @param points_pl1
 * @param points_pl2
 * @param is_multiplayer
 * @param turn
 */
void checkFullRow(fieldType *field_player1, fieldType *field_player2, int *points_pl1, int *points_pl2, int is_multiplayer, int turn);

/**
 * @brief
 * @param font
 * @param points_pl1
 * @param points_pl2
 * @param turn
 * @param is_multiplayer
 * @param nickname1
 * @param nickname2
 */
void printGameOver(Font font, int points_pl1, int points_pl2, int turn, int is_multiplayer, char *nickname1, char *nickname2, Texture2D back_arrow);

/**
 * @brief
 * @param font
 * @param points_pl1
 * @param points_pl2
 * @param turn
 * @param is_multiplayer
 * @param nickname1
 * @param nickname2
 * @param trofeo
 * @param back_arrow
 */
void printWin(Font font, int points_pl1, int points_pl2, int turn, int is_multiplayer, char *nickname1, char *nickname2, Texture2D trofeo, Texture2D back_arrow);

/**
 * @brief initialises game variables
 * @param isPieceMoving
 * @param pieceID
 * @param points_pl1
 * @param points_pl2
 * @param gameOver
 * @param saved
 * @param gameStarted
 * @param turn
 * @param isWin
 * @param field_player1
 * @param field_player2
 * @param activePiece
 */
void initGame(int *isPieceMoving, int *pieceID, int *points_pl1, int *points_pl2, int *gameOver,
              int *saved, int *gameStarted, int *turn, int *isWin, fieldType *field_player1, fieldType *field_player2,
              pieceType *activePiece);

/**
 * @brief checks whether the player has won by checking whether all the pieces have been used
 * @param infoPieces
 * @return
 */
int win(pieceInfo *infoPieces);
#endif

