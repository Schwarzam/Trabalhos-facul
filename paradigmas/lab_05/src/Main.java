public class Main {
    public static void main(String[] args) {

        System.out.println("Hello world!");

        //1
        Livro livro1 = new Livro("Harry Potter e a Pedra Filosofal", "J. K. Rowling", 264);
        Livro livro2 = new Livro("Poeira em alto mar", "Alan Bida", 133);

        //2
        Triangular t1 = new Triangular();
        System.out.println("O perimetro do triangulo eh: ");
        System.out.println(t1.calcularPerimetro());

        //3
        Tv tv = new Tv();
        tv.alterar_canal(6);
        tv.aumentar_volume();
        tv.aumentar_volume();
        tv.aumentar_volume();
        tv.diminuir_volume();
        System.out.printf("A tv está no canal %d\n", tv.canal); // A tv está no canal 6
        System.out.printf("A tv está no volume %d\n", tv.volume); // A tv está no volume 2

        //4
        Funcionario f1 = new Funcionario();
        f1.setSalario(1000);
        f1.aumentar_salario(30);

        //5
        Carro meu_carro = new Carro();
        meu_carro.adicionar_combustivel(20); // Adiciona 20 litros de combustível
        meu_carro.andar(80); // Andar 80 km
        System.out.printf("Litros de combustível no tanque: %f\n", meu_carro.obter_combustivel());

    }
}

