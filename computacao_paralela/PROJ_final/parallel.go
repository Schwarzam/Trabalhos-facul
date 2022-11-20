package main

//Gustavo Bernard Schwarz 32141157

import (
	"fmt"
	"math/big"
	"sync"
)

var arr []big.Int
var mu sync.Mutex

type arr_struct struct {
	MU  sync.Mutex
	arr []big.Int
}

var data arr_struct

var wg sync.WaitGroup

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

func appendToArray(n big.Int, index int64) {
	fmt.Println()
	fmt.Println(n, index, len(data.arr))
	fmt.Println(data.arr)
	if len(data.arr) == int(index) {
		data.arr = append(data.arr, *big.NewInt(index * index))
	}
	if len(data.arr) > int(index) {
		data.arr[index-1] = *big.NewInt(index * index)
	}
	if len(data.arr) < int(index) {
		fmt.Println(int(index) - len(data.arr))
		for x := 0; x <= int(index)-len(data.arr); x++ {
			fmt.Println(x)
			data.arr = append(data.arr, *big.NewInt(-1))
		}
		data.arr = append(data.arr, *big.NewInt(index * index))
	}
	fmt.Println(data.arr)
	fmt.Println()
}

func factorial(n int, start int, startvalue big.Int) *big.Int {
	res := big.NewInt(1)
	for i := n; i > start; i-- {
		res = res.Mul(res, big.NewInt(int64(i)))
	}
	res = res.Mul(res, &startvalue)
	return res
}

func printarr() {
	fmt.Println(data.arr)
}

func teste(n big.Int, index int64) {
	defer wg.Done()

	data.MU.Lock()
	appendToArray(n, index)
	data.MU.Unlock()
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

	data.arr = append(data.arr, *big.NewInt(1))
	e := [8]int{2, 1, 3, 5, 4, 7, 9, 11}

	for _, value := range e {
		wg.Add(1)
		go teste(*big.NewInt(int64(value)), int64(value))
	}

	wg.Wait()

	printarr()
	// fmt.Printf("Resposta obtida: ")
	// fmt.Println(res.Text('f', -1))
}

//https://www.math.utah.edu/~pa/math/e.html
