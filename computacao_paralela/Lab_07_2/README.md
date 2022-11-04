## Gustavo Bernard Schwarz 32141157

## Execução em: 
 - Distributor ID: Ubuntu
 - Description:    Ubuntu 22.04.1 LTS
 - Release:        22.04
 - Codename:       jammy

#### Comando para compilar: gcc ${arquivo}.cpp -fopenmp -lm -lstdc++

<br>

Testes usando dois métodos diferentes de controle de acesso à região crítica (**reduction** e **critical**):


#### **critical**:
| - | 1 CPU | 2 CPUs | 4 CPUs | 8 CPUs |
|---|-------|--------|--------|--------|
||7,872s|4,094s|2,066s|1,512s
||7,852s|4,026s|2,082s|1,439s
||8,091s|4,045s|2,161s|1,500s
| **media** | 7,938s | 4,055s | 2,103s | 1,4837s 
| **speedup** | 1 | 1.957 | 3.774 | 5.350

![](https://raw.githubusercontent.com/Schwarzam/Trabalhos-facul/master/computacao_paralela/Lab_07_2/critical.png)

<br>

#### **reduction**:
| - | 1 CPU | 2 CPUs | 4 CPUs | 8 CPUs |
|---|-------|--------|--------|--------|
|| 7,794s | 3,906s | 1,984s | 1,456s
||7,588s | 3,915s | 1,996s | 1,420s  
||7,568s | 3,905s | 2,038s | 1,463s
| **media** | 7,65s | 3,908s | 2,006s | 1,446s 
| **speedup** | 1 | 1.957 | 3.813 | 5.290

![](https://raw.githubusercontent.com/Schwarzam/Trabalhos-facul/master/computacao_paralela/Lab_07_2/reduction.png)


### alguns prints da execução:

![](https://raw.githubusercontent.com/Schwarzam/Trabalhos-facul/master/computacao_paralela/Lab_07_2/execucao.png)

![](https://raw.githubusercontent.com/Schwarzam/Trabalhos-facul/master/computacao_paralela/Lab_07_2/execucao2.png)