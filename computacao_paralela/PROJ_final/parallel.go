package main

//Gustavo Bernard Schwarz 32141157

import (
	"fmt"
	"math/big"
)

func getLastIndex(arr []big.Int, actualIndex int) (int, big.Int) {
	if len(arr)-1 < actualIndex {
		actualIndex = len(arr) - 1
	}
	for i := actualIndex; i > 0; i-- {
		if arr[i].String() != "-1" {
			return i, arr[i]
		}
	}
	return 0, *big.NewInt(0)
}

func appendToArray(arr []big.Int, n big.Int, index int64) []big.Int {
	if len(arr) == int(index) {
		arr = append(arr, *big.NewInt(index * index))
	}
	if len(arr) > int(index) {
		arr[index] = *big.NewInt(index * index)
	}
	if len(arr) < int(index) {
		for x := 0; x <= int(index)-len(arr); x++ {
			arr = append(arr, *big.NewInt(-1))
		}
		arr = append(arr, *big.NewInt(index * index))
	}
	return arr
}

func factorial(n int, start int, startvalue big.Int) *big.Int {
	res := big.NewInt(1)
	for i := n; i > start; i-- {
		res = res.Mul(res, big.NewInt(int64(i)))
	}
	res = res.Mul(res, &startvalue)
	return res
}

func calculate_routine()

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

	arr := []big.Int{}
	arr = append(arr, *big.NewInt(1))
	e := [8]int{0, 2, 1, 3, 5, 4, 7, 9}

	for _, value := range e {
		arr = appendToArray(arr, *big.NewInt(int64(value)), int64(value))
	}

	fmt.Println(arr)
	fmt.Println(getLastIndex(arr, 9))
	fmt.Println(factorial(6, 3, *big.NewInt(6)))
	// fmt.Printf("Resposta obtida: ")
	// fmt.Println(res.Text('f', -1))
}
