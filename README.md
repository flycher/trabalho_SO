# My project's README

* Processador: Core i7 7500u
* Memória: 8GB DDR4
* Sistema Operacional: Deepin 15.5 64bits
* Compilador: gcc (Debian 6.4.0-2) 6.4.0

____________________________________________________________________
Ordem da Matriz |      Versão Serial          |  Versão Paralela
:--------------:|:---------------------------:|:-------------------:
    1000        |    3.380517 segundos        |  2.137075 segundos
    2000        |    23.663571 segundos       |  15.365730 segundos
    3000        |    76.525247 segundos       |  49.849137 segundos
    4000        |    179.464801 segundos      |  118.776559 segundos
    5000        |    342.793546 segundos      |  229.725560 segundos
    
> ##Para compilar e executar o código serial
>
> > **$** gcc trabalhoso_serial.c -o serial
>
> > **$** ./serial arquivomatrizA.txt arquivomatrizB.txt resultadoserial.txt
> 
> ##Para compilar e executar o código paralelo
>
> > **$** gcc trabalhoso_paralelo.c -pthread -o paralelo
>
> > **$** ./paralelo arquivomatrizA.txt arquivomatrizB.txt resultadoparalelo.txt
> 