#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define RESET   "\x1b[0m"

void exibir00InstrucoesQ2(){
    printf(YELLOW "\n ALUNA: YASMIN SOUSA ABDON - MATRÍCULA 232014271 \n" RESET);
    printf(MAGENTA "\n************************ CHAVES PERIÓDICAS ************************\n" RESET);
    printf("\nObjetivo: Encontrar o primeiro ano (entre 1 e 50) em que todas as N chaves, com ciclos C1 a CN, ativam-se simultaneamente.\n");
}

long long mdc_com_passos(long long a, long long b) {
    printf( "    Calculando MDC(%lld, %lld):\n" , a, b);
    long long a_orig = a;
    long long b_orig = b;
    
    // Guarda o 'a' original para o caso de b ser 0
    long long mdc_final = a; 

    if (b == 0) {
         printf("      b=0. O MDC é 'a'.\n");
    }

    while (b != 0) {
        long long resto = a % b;
        printf("      a = %-5lld b = %-5lld resto = %lld\n", a, b, resto);
        a = b;
        b = resto;
        if (b != 0) {
             mdc_final = b; // O último resto não-nulo
        }
    }
    printf( "    MDC(%lld, %lld) = %lld\n" RESET, a_orig, b_orig, mdc_final);
    return mdc_final;
}

long long mmc(long long a, long long b) {
    if (a == 0 || b == 0) return 0;

    // 1. Calcula o MDC (e imprime seus passos)
    long long mdc_resultado = mdc_com_passos(a, b);
    
    if (mdc_resultado == 0) return 0; // Evita divisão por zero

    // 2. Calcula o MMC
    // Usamos (a / mdc) * b para evitar overflow, que é mais seguro que (a * b) / mdc
    long long mmc_resultado = (a / mdc_resultado) * b;

    // 3. Imprime o cálculo do MMC
    printf("\n    Calculando MMC: (a / MDC(a,b)) * b\n");
    printf( "    (%lld / %lld) * %lld = %lld\n" RESET, a, mdc_resultado, b, mmc_resultado);
    
    return mmc_resultado;
}

int main(){

    exibir00InstrucoesQ2();
    int N; 
    long long C[20];

    printf("Digite um número N, sabendo que ele deve estar entre 1 e 10:\n");
    scanf("%d", &N);
    if(N < 1 || N > 10){
        printf(RED "Erro! N precisa está entre 1 e 10!\n" RESET);
        return 1;
    }

    printf("Digite os ciclos que pertencem a sua lista sabendo que eles devem estar entre 2 e 20\n");
    for(int i = 0; i < N; i++){
        printf(GREEN "Ciclo C[%d]: " RESET, i+1);
        scanf("%lld", &C[i]);
        if(C[i] < 2 || C[i] > 20){
            printf(RED "Erro! %lld é um número fora do parâmetro autorizado!" RESET, C[i]);
            return 1;
        }
    }
    
    printf(MAGENTA "\n********** Calculando o MMC de todos os ciclos **********\n" RESET);

    long long mmc_final = C[0];
    printf("MMC inicial = %lld\n", mmc_final);

    for(int i = 1; i < N; i++){
        long long mmc_anterior = mmc_final;
        mmc_final = mmc(mmc_final, C[i]);

        printf("Passo %d: MMC(%lld, %lld) = %lld\n\n", i, mmc_anterior, C[i], mmc_final);

        if(mmc_final > 50){
            printf(YELLOW "O MMC parcial (%lld) já ultrapassou o limite de 50 anos.\n" RESET, mmc_final);
            break;
        }
    }

   printf(MAGENTA"\n************************ RESULTADO ************************\n"RESET);
   if(mmc_final > 50){
    printf(RED "FALHA! Não há sincronização de chaves no período de 1 a 50 anos.\n"RESET);
    printf(RED "O primeiro ano de sincronização seria %lld, que está fora do limite estabelecido.\n" RESET, mmc_final);
   }
   else{
    printf(GREEN"YAY! O primeiro ano em que todas as chaves estão sincronizadas é: %lld < 50\n"RESET, mmc_final);
   }

    return 0;
}