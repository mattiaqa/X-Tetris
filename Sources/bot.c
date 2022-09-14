#include <stdlib.h>
#include <stdio.h>

#include "../Libraries/bot.h"
#include "../Libraries/tetramino.h"
#include "../Libraries/auxiliary.h"

int leftCollisionAi(pieceType *piece, const fieldType *field){
    size_t i, j;
    size_t yPiece = (size_t)piece->piecePosition.y;
    size_t xPiece;

    for(i = 0; i < TETRAMINO_DIM; ++i){
        xPiece = (size_t)piece->piecePosition.x;
        for(j = 0; j < TETRAMINO_DIM; ++j){
            if(piece->structure[i * TETRAMINO_DIM + j] == TETRAMINO){
                if(xPiece < 0 || field[yPiece * FIELD_COLS + xPiece - 1] == TETRAMINO)
                    return 1;
                ++xPiece;
            }else if(piece->structure[i * TETRAMINO_DIM + j] == INTERNAL_EMPTY){
                ++xPiece;
            }
        }
        ++yPiece;
    }
    return 0;
}

int rightCollisionAi(pieceType *piece, const fieldType *field){
    size_t i, j;
    size_t yPiece = (size_t)piece->piecePosition.y;
    size_t xPiece;

    for(i = 0; i < TETRAMINO_DIM; ++i){
        xPiece = (size_t)piece->piecePosition.x;
        for(j = 0; j < TETRAMINO_DIM; ++j){
            if( piece->structure[i * TETRAMINO_DIM + j] == TETRAMINO){
                if(xPiece > 9 || field[yPiece * FIELD_COLS + xPiece + 1] == TETRAMINO)
                    return 1;
                ++xPiece;
            }else if(piece->structure[i * TETRAMINO_DIM + j] == INTERNAL_EMPTY){
                ++xPiece;
            }
        }
        ++yPiece;
    }
    return 0;
}

void copyField(const fieldType *source, fieldType *dest){
    size_t i, j;
    for(i = 0; i < FIELD_ROW; ++i){
        for(j = 0; j < FIELD_COLS; ++j){
            dest[i * FIELD_COLS + j] = source[i * FIELD_COLS + j];
        }
    }
}

int simulateGame(fieldType *field, pieceType *piece){
    size_t i, j, xPiece , yPiece;
    int count = 0;

    while(!bottomCollision(field, piece)){
        piece->piecePosition.y++;
    }

    yPiece = (size_t) piece->piecePosition.y;

    for(i = 0; i < TETRAMINO_DIM; ++i){
        xPiece = (size_t) piece->piecePosition.x;
        for(j = 0; j < TETRAMINO_DIM; ++j){
            if(piece->structure[i * TETRAMINO_DIM + j == TETRAMINO]){
                field[yPiece * TETRAMINO_DIM + xPiece] = TETRAMINO;
                ++xPiece;
            }
            if(piece->structure[i * TETRAMINO_DIM + j] == INTERNAL_EMPTY)
                ++xPiece;
        }
        yPiece++;
    }

    for(i = (size_t)piece->piecePosition.y; i < FIELD_ROW; ++i){
        for(j = 0; j < FIELD_COLS; ++j){
            if(field[i * FIELD_COLS + j] == EMPTY)
                ++count;
        }
    }

    return count;
}

evaluatedMove findPieceToMove(const fieldType *field, const pieceInfo *infoPieces){
    size_t i, x, r;
    pieceType *piece = malloc(sizeof(pieceType));
    fieldType *copiedField = malloc(sizeof(fieldType) * FIELD_COLS * FIELD_ROW);
    evaluatedMove temp, retValue;
    evaluatedMove *availableMoves = malloc(sizeof(evaluatedMove) * 420);
    int index = 0, minBlankPos, indexTemp, blankPos;

    for(i = 0; i < 7; ++i){
        initPiece(piece);
        getTetraminoFromID((int)i, piece);

        if(infoPieces[i].remaining != 0) {
            for (x = 0; x < FIELD_COLS; ++x) {
                for (r = 0; r < 4; ++r) {
                    copyField(field, copiedField);
                    piece->piecePosition.x = (float) x;
                    piece->piecePosition.y = 0;

                    if (!leftCollisionAi(piece, copiedField) && !rightCollisionAi(piece, copiedField)) {
                        blankPos = simulateGame(copiedField, piece);

                        temp.coords_x = (int) x;
                        temp.pieceID = (int) i;
                        temp.rotations = (int) r;
                        temp.blankPos = blankPos;
                        availableMoves[index++] = temp;
                    }

                    turnPiece(piece);
                }
            }
        }
    }

    free(copiedField);
    free(piece);

    minBlankPos = availableMoves[0].blankPos;
    indexTemp = 0;

    for(i = 1; i < index; ++i){
        if(availableMoves[i].blankPos < minBlankPos){
            minBlankPos = availableMoves[i].blankPos;
            indexTemp = (int) i;
        }
    }

    retValue = availableMoves[indexTemp];

    free(availableMoves);

    return retValue;
}




