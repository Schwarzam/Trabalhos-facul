package main

//Gustavo Bernard Schwarz 32141157

import (
	"fmt"
	"math/big"
)

func appendToArray(arr *[]int, n int, index int) {

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

	factorials_arr := []int{-1}
	factorials_arr = append(factorials_arr, 0)

	for key, value := range 10 {
		if len(factorials_arr) >= key {

		}
	}

	fmt.Println(len(factorials_arr))
	fmt.Println(factorials_arr)
	// fmt.Printf("Resposta obtida: ")
	// fmt.Println(res.Text('f', -1))
}
