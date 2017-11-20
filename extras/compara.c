#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void adicionaFinalString(char *str, char c, int limite){
   int tamanho = strlen(str);

   if (tamanho > limite)
      return;

   str[tamanho] = c;
   str[tamanho + 1] = '\0';

   return;
}

void lerElementos(FILE *matriz, float *elementos, int ordem) {
   char ch;
   // 100 é o limite para a representação em string de um número.
   char str[100] = "";
   int numeroDeElementos = ordem * ordem;
   int posicao = 0;

   ch = fgetc(matriz);
   while (ch != EOF) {
      if (ch == '\n' || ch == ':') {
         elementos[posicao] = atof(str);
         posicao++;
	 strcpy(str, "");
      } else {
         adicionaFinalString(str, ch, 100);
      }
      ch = fgetc(matriz);
   }

   return;
}

int main(int argc, char *argv[]) {
   // 0 - matrizes iguais, 1 - matrizes diferentes
   int status = 0;

   // Recuperar o nome do arquivo da primeira matriz.
   char *arquivoMatrizUm = argv[1];

   // Recuperar nome do arquivo da segunda matriz.
   char *arquivoMatrizDois = argv[2];

   // Abrir arquivos para leitura.
   FILE *matrizUm = fopen(arquivoMatrizUm, "r");
   FILE *matrizDois = fopen(arquivoMatrizDois, "r");

   // Ler e compara as ordens.
   char c[10];
   fscanf(matrizUm, "%[^\n]", c);
   int ordemUm = atof(c);
   fscanf(matrizDois, "%[^\n]", c);
   int ordemDois = atof(c);
   if (ordemUm != ordemDois)
      status = 1;

   // Ler o caractere nova linha.
   fgetc(matrizUm);
   fgetc(matrizDois);

   float *elementosMatrizUm;
   float *elementosMatrizDois;

   // Ler e compara cada elemento das matriz.
   if (status == 0) {

      // Aloca espaço para as matrizes em um vetor linear.
      elementosMatrizUm = malloc(ordemUm * ordemUm * sizeof(float));
      elementosMatrizDois = malloc(ordemDois * ordemDois * sizeof(float));

      // Carrega os elementos a partir dos arquivos.
      lerElementos(matrizUm, elementosMatrizUm, ordemUm);
      lerElementos(matrizDois, elementosMatrizDois, ordemDois);

      // Se algum elemento for diferente, as matrizes são diferentes.
      for (int i = 0; i < ordemUm * ordemUm; ++i)
         if (elementosMatrizUm[i] != elementosMatrizDois[i])
	    status = 1;
   }

   // Fecha arquivos.
   fclose(matrizUm);
   fclose(matrizDois);

   // Desaloca vetores.
   free(elementosMatrizUm);
   free(elementosMatrizDois);

   // Imprime resultado.
   if (status == 1)
      printf("Diferentes.\n");
   else
      printf("Iguais.\n");
   return 0;
}