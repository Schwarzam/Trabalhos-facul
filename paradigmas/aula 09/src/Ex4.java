
abstract class Conta{
    int num_conta;
    String nome;
    Double saldo;

    void deposito(int valor){
        saldo += valor;
    };
    void saque(int valor){
        if (saldo - valor > 0){
            saldo -= valor;
        }
        else{
            System.out.printf("saldo nao disponivel para saque \n");
        }
    };

    void imprimirSaldo(){
        System.out.printf("saldo: %f \n", saldo);
    };
}

class Corrente extends Conta{

}

class CorrenteEspecial extends Conta {
    Double limite;

    @Override
    void saque(int valor){
        if (saldo - valor < limite){
            System.out.printf("saldo nao disponivel para saque \n");
        }else{
            saldo -= valor;
        }
    }
}

class Poupanca extends Conta{

}

public class Ex4 {

}

