public class Pessoa {

    public Pessoa (String nome, int idade){
        this.nome = nome;
        this.idade = idade;
    }
    String nome;
    int idade;
    Carro carro;

    public void compraCarro(Carro carro){
        this.carro = carro;
    }
}
