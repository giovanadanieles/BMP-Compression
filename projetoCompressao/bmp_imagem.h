/*
    Gabriel Garcia Lorencetti
    NUSP: 10691891

    Giovana Daniele da Silva
    NUSP: 10692224

    TAD responsavel pela manipulacao dos dados da imagem BMP.
*/
#ifndef BMPIMAGEM_H
#define BMPIMAGEM_H

    #include "bmp_cabecalho.h"
    
    /* 
       Definindo o tipo de dado BMPImagem, que contem os
       componentes RGB.
    */
    typedef struct BMPImagem_ BMPImagem;

    BMPImagem** BMP_loadImagem(FILE*, BMPCabecalho*);
    int returnElementB(BMPImagem**, int);
    int returnElementG(BMPImagem**, int);
    int returnElementR(BMPImagem**, int);
    int **aloca_matriz(int, int);
    void desaloca_matriz(int**, int);
    void BMP_freeImagem(BMPImagem**, int);   
    void assignValues(int**, int**, int**, int, int, BMPImagem**);
    void RGBToYCbCr(int**, int**, int**, int**, int**, int**, int, int);
    void YCbCrToRGB(int**, int**, int**, int**, int**, int**, int, int);
    void inicializacao();
    int** BMP_DCT(int**, int, int);
    int** BMP_IDCT(int**, int, int);
    int** BMP_Quantization(int**, int, int);    
    double PSNR(int, int, int**, int**);
    void run_length(int**, int, int, FILE*);
    int **run_length_decodifica(int, int, FILE*);
    unsigned char cast(int);
    void BMP_comprime(BMPImagem**, BMPCabecalho *a, FILE*);
    void BMP_descomprime(BMPCabecalho*, FILE*);
    long int tamanhoArquivo(char*);

#endif