public class Funcionario {

    String nome;
    int salario;

    public void aumentar_salario(int percentual){
        salario *= 1 + (percentual / 100);
        System.out.printf("O novo salario eh de: %d\n", salario);
    }

    public void setSalario(int salario){
        this.salario = salario;
    }
}
