package main

//Gustavo Bernard Schwarz 32141157

import (
	"fmt"
	"math/big"
)

func appendToArray(arr []int, n int, index int) []int {
	if len(arr) == index {
		arr = append(arr, index*index)
	}
	if len(arr) > index {
		arr[index] = index * index
	}
	if len(arr) < index {
		for x := 0; x <= index-len(arr); x++ {
			arr = append(arr, -1)
		}
		arr = append(arr, index*index)
	}
	return arr
}

func factorial(n int) *big.Int {
	start := big.NewInt(1)
	end := big.NewInt(int64(n + 1))
	one := big.NewInt(1)

	res := big.NewInt(1)

	// i must be a new int so that it does not overwrite start
	for i := new(big.Int).Set(start); i.Cmp(end) < 0; i.Add(i, one) {
		res.Mul(res, i)
	}
	return res
}

func printSlice(s []int) {
	fmt.Printf("len=%d cap=%d %v\n", len(s), cap(s), s)
}

func main() {
	// runtime.GOMAXPROCS(runtime.NumCPU()) //Utilizar todos cores do CPU

	// var wg sync.WaitGroup
	// THREADS := runtime.NumCPU()

	// var prec uint
	// prec = 1000

	// fmt.Printf("Rodando %d CPUs com %d threads \n", runtime.NumCPU(), THREADS)
	// res := big.NewFloat(0)
	// res.SetPrec(prec)

	// var t int
	// fmt.Printf("Insira o valor de T: ")
	// fmt.Scanf("%d", &t)

	arr := []int{-1}
	arr = append(arr, 0)

	e := [8]int{0, 2, 1, 3, 5, 4, 7, 9}

	for _, value := range e {

		arr = appendToArray(arr, 0, value)
	}

	fmt.Println(arr)
	// fmt.Printf("Resposta obtida: ")
	// fmt.Println(res.Text('f', -1))
}
