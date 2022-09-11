import java.util.ArrayList;

public class Carro2 {

    public Carro2(Pneu pneu1, Pneu pneu2, Pneu pneu3, Pneu pneu4){
        this.pneu1 = pneu1;
        this.pneu2 = pneu2;
        this.pneu3 = pneu3;
        this.pneu4 = pneu4;
    }

    boolean ligado;
    Pneu pneu1;
    Pneu pneu2;
    Pneu pneu3;
    Pneu pneu4;

    public void ligar(){
        ligado = true;
    }
    public void desligar(){
        ligado = false;
    }
    public void verificar_pneu(){
        if (ligado){
            System.out.printf("pneu 1: %d\n", pneu1.pressao);
            System.out.printf("pneu 2: %d\n", pneu2.pressao);
            System.out.printf("pneu 3: %d\n", pneu3.pressao);
            System.out.printf("pneu 4: %d\n", pneu4.pressao);
        } else {
            System.out.printf("Carro desligado. \n");
        }
    }



}
