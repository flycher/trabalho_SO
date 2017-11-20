# My project's README

* Processador: Core i5 4690
* Memória: 8GB DDR3
* Sistema Operacional: Ubuntu 16.04 64bits
* Compilador: gcc (Ubuntu 5.4.0-6ubuntu1~16.04.5)

|Ordem da Matriz |      Versão Serial          |  Versão Paralela    |
|:--------------:|:---------------------------:|:-------------------:|
|    1000        |         0m3.088s            |       0m1.857s      |
|    2000        |         0m22.471s           |       0m12.906s     |
|    3000        |         1m13.128s           |       0m41.583s     |
|    4000        |         2m50.647s           |       1m35.890s     |
|    5000        |         5m30.347s           |       3m4.270s      |
    
 ## Para compilar e executar o código serial
 
    $ gcc trabalhoso_serial.c -o serial
    $ time ./serial arquivomatrizA.txt arquivomatrizB.txt resultadoserial.txt
 ## Para compilar e executar o código paralelo
 
    $ gcc trabalhoso_paralelo.c -pthread -o paralelo
    $ time ./paralelo arquivomatrizA.txt arquivomatrizB.txt resultadoparalelo.txt
