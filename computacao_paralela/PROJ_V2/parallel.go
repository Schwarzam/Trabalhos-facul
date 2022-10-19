package main

import (
	"fmt"
	"math/big"
	"sync"
)

func makeArray(tam int) []int { //Cria um array de 1 até tam
	a := make([]int, tam-1+1)
	for i := range a {
		a[i] = 1 + i
	}
	return a
}

func multip(wg *sync.WaitGroup, s []int, c chan big.Int) { //Multiplica todos elementos do vetor
	defer wg.Done()

	sum := big.NewInt(1)
	for _, v := range s {
		sum.Mul(sum, big.NewInt(int64(v)))
	}
	c <- *sum // adicionar soma ao channel
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

func factorial(wg *sync.WaitGroup, num int) *big.Int {
	arr := makeArray(num)
	arrays := dividirArray(arr, 1)
	channel := make(chan big.Int)

	for chunk := range arrays {
		wg.Add(1)
		go multip(wg, arrays[chunk], channel)
	}

	go func() {
		wg.Wait()
		close(channel)
	}()

	res := big.NewInt(1)
	for n := range channel {

		fmt.Println(n)
	}

	return res
}

func main() {
	var wg sync.WaitGroup

	res := factorial(&wg, 10)

	fmt.Printf("res %d \n", res)
}
