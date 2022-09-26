public class Main {
    public static void main(String[] args) {

        //1
        new Ex1();

        //2
        Pessoa p1 = new Pessoa("João da Silva");
        Pessoa p2 = new Pessoa("Maria Andrade");
        Pessoa p3 = new Pessoa("Alan Bida");
        p1.escreverNome(); // João da Silva
        p2.escreverNome("Senhorita"); // Senhorita Maria Andrade
        p3.escreverNome(3); // Alan Bida Alan Bida Alan Bida

        //3
        new Ex3();

        //4
        new Ex4();
    }
}

