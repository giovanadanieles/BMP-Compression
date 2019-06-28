/*
    Gabriel Garcia Lorencetti
    NUSP: 10691891

    Giovana Daniele da Silva
    NUSP: 10692224

    TAD responsavel pela manipulacao do cabecalho da imagem BMP.
*/
#include "bmp_cabecalho.h"

/* 
    Struct que condensa as structs BMP_CabecalhoArquivo
    e BMP_CabecalhoInformacao.
*/
struct BMPCabecalho_{
	BMP_CabecalhoArquivo *arquivo;
	BMP_CabecalhoInformacao *info;
};

/* 
    Struct que guarda o cabecalho do arquivo BMP (tipo, tamanho, entre outros).
*/
struct BMP_CabecalhoArquivo_{	
    unsigned short Type;           /* Magic number for file */
    unsigned int   Size;           /* Size of file */
    unsigned short Reserved1;      /* Reserved */
    unsigned short Reserved2;      /* ... */
    unsigned int   OffBits;        /* Offset to bitmap data */
};

/* 
    Struct que guarda as informacoes cabecalho do arquivo BMP (comprimento, altura, entre outros).
*/
struct BMP_CabecalhoInformacao_{
	unsigned int   Size;           /* Size of info header */
    int            Width;          /* Width of image */
    int            Height;         /* Height of image */
    unsigned short Planes;         /* Number of color planes */
    unsigned short BitCount;       /* Number of bits per pixel */
    unsigned int   Compression;    /* Type of compression to use */
    unsigned int   SizeImage;      /* Size of image data */
    int            XResolution;    /* X pixels per meter */
    int            YResolution;    /* Y pixels per meter */
    unsigned int   NColours;        /* Number of colors used */
    unsigned int   ImportantColours;   /* Number of important colors */
};

/*
    Funcao que le o cabecalho do arquivo BMP, que contem informacoes
    como a resolucao, profundidade de pixels, entre outros (padrao BMP).

    @Parâmetros
        FILE *bmp : arquivo da imagem BMP a ser lido o cabecalho;
    @Retorno
        BMPCabecalho** : cabecalho lido;
*/
BMPCabecalho* BMP_loadCabecalho(FILE* bmp){

	BMPCabecalho *cabecalho = NULL;

	cabecalho = (BMPCabecalho*)malloc(sizeof(BMPCabecalho));
	cabecalho->arquivo = (BMP_CabecalhoArquivo*)malloc(sizeof(BMP_CabecalhoArquivo));
	cabecalho->info = (BMP_CabecalhoInformacao*)malloc(sizeof(BMP_CabecalhoInformacao));

	BMP_leCabecalhoArquivo(bmp, cabecalho->arquivo);
    BMP_leCabecalhoInformacao(bmp, cabecalho->info);

    return cabecalho;
}

/*
    Funcao que le o cabecalho do arquivo.

    @Parâmetros
        FILE *bmp : arquivo da imagem BMP a ser lido o cabecalho;
    @Retorno
        BMPCabecalho** : cabecalho lido;
*/
void BMP_leCabecalhoArquivo(FILE *bmp, BMP_CabecalhoArquivo *arquivo){
     fread(&arquivo->Type, sizeof(unsigned short int), TAM, bmp);
     fread(&arquivo->Size, sizeof(unsigned int), TAM, bmp);
     fread(&arquivo->Reserved1, sizeof(unsigned short int), TAM, bmp);
     fread(&arquivo->Reserved2, sizeof(unsigned short int), TAM, bmp);
     fread(&arquivo->OffBits, sizeof(unsigned int), TAM, bmp);
}

/*
    Funcao que le as informacoes do cabecalho do arquivo.

    @Parâmetros
        FILE *bmp : arquivo da imagem BMP a ser lido o cabecalho;
    @Retorno
        BMPCabecalho** : cabecalho lido;
*/
void BMP_leCabecalhoInformacao(FILE *bmp, BMP_CabecalhoInformacao *info){
     fread(&info->Size, sizeof(unsigned int), TAM, bmp);
     fread(&info->Width, sizeof(int), TAM, bmp);
     fread(&info->Height, sizeof(int), TAM, bmp);
     fread(&info->Planes, sizeof(unsigned short int), TAM, bmp);
     fread(&info->BitCount, sizeof(unsigned short int), TAM, bmp);
     fread(&info->Compression, sizeof(unsigned int), TAM, bmp);
     fread(&info->SizeImage, sizeof(unsigned int), TAM, bmp);
     fread(&info->XResolution, sizeof(int), TAM, bmp);
     fread(&info->YResolution, sizeof(int), TAM, bmp);
     fread(&info->NColours, sizeof(unsigned int), TAM, bmp);
     fread(&info->ImportantColours, sizeof(unsigned int), TAM, bmp);        
}

/*
    Funcao que retorna o comprimento da imagem (width).

    @Parâmetros
        BMPCabecalho *bmp : cabecalho da imagem BMP;
    @Retorno
        int : comprimento da imagem;
*/
int BMP_getResolutionX(BMPCabecalho *bmp){
    return (bmp->info->Width);
}

/*
    Funcao que retorna a altura da imagem (height).

    @Parâmetros
        BMPCabecalho *bmp : cabecalho da imagem BMP;
    @Retorno
        int : altura da imagem;
*/
int BMP_getResolutionY(BMPCabecalho *bmp){
    return (bmp->info->Height);
}

/*
    Funcao que retorna a dimensao da imagem (width*height).

    @Parâmetros
        BMPCabecalho *bmp : cabecalho da imagem BMP;
    @Retorno
        int : comprimento da imagem;
*/
int BMP_getDimensao(BMPCabecalho *bmp){
    return (bmp->info->Height * bmp->info->Width);
}

/*
    Funcao que libera da memoria a struct BMPCabecalho.

    @Parâmetros
        BMPCabecalho *bmp : cabecalho da imagem BMP;
    @Retorno
        VOID
*/
void BMP_freeCabecalho(BMPCabecalho* bmp){
	free(bmp->arquivo);
	free(bmp->info);
	free(bmp);
}

