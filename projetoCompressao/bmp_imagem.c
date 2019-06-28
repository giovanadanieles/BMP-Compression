/*
	Gabriel Garcia Lorencetti
	NUSP: 10691891

	Giovana Daniele da Silva
	NUSP: 10692224

	TAD responsavel pela manipulacao dos dados da imagem BMP.
*/
#include "bmp_imagem.h"

/* 
	Struct para guardar os campos R, G e B da imagem BMP.
*/
struct BMPImagem_{
	unsigned char R;
	unsigned char G;
	unsigned char B;  
};

// Variaveis globais para facilitar e agilizar o calculo da DCT.
double COS[8][8], C[8];

/*
	Funcao que le a imagem do arquivo BMP e os separa na struct BMPImagem,
	nos componentes de cor R, G e B.

	@Parâmetros
		FILE *bmp : arquivo da imagem BMP a ser lido;
		BMPCabecalho *cabecalho : cabecalho da imagem, lido anteriormente;
	@Retorno
		BMPImagem** : imagem lida, separado nos componentes BMP;
*/
BMPImagem** BMP_loadImagem(FILE *bmp, BMPCabecalho *cabecalho){

	int i, tam;

	// Captura a dimensao da imagem (X*Y);
	tam = BMP_getDimensao(cabecalho);

	// Aloca dinamicamente a imagem, com tamanho tam;
	BMPImagem** imagem = (BMPImagem**)malloc(tam*sizeof(BMPImagem*));

	// Pula o cabecalho (padrao BMP -> 54 bytes);
	fseek(bmp, 54, SEEK_SET);

	// Le do arquivo os componentes B, G e R e os guarda na struct BMPImagem;
	for (i = 0; i < tam; i++){
		imagem[i] = (BMPImagem*)malloc(sizeof(BMPImagem));
		imagem[i]->B = fgetc(bmp);
		imagem[i]->G = fgetc(bmp);
		imagem[i]->R = fgetc(bmp);
	}

	return imagem;
}

/*
	Funcao que retorna o componente B de um vetor do tipo BMPImagem,
	dado a posicao (indice).

	@Parâmetros
		BMPImagem** i : struct da imagem, que contem os dados R, G e B;
		int index : posicao do vetor;
	@Retorno
		int : componente B da imagem;
*/
int returnElementB(BMPImagem** i, int index){
	return i[index]->B;
} 

/*
	Funcao que retorna o componente G de um vetor do tipo BMPImagem,
	dado a posicao (indice).

	@Parâmetros
		BMPImagem** i : struct da imagem, que contem os dados R, G e B;
		int index : posicao do vetor;
	@Retorno
		int : componente G da imagem;
*/
int returnElementG(BMPImagem** i, int index){
	return i[index]->G;
} 

/*
	Funcao que retorna o componente R de um vetor do tipo BMPImagem,
	dado a posicao (indice).

	@Parâmetros
		BMPImagem** i : struct da imagem, que contem os dados R, G e B;
		int index : posicao do vetor;
	@Retorno
		int : componente R da imagem;
*/
int returnElementR(BMPImagem** i, int index){
	return i[index]->R;
}

/*
	Funcao que aloca uma matriz de inteiros, dados
	os parametros X e Y.

	@Parâmetros
		int x : tamanho da linha;
		int y : tamanho da coluna;
	@Retorno
		int ** : ponteiro para a matriz alocada;
*/
int **aloca_matriz(int x, int y){
	int i;
	int **mat = (int**)malloc(sizeof(int*)*x);
	for (i = 0; i < x; i++){
		mat[i] = (int*)malloc(sizeof(int)*y);
	}
	return mat;
}

/*
	Funcao que desaloca uma matriz de inteiros, dados
	o parametro X.

	@Parâmetros
		int **mat : matriz a ser desalocada;
		int x : tamanho da linha;
	@Retorno
		VOID
*/
void desaloca_matriz(int **mat, int x){
	int i;
	for(i = 0; i < x; i++)
		free(mat[i]);
	free(mat);
}

/*
	Funcao que libera da memoria heap a struct BMPImagem, anteriormente alocada;

	@Parâmetros
		BMPImagem **imagem : arquivo da imagem BMP;
		int tam : tamanho da imagem;
	@Retorno
		VOID
*/
void BMP_freeImagem(BMPImagem **imagem, int tam){
	int i;
	for(i = 0; i < tam; i++){
		free(imagem[i]);
	}
	free(imagem);
}

/*
	Funcao que atribui os valores B, G, R (unsigned char), nas
	matrizes B, G, R (int), para os calculos realizados pela aplicacao;

	@Parâmetros
		int **imgB : componente B (int), previamente alocado;
		int **imgG : componente G (int), previamente alocado;
		int** imgR : componente R (int), previamente alocado;
		int X :	comprimento da imagem;
		int Y : altura da imagem;
		BMPImagem **i : struct BMPImagem previamente lida do arquivo;
	@Retorno
		VOID;
*/
void assignValues(int** imgB, int** imgG, int** imgR, int X, int Y, BMPImagem** i){
	
	int k = 0, x, y;

	for(x = 0; x < X; x++){
		for(y = 0; y < Y; y++){
			imgB[x][y] = returnElementB(i, k);			
			imgG[x][y] = returnElementG(i, k);
			imgR[x][y] = returnElementR(i, k);
			k++;
		}
	}
}

/*
	Funcao que transforma B, G e R no padrao YCbCr;

	@Parâmetros
		int **imgB : componente B (int);
		int **imgG : componente G (int);
		int **imgR : componente R (int);
		int **imgY : componente Y (int);
		int **imgCb : componente Cb (int);
		int** imgCr : componente Cr (int);
		int X :	comprimento da imagem;
		int Y : altura da imagem;
	@Retorno
		VOID;
*/
void RGBToYCbCr(int** imgB, int** imgG, int** imgR, 
				int** imgY, int** imgCb, int** imgCr, int X, int Y){
	int x, y;

	//Transformando RGB -> YCbCr
	for(x = 0; x < X; x++){
		for(y = 0; y < Y; y++){
			imgY[x][y] = round((0.299 * imgR[x][y]) + (0.587 * imgG[x][y]) + (0.114 * imgB[x][y]));			
			imgCb[x][y] = round(128 - (0.168736 * imgR[x][y]) - (0.331264 * imgG[x][y]) + (0.500 * imgB[x][y]));
			imgCr[x][y] = round(128 + (0.500 * imgR[x][y]) - (0.418688 * imgG[x][y]) - (0.081312 * imgB[x][y]));
		}
	}
}

/*
	Funcao que transforma Y, Cb e Cr no padrao BGR;

	@Parâmetros
		int **imgB : componente B (int);
		int **imgG : componente G (int);
		int **imgR : componente R (int);
		int **imgY : componente Y (int);
		int **imgCb : componente Cb (int);
		int** imgCr : componente Cr (int);
		int X :	comprimento da imagem;
		int Y : altura da imagem;
	@Retorno
		VOID;
*/
void YCbCrToRGB(int** imgB, int** imgG, int** imgR, 
				int** imgY, int** imgCb, int** imgCr, int X, int Y){
	int x, y;

	//Transformando YCbCr -> RGB
	for(x = 0; x < X; x++){
		for(y = 0; y < Y; y++){
			imgR[x][y] = round(imgY[x][y] + 1.402 * (imgCr[x][y] - 128));			
			imgG[x][y] = round(imgY[x][y] - 0.344136 * (imgCb[x][y] - 128) - 0.714136 * (imgCr[x][y] - 128));
			imgB[x][y] = round(imgY[x][y] + 1.772 * (imgCb[x][y] - 128));
		}
	}

	//Liberando as antigas matrizes YCbCr
	desaloca_matriz(imgY, X);
	desaloca_matriz(imgCb, X);
	desaloca_matriz(imgCr, X);
}

/*
	Funcao responsavel por criar a "tabela de cossenos"	e por atribuir
	os devidos valores a C. Auxilia na funcao do calculo da DCT;

	@Parâmetros
		VOID
	@Retorno
		VOID
*/
void inicializacao(){
	int i, j;
	for (i = 0; i < 8; i++) {
		for (j = 0; j < 8; j++)
			COS[i][j] = cos((2 * i + 1) * j * acos(-1) / 16.0);

		if (i) C[i] = 1;
		else C[i] = 1 / sqrt(2);
	}
}

/*
	Funcao que realiza a Transformada discreta de cosseno (DCT), que transfere
	a maior parte da informação contida para os primeiros elementos do vetor, 
	otimizando o armazenamento (para compressão	sem perdas) e facilitando a
	quantização dos valores (para compressão com perdas).

	@Parâmetros
		int **img : matriz com os dados de um dos componentes da imagem;
		int X :	comprimento da imagem;
		int Y : altura da imagem;
	@Retorno
		int ** : matriz com a DCT aplicada;
*/
int** BMP_DCT(int** img, int X, int Y){
	int a, b, c, d, e, f;
	long double soma;

	//Alocando a matriz DCT dinamicamente
	int **dct = aloca_matriz(X, Y);

	//Realizando a DCT em blocos 8x8
	for(a = 0; a < ceil(X/8); a++){
		for(b = 0; b < ceil(Y/8); b++){
			for(c = 0; c < 8; c++){
				for(d = 0; d < 8; d++){
					soma = 0;
					for(e = 0; e < 8; e++){
						for(f = 0; f < 8; f++){
							soma += (img[a * 8 + e][b * 8 + f] - 128) * COS[e][c] * COS[f][d];
						}
					}
					soma *= C[c] * C[d] * 0.25;
					dct[a * 8 + c][b * 8 + d] = soma;
				}
			}
		}
	}

	desaloca_matriz(img, X);

	return dct;
}

/*
	Funcao que realiza a inversa da Transformada discreta de cosseno (IDCT),
	que recupera os dados transformados anteriormente (realiza o operacao
	inversa da DCT).

	@Parâmetros
		int **img : matriz com os dados de um dos componentes da imagem, com DCT aplicada;
		int X :	comprimento da imagem;
		int Y : altura da imagem;
	@Retorno
		int ** : matriz com a IDCT aplicada;
*/
int** BMP_IDCT(int** img, int X, int Y){
	int a, b, c, d, e, f;
	long double soma;

	//Alocando a matriz DCT dinamicamente
	int **idct = aloca_matriz(X, Y);

	//Realizando a IDCT em blocos 8x8
	for(a = 0; a < ceil(X/8); a++){
		for(b = 0; b < ceil(Y/8); b++){
			for(c = 0; c < 8; c++){
				for(d = 0; d < 8; d++){
					soma = 0;
					for(e = 0; e < 8; e++){
						for(f = 0; f < 8; f++){
							soma += C[e] * C[f] * img[a * 8 + e][b * 8 + f] * COS[c][e] * COS[d][f];
						}
					}
					soma *= 0.25;
					soma += 128;	
					idct[a * 8 + c][b * 8 + d] = soma;
				}
			}
		}
	}

	desaloca_matriz(img, X);

	return idct;
}

/*
	Funcao que realiza a quantização dos valores da matriz de um dos
	componentes (para compressão com perdas).

	@Parâmetros
		int **dct : matriz com os dados de um dos componentes da imagem, com a DCT aplicada;
		int X :	comprimento da imagem;
		int Y : altura da imagem;
	@Retorno
		int ** : matriz com a quantizacao aplicada;
*/
int** BMP_Quantization(int** dct, int X, int Y){

	// Tabela de quantizacao;
	int table[8][8] = {\
		{16, 11, 10, 16, 24, 40, 51, 61},\
		{12, 12, 14, 19, 26, 58, 60, 55},\
		{14, 13, 16, 24, 40, 57, 69, 56},\
		{14, 17, 22, 29, 51, 87, 80, 82},\
		{18, 22, 37, 56, 68, 109, 103, 77},\
		{24, 35, 55, 64, 81, 104, 113, 92},\
		{49, 64, 78, 87, 103, 121, 120, 101},\
		{72, 92, 95, 98, 112, 100, 103, 99}};

	int a, b, c, d;

	// Aplicando a quantizacao na matriz;
	for (a = 0; a < ceil(X/8); a++){
		for (b = 0; b < ceil(Y/8); b++){
			for (c = 0; c < 8; c++){
				for (d = 0; d < 8; d++) {
					dct[a * 8 + c][b * 8 + d] = round(dct[a * 8 + c][b * 8 + d] / table[c][d]);
					dct[a * 8 + c][b * 8 + d] = dct[a * 8 + c][b * 8 + d] * table[c][d];
				}
			}
		}
	}

	return dct;
}

/*
	Funcao que realiza o calculo da relação sinal-ruído de pico, também
	expressa como PSNR (Peak Signal-to-Noise Ratio). É utilizado como
	medida quantitativa da qualidade de reconstrução no campo de compressão de imagem.

	@Parâmetros
		int X :	comprimento da imagem;
		int Y : altura da imagem;
		int **imgOriginal : matriz com os dados da imagem original;
		int **imgIDCT : matriz com os dados da imagem depois da compressao;
	@Retorno
		int ** : valor do PSNR em double;
*/
double PSNR(int X, int Y, int** imgOriginal, int** imgIDCT) {
	double MSE = 0;
	int a, b;

	for (a = 0; a < X-1; a++)
		for (b = 0; b < Y-1; b++) {
		MSE += fabs((imgOriginal[a][b] - imgIDCT[a][b]) * (imgOriginal[a][b] - imgIDCT[a][b]));
	}

	MSE /= (X * Y);
	double PSNR = 10 * log10(255 * 255 / MSE);
	
	return PSNR;
}

/*
	Funcao que realiza o Run-length (ou RLE), tecnica para comprimir cadeias
	de caracteres onde existem sequencias longas de caracteres repetidos (compressao
	sem perdas).

	@Parâmetros
		int **mat : matriz com os dados da imagem;
		int X :	comprimento da imagem;
		int Y : altura da imagem;
		FILE *f : arquivo onde sera escrito o arquivo comprimido;
	@Retorno
		VOID
*/
void run_length(int **mat, int x, int y, FILE *f){
	
	int i, j;
	short contador = 1;
	short valor = -1, valorAnterior = -1;

	// Percorre a matriz;
	for (i = 0; i < x; i++){
		for(j = 0; j < y; j++){
			valorAnterior = valor;
			valor = mat[i][j];

			// Caso o valor atual seja igual ao anterior, incrementa o contador;
			if(valor == valorAnterior){
				contador++;
			}
			// Caso contrario, escreve no arquivo o contador (quantidade de vezes que
			//o valor aparece) e o valor do mesmo;
			else if(valorAnterior != -1){
				fwrite(&contador, sizeof(short), 1, f);
				fwrite(&valorAnterior, sizeof(short), 1, f);
				contador = 1;
			}
		}
	}
}

/*
	Funcao que decodifica o Run-length. Le do arquivo comprimido,
	e retorna a matriz com os valores do componente lido.

	@Parâmetros
		int X :	comprimento da imagem;
		int Y : altura da imagem;
		FILE *f : arquivo comprimido;
	@Retorno
		int** : matriz com os valores decodificados;
*/
int **run_length_decodifica(int x, int y, FILE *f){
	
	int i, j = 0, k = 0;
	short contador = 1;
	short valor;
	int **mat = aloca_matriz(x, y);
	int flag = 0;	

	// Enquanto nao chegar no fim do arquivo;
	while(flag != 1 && !feof(f)){

		// Le a quantidade e o valor;
		fread(&contador, sizeof(short), 1, f);
		fread(&valor, sizeof(short), 1, f);	

		// Salva na matriz a quantidade de vezes necessaria;
		for(i = 0; i < contador; i++){

				mat[j][k] = valor;

				if(k < y-1) k++;
				else if(j < x-1){
					k = 0;
					j++;
				}
				else flag = 1;
		}
	}

	return mat;
}

/*
	Funcao que realiza o cast de um inteiro para um unsigned char.
	Caso o valor seja menor que zero, retorna 0. Caso seja maior que
	255, retorna 255. Caso esteja dentro do intervalo, retorna o 
	proprio valor, realizando o cast.

	@Parâmetros
		int a : valor em inteiro
	@Retorno
		unsigned char : valor com cast realizado;
*/
unsigned char cast(int a){
	if(a > 255) return 255;
	else if (a < 0) return 0;
	else return (unsigned char)a;
}

/*
	Funcao que comprime uma imagem BMP. Primeiramente, os componentes
	RGB sao transformados em YCbCr, para o calculo da DCT. Logo apos,
	uma tabela de quantizacao eh aplicada (compressao com perdas), e
	atraves do run-length (compressao sem perdas), escreve em um arquivo
	com a imagem comprimida ("comprimido.bin");

	@Parâmetros
		BMPImagem **i : imagem lida do arquivo BMP (em RGB);
		BMPCabecalho *a : cabecalho da imagem BMP;
		FILE *imgOriginal : arquivo da imagem original;
	@Retorno
		VOID
*/
void BMP_comprime(BMPImagem **i, BMPCabecalho *a, FILE *imgOriginal){
	
	long int bo1 = -1, bo2 = -1;
	int x;

	//Inicializando a matriz de cossenos;
	inicializacao();

	//Alocando as matrizes RGB;
	int** imgB = aloca_matriz(BMP_getResolutionX(a), BMP_getResolutionY(a));
	int** imgG = aloca_matriz(BMP_getResolutionX(a), BMP_getResolutionY(a));
	int** imgR = aloca_matriz(BMP_getResolutionX(a), BMP_getResolutionY(a));

	//Alocando as matrizes YCbCr;
	int** imgY = aloca_matriz(BMP_getResolutionX(a), BMP_getResolutionY(a));
	int** imgCb = aloca_matriz(BMP_getResolutionX(a), BMP_getResolutionY(a));
	int** imgCr = aloca_matriz(BMP_getResolutionX(a), BMP_getResolutionY(a));

	//Atribuindo os valores da imagem às componentes das matrizes;
	assignValues(imgB, imgG, imgR, BMP_getResolutionX(a), BMP_getResolutionY(a), i);

	//Transformando a imagem RGB em YCbCr
	RGBToYCbCr(imgB, imgG, imgR, imgY, imgCb, imgCr, BMP_getResolutionX(a), BMP_getResolutionY(a));

	// Aplicando a DCT;
	imgY = BMP_DCT(imgY, BMP_getResolutionX(a), BMP_getResolutionY(a));
	imgCb = BMP_DCT(imgCb, BMP_getResolutionX(a), BMP_getResolutionY(a));
	imgCr = BMP_DCT(imgCr, BMP_getResolutionX(a), BMP_getResolutionY(a));

	//Aplicando a tabela de quantizacao;
	imgY = BMP_Quantization(imgY, BMP_getResolutionX(a), BMP_getResolutionY(a));
	imgCb = BMP_Quantization(imgCb, BMP_getResolutionX(a), BMP_getResolutionY(a));
	imgCr = BMP_Quantization(imgCr, BMP_getResolutionX(a), BMP_getResolutionY(a));

	// Abrindo o arquivo onde a imagem comprimida sera gravada;
	FILE *comprimido = fopen("comprimido.bin", "wb+");

	//Escrevendo cabecalho da imagem original no arquivo comprimido;
	fseek(imgOriginal, 0, SEEK_SET);
	for(x = 0; x < 54; x++) fputc(fgetc(imgOriginal), comprimido);
	// Escrevendo byteoffsets auxiliares, para leitura das componentes Y, Cb e Cr na descompressao;
	fwrite(&bo1, sizeof(long int), 1, comprimido);
	fwrite(&bo2, sizeof(long int), 1, comprimido);

	// Aplicando o run-length para cada componente; 
	run_length(imgY, BMP_getResolutionX(a), BMP_getResolutionY(a), comprimido);
	bo1 = ftell(comprimido)+1+54+2*sizeof(long int);
	fseek(comprimido, bo1, SEEK_SET);
	run_length(imgCb, BMP_getResolutionX(a), BMP_getResolutionY(a), comprimido);
	bo2 = ftell(comprimido)+1+54+2*sizeof(long int);
	fseek(comprimido, bo2, SEEK_SET);
	run_length(imgCr, BMP_getResolutionX(a), BMP_getResolutionY(a), comprimido);

	fseek(comprimido, 54, SEEK_SET);
	fwrite(&bo1, sizeof(long int), 1, comprimido);
	fwrite(&bo2, sizeof(long int), 1, comprimido);

	// Desalocando as matrizes de cada componente e fechando o arquivo;
	desaloca_matriz(imgB, BMP_getResolutionX(a));
	desaloca_matriz(imgG, BMP_getResolutionX(a));
	desaloca_matriz(imgR, BMP_getResolutionX(a));
	desaloca_matriz(imgY, BMP_getResolutionX(a));
	desaloca_matriz(imgCb, BMP_getResolutionX(a));
	desaloca_matriz(imgCr, BMP_getResolutionX(a));
	fclose(comprimido);
}


/*
	Funcao que descomprime uma imagem BMP. Primeiramente, o arquivo
	comprimido eh lido, decodificando o run-length. A IDCT eh aplicada,
	e o resultado eh transformado em RGB novamente, para escrever os
	componentes da imagem no arquivo descomprimido ("imagemFinal.bmp").

	@Parâmetros
		BMPImagem **i : imagem lida do arquivo BMP (em RGB);
		BMPCabecalho *a : cabecalho da imagem BMP;
		FILE *imgOriginal : arquivo da imagem original;
	@Retorno
		VOID
*/
void BMP_descomprime(BMPCabecalho *a, FILE *comprimido){
	
	int x, y;
	long int bo1, bo2;

	// Pulando o cabecalho, lido anteriormente;
	fseek(comprimido, 54, SEEK_SET);

	// Lendo os byteoffsets auxiliares, que sao as posicoes dos componentes YCbCr;
	fread(&bo1, sizeof(long int), 1, comprimido);
	fread(&bo2, sizeof(long int), 1, comprimido);

	// Aplicando a decodificacao do run-length em cada componente;
	int** imgY = run_length_decodifica(BMP_getResolutionX(a), BMP_getResolutionY(a), comprimido);
	fseek(comprimido, bo1, SEEK_SET);
	int** imgCb = run_length_decodifica(BMP_getResolutionX(a), BMP_getResolutionY(a), comprimido);
	fseek(comprimido, bo2, SEEK_SET);
	int** imgCr = run_length_decodifica(BMP_getResolutionX(a), BMP_getResolutionY(a), comprimido);	

	// Aplicando a IDCT;
	imgY = BMP_IDCT(imgY, BMP_getResolutionX(a), BMP_getResolutionY(a));
	imgCb = BMP_IDCT(imgCb, BMP_getResolutionX(a), BMP_getResolutionY(a));
	imgCr = BMP_IDCT(imgCr, BMP_getResolutionX(a), BMP_getResolutionY(a));

	//Transformando a imagem YCbCr em RGB
	int** imgB = aloca_matriz(BMP_getResolutionX(a), BMP_getResolutionY(a));
	int** imgG = aloca_matriz(BMP_getResolutionX(a), BMP_getResolutionY(a));
	int** imgR = aloca_matriz(BMP_getResolutionX(a), BMP_getResolutionY(a));
	YCbCrToRGB(imgB, imgG, imgR, imgY, imgCb, imgCr, BMP_getResolutionX(a), BMP_getResolutionY(a));

	// Abrindo o arquivo para escrever a imagem final;
	FILE *imagemFinal = fopen("imagemFinal.bmp", "wb");

	//Escrevendo cabecalho
	fseek(comprimido, 0, SEEK_SET);
	for(x = 0; x < 54; x++) fputc(fgetc(comprimido), imagemFinal);
	//Escrevendo os dados;
	for (x = 0; x <BMP_getResolutionX(a); x++){
		for(y = 0; y < BMP_getResolutionY(a); y++){
			fputc(cast(imgB[x][y]), imagemFinal);
			fputc(cast(imgG[x][y]), imagemFinal);
			fputc(cast(imgR[x][y]), imagemFinal);
		}
    }

    // Desalocando as matrizes BGR, e fechando os arquivos;
    desaloca_matriz(imgB, BMP_getResolutionX(a));
	desaloca_matriz(imgG, BMP_getResolutionX(a));
	desaloca_matriz(imgR, BMP_getResolutionX(a));
	fclose(comprimido);
	fclose(imagemFinal);
}

/*
	Funcao que calcula o tamanho do arquivo, dado o nome do mesmo.

	@Parâmetros
		char *nomeArq : nome do arquivo;
	@Retorno
		long int : tamanho do arquivo, em bytes;
*/
long int tamanhoArquivo(char *nomeArq){

    FILE* arq = fopen(nomeArq, "r");
    if (arq == NULL) { 
        printf("Falha ao abrir o arquivo.\n"); 
        return 1; 
    } 
  
    fseek(arq, 0, SEEK_END); 
  
    // Calculando o tamanho do arquivo; 
    long int tam = ftell(arq); 
  
    // Fechando o arquivo;
    fclose(arq); 
  
    return tam; 
} 