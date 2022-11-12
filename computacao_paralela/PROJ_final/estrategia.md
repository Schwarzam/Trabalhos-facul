####Objetivo: obter série de taylor convergindo para o número de euler 2.71….. Isso de maneira paralela. 

Golang foi a linguagem escolhida pois é possível trabalhar com números decimais com precisão infinita de maneira simples. 

Fatorial funciona perfeitamente com precisão infinita. 
1 / Fatorial funciona perfeito com precisão infinita. 

Entretanto existe um problema na adição, a precisão é comprometida na adição.

Estratégia (iterações): 

**0** (res = 0)
res = res + 1/0! => 1

**1** (res = 1)
res = res + 1 / 1! => 1

**2** (res == 2)
res = res + 1 / 2! => 0.5

**3** (res == 2.5)
res = res + 1 / 3! => 0.125

**4** (res == 2.625)
res = res + 1 / 4! => 0.0625 

**5** (res == 2.6875)
res = res + 1 / 5! => 0.008333..


