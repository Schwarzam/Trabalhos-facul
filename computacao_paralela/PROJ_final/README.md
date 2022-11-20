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









