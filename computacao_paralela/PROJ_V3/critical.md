## Gustavo Bernard Schwarz 32141157

## Execução em: 
 - Distributor ID: Ubuntu
 - Description:    Ubuntu 22.04.1 LTS
 - Release:        22.04
 - Codename:       jammy

#### Comando para compilar: gcc main.cpp -fopenmp -lm -lstdc++

<br>


#### Como é feito o controle de acesso à região crítica para a variável global compartilhada do seu projeto?

A variável global que contém o valor da resposta global é passada para a função "sum_factorial" por referência. Assim na hora de somar na variável global dentro da função, é utilizado o #pragma omp critical. 

<br>

Valor de T: 200000

#### **Tempos speedup**:
| - | 1 CPU | 2 CPUs | 4 CPUs | 8 CPUs |
|---|-------|--------|--------|--------|
||38,039s|28,195s|16,361s|9,256s
||37,792s|28,065s|16,396s|9,185s
||37,598s|28,319s|16,533s|9,243s
| **media** | 37,809s | 28,193s | 16,430s | 9,228s 
| **speedup** | 1 | 1.341 | 2.301 | 4.097

