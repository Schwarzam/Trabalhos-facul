import java.util.ArrayList;

abstract class Funcionario{
    String nome;
    String matricula;
    protected int salario_base = 1000;

    abstract int calcular_salario();
}

class Gerente extends Funcionario{

    @Override
    int calcular_salario() {
        return this.salario_base * 2;
    }
}

class Assistente extends Funcionario{

    @Override
    int calcular_salario() {
        return this.salario_base;
    }
}

class Vendedor extends Funcionario{

    @Override
    int calcular_salario() {
        return (int) (this.salario_base * 1.1);
    }
}

public class Ex3 {
    public Ex3(){

        ArrayList<Funcionario> lista = new ArrayList<Funcionario>();;

        lista.add(new Vendedor());
        lista.add(new Gerente());
        lista.add(new Assistente());

        lista.forEach(funcionario -> {
            System.out.printf("%d ", funcionario.calcular_salario());
        });
    }
    
}
