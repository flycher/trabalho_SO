# My project's README

* Processador: Core i5 4690
* Memória: 8GB DDR3
* Sistema Operacional: Ubuntu 16.04 64bits
* Compilador: gcc (Ubuntu 5.4.0-6ubuntu1~16.04.5)

|Ordem da Matriz |      Versão Serial          |  Versão Paralela    |
|:--------------:|:---------------------------:|:-------------------:|
|    1000        |         0m3.576s            |       0m1.902s      |
|    2000        |         0m24.846s           |       0m11.125s     |
|    3000        |         1m19.757s           |       0m33.165s     |
|    4000        |         3m5.561s            |       1m14.278s     |
|    5000        |         5m57.424s           |       2m22.036s     |
    
 ## Para compilar e executar o código serial
 
    $ gcc trabalhoso_serial.c -o serial
    $ time ./serial arquivomatrizA.txt arquivomatrizB.txt resultadoserial.txt
 ## Para compilar e executar o código paralelo
 
    $ gcc trabalhoso_paralelo.c -pthread -o paralelo
    $ time ./paralelo arquivomatrizA.txt arquivomatrizB.txt resultadoparalelo.txt

