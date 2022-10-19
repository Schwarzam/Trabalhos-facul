package main

//Gustavo Bernard Schwarz 32141157

import (
	"fmt"
	"math/big"
	"runtime"
	"sync"
)

func makeArray(tam int) []int { //Cria um array de 1 até tam
	a := make([]int, tam-1+1)
	for i := range a {
		a[i] = 1 + i
	}
	return a
}

func multip(wg *sync.WaitGroup, s []int, c chan *big.Int) { //Multiplica todos elementos do vetor
	defer wg.Done()

	sum := big.NewInt(1)
	for _, v := range s {
		sum.Mul(sum, big.NewInt(int64(v)))
	}
	c <- sum // adicionar soma ao channel
	return
}

func dividirArray(slice []int, chunkSize int) [][]int { //Dividir array em X partes
	var chunks [][]int
	for {
		if len(slice) == 0 {
			break
		}

		// Nao cortar além da capacidade
		if len(slice) < chunkSize {
			chunkSize = len(slice)
		}

		chunks = append(chunks, slice[0:chunkSize])
		slice = slice[chunkSize:]
	}
	return chunks
}

func factorial(wg *sync.WaitGroup, num int, threads int) *big.Int {
	arr := makeArray(num) //Cria um array de 1 ao numero
	size := (len(arr) / threads) + 1

	arrays := dividirArray(arr, size)       //Divide array em pequenos pedacos de tamanho size
	channel := make(chan *big.Int, threads) //Canal compartilhado com threads para troca de infos

	for chunk := range arrays {
		wg.Add(1)
		go multip(wg, arrays[chunk], channel) //Faz a multiplicacao dos elementos no array
	}

	go func() { //Espera todas threads terminarem
		wg.Wait()
		close(channel)
	}()

	res := big.NewInt(1)
	for n := range channel {
		res.Mul(res, n) //Multiplica os resultados de cada thread
	}

	return res
}

func main() {
	runtime.GOMAXPROCS(runtime.NumCPU()) //Utilizar todos cores do CPU

	var wg sync.WaitGroup
	THREADS := runtime.NumCPU()

	fmt.Printf("Rodando %d CPUs com %d threads \n", runtime.NumCPU(), THREADS)
	res := big.NewFloat(0)
	res.SetPrec(100)

	var t int
	fmt.Printf("Insira o valor de T: ")
	fmt.Scanf("%d", &t)

	for i := 0; i < t; i++ {
		f := new(big.Float).Quo(big.NewFloat(1), new(big.Float).SetInt(factorial(&wg, i, THREADS)))
		res = res.Add(res, f)
	}

	fmt.Printf("Resposta obtida: ")
	fmt.Println(res.Text('f', -1))

	fmt.Printf("Resposta real: ")
	fmt.Printf("2.718281828459045235360287471352662497757247093699 \n") //Valor real

}

//No meu PC:

// $ time go run serial.go
// Insira o valor de T: 10000
// Resposta obtida: 2.71828182845904523536628951163
// Resposta real: 2.718281828459045235360287471352662497757247093699
// go run serial.go  36.03s user 0.88s system 95% cpu 38.837 total

// $ time go run parallel.go
// Rodando em 8 CPUs, com 10 threads
// Insira o valor de T: 10000
// Resposta obtida: 2.71828182845904523536628951163
// Resposta real: 2.718281828459045235360287471352662497757247093699
// go run parallel.go  16.85s user 1.23s system 116% cpu 15.488 total
