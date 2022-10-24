### Projeto escrito em GOLANG
###### Gustavo Schwarz 32141157

<br>

#### Calculando Speedup

T = 10000

| procs | 1 | 2 |
|---|---|---|
| Tempo | 39.901s | 23.893s |
| Speedup | 1 | 1.67 |
| Eficiencia | 1 | 0.835 |


Valor de euler alcancado:
2.71828182845904523536


**Observações:**
Existem problemas com a precisao. Toda operação da Série de Taylor ocorre de maneira correta, mas a precisção ao fazer a soma da iteração da Série de Taylor no resultado final ocorre algum problema que estou para descobrir.

<br>

#### Como instalar golang no ubuntu 22.04:
sudo apt update
sudo add-apt-repository ppa:longsleep/golang-backports
sudo apt update
sudo apt install golang-go


##### Rodar um script .go

```
go run script.go
```







