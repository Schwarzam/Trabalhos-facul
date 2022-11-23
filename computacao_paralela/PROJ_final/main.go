package main

//Gustavo Bernard Schwarz 32141157

import (
	"fmt"
	"math/big"
	"os"
	"runtime"
	"strconv"
	"sync"
	"time"
)

var arr []big.Int
var mu sync.Mutex

var wg sync.WaitGroup

func factorial(n int, start int, startvalue big.Int, channel chan *big.Int) {
	//Calcula o fatorial, pode fornecer valores intermediários para agilizar.
	defer wg.Done()
	res := big.NewInt(1)
	for i := n; i > start; i-- {
		res = res.Mul(res, big.NewInt(int64(i)))
	}
	res = res.Mul(res, &startvalue)
	channel <- res
}

func main() {
	t1 := time.Now()

	//Checa se tem input para numero de threads
	var num_cpu int
	if len(os.Args) > 2 {
		tmp, _ := strconv.ParseInt(os.Args[2], 0, 64)
		num_cpu = int(tmp)
	} else {
		num_cpu = runtime.NumCPU() //Utilizar todos cores do CPU
	}
	runtime.GOMAXPROCS(num_cpu)

	//Checa se tem input para precisao em bits
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

	//While True
	for true {
		channel := make(chan *big.Int, num_cpu)

		for i := 0; i < num_cpu; i++ {
			wg.Add(1)
			counter++
			go factorial(counter, biggerIndex, *bigger, channel)
		} //Entrega ã num_cpu threads os proximos fatoriais com o resultado da ultima rodada já para agilizar.

		wg.Wait()
		close(channel)

		for n := range channel { //Recebe os resultados de cada thread pelo canal
			switch n.Cmp(bigger) {
			case 1:
				bigger = n //Salva o resultado mais alto da rodada.
			}

			f := new(big.Float).SetPrec(prec)
			f.Quo(big.NewFloat(1), new(big.Float).SetInt(n))
			res = res.Add(res, f)
		}
		//fmt.Printf("Obtained: %s \nT value: %d \n", res.Text('f', -1), counter)
		fmt.Printf("T value: %d \n", counter)
		biggerIndex = counter //Salva o indice do maior numero da rodada.

		if counter > 4 {
			if res.Text('f', -1)[0:len(res.Text('f', -1))-3] == euler[0:len(res.Text('f', -1))-3] { //Significa que chegou na precisao maxima
				fmt.Println("Converged to max precision.")
				t2 := time.Now()
				diff := t2.Sub(t1)

				fmt.Printf("Obtained: %d correct decimalss \nT value: %d \n", checkPrecision(res.Text('f', -1))-2, counter)

				f, _ := os.Create("result.txt")
				_, err2 := f.WriteString(fmt.Sprintf(`Converged to max precision.
Threads = %d
T = %d
Time = %s
Res bits precision = %d
Decimal precision (number of correct decimals) = %d
Euler: 
%s
				`, num_cpu, counter, diff, prec, checkPrecision(res.Text('f', -1))-2, res.Text('f', -1)))

				if err2 != nil {
					fmt.Println(err2)
				}

				break
			}
		}

		if counter%5*num_cpu == 0 {
			fmt.Printf("Current preciosion: %d number of decimal digits.\n", checkPrecision(res.Text('f', -1))-2)
		}
	}
}

//https://www.math.utah.edu/~pa/math/e.html
