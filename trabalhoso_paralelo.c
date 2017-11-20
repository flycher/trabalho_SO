#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; //mutex para evitar conflito ao passar argumentos para threads

struct matrix { //struct para guardar argumentos para passar aos threads
	int parte;
	int tamanho;
	int num_cores;
	float *matA;
	float *matB;
	float *matC;
	char *arquivoA;
	char *arquivoB;
};

void* ler_matriz_a(void *matriz) {
	struct matrix *mat = matriz; //copia as variaveis da struct em cada thread
	FILE *f = fopen(mat->arquivoA, "r"); //abre arquivo con nome dado no argumento em modo leitura
	if (f == 0) { //checa se o arquivo foi aberto com sucesso
    	printf("Erro: nao foi possivel abrir arquivo!");
    	exit(0);
    }

	printf("Lendo matrizA de %s\n", mat->arquivoA);
	int i, j, tam;
	fscanf(f, "%d\n", &tam); //lê o tamanho da matriz do arquivo
  	mat->matA = (float *) malloc(tam * tam * sizeof(float)); //aloca memoria para a matriz

  	for (i = 0; i < tam; i++) {
   		for (j = 0; j < tam; j++) {
       		if (!fscanf(f, "%f:", &mat->matA[i*tam + j])) //lê a matriz do arquivo
       			break;
  		}
  	}

	fclose(f); //fecha o arquivo
}

void* ler_matriz_b(void *matriz) {
	struct matrix *mat = matriz; //copia as variaveis da struct em cada thread
	FILE *f = fopen(mat->arquivoB, "r"); //abre arquivo con nome dado no argumento em modo leitura
	if (f == 0) { //checa se o arquivo foi aberto com sucesso
    	printf("Erro: nao foi possivel abrir arquivo!");
    	exit(0);
    }

	printf("Lendo matrizB de %s\n", mat->arquivoB);
	int i, j, tam;
	fscanf(f, "%d\n", &tam); //lê o tamanho da matriz do arquivo
  	mat->matB = (float *) malloc(tam * tam * sizeof(float)); //aloca memoria para a matriz

  	for (i = 0; i < tam; i++) {
   		for (j = 0; j < tam; j++) {
       		if (!fscanf(f, "%f:", &mat->matB[j*tam + i])) //lê a matriz do arquivo
       			break;
  		}
  	}

	fclose(f); //fecha o arquivo
}

int ler_tamanho_matriz(char *arquivo) {
	FILE *f = fopen(arquivo, "r"); //abre arquivo con nome dado no argumento em modo leitura
	if (f == 0) { //checa se o arquivo foi aberto com sucesso
   		printf("Erro: nao foi possivel abrir arquivo!");
   		exit(0);
   	}

	int tamanho;
	fscanf(f, "%d\n", &tamanho); //lê o tamanho da matriz do arquivo
 	fclose(f); //fecha o arquivo
	return tamanho;
}

void* multiplicacao_matrizes(void* matrizes) {
	struct matrix *mat = matrizes; //copia as variaveis da struct em cada thread

	int tam;
	pthread_mutex_lock(&mutex); //trava mutex para evitar sobreposição de valores
	tam = mat->parte;
	mat->parte++; //aumenta a variavel para o proximo thread
	pthread_mutex_unlock(&mutex); //destrava mutex
	int de = (tam * mat->tamanho)/mat->num_cores; //linha em que o thread começa a fazer a multiplicação
  	int ate = ((tam+1) * mat->tamanho)/mat->num_cores; //linha ate onde o thread faz a multiplicação
  	int i, j, k;

  	printf("Iniciado parte %d (de %d ate %d)\n", tam, de, ate-1);
  	for (i = de; i < ate; i++) {
    	for (j = 0; j < mat->tamanho; j++) {
    	  	mat->matC[i*mat->tamanho + j] = 0;
      		for (k = 0; k < mat->tamanho; k++)
				mat->matC[i*mat->tamanho + j] += mat->matA[i*mat->tamanho + k] * mat->matB[k + j*mat->tamanho];
		}
  	}

  	printf("Finalizado parte %d\n", tam);
}

int main(int argc, char* argv[]) {

	//checa se os argumentos com o nome dos arquivos foram inseridos na execução
	if(argc != 4){
		printf("Argumentos insuficientes. Insira os arquivos contendo as matrizes e o arquivo em que sera salvo o resultado da multiplicação.\n");
		return 2;
	}

	int i, j;
	int num_cores = sysconf( _SC_NPROCESSORS_ONLN ); //detecta e salva numero de cores
	struct matrix matrizes; //passa valores para estrutura
	    matrizes.parte = 0; //valor inicial da parte que o thread fará as multiplicaçoes
	    matrizes.tamanho = ler_tamanho_matriz(argv[1]); //lê o tamanho da matriz resultado do arquivo
	    matrizes.num_cores = num_cores; //numero de threads que serao criados para multiplicação
		matrizes.arquivoA = argv[1];
		matrizes.arquivoB = argv[2];
  		matrizes.matC = (float *)malloc(matrizes.tamanho * matrizes.tamanho * sizeof(float)); //aloca memoria para matrizC


  	pthread_t* thread = (pthread_t*)malloc(2 * sizeof(pthread_t)); //aloca memoria para os threads
  	pthread_create (&thread[i], NULL, ler_matriz_a, (void *)&matrizes);
  	pthread_create (&thread[i], NULL, ler_matriz_b, (void *)&matrizes);
  	for (i = 0; i < 2; i++)
		pthread_join(thread[i], NULL);
  	free(thread); //libera a memoria de threads


  	thread = (pthread_t*)malloc(num_cores * sizeof(pthread_t)); //aloca memoria para os threads

	FILE *f = fopen(argv[3], "w"); //abre ou cria o arquivo com o nome do quarto argumento

	fprintf(f, "%d\n", matrizes.tamanho); //armazena o tamanho da matriz no arquivo
	printf("Tamanho %d da matriz resultado salvo no arquivo.\n", matrizes.tamanho);
	printf("Calculando o produto de Matrizes...\n");

  	for (i = 0; i < num_cores; i++) {
  		//cria thread e passa funcao para multiplicar e parametros como estrutura convertida em void
	    if (pthread_create (&thread[i], NULL, multiplicacao_matrizes, (void *)&matrizes) != 0 ) {
	      	printf("Não foi possivel criar thread.");
	      	free(thread);
	      	exit(0);
	    }
  	}

  	//espera para que todos os threads terminem
  	for (i = 0; i < num_cores; i++)
		pthread_join(thread[i], NULL);
  	free(thread); //libera a memoria de threads

	for (i = 0; i < matrizes.tamanho; i++) {
		for(j = 0; j < matrizes.tamanho; j++) {
			if(j != matrizes.tamanho -1)
				fprintf(f, "%.1f:", matrizes.matC[i*matrizes.tamanho + j]); //armazena o resultado no arquivo
			else
				fprintf(f, "%.1f", matrizes.matC[i*matrizes.tamanho + j]); //armazena o resultado no arquivo
		}
		fprintf(f, "\n");
	}

	printf("Matriz Resultante salva em %s\n", argv[3]);
	fclose(f); //fecha o arquivo

	free(matrizes.matA); //libera memoria da matriz A
	free(matrizes.matB); //libera memoria da matriz B
	free(matrizes.matC); //libera memoria da matriz C

	return 0;
}