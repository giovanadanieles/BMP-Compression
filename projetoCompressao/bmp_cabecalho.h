/*
    Gabriel Garcia Lorencetti
    NUSP: 10691891

    Giovana Daniele da Silva
    NUSP: 10692224

    TAD responsavel pela manipulacao do cabecalho da imagem BMP.
*/
#ifndef BMPCAB_H
    #define BMPCAB_H

    #include <stdio.h>
    #include <stdlib.h>
    #include <math.h>

    typedef struct BMPCabecalho_ BMPCabecalho;
    typedef struct BMP_CabecalhoArquivo_ BMP_CabecalhoArquivo;
    typedef struct BMP_CabecalhoInformacao_ BMP_CabecalhoInformacao;

    #define TAM 1

    BMPCabecalho* BMP_loadCabecalho(FILE*);
    void BMP_leCabecalhoArquivo(FILE*, BMP_CabecalhoArquivo*);
    void BMP_leCabecalhoInformacao(FILE*, BMP_CabecalhoInformacao*);
    void BMP_freeCabecalho(BMPCabecalho*);
    int BMP_getResolutionX(BMPCabecalho *bmp);
    int BMP_getResolutionY(BMPCabecalho *bmp);
    int BMP_getDimensao(BMPCabecalho*);

#endif