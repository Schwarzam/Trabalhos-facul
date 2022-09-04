public class Carro {
    float quantidade_combustivel;

    public void adicionar_combustivel(float litros){
        quantidade_combustivel += litros;
    }

    public float obter_combustivel(){
        return quantidade_combustivel;
    }

    public void andar(float distancia){
        quantidade_combustivel -= distancia * 0.2;
    }
}
