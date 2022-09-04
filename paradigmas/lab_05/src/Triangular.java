import java.util.Scanner;

public class Triangular {

    int lado_a;
    int lado_b;
    int lado_c;
    public Triangular(){
        Scanner input = new Scanner(System.in);

        System.out.println("lado_a: ");
        lado_a = input.nextInt();
        System.out.println("lado_b: ");
        lado_b = input.nextInt();
        System.out.println("lado_c: ");
        lado_c = input.nextInt();
    }


    public int calcularPerimetro(){
        return this.lado_a + this.lado_b + this.lado_c;
    }

}
