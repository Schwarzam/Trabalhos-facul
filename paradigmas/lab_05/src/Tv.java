public class Tv {

    int canal = -1;
    int volume = 0;

    public void aumentar_volume(){
        volume ++;
    }

    public void diminuir_volume(){
        volume --;
    }

    public void alterar_canal(int canal){
        this.canal = canal;
    }
}
