#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
   // Recuperar ordem da matriz.
   int ordem = atoi(argv[1]);

   // Recuperar nome do arquivo para salvar a matriz.
   char *nomeDoArquivo = argv[2];

   // Abrir arquivo para escrita.
   FILE *arquivo = fopen(nomeDoArquivo, "w+");

   // Escreve a ordem.
   fprintf(arquivo, "%d\n", ordem);
   float x, a = 10;
   for (int i = 0; i < ordem; i++) {
      for (int j = 0; j < ordem; j++) {
      	x = (float)rand()/(float)(RAND_MAX/a);
         if (j < ordem - 1)
            fprintf(arquivo, "%.2f:", x);
	 else
            fprintf(arquivo, "%.2f", x);
      }
      fprintf(arquivo, "\n");
   }

   // Escreve os elementos.

   // Fecha arquivo.
   fclose(arquivo);

   return 0;
}