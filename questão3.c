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

void exibir00InstrucoesQ3(){
    printf(YELLOW "\n ALUNA: YASMIN SOUSA ABDON - MATRÍCULA 232014271 \n" RESET);
    printf(MAGENTA "\n************************ A Razão de Eficiência de um Número ************************\n" RESET);
    printf("\nObjetivo: Este programa calcula a Razão de Eficiência (σ(N) / τ(N)) com duas casas decimais.\n");
}

//Função auxiliar para calcular potências de inteiros.
long long power_int(int base, int exp){
    long long res = 1;
    for(int i = 0; i < exp; i++){
        res *= base;
    }
    return res;
}

//Decompõe N em fatores primos (Trial Division) e preenche os arrays de saída.
void Fatoration_Trial_Division(int N, int* fatores_primos_out, int* expoentes_out, int* num_fatores_out) {
    *num_fatores_out = 0; // Zera a contagem de fatores
    int N_atual = N;

    printf(BLUE "\nPASSO 1. Decomposição de N = %d (Trial Division)...\n" RESET, N);

    if(N_atual == 1){
        printf("N = 1 não tem fatores primos! Sem decomposição de N!\n");
    }


    //testando o único primo par -> 2
    int expoente = 0;
    while (N_atual % 2 == 0) {
        expoente++;
        N_atual /= 2;
    }
    if (expoente > 0) {
        printf(GREEN "   Resultado: Fator primo 2, Expoente %d\n" RESET, expoente);
        fatores_primos_out[*num_fatores_out] = 2;
        expoentes_out[*num_fatores_out] = expoente;
        (*num_fatores_out)++;
    }

    //testando divisores ímpares -> começando com o 3 (óbvio)
    for (int divisor = 3; divisor * divisor <= N_atual; divisor = divisor + 2) {
        expoente = 0;
        while (N_atual % divisor == 0) {
            expoente++;
            N_atual /= divisor;
        }
        if (expoente > 0) {
            printf(GREEN "   Resultado: Fator primo %d, Expoente %d\n" RESET, divisor, expoente);
            fatores_primos_out[*num_fatores_out] = divisor;
            expoentes_out[*num_fatores_out] = expoente;
            (*num_fatores_out)++;
        }
    }

    //verifica o N restante
    if (N_atual > 1) {
        printf(GREEN "   Resultado: O N restante (%d) é o último fator primo, com expoente 1.\n" RESET, N_atual);
        fatores_primos_out[*num_fatores_out] = N_atual;
        expoentes_out[*num_fatores_out] = 1;
        (*num_fatores_out)++;
    }
    // A verificação se N era primo é desnecessária aqui,
    // pois se ele for primo, o Passo 3 irá capturá-lo.
}

//Calcula tau(N), o número total de divisores de N.
long long calcular_tau(int N_original, int* fatores_primos, int* expoentes, int num_fatores){
    printf(BLUE "\nPASSO 2. Cálculo de τ(N) (Número de Divisores)...\n" RESET);
    printf("Fórmula: τ(N) = (e1 + 1) * (e2 + 1) * ... * (ek + 1)\n");

    long long tau = 1;
    char calculo[256] = "τ(N) = "; 

    for (int i = 0; i < num_fatores; i++) {
        int e = expoentes[i];
        int p = fatores_primos[i];
        
        printf("   Termo para p=%d (e=%d): (%d + 1) = %d\n", p, e, e, e + 1);
        tau = tau * (e + 1);
        
        char termo[20];
        sprintf(termo, "(%d + 1)", e);
        strcat(calculo, termo);
        if (i < num_fatores - 1) {
            strcat(calculo, " * ");
        }
    }

    printf("Cálculo: %s = %lld\n", calculo, tau);
    printf(GREEN "Resultado: τ(%d) = %lld\n" RESET, N_original, tau);
    return tau;
}

// Calcula sigma(N), a soma de todos os divisores de N.
long long calcular_sigma(int N_original, int* fatores_primos, int* expoentes, int num_fatores){
    printf(BLUE "\nPASSO 3. Cálculo de σ(N) (Soma dos Divisores)...\n" RESET);
    printf("Fórmula: σ(N) = [ (p1^(e1+1) - 1) / (p1 - 1) ] * [ ... ]\n");
    
    long long sigma = 1;
    char calculo[256] = "σ(N) = ";

    for (int i = 0; i < num_fatores; i++) {
        int p = fatores_primos[i];
        int e = expoentes[i];
        
        long long p_exp = power_int(p, e + 1);
        long long termo = (p_exp - 1) / (p - 1);

        printf("   Termo para p=%d (e=%d): [ (%lld - 1) / %d ] = %lld\n", p, e, p_exp, p - 1, termo);
        
        sigma = sigma * termo;

        char str_termo[20];
        sprintf(str_termo, "[%lld]", termo);
        strcat(calculo, str_termo);
         if (i < num_fatores - 1) {
            strcat(calculo, " * ");
        }
    }

    printf("Cálculo: %s = %lld\n", calculo, sigma);
    printf(GREEN "Resultado: σ(%d) = %lld\n" RESET, N_original, sigma);
    return sigma;
}

int main(){

    exibir00InstrucoesQ3();

    int N;
    printf("Digite um único inteiro N (entre 1 e 105):\n");
    scanf("%d", &N);
    if(N < 1 || N > 105){
        printf(RED "ERRO! N está fora dos limites estabelecidos!\n" RESET);
        return 1;
    }

    int fatores_primos[50];
    int expoentes[50];
    int num_fatores = 0;

    //calculando a fatoração
    Fatoration_Trial_Division(N, fatores_primos, expoentes, &num_fatores);

    //calculando tau e sigma
    long long tau_N = calcular_tau(N, fatores_primos, expoentes, num_fatores);
    long long sigma_N = calcular_sigma(N, fatores_primos, expoentes, num_fatores);

    //calculando a razão de eficiência
    printf(BLUE "\nPASSO 4. Cálculo da Razão de Eficiência... \n" RESET);
    printf("Definição: = σ(N) / τ(N)\n");

    // Convertemos para double para garantir a divisão com casas decimais
    double razao = 0.0;
    if(tau_N > 0){
        razao = (double)sigma_N / (double)tau_N;
    }

    printf("Cálculo: %lld / %lld = %.2f\n", sigma_N, tau_N, razao);
    printf(GREEN "\nResultado Final: A Razão de Eficiência é %.2f\n" RESET, razao);

    return 0;
}