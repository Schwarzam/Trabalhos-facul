
main(){
  int valor;
  float parcela, contador;

  printf("Digite um valor: ");
  scanf("%d", &valor);

  if (valor<=1000){
    printf("Valor da compra: %d", valor);
  }
  else if (valor>1000 && valor<=3000){
    printf("Pagar a vista: %d", valor);
    parcela = (valor/2) + (valor/2)*0.05;
    contador = (parcela*2);
    printf("\n Pagar parcelado em 2x de: %f, totalizando: %f", parcela, contador);

  }
  else if (valor>3000 && valor<=5000){
    printf("Pagar a vista: %d", valor);
    parcela = (valor/3) + (valor/3)*0.07;
    contador = (parcela*3);
    printf("\n Pagar parcelado em 3x de: %f, totalizando: %f", parcela, contador);
}
}
