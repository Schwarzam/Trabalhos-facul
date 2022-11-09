#include <iostream>
#include <iomanip>

void sum_fatorial(int n, long double *res){
    int local_res = 1;
    for (int i = n; i > 0; i--){
        local_res = local_res * i;
    }
    #pragma omp critical
    *res += (long double)1 / (long double)local_res;
}

int main() {

    int T = 200000;
    long double res = 1;
    // std::cout << "Valor de T: ";
    // std::cin >> T;

    #pragma omp parallel num_threads(8)
    { 
        #pragma omp for
        for (int i = 1; i <= T; i++){
            sum_fatorial(i, &res);
        }
    }

    std::cout << "Resposta: " << std::setprecision(40) << res << std::endl;
}

