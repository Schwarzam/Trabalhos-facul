public class Main {
    public static void main(String[] args) {

        //1
        Carro golzinho = new Carro("Volkswagem", "Gol", "AAA-1111", 2015);
        Pessoa eu = new Pessoa("João", 25);
        eu.compraCarro(golzinho);
        System.out.println("Meu nome:" + eu.nome);
        System.out.println("Modelo do meu carro:" + eu.carro.modelo);
        System.out.println("Placa do meu carro:" + eu.carro.placa);


        //2
        Produto cafe = new Produto("Café solúvel", 5.50, 1);
        Produto arroz = new Produto("Arroz integral", 4.90, 2);
        Produto feijao = new Produto("Feijão preto", 2.80, 2);
        Pedido meuPedido = new Pedido();
        meuPedido.adicionarProduto(cafe);
        meuPedido.adicionarProduto(arroz);
        meuPedido.adicionarProduto(feijao);
        System.out.printf("Total: %.2f \n", meuPedido.calcularValorTotal());

        //3
        Pneu p1 = new Pneu(32);
        Pneu p2 = new Pneu(32);
        Pneu p3 = new Pneu(36);
        Pneu p4 = new Pneu(36);

        Carro2 meucarro = new Carro2(p1, p2, p3, p4);

        meucarro.ligar();
        meucarro.pneu3.furar();
        meucarro.verificar_pneu();
        meucarro.desligar();
        meucarro.verificar_pneu();


        //4
        Paciente paciente = new Paciente("Marcelo Silva", "033444555-22", 26);
        Medico medico = new Medico("Ana Beatriz", 333431, "Clinico Geral");
        Exame exame01 = new Exame(medico, paciente, "COVID-19", "Negativo");
        exame01.imprimirExame();





    }
}

