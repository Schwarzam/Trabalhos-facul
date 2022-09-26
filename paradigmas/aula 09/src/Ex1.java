abstract class Operacao {
    public abstract int calcular(int x, int y);
}

class Soma extends Operacao{

    @Override
    public int calcular(int x, int y) {
        return x + y;
    }
}

class Subtracao extends Operacao{

    @Override
    public int calcular(int x, int y) {
        return x - y;
    }
}
class Divisao extends Operacao{

    @Override
    public int calcular(int x, int y) {
        return x / y;
    }
}

class Multiplicacao extends Operacao{
    @Override
    public int calcular(int x, int y) {
        return x * y;
    }
}

public class Ex1 {
    public Ex1(){
        Soma soma = new Soma();
        Subtracao sub = new Subtracao();
        Divisao div = new Divisao();
        Multiplicacao mult = new Multiplicacao();
        System.out.printf("Soma: %d\n", soma.calcular(10, 5)); // 15
        System.out.printf("Subtração: %d\n", sub.calcular(10, 5)); // 5
        System.out.printf("Divisão: %d\n", div.calcular(10, 5)); // 2
        System.out.printf("Multiplicação: %d\n", mult.calcular(10, 5)); // 50
    }
}
