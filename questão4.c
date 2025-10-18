#include <stdio.h>

#ifdef _WIN32
#include <windows.h>
#endif

//função para calcular o máximo divisor comum (MDC) com exibição dos passos
int mdcComPassos(int a, int b){
    int resto;
    while(b != 0){ //b = [1]
        resto = a % b;
        printf("Algoritmo de Euclides: %d mod %d = %d\n", a, b, resto);
        a = b;
        b = resto; //resto = [2] 
    }
    return a;
}
int inversoModular(int a, int m){
    int m0 = m, t, q;
    int x0 = 0, x1 = 1;
    int A = a, B = m;

    mdcComPassos(a, m); // mdcComPassos = [3]

    while(m != 0){
        q = a / m;
        t = m;
        m = a % m;
        a = t;

        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }
    if(x1 < 0)
        x1 += m0; //x1 = [4]
    printf("\nSubstituindo, temos que o inverso de %d em %d é %d.\n\n", A, B, x1);
    return x1;
}

int powMod(int base, int exp, int mod){
    long long res = 1;
    long long b = base % mod;
    while(exp > 0){
        if(exp % 2 == 1) //exp % 2 == 1 = [5]
            res = (res * b) % mod;
        b = (b * b) % mod;
        exp >>= 1;
    }
    return (int)res;
}

int main(){
#ifdef _WIN32
    setConsoleOutputCP(CP_UTF8);
#endif 

    printf("ALUNA: Yasmin Sousa Abdon, MATRÍCULA: 232014271\n");
    printf("Questão 4 -> resposta da 1 no código abaixo e resposta da 2 no README\n");
    int H, G, Zn, x, n1;
    printf("Insira H: ");
    scanf("%d", &H);
    printf("Insira G: ");
    scanf("%d", &G);
    printf("Insira Zn: ");
    scanf("%d", &Zn);
    printf("Insira x: ");
    scanf("%d", &x);
    printf("Insira n1: ");
    scanf("%d", &n1);
    printf("\n");

    int inverso = inversoModular(G, Zn); //inversoModular = [6]
    int a = (H * inverso) % Zn;

    printf("Fazendo a multiplicação modular: %d * %d mod %d = %d\n", H, inverso, Zn, a);
    printf(" Sendo %d o inverso de %d.\n", inverso, G);

    int resultado = powMod(a, x, n1); //powMod = [7]
    printf("Valor final de congruência: %d\n", resultado);

/*

INÍCIO DA SAÍDA DO CONSOLE:

ALUNA: Yasmin Sousa Abdon, MATRÍCULA: 232014271
Questão 4 -> resposta da 1 no código abaixo e resposta da 2 no README
Insira H: 7
Insira G: 3
Insira Zn: 11
Insira x: 10
Insira n1: 13

Algoritmo de Euclides: 3 mod 11 = 3
Algoritmo de Euclides: 11 mod 3 = 2
Algoritmo de Euclides: 3 mod 2 = 1
Algoritmo de Euclides: 2 mod 1 = 0

Substituindo, temos que o inverso de 3 em 11 é 4.

Fazendo a multiplicação modular: 7 * 4 mod 11 = 6
 Sendo 4 o inverso de 3.
Valor final de congruência: 4

FIM DA SAÍDA DO CONSOLE

*/

    return 0;

}