# BMP Compression

Simple BMP-type image compressor and decompressor, developed in C.<br><br>


<h3>Desenvolvedores</h3>
Gabriel Garcia Lorencetti &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp10691891<br>
Giovana Daniele da Silva&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;10692224<br>

<br>

<h3>Descrição</h3>
<p>Para a implementação do projeto de compressao e descompressao, foram utilizadas duas técnicas principais: a DCT, com tabela de quantização (compressão com perdas) e o run-length (compressão sem perdas).</p>
<p>Após da leitura da imagem (cabeçalho e componentes RGB), os canais RGB foram transformados em YCbCr, para o cálculo da Transformada discreta dos cossenos (DCT), que transfere a maior parte da informação contida para os primeiros elementos da matriz. A partir dessa matriz DCT, foi possível aplicar uma tabela de quantização (para a compressão com perdas), e o run-length, técnica para comprimir cadeias	de caracteres onde existem sequências longas de caracteres repetidos (compressão sem perdas). Esses dados comprimidos foram escritos em um arquivo ("comprimido.gagi").</p>
<p>Para descomprimir o arquivo, é necessario decodificar o run-length, aplicar a inversa da Transformada discreta dos cossenos (IDCT), transformar a matriz novamente para RGB e escrevê-la no arquivo ("imagemFinal.bmp").</p><br>

<h3>Compilador</h3>
: GCC 7.4.0<br><br>

<h3>Para compilar</h3>
 Para compilar o programa basta rodar, no terminal, o comando <em>make</em>.<br><br>

<h3>Para executar</h3>
Para compilar o programa basta rodar, no terminal, o comando <em>make run</em>.<br><br>

<h3>Bibliotecas utilizadas</h3>
<ul>
  <li><em>stdio.h</em>;</li>
  <li><em>stdlib.h</em>;</li>
  <li><em>math.h</em>: para cálculos de DCT e IDCT;</li>
  <li><em>time.h</em>: para checar o tempo gasto no processo de compressão e de descompressão.</li>
</ul>
	
<h3>Estruturas de dados utilizadas:</h3>
<ul>
  <li><em>BMPCabecalho</em>: estrutura que armazena o cabecalho da imagem (padrão BMP);</li>
  <li><em>BMPImagem</em>: estrutura que armazenda os dados dos canais RGB (padrão BMP).</li>
</ul>
