#include <stdlib.h>

#include "../Libraries/dataStructure.h"
#include "../Libraries/auxiliary.h"
#include "../Libraries/tetramino.h"

void initPiece(pieceType *piece){
    size_t i, j;

    for(i = 0; i < TETRAMINO_DIM; i++){
        for(j = 0; j < TETRAMINO_DIM; j++){
            piece->structure[i * TETRAMINO_DIM + j] = EMPTY;
        }
    }

    piece->piecePosition.x = 3;
    piece->piecePosition.y = 0;
}

void getTetraminoFromID(int pieceID, pieceType *piece){
    initPiece(piece);
    piece->color = getColor(RANDOM_COLOR);

    switch(pieceID){
        //I
        case 0:
            piece->structure[4] = TETRAMINO;
            piece->structure[5] = TETRAMINO;
            piece->structure[6] = TETRAMINO;
            piece->structure[7] = TETRAMINO;
            break;
        //J
        case 1:
            piece->structure[0] = TETRAMINO;
            piece->structure[4] = TETRAMINO;
            piece->structure[5] = TETRAMINO;
            piece->structure[6] = TETRAMINO;
            break;
        //L
        case 2:
            piece->structure[2] = TETRAMINO;
            piece->structure[4] = TETRAMINO;
            piece->structure[5] = TETRAMINO;
            piece->structure[6] = TETRAMINO;
            piece->structure[0] = INTERNAL_EMPTY;
            piece->structure[1] = INTERNAL_EMPTY;
            break;
        //Z
        case 3:
            piece->structure[0] = TETRAMINO;
            piece->structure[1] = TETRAMINO;
            piece->structure[5] = TETRAMINO;
            piece->structure[6] = TETRAMINO;
            piece->structure[2] = INTERNAL_EMPTY;
            piece->structure[4] = INTERNAL_EMPTY;
            break;
        //S
        case 4:
            piece->structure[1] = TETRAMINO;
            piece->structure[2] = TETRAMINO;
            piece->structure[4] = TETRAMINO;
            piece->structure[5] = TETRAMINO;
            piece->structure[0] = INTERNAL_EMPTY;
            piece->structure[6] = INTERNAL_EMPTY;
            break;
        //T
        case 5:
            piece->structure[1] = TETRAMINO;
            piece->structure[4] = TETRAMINO;
            piece->structure[5] = TETRAMINO;
            piece->structure[6] = TETRAMINO;
            piece->structure[0] = INTERNAL_EMPTY;
            piece->structure[2] = INTERNAL_EMPTY;
            break;
        //O
        case 6:
            piece->structure[1] = TETRAMINO;
            piece->structure[2] = TETRAMINO;
            piece->structure[5] = TETRAMINO;
            piece->structure[6] = TETRAMINO;
            break;
    }
}

void initInfo(pieceInfo *infoPieces, int is_multiplayer){
    size_t i;

    for(i = 0; i < 7; i++){
        infoPieces[i].pieceID = (int)i;
        if(!is_multiplayer)
            infoPieces[i].remaining = 20;
        else
            infoPieces[i].remaining = 40;
    }
}

void emptyPiece(pieceType *piece){
    size_t i, j;

    for(i = 0; i < TETRAMINO_DIM; i++){
        for(j = 0; j < TETRAMINO_DIM; j++){
            piece->structure[i * TETRAMINO_DIM + j] = EMPTY;
        }
    }
}

void turnPiece(pieceType *piece){
    //I
    if ( piece->structure[4] == TETRAMINO &&
         piece->structure[5] == TETRAMINO &&
         piece->structure[6] == TETRAMINO &&
         piece->structure[7] == TETRAMINO ){

        emptyPiece(piece);

        piece->structure[2] = TETRAMINO;
        piece->structure[6] = TETRAMINO;
        piece->structure[10] = TETRAMINO;
        piece->structure[14] = TETRAMINO;
    }else if(piece->structure[2] == TETRAMINO &&
             piece->structure[6] == TETRAMINO &&
             piece->structure[10] == TETRAMINO &&
             piece->structure[14] == TETRAMINO){

        emptyPiece(piece);

        piece->structure[8] = TETRAMINO;
        piece->structure[9] = TETRAMINO;
        piece->structure[10] = TETRAMINO;
        piece->structure[11] = TETRAMINO;
    }else if(piece->structure[8] == TETRAMINO &&
             piece->structure[9] == TETRAMINO &&
             piece->structure[10] == TETRAMINO &&
             piece->structure[11] == TETRAMINO){

        emptyPiece(piece);

        piece->structure[1] = TETRAMINO;
        piece->structure[5] = TETRAMINO;
        piece->structure[9] = TETRAMINO;
        piece->structure[13] = TETRAMINO;
    }else if(piece->structure[1] == TETRAMINO &&
             piece->structure[5] == TETRAMINO &&
             piece->structure[9] == TETRAMINO &&
             piece->structure[13] == TETRAMINO){

        emptyPiece(piece);

        piece->structure[4] = TETRAMINO;
        piece->structure[5] = TETRAMINO;
        piece->structure[6] = TETRAMINO;
        piece->structure[7] = TETRAMINO;
    }

    //J
    if ( piece->structure[0] == TETRAMINO &&
         piece->structure[4] == TETRAMINO &&
         piece->structure[5] == TETRAMINO &&
         piece->structure[6] == TETRAMINO ){

        emptyPiece(piece);

        piece->structure[1] = TETRAMINO;
        piece->structure[2] = TETRAMINO;
        piece->structure[5] = TETRAMINO;
        piece->structure[9] = TETRAMINO;
        piece->structure[6] = INTERNAL_EMPTY;
        piece->structure[10] = INTERNAL_EMPTY;

    }else if(piece->structure[1] == TETRAMINO &&
             piece->structure[2] == TETRAMINO &&
             piece->structure[5] == TETRAMINO &&
             piece->structure[9] == TETRAMINO){

        emptyPiece(piece);

        piece->structure[4] = TETRAMINO;
        piece->structure[5] = TETRAMINO;
        piece->structure[6] = TETRAMINO;
        piece->structure[10] = TETRAMINO;
        piece->structure[8] = INTERNAL_EMPTY;
        piece->structure[9] = INTERNAL_EMPTY;

    }else if(piece->structure[4] == TETRAMINO &&
             piece->structure[5] == TETRAMINO &&
             piece->structure[6] == TETRAMINO &&
             piece->structure[10] == TETRAMINO){

        emptyPiece(piece);

        piece->structure[2] = TETRAMINO;
        piece->structure[6] = TETRAMINO;
        piece->structure[9] = TETRAMINO;
        piece->structure[10] = TETRAMINO;
        piece->structure[1] = INTERNAL_EMPTY;
        piece->structure[5] = INTERNAL_EMPTY;
    }else if(piece->structure[2] == TETRAMINO &&
             piece->structure[6] == TETRAMINO &&
             piece->structure[9] == TETRAMINO &&
             piece->structure[10] == TETRAMINO){

        emptyPiece(piece);

        piece->structure[0] = TETRAMINO;
        piece->structure[4] = TETRAMINO;
        piece->structure[5] = TETRAMINO;
        piece->structure[6] = TETRAMINO;
    }

    //L
    if ( piece->structure[2] == TETRAMINO &&
         piece->structure[4] == TETRAMINO &&
         piece->structure[5] == TETRAMINO &&
         piece->structure[6] == TETRAMINO ){

        emptyPiece(piece);

        piece->structure[1] = TETRAMINO;
        piece->structure[5] = TETRAMINO;
        piece->structure[9] = TETRAMINO;
        piece->structure[10] = TETRAMINO;
        piece->structure[2] = INTERNAL_EMPTY;
        piece->structure[6] = INTERNAL_EMPTY;

    }else if(piece->structure[1] == TETRAMINO &&
             piece->structure[5] == TETRAMINO &&
             piece->structure[9] == TETRAMINO &&
             piece->structure[10] == TETRAMINO){

        emptyPiece(piece);

        piece->structure[4] = TETRAMINO;
        piece->structure[5] = TETRAMINO;
        piece->structure[6] = TETRAMINO;
        piece->structure[8] = TETRAMINO;
        piece->structure[9] = INTERNAL_EMPTY;
        piece->structure[10] = INTERNAL_EMPTY;

    }else if(piece->structure[4] == TETRAMINO &&
             piece->structure[5] == TETRAMINO &&
             piece->structure[6] == TETRAMINO &&
             piece->structure[8] == TETRAMINO){

        emptyPiece(piece);

        piece->structure[0] = TETRAMINO;
        piece->structure[1] = TETRAMINO;
        piece->structure[5] = TETRAMINO;
        piece->structure[9] = TETRAMINO;
        piece->structure[4] = INTERNAL_EMPTY;
        piece->structure[8] = INTERNAL_EMPTY;
    }else if(piece->structure[0] == TETRAMINO &&
             piece->structure[1] == TETRAMINO &&
             piece->structure[5] == TETRAMINO &&
             piece->structure[9] == TETRAMINO){

        emptyPiece(piece);

        piece->structure[2] = TETRAMINO;
        piece->structure[4] = TETRAMINO;
        piece->structure[5] = TETRAMINO;
        piece->structure[6] = TETRAMINO;
    }

    //S
    if ( piece->structure[1] == TETRAMINO &&
         piece->structure[2] == TETRAMINO &&
         piece->structure[4] == TETRAMINO &&
         piece->structure[5] == TETRAMINO ){

        emptyPiece(piece);

        piece->structure[1] = TETRAMINO;
        piece->structure[5] = TETRAMINO;
        piece->structure[6] = TETRAMINO;
        piece->structure[10] = TETRAMINO;
        piece->structure[2] = INTERNAL_EMPTY;
        piece->structure[9] = INTERNAL_EMPTY;

    }else if(piece->structure[1] == TETRAMINO &&
             piece->structure[5] == TETRAMINO &&
             piece->structure[6] == TETRAMINO &&
             piece->structure[10] == TETRAMINO){

        emptyPiece(piece);

        piece->structure[5] = TETRAMINO;
        piece->structure[6] = TETRAMINO;
        piece->structure[8] = TETRAMINO;
        piece->structure[9] = TETRAMINO;
        piece->structure[4] = INTERNAL_EMPTY;
        piece->structure[10] = INTERNAL_EMPTY;

    }else if(piece->structure[5] == TETRAMINO &&
             piece->structure[6] == TETRAMINO &&
             piece->structure[8] == TETRAMINO &&
             piece->structure[9] == TETRAMINO){

        emptyPiece(piece);

        piece->structure[0] = TETRAMINO;
        piece->structure[4] = TETRAMINO;
        piece->structure[5] = TETRAMINO;
        piece->structure[9] = TETRAMINO;
        piece->structure[1] = INTERNAL_EMPTY;
        piece->structure[8] = INTERNAL_EMPTY;
    }else if(piece->structure[0] == TETRAMINO &&
             piece->structure[4] == TETRAMINO &&
             piece->structure[5] == TETRAMINO &&
             piece->structure[9] == TETRAMINO){

        emptyPiece(piece);

        piece->structure[1] = TETRAMINO;
        piece->structure[2] = TETRAMINO;
        piece->structure[4] = TETRAMINO;
        piece->structure[5] = TETRAMINO;
        piece->structure[0] = INTERNAL_EMPTY;
        piece->structure[6] = INTERNAL_EMPTY;
    }

    //T
    if ( piece->structure[1] == TETRAMINO &&
         piece->structure[4] == TETRAMINO &&
         piece->structure[5] == TETRAMINO &&
         piece->structure[6] == TETRAMINO ){

        emptyPiece(piece);

        piece->structure[1] = TETRAMINO;
        piece->structure[5] = TETRAMINO;
        piece->structure[6] = TETRAMINO;
        piece->structure[9] = TETRAMINO;
        piece->structure[2] = INTERNAL_EMPTY;
        piece->structure[10] = INTERNAL_EMPTY;

    }else if(piece->structure[1] == TETRAMINO &&
             piece->structure[5] == TETRAMINO &&
             piece->structure[6] == TETRAMINO &&
             piece->structure[9] == TETRAMINO){

        emptyPiece(piece);

        piece->structure[4] = TETRAMINO;
        piece->structure[5] = TETRAMINO;
        piece->structure[6] = TETRAMINO;
        piece->structure[9] = TETRAMINO;
        piece->structure[8] = INTERNAL_EMPTY;
        piece->structure[10] = INTERNAL_EMPTY;

    }else if(piece->structure[4] == TETRAMINO &&
             piece->structure[5] == TETRAMINO &&
             piece->structure[6] == TETRAMINO &&
             piece->structure[9] == TETRAMINO){

        emptyPiece(piece);

        piece->structure[1] = TETRAMINO;
        piece->structure[4] = TETRAMINO;
        piece->structure[5] = TETRAMINO;
        piece->structure[9] = TETRAMINO;
        piece->structure[0] = INTERNAL_EMPTY;
        piece->structure[8] = INTERNAL_EMPTY;
    }else if(piece->structure[1] == TETRAMINO &&
             piece->structure[4] == TETRAMINO &&
             piece->structure[5] == TETRAMINO &&
             piece->structure[9] == TETRAMINO){

        emptyPiece(piece);

        piece->structure[1] = TETRAMINO;
        piece->structure[4] = TETRAMINO;
        piece->structure[5] = TETRAMINO;
        piece->structure[6] = TETRAMINO;
        piece->structure[0] = INTERNAL_EMPTY;
        piece->structure[2] = INTERNAL_EMPTY;
    }

    //Z
    if ( piece->structure[0] == TETRAMINO &&
         piece->structure[1] == TETRAMINO &&
         piece->structure[5] == TETRAMINO &&
         piece->structure[6] == TETRAMINO ){

        emptyPiece(piece);

        piece->structure[2] = TETRAMINO;
        piece->structure[5] = TETRAMINO;
        piece->structure[6] = TETRAMINO;
        piece->structure[9] = TETRAMINO;
        piece->structure[1] = INTERNAL_EMPTY;
        piece->structure[10] = INTERNAL_EMPTY;

    }else if(piece->structure[2] == TETRAMINO &&
             piece->structure[5] == TETRAMINO &&
             piece->structure[6] == TETRAMINO &&
             piece->structure[9] == TETRAMINO){

        emptyPiece(piece);

        piece->structure[4] = TETRAMINO;
        piece->structure[5] = TETRAMINO;
        piece->structure[9] = TETRAMINO;
        piece->structure[10] = TETRAMINO;
        piece->structure[6] = INTERNAL_EMPTY;
        piece->structure[8] = INTERNAL_EMPTY;

    }else if(piece->structure[4] == TETRAMINO &&
             piece->structure[5] == TETRAMINO &&
             piece->structure[9] == TETRAMINO &&
             piece->structure[10] == TETRAMINO){

        emptyPiece(piece);

        piece->structure[1] = TETRAMINO;
        piece->structure[4] = TETRAMINO;
        piece->structure[5] = TETRAMINO;
        piece->structure[8] = TETRAMINO;
        piece->structure[0] = INTERNAL_EMPTY;
        piece->structure[9] = INTERNAL_EMPTY;
    }else if(piece->structure[1] == TETRAMINO &&
             piece->structure[4] == TETRAMINO &&
             piece->structure[5] == TETRAMINO &&
             piece->structure[8] == TETRAMINO){

        emptyPiece(piece);

        piece->structure[0] = TETRAMINO;
        piece->structure[1] = TETRAMINO;
        piece->structure[5] = TETRAMINO;
        piece->structure[6] = TETRAMINO;
        piece->structure[2] = INTERNAL_EMPTY;
        piece->structure[4] = INTERNAL_EMPTY;
    }
}
