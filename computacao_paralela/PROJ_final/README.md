## Gustavo Bernard Schwarz 32141157

## Execução em: 
 - Distributor ID: Ubuntu
 - Description:    Ubuntu 22.04.1 LTS
 - Release:        22.04
 - Codename:       jammy

#####Objetivo: obter série de taylor convergindo para o número de euler 2.71….. Isso de maneira paralela. 

Golang foi a linguagem escolhida pois é possível trabalhar com números decimais com precisão infinita de maneira simples. Além disso é possível paralelizar o código de maneira simples.

#### Comando para rodar o código: 

```shell
go run main.go euler.go
```

Para rodar com um número específico de bits de precisao na resposta.

```shell
go run main.go euler.go <n_bits>

go run main.go euler.go 20000
```

#### Referencia de resposta:

[https://apod.nasa.gov/htmltest/gifcity/e.2mil](https://apod.nasa.gov/htmltest/gifcity/e.2mil) número de Euler com 2mi de casas decimais de precisão.

<br>

#### Estatísticas Apple m1:

Apple clang version 13.1.6 (clang-1316.0.21.2.5)
Target: arm64-apple-darwin21.3.0
Chip:	Apple M1 Pro
Total Number of Cores:	8

| Threads | t1 | t2 | t3 | t_mean | speedup |
|--------|-----|----|----|--------|---------|
| **1** | 591.52s | 591.31s | 592.70 | 591.84s | 1.0 |
| **2** | 297.08s | 297.07s | 296.70 | 296.95s | 1.99 |
| **4** | 149.30s | 149.65s | 150.62 | 149.85s | 3.94 |
| **8** | 75.39s | 75.37s | 75.36s | 75.37s | 7.85 | 
| **16** | 38.31s | 38.30s | 38.35s| 38.32s | 15.44 |
| **32** | 19.73s | 19.50s | 19.52s | 19.58s | 30.22 |
| **64** | 10.44s | 10.35s | 10.32s | 10.37s | 57.07 | 
| **128** | 5.74s | 5.74s | 5.76s | 5.74s | 103.10 | 
| **256** | 3.39s | 3.39s | 3.40s | 3.39s | 174.58 |
| **512** | 2.21s | 2.22s | 2.23s | 2.22s | 266.59 |
| **768** | 2.12s | 1.80s | 1.80s | 1.90s | 311.49 |
| **1024** | 1.62s | 1.62s | 1.62s | 1.62s | 365.33 |
| **1536** | 1.80s | 1.48s | 1.50s | 1.59s | 372.22 |

**threads X speedup**

![](https://raw.githubusercontent.com/Schwarzam/Trabalhos-facul/master/computacao_paralela/PROJ_final/plots/speedup_plot_mac.png)








