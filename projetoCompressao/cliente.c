/*
	SCC0561 - Multimídia
	Compressão de Imagem Digital

	Gabriel Garcia Lorencetti
	NUSP: 10691891

	Giovana Daniele da Silva
	NUSP: 10692224
	
*/
#include "bmp_cabecalho.h"
#include "bmp_imagem.h"
#include <time.h>

/*
	Funcao que imprime o menu principal de funcoes do programa.

	@Parâmetros
		VOID
	@Retorno
		VOID
*/
void imprime_menu(){
	printf("\n----------------------- MENU -----------------------\n");
	printf("\n1. Compressao de uma imagem BMP;\n2. Desompressao de uma imagem BMP;\n");
	printf("3. Compressao e descompressao de uma imagem BMP;\n4. Terminar a aplicacao.");
	printf("\n----------------------------------------------------\n\n");
}

int main(int argc, char *argv[]){
	BMPCabecalho *a = NULL;			// Cabecalho da imagem BMP;
	BMPImagem **i = NULL;			// Dados BGR da imagem BMP;
	FILE *imagemOriginal = NULL;	// Arquivo da imagem original, sem compressao;
	FILE *imagemComprimida = NULL;	// Arquivo da imagem comprimida;
	char nomeBMP[30];				// String para captura do nome do arquivo;
	int op = 0;						// Operacao;
	clock_t c1, c2;					// Variaveis para capturar o tempo;
	double compressao_time;			// Tempo de compressao/descompressao;
	int **imgOR, **imgOG, **imgOB, **imgCR, **imgCG, **imgCB;
	double PSNRValue = 0;

	// Loop principal do menu;
	while(1){
		imprime_menu();

		printf("Digite a operacao: ");
		scanf("%d", &op);
		printf("\n");

		// Switch case para escolha da funcionalidade;
		switch(op){

			case 1: // FUNCIONALIDADE 1: Compressao de imagem

				printf("\nDigite o nome da imagem BMP a ser comprimida:\n");
				scanf("%s", nomeBMP);

				// Abrindo a imagem e checando se a operacao foi bem sucedida;
				imagemOriginal = fopen(nomeBMP, "rb");
				if(imagemOriginal == NULL){
					printf("Falha ao abrir o arquivo.\n");
					break;
				}

				// Lendo o cabecalho da imagem BMP;
				a = BMP_loadCabecalho(imagemOriginal);
				// Lendo as informacoes RGB da imagem BMP;
				i = BMP_loadImagem(imagemOriginal, a);

				// Obtem o tempo antes da compressao;
				c1 = clock();

				// Comprime a imagem e salva no arquivo "comprimido.bin"
				BMP_comprime(i, a, imagemOriginal);

				// Obtem o tempo depois da compressao;
				c2 = clock();

				// Calculando o tempo de compressao e imprimindo na tela;
				compressao_time = (c2-c1)/(double)CLOCKS_PER_SEC;
				printf("\nTempo para compressao: %lf segundos.\n", compressao_time);

				// Liberando da memoria a imagem, o cabecalho, e fechando o arquivo;
				BMP_freeImagem(i, BMP_getDimensao(a));
   				BMP_freeCabecalho(a);
				fclose(imagemOriginal);

				// Calculando a taxa de compressao, de acordo com o tamanho do arquivo original e do arquivo comprimido;
				printf("Taxa de compressao: %.1lf%c\n\n", (100-(100*((double)tamanhoArquivo("comprimido.bin")/(double)tamanhoArquivo(nomeBMP)))), '%');

				break;

			case 2:	// FUNCIONALIDADE 2: Descompressao de imagem

				printf("\nDigite o nome da imagem a ser descomprimida:\n");
				scanf("%s", nomeBMP);

				// Abrindo o arquivo comprimido e checando se a operacao foi bem sucedida;
				imagemComprimida = fopen(nomeBMP, "rb");
				if(imagemComprimida == NULL){
					printf("Falha ao abrir o arquivo.\n");
					break;
				}

				// Lendo o cabecalho do arquivo comprimido;
				a = BMP_loadCabecalho(imagemComprimida);

				// Obtem o tempo antes da compressao;
				c1 = clock();

				// Comprime a imagem e salva no arquivo "imagemFinal.bmp"
				BMP_descomprime(a, imagemComprimida);

				// Obtem o tempo depois da compressao;
				c2 = clock();

				// Calculando o tempo de compressao e imprimindo na tela;
				compressao_time = (c2-c1)/(double)CLOCKS_PER_SEC;
				printf("\nTempo para descompressao: %lf segundos.\n", compressao_time);

				// Liberando da memoria o cabecalho e fechando o arquivo;
				BMP_freeCabecalho(a);
				fclose(imagemComprimida);

				break;

			case 3: // FUNCIONALIDADE 3: Compressao e descompressao de imagem;

				printf("\nDigite o nome da imagem BMP a ser comprimida:\n");
				scanf("%s", nomeBMP);

				// Abrindo a imagem e checando se a operacao foi bem sucedida;
				imagemOriginal = fopen(nomeBMP, "rb");
				if(imagemOriginal == NULL){
					printf("Falha ao abrir o arquivo.\n");
					break;
				}

				// Lendo o cabecalho da imagem BMP;
				a = BMP_loadCabecalho(imagemOriginal);
				// Lendo as informacoes RGB da imagem BMP;
				i = BMP_loadImagem(imagemOriginal, a);

				//Alocando as matrizes RGB;
				imgOB = aloca_matriz(BMP_getResolutionX(a), BMP_getResolutionY(a));
				imgOG = aloca_matriz(BMP_getResolutionX(a), BMP_getResolutionY(a));
				imgOR = aloca_matriz(BMP_getResolutionX(a), BMP_getResolutionY(a));

				//Alocando as matrizes YCbCr;
				imgCB = aloca_matriz(BMP_getResolutionX(a), BMP_getResolutionY(a));
				imgCG = aloca_matriz(BMP_getResolutionX(a), BMP_getResolutionY(a));
				imgCR = aloca_matriz(BMP_getResolutionX(a), BMP_getResolutionY(a));

				//Atribuindo os valores da imagem às componentes das matrizes;
				assignValues(imgOB, imgOG, imgOR, BMP_getResolutionX(a), BMP_getResolutionY(a), i);

				// Obtem o tempo antes da compressao;
				c1 = clock();

				// Comprime a imagem e salva no arquivo "comprimido.bin"
				BMP_comprime(i, a, imagemOriginal);

				// Obtem o tempo depois da compressao;
				c2 = clock();

				// Calculando o tempo de compressao e imprimindo na tela;
				compressao_time = (c2-c1)/(double)CLOCKS_PER_SEC;
				printf("\nTempo para compressao: %lf segundos.\n", compressao_time);

				// Liberando da memoria a imagem, o cabecalho, e fechando o arquivo;
				BMP_freeImagem(i, BMP_getDimensao(a));
   				BMP_freeCabecalho(a);
				fclose(imagemOriginal);

				// Calculando a taxa de compressao, de acordo com o tamanho do arquivo original e do arquivo comprimido;
				printf("Taxa de compressao: %.1lf%c\n\n", (100-(100*((double)tamanhoArquivo("comprimido.bin")/(double)tamanhoArquivo(nomeBMP)))), '%');

				// Abrindo o arquivo comprimido e checando se a operacao foi bem sucedida;
				imagemComprimida = fopen("comprimido.bin", "rb");
				if(imagemComprimida == NULL){
					printf("Falha ao abrir o arquivo.\n");
					break;
				}

				// Lendo o cabecalho do arquivo comprimido;
				a = BMP_loadCabecalho(imagemComprimida);

				// Obtem o tempo antes da compressao;
				c1 = clock();

				// Comprime a imagem e salva no arquivo "imagemFinal.bmp"
				BMP_descomprime(a, imagemComprimida);

				// Obtem o tempo depois da compressao;
				c2 = clock();

				// Calculando o tempo de compressao e imprimindo na tela;
				compressao_time = (c2-c1)/(double)CLOCKS_PER_SEC;
				printf("\nTempo para descompressao: %lf segundos.\n\n", compressao_time);

				// Liberando da memoria o cabecalho e fechando o arquivo;
				BMP_freeCabecalho(a);
				fclose(imagemComprimida);

				// Abrindo a imagem e checando se a operacao foi bem sucedida;
				imagemComprimida = fopen("comprimido.bin", "rb");
				if(imagemComprimida == NULL){
					printf("Falha ao abrir o arquivo.\n");
					break;
				}

				// Lendo o cabecalho da imagem BMP;
				a = BMP_loadCabecalho(imagemComprimida);
				// Lendo as informacoes RGB da imagem BMP;
				i = BMP_loadImagem(imagemComprimida, a);

				//Atribuindo os valores da imagem às componentes das matrizes;
				assignValues(imgCB, imgCG, imgCR, BMP_getResolutionX(a), BMP_getResolutionY(a), i);

				//Fazendo avaliação por meio do PSNR
				PSNRValue += PSNR(BMP_getResolutionX(a), BMP_getResolutionY(a), imgOR, imgCR);
				PSNRValue += PSNR(BMP_getResolutionX(a), BMP_getResolutionY(a), imgOG, imgCG);
				PSNRValue += PSNR(BMP_getResolutionX(a), BMP_getResolutionY(a), imgOB, imgCB);
				printf("PSNR: %.2lf\n\n", PSNRValue/3);

				// Desalocando as matrizes de cada componente e fechando o arquivo;
				desaloca_matriz(imgOR, BMP_getResolutionX(a));
				desaloca_matriz(imgOG, BMP_getResolutionX(a));
				desaloca_matriz(imgOB, BMP_getResolutionX(a));
				desaloca_matriz(imgCR, BMP_getResolutionX(a));
				desaloca_matriz(imgCG, BMP_getResolutionX(a));
				desaloca_matriz(imgCB, BMP_getResolutionX(a));
				fclose(imagemComprimida);
				break;			

			case 4: // Termina a aplicacao;
				return 0;
				break;

			default: // Caso o usuario, digite uma opcao invalida, pede para o mesmo digitar novamente;
				printf("Digite uma opção válida!\n");
		}
	}

	return 0;
}