package main

//Gustavo Bernard Schwarz 32141157

import (
	"fmt"
	"math/big"
	"os"
	"runtime"
	"strconv"
	"sync"
)

var arr []big.Int
var mu sync.Mutex

var wg sync.WaitGroup

func factorial(n int, start int, startvalue big.Int, channel chan *big.Int) {
	defer wg.Done()
	res := big.NewInt(1)
	for i := n; i > start; i-- {
		res = res.Mul(res, big.NewInt(int64(i)))
	}
	res = res.Mul(res, &startvalue)
	channel <- res
}

func main() {

	num_cpu := runtime.NumCPU()
	runtime.GOMAXPROCS(num_cpu) //Utilizar todos cores do CPU

	var prec uint
	if len(os.Args) > 1 {
		tmp, _ := strconv.ParseInt(os.Args[1], 0, 64)
		prec = uint(tmp)
	} else {
		prec = 100000
	}

	fmt.Printf("Rodando %d CPUs com %d threads \n", runtime.NumCPU(), num_cpu)
	res := big.NewFloat(1)
	res.SetPrec(prec)

	//lastResults := []big.Int{}
	counter := 0
	bigger := big.NewInt(1)
	biggerIndex := 0

	for true {

		channel := make(chan *big.Int, num_cpu)

		for i := 0; i < num_cpu; i++ {
			wg.Add(1)
			counter++
			go factorial(counter, biggerIndex, *bigger, channel)
		}

		wg.Wait()
		close(channel)

		for n := range channel {
			switch n.Cmp(bigger) {
			case 1:
				bigger = n
			}

			f := new(big.Float).SetPrec(prec)
			f.Quo(big.NewFloat(1), new(big.Float).SetInt(n))
			res = res.Add(res, f)
		}
		//fmt.Printf("Obtained: %s \nT value: %d \n", res.Text('f', -1), counter)
		fmt.Printf("T value: %d \n", counter)
		biggerIndex = counter

		if res.Text('f', -1)[0:len(res.Text('f', -1))-3] == euler[0:len(res.Text('f', -1))-3] && counter > 4 {
			fmt.Println("Converged to max precision.")
			fmt.Printf("Obtained: %s \nT value: %d \n", res.Text('f', -1), counter)
			break
		}

		if counter%5*num_cpu == 0 {
			fmt.Printf("Current preciosion: %d number of decimal digits.\n", checkPrecision(res.Text('f', -1))-2)
		}
	}

	// fmt.Printf("Resposta obtida: ")
	// fmt.Println(res.Text('f', -1))
}

//https://www.math.utah.edu/~pa/math/e.html
