# My project's README

* Processador: Core i5 3470
* Memória: 8GB DDR3
* Sistema Operacional: Ubuntu 16.04 64bits
* Compilador: gcc (Debian 6.4.0-2)

Ordem da Matriz | Versão Serial | Versão Paralela
:---------------:|:------------:|:---------------:
        1000     | 0m3.141s     | 0m1.473s
        2000     | 0m22.849s    | 0m9.436s
        3000     | 1m14.392s    | 0m28.948s
        4000     | 2m52.598s    | 1m5.737s
        5000     | 5m34.305s    | 2m3.487s
    
 ##Para compilar e executar o código serial
 
    **$** gcc trabalhoso_serial.c -o serial
    **$** ./serial arquivomatrizA.txt arquivomatrizB.txt resultadoserial.txt
 ##Para compilar e executar o código paralelo
 
    **$** gcc trabalhoso_paralelo.c -pthread -o paralelo
    **$** ./paralelo arquivomatrizA.txt arquivomatrizB.txt resultadoparalelo.txt