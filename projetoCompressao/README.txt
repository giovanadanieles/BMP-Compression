SCC0561 - Multimídia
Compressão de Imagem Digital

Gabriel Garcia Lorencetti
NUSP: 10691891

Giovana Daniele da Silva
NUSP: 10692224


Foi utilizado o compilador GCC, na versao 7.4.0.
Para executar o programa, é necessario somente rodar no terminal
o comando make (para compilar) e make run (para executar).


Foram utilizadas as seguintes bibliotecas:
	- stdio.h;
	- stdlib.h;
	- math.h (para calculos da DCT e IDCT);
	- time.h (para checar o tempo de compressão e descompressão);
	
	
Estruturas de dados utilizadas:

	BMPCabecalho: estrutura que armazena o cabecalho da imagem (padrão BMP);
	BMPImagem: estrutura que armazenda os dados dos canais RGB (padrão BMP);


Algoritmos:

	Para a implementação do projeto de compressao e descompressao, foram utilizadas
duas técnicas principais: a DCT, com tabela de quantização (compressão com perdas) e
o run-length (compressão sem perdas).
	Após da leitura da imagem (cabeçalho e componentes RGB), os canais RGB foram 
transformados em YCbCr, para o cálculo da Transformada discreta dos cossenos (DCT), 
que transfere a maior parte da informação contida para os primeiros elementos da matriz.
A partir dessa matriz DCT, foi possível aplicar uma tabela de quantização (para a compressão
com perdas), e o run-length, técnica para comprimir cadeias	de caracteres onde existem
sequências longas de caracteres repetidos (compressão sem perdas). Esses dados comprimidos
foram escritos em um arquivo ("comprimido.gagi").
	Para descomprimir o arquivo, é necessario decodificar o run-length, aplicar a inversa
da Transformada discreta dos cossenos (IDCT), transformar a matriz novamente para RGB e
escrevê-la no arquivo ("imagemFinal.bmp").
