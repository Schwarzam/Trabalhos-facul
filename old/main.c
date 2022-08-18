//  N2
#include <stdio.h>
void func_ind(void);
int main (void){
    func_ind();
}
    
void func_ind(){
    float indice;
    int Sair = 1;
    indice = 0;
    while (Sair==1){
        printf("Insira o indice: ");
        scanf("%f", &indice);
        
        if(indice>=0.05 && indice<=0.25)
      {
          printf("indice aceitavel! \n");
        }
        else if(indice > 0.25 && indice <= 0.4)
      {
          printf("Suspender as atividades de industrias do primeiro grupo! \n");
        }
        else if(indice > 0.4 && indice <0.5)
      {
          printf("Suspender as atividades de industrias do primeiro e segundo grupo! \n");
        }
        else if(indice<=0.5)
      {
          printf("Suspender as atividades de industrias de todos os grupos! \n");
        }
        printf("Para continuar digite '1', para parar digite '0': ");
        scanf("%d", &Sair);
    }
}
