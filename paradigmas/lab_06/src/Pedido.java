import java.util.ArrayList;
import java.util.concurrent.atomic.AtomicReference;

public class Pedido {

    ArrayList<Produto> produtos = new ArrayList<Produto>();

    public void adicionarProduto(Produto produto){
        produtos.add(produto);
    }

    public Double calcularValorTotal(){
        AtomicReference<Double> soma = new AtomicReference<>((double) 0);
        produtos.forEach(produto -> {
            soma.set(soma.get() + produto.preco);
        });
        return soma.get();
    }
}
