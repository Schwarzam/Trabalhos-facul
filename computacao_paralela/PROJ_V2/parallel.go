package main

import (
	"fmt"
)

func makeArray(min, max int) []int { //Cria um array de x até y
	a := make([]int, max-min+1)
	for i := range a {
		a[i] = min + i
	}
	return a
}

func multip(s []int, c chan int) {
	sum := 1
	for _, v := range s {
		sum *= v
	}
	c <- sum // send sum to c
}

func dividirArray(slice []int, chunkSize int) [][]int {
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

func main() {
	d := makeArray(1, 11)
	arrays := dividirArray(d, 2)

	fmt.Printf("%v \n", arrays)

	for s := range d {
		fmt.Println(s)
	}

}
