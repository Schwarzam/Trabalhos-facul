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

	t := 100000
	for i := 0; i < t; i++ {
		f := new(big.Float).Quo(big.NewFloat(1), new(big.Float).SetInt(factorial(i)))

		// fmt.Println(i, f)
		// fmt.Println(res.Acc())

		res = res.Add(res, f)
		// fmt.Println(res.Text('f', -1))
	}
	fmt.Println(res.Text('f', -1))
	fmt.Printf("2.718281828459045235360287471352662497757247093699 \n")
}
