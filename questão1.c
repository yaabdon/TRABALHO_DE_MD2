/*  
    Aluna: Yasmin Sousa Abdon
    Matrícula: 232014271
*/
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

/* Instruções da Questão 1 */
void exibir00InstrucoesQ1(){
    printf(YELLOW "\n ALUNA: YASMIN SOUSA ABDON - MATRÍCULA 232014271 \n" RESET);
    printf(MAGENTA "************************ ETAPA 1: FATORAÇÃO INTERATIVA (Método p de Pollard) ************************\n" RESET);
    printf("Digite dois números compostos distintos e não primos: N1 e N2 que estejam entre 100 e 9999\n");
}

/* Verifica se é primo */
bool eh00primo(int N){
    if(N < 2) return false;
    for(int i = 2; i <= sqrt(N); i++){
        if(N % i == 0) return false;
    }
    return true;
}

/* Solicita número composto */
int Numero00Composto(const char* c){
    int num;
    int entrada;

    while(true){
        printf("%s", c);
        entrada = scanf("%d", &num);
        while(getchar() != '\n');

        if(entrada != 1){
            printf(RED "Erro! Digite um número inteiro.\n" RESET);
            continue;
        }
        if(num < 100 || num > 9999){
            printf(RED "Erro! Digite um número entre 100 e 9999.\n" RESET);
            continue;
        }
        if(eh00primo(num)){
            printf(RED "Erro! Insira um número composto e não primo (%d).\n" RESET, num);
            continue;
        }
        return num;
    }
}

/* Calcula (a*b) mod n */
long long modmul(long long a, long long b, long long mod) {
    long long res = 0;
    a = a % mod;
    while (b > 0) {
        if (b % 2 == 1) res = (res + a) % mod;
        a = (a * 2) % mod;
        b /= 2;
    }
    return res;
}


/* Função de iteração g(x) = (x^2 + 1) mod n
long long g(long long x, int n){
    return (mod(x, x, n) + 1) % n;
}*/

/* Algoritmo de Euclides */
long long mdc00euclides(long long a, long long b){
    long long resto;
    printf( "\nCalculando MDC(%lld, %lld)\n", a, b);
    while(b != 0){
        resto = a % b;
        printf("a = %lld, b = %lld, resto = %lld\n", a, b, resto);
        a = b;
        b = resto;
    }
    printf("MDC: %lld\n\n", a);
    return a;
}

/* Pollard Rho retorna um fator */
long long pollard00Rho(long long n) {
    long long x1 = 2, x2 = 2, d = 1;
    int i = 0;

    printf("\n************* Aplicando Pollard ρ para N = %lld *************\n", n);

    while(d == 1){
        i++;

        // x1
        long long x1_ant = x1;
        x1 = (modmul(x1_ant, x1_ant, n) + 1) % n;

        // x2 aplica g duas vezes
        long long x2_ant = x2;
        x2 = (modmul(x2_ant, x2_ant, n) + 1) % n;
        x2 = (modmul(x2, x2, n) + 1) % n;

        long long diff = llabs(x2 - x1);
        d = mdc00euclides(diff, n);

        printf("Iter %2d | x1 = %lld | x2 = %lld | |x2-x1| = %lld | MDC = %lld\n",
               i, x1, x2, diff, d);

        if(d == n){
            printf("Erro! Nenhum fator encontrado com esta semente.\n");
            return -1;
        }
    }

    printf("Yay! Fator trivial encontrado: %lld\n", d);
    return d;
}

//CALCULO DO ALGORITMO ESTENDINDO
long long euclides00Estendido(long long a, long long b, long long *x, long long *y){
    if(a == 0){
        *x = 0;
        *y = 1;
        printf("Chamada base: a = %lld, b = %lld -> x = %lld, y = %lld, mdc = %lld\n", a, b, *x, *y, b);
        return b;
    }
    long long x1, y1;
    long long mdc = euclides00Estendido(b % a, a, &x1, &y1);
    *x = y1 - (b / a) * x1;
    *y = x1;
    printf("Recursão: a = %lld, b = %lld, b%%a = %lld, x1 = %lld, y1 = %lld -> x = %lld, y = %lld, mdc = %lld\n",
           a, b, b % a, x1, y1, *x, *y, mdc);
    return mdc;
}

long long inverso00Modular(long long E, long long z){
    long long x, y;
    long long g = euclides00Estendido(E, z, &x, &y);
    if(g != 1) {
        printf("Não existe inverso modular!\n");
        return -1;
    } else {
        long long D = (x % z + z) % z;  // garante positivo
        return D;
    }
}

void Pre00Codificar(const char* mensagem, long long codificada[], long long* tamanho){
    int k = 0;
    for(int i = 0; mensagem[i] != '\0'; i++){
        char c = toupper(mensagem[i]); 
            if(c >='A' && c <= 'Z'){
                codificada[k++] = (c - 'A') + 11;  
            }
            else if(c == ' '){
                codificada[k++] = 0;
            }
            if(k >= 100) break;
    }

     *tamanho = k;
}

/* * CORREÇÃO DA EXPONENCIAÇÃO MODULAR
 * 1. Corrige a multiplicação dupla no if(impar)
 * 2. Corrige a redução de expoente incorreta (E % n)
 * 3. Usa modmul() para evitar overflow em (base*base) e (result*base)
 */
long long exponenciacao00Modular(long long M, long long E, long long n, long long z) {
    printf("--------------------------------------------------\n");
    printf("Calculando %lld^%lld (mod %lld)\n", M, E, n);
    printf("--------------------------------------------------\n");

    long long expoente_reduzido = E;
    long long base = M % n;

    // 1. Tenta aplicar o Pequeno Teorema de Fermat
    if (eh00primo(n)) {
        printf("--> Condição verificada: n (%lld) é primo.\n", n);
        printf("--> Aplicando Pequeno Teorema de Fermat.\n");
        expoente_reduzido = E % (n - 1);
        // Se E for múltiplo de (n-1), o expoente_reduzido vira 0. O loop tratará x^0 = 1.
        printf("    Cálculo: %lld^%lld ≡ %lld^(%lld mod %lld) ≡ %lld^%lld (mod %lld)\n",
               M, E, M, E, n - 1, M, expoente_reduzido, n);
    }
    // 2. Se não, tenta aplicar o Teorema de Euler
    // (Usamos mdc00euclides, mesmo que ele imprima o passo-a-passo)
    else if (mdc00euclides(base, n) == 1) {
        printf("--> Condição verificada: n (%lld) não é primo, mas mdc(%lld, %lld) = 1.\n", n, base, n);
        printf("--> Aplicando Teorema de Euler.\n");
        // 'z' (phi(n)) foi calculado no main e passado como parâmetro
        expoente_reduzido = E % z; 
        printf("    Cálculo: φ(n) = %lld (fornecido)\n", z);
        printf("    %lld^%lld ≡ %lld^(%lld mod %lld) ≡ %lld^%lld (mod %lld)\n",
               M, E, M, E, z, M, expoente_reduzido, n);
    }
    // 3. Caso contrário, não é possível reduzir o expoente
    else {
        printf("--> Condição verificada: n (%lld) não é primo e mdc(%lld, %lld) != 1.\n", n, base, n);
        printf("--> Não é possível aplicar Fermat ou Euler. Usando exponenciação binária direta.\n");
        // O expoente não é alterado (expoente_reduzido = E)
        expoente_reduzido = E;
    }

    // --- Algoritmo de Exponenciação Modular (Binária) ---
    printf("\n--- Início do cálculo de %lld^%lld (mod %lld) ---\n", base, expoente_reduzido, n);
    long long resultado = 1;

    // Caso o expoente seja 0 (após redução), o resultado é 1
    if (expoente_reduzido == 0) {
        resultado = 1;
    }

    while (expoente_reduzido > 0) {
        // Se o expoente é ímpar, multiplica o resultado pela base atual
        if (expoente_reduzido % 2 == 1) {
            printf("    Expoente (%lld) é ímpar: resultado = (%lld * %lld) mod %lld", expoente_reduzido, resultado, base, n);
            // CORREÇÃO: Usar modmul e fazer a operação SÓ UMA VEZ
            resultado = modmul(resultado, base, n); 
            printf(" = %lld\n", resultado);
        } else {
            printf("    Expoente (%lld) é par: resultado permanece = %lld\n", expoente_reduzido, resultado);
        }

        // Divide o expoente por 2
        expoente_reduzido /= 2;

        if (expoente_reduzido > 0) {
             printf("    Eleva base ao quadrado: base = (%lld * %lld) mod %lld", base, base, n);
             // CORREÇÃO: Usar modmul para evitar overflow
             base = modmul(base, base, n);
             printf(" = %lld\n", base);
             printf("    Divide expoente por 2: novo expoente = %lld\n\n", expoente_reduzido);
        }
    }

    printf("--- Fim do cálculo ---\n");
    printf("Resultado final: %lld\n\n", resultado);
    return resultado;
}

//transforma numero em letra
char numeroParaLetra(int num){
    if(num == 0) return ' ';
    else return 'A' + (num - 11);
}

//transforma de volta letra em número
int letraParaNumero(char c){
    if(c == ' ') return 0;
    return (c - 'A' + 11);
}

int main(){

    /*
    
    ETAPA 1 DO CÓDIGO
    
    */


    //instruções sobre o código + cabeçalho
    exibir00InstrucoesQ1();

    //leitura 
    int N1 = Numero00Composto("Digite o valor de N1: ");
    int N2;

    while(true){
        N2 = Numero00Composto("Digite o valor de N2: ");
        if(N2 != N1) break;
        else printf(RED"Erro! N2 precisa ser diferente de N1!\n" RESET);
    }
    printf("\nNúmeros validados:\nN1 = %d\nN2 = %d\n", N1, N2);
    printf(MAGENTA "\n************* Executando Pollard Rho e fatoração completa *************\n" RESET);
    

    //Calculo de Pollard p
    long long p = pollard00Rho(N1);
    long long q = pollard00Rho(N2);

    //mensagem de erro
     if (p == -1 || q == -1) {
        printf(RED "Erro: não foi possível fatorar N1 ou N2. Abortar geração de chaves.\n" RESET);
        return 1;
    }
    printf(BLUE "\n************* Definição dos primos RSA *************\n"RESET);
    printf("p (fator de N1 = %d) = %lld\n", N1, p);
    printf("q (fator de N2 = %d) = %lld\n", N2, q);
  
    //verificação se p e q são válidos para RSA
    if(p != -1) printf("N1 = %lld x %lld\n", p, N1/p);
    if(q != -1) printf("N2 = %lld x %lld\n", q, N2/q);

    if (!eh00primo(p)) {
        printf(RED "Erro: O fator p = %lld encontrado em N1 NÃO é primo!\n" RESET, p);
        printf(RED "Por favor, escolha outro N1.\n" RESET);
        return 1;
    }
    if (!eh00primo(q)) {
        printf(RED "Erro: O fator q = %lld encontrado em N2 NÃO é primo!\n" RESET, q);
        printf(RED "No seu último teste, q foi %lld. Tente outro N2.\n" RESET, q);
        return 1;
    }





    /*
    
    2 ETAPA DO CÓDIGO 
    
    */




   printf(MAGENTA "\n************************ ETAPA 2: GERAÇÃO DAS CHAVES RSA ************************\n" RESET);
   
    long long n = p * q;
    long long z = (p - 1) * (q - 1);

    //calculando o modulo n
    printf(BLUE "\n************* Calculando o Modulo n *************\n" RESET);
    printf("Modulo n = p * q = %lld * %lld = %lld\n", p, q, n);

    //calculando o totiente de euler
    printf(BLUE "\n************* Calculando o Totiente de Euler z *************\n" RESET);
    printf("Totiente de Euler z(n) = (p-1)*(q-1) = (%lld-1)*(%lld-1) = %lld\n", p, q, z); 


    //CÁLCULO DO EXPOENTE PÚBLICO
    printf(BLUE "\n************* Calculando o expoente público E *************\n" RESET);
    long long e = 2;
    long long achou = false;
    while(e < z){ 
        printf("Testando e = %lld: \n", e);
        long long g = mdc00euclides(e, z);
        if(g==1){
            achou = true;
            break;
        }
        else {
            printf(RED "mdc(%lld, %lld) = %lld -> Não serve\n" RESET, e, z, g);
            e++;
        }
    }
    if(!achou){
        printf(RED "Erro: não foi possível encontrar E tal que mdc(E, z) = 1\n" RESET);
        return 1;
    }
    printf("Expoente público (E) calculado = %lld\n\n", e);


    //CÁLCULO DO EXPOENTE PRIVADO
    printf(BLUE "************* Calculando o expoente privado D *************\n" RESET);
    long long x, y;
    long long g = euclides00Estendido(e, z, &x, &y);
    if(g != 1){
        printf(RED "Erro: mdc(e,z) != 1 (== %lld). Inverso modular não existe.\n" RESET, g);
        return 1;
    }
    long long d = (x % z + z) % z; // garante que d seja positivo
    printf("\nExpoente privado (D) calculado = %lld\n\n", d);


    //chave pública
    printf(GREEN "Chave pública:  (n = %lld, e = %lld)\n" RESET, n, e);
    //chave privada
    printf(GREEN "Chave privada:  (n = %lld, d = %lld)\n" RESET, n, d);


    
    

    /*
    
    3 ETAPA DO CÓDIGO 
    
    */



    printf(MAGENTA "\n************************ ETAPA 3: CODIFICAÇÃO (CRIPTOGRADIA) E DECODIFICAÇÃO (DESCRIPTOGRAFIA) ************************\n\n" RESET);
    printf("Digite uma mensagem para ser PRÉ-CODIFICADA de até 100 caracteres, por favor: ");
    
    char mensagem[101];
    long long codificada[100];
    long long codificadaRSA[100];
    char mensagemDecodificada[100];
    long long tamanho;

    //leitura da mensagem de até 100 caracteres
    fgets(mensagem, sizeof(mensagem), stdin);
    mensagem[strcspn(mensagem, "\n")] = 0;

    //pre-codificando 
    Pre00Codificar(mensagem, codificada, &tamanho);

    //impressão da mensagem pré-codificada
    printf(BLUE"\nMensagem pré-codificada:\n"RESET);
    for(int i = 0; i < tamanho; i++){
        printf("Bloco %02d: M = %02lld \n", i+1, codificada[i]);
    }
    printf("\n");


    //codificação RSA
    printf(BLUE"\n************** CODIFICAÇÃO **************\n"RESET);
    for(int i = 0; i < tamanho; i++){
        codificadaRSA[i] = exponenciacao00Modular(codificada[i], e, n, z);
        printf("Bloco %02d: C = %lld\n\n", i+1, codificadaRSA[i]);
        
    }
    printf("\n");


    //decodificação RSA
    printf(BLUE "\n************** DECODIFICAÇÃO **************\n" RESET);
        
        for(int i = 0; i < tamanho; i++){
            long long M = exponenciacao00Modular(codificadaRSA[i], d, n, z);
                if(M == 0) mensagemDecodificada[i] = ' ';
                else mensagemDecodificada[i] = numeroParaLetra(M);
                printf("Bloco: %02d reconvertido: '%c'\n\n", i+1, mensagemDecodificada[i]);

        }
        
    mensagemDecodificada[tamanho] = '\0';
    printf(GREEN "Mensagem final decodificada: %s\n" RESET, mensagemDecodificada);




    
    

    /*
    
    ETAPA EXTRA (4 ETAPA DO CÓDIGO) -> VERIFICAR A MENSAGEM DECODIFICADA = MENSAGEM PRE-CODIFICADA DIGITADA PELO USUÁRIO
    
    */



    printf(MAGENTA "\n************************ ETAPA 4: VERIFICAÇÃO DA STRING ************************\n\n" RESET);
    char mensagemOriginalLimpada[101];
    int k = 0;
    for(int i = 0; mensagem[i] != '\0'; i++){
        char c = toupper(mensagem[i]);
        if((c >= 'A' && c <= 'Z') || c == ' '){
            mensagemOriginalLimpada[k++] = c;
        }
    }
    mensagemOriginalLimpada[k] = '\0';

    if (strcmp(mensagemOriginalLimpada, mensagemDecodificada) == 0) {
        printf(GREEN "SUCESSO! A mensagem decodificada é idêntica à original.\n" RESET);
        printf("Original (processada): %s\n", mensagemOriginalLimpada);
        printf("Decodificada:          %s\n", mensagemDecodificada);
    } else {
        printf(RED "FALHA! A mensagem decodificada NÃO é idêntica à original.\n" RESET);
        printf(RED "Original (processada): %s\n" RESET, mensagemOriginalLimpada);
        printf(RED "Decodificada:          %s\n" RESET, mensagemDecodificada);
    }
    return 0;
}
