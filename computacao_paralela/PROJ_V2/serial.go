package main

import (
	"fmt"
	"math/big"
)

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

func main() {
	res := big.NewFloat(0)
	res.SetPrec(100)

	var t int
	fmt.Printf("Insira o valor de T: ")
	fmt.Scanf("%d", &t)

	for i := 0; i < t; i++ {
		f := new(big.Float).Quo(big.NewFloat(1), new(big.Float).SetInt(factorial(i)))

		// fmt.Println(i, f)
		// fmt.Println(res.Acc())

		res = res.Add(res, f)
		// fmt.Println(res.Text('f', -1))
	}

	fmt.Printf("Resposta obtida: ")
	fmt.Println(res.Text('f', -1))

	fmt.Printf("Resposta real: ")
	fmt.Printf("2.718281828459045235360287471352662497757247093699 \n") //Valor real
}

// Rodando no ubuntu 22.04 AWS
// go version go1.19.2 linux/amd64

// $time go run serial.go

// Insira o valor de T: 10000
// Resposta obtida: 2.71828182845904523536628951163
// Resposta real: 2.718281828459045235360287471352662497757247093699

// real    0m39.901s
// user    0m37.682s
// sys     0m0.720s
