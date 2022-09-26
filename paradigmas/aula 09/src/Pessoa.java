public class Pessoa{
    public Pessoa(String nome){
        this.nome = nome;
    }

    private String nome;

    public void escreverNome() {
        System.out.printf(nome + "\n");
    }

    public void escreverNome(String titulo) {
        System.out.printf(titulo + " " + nome + "\n");
    }

    public void escreverNome(int vezes) {
        for (int i = 0; i < vezes; i++){
            System.out.printf(nome + " ");
        }
        System.out.printf("\n");
    }

    public static void main(String args[]){
        Pessoa p1 = new Pessoa("João da Silva");
        Pessoa p2 = new Pessoa("Maria Andrade");
        Pessoa p3 = new Pessoa("Alan Bida");

        p1.escreverNome(); // João da Silva
        p2.escreverNome("Senhorita"); // Senhorita Maria Andrade
        p3.escreverNome(3); // Alan Bida Alan Bida Alan Bida
    }

}
