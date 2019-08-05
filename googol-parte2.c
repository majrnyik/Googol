/********************************************************************************************************
 *
 * ALUNAS: Beatriz de Castro Moreira Farkas (11201722860) e Rafaela Ferraz Martin (11201720724)
 *
 * SOBRE O PROGRAMA -> Basicamente trata-se de uma calculadora, com o diferencial de que essa consegue
 *                     aguentar números extremamente longos (como um googol, por exemplo). A explicação
 *                     cada função executada neste programa pode ser encontrada logo acima do código
 *                     respectivo de cada uma. As variáveis contém explicações logo que declaradas,
 *                     facilitando a correção.
 *
 * INFORMAÇÕES GERAIS -> O sinal de positivo/negativo neste programa é definido pela primeira casa de
 *                       cada string seguindo a seguinte regra:
 *                          ~ 0 - positivo
 *                          ~ 1 - negativo
 *
 ********************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#define MAX 1005 /* tamanho máximo que um numerão pode ter */

char *novo(int tam_num);
void preenche_numero(char *numero, int *tam, int *itsover);
void inverte_numero(char *numero, int tamanho);
void soma(char *numero1, char *numero2, int tam_num1, int tam_num2);
void subtracao(char *numero1, char *numero2, int tam_num1, int tam_num2);
int tamanho(char *numero);
void imprime(char *numero, int tam_num);
void verifica_maior(char *numero1, char *numero2, int tam_num1, int tam_num2, int *maior_tam, int *menor_tam, int *maior_n);
void completa_numero(char *numero1, char *numero2, int tam_num1, int tam_num2, int maior_n);
void multiplicacao(char *numero1, char *numero2, int tam_num1, int tam_num2);
void divisao(char *numero1, char *numero2, int tam_num1, int tam_num2);

int main()
{
    char *num1,       /* primeiro numerão */
        *num2,        /* segundo numerão*/
        *recebe;      /* operação desejada */
    int tamanho_num1, /* tamanho do primeiro numerão */
        tamanho_num2, /* tamanho do segundo numerão */
        its_over;     /* variável booleana para verificação de fim do programa */

    num1 = NULL;
    num2 = NULL;
    tamanho_num1 = 0;
    tamanho_num2 = 0;
    its_over = 0;
    recebe = NULL;
    recebe = novo(4);
    num1 = novo(MAX);
    num2 = novo(MAX);

    do
    {
        /* recebe e inverte o primeiro número */
        preenche_numero(num1, &tamanho_num1, &its_over);
        inverte_numero(num1, tamanho_num1);

        if (its_over)
            break;

        /* recebe e inverte o segundo número */
        preenche_numero(num2, &tamanho_num2, &its_over);
        inverte_numero(num2, tamanho_num2);

        /* define a operação a ser realizada (soma ou subtração) */
        scanf("%s", recebe);
        switch (*recebe)
        {
        case '+':
            soma(num1, num2, tamanho_num1, tamanho_num2);
            break;
        case '-':
            subtracao(num1, num2, tamanho_num1, tamanho_num2);
            break;
        case '*':
            multiplicacao(num1, num2, tamanho_num1, tamanho_num2);
            break;
        }
    } while (1);

    free(recebe);
    free(num1);
    free(num2);
    return 0;
}

/*
 * Recebe como parâmetro o tamanho de memória a ser alocada para uma string específica e retorna esta
 * mesma string.
 */
char *novo(int tam_num)
{
    char *v; /* vetor auxiliar */
    v = malloc(tam_num * sizeof(char));
    return v;
}

/*
 * Recebe como parâmetro uma string, (o endereço do) seu tamanho e (o endereço da) variável booleana
 * que definirá o fim ou não do programa. Preenche a string com o numerão digitado pelo usuário.
 * Devolve a string preenchida com a informação de ser ou não um número negativo, o tamanho dessa
 * string e o operador booleano.
 */
void preenche_numero(char *numero, int *tam, int *itsover)
{
    int i;   /* contador do for */
    char *v; /* vetor auxiliar */

    scanf("%s", numero);
    *itsover = (*numero == 'F') ? 1 : 0;
    *tam = tamanho(numero);
    v = malloc(((*tam) + 5) * sizeof(char));

    if (*numero == '-')
    {
        *numero = '1';
        (*tam)--;
    }
    else
    {
        *v = '0';
        for (i = 0; i <= (*tam); i++)
        {
            *(v + i + 1) = *(numero + i);
        }
        for (i = 0; i <= (*tam); i++)
        {
            *(numero + i) = *(v + i);
        }
        *(numero + i) = '\0';
    }
}

/*
 * Recebe como parâmetro uma string e seu tamanho. Inverte a string mantendo a informação de
 * positivo/negativo na primeira casa da string e o \0 em seus respectivos lugares.
 */
void inverte_numero(char *numero, int tamanho)
{
    int i;    /* contador do for */
    char aux; /* auxiliar para troca de posições */

    for (i = 1; i <= (tamanho / 2); i++)
    {
        aux = *(numero + i);
        *(numero + i) = *(numero + (tamanho - i + 1));
        *(numero + (tamanho - i + 1)) = aux;
    }
}

/*
 * Recebe como parâmetro os dois numerões (que plural estranho) e seus tamanhos. Verifica caso a
 * caso, LEVANDO EM CONTA OS SINAIS DE CADA NUMERÃO. Devolve a soma dos dois numerões.
 */
void soma(char *numero1, char *numero2, int tam_num1, int tam_num2)
{
    int i,         /* contador do for */
        carry,     /* referente ao "sobe um" da adição no papel */
        sum,       /* soma dos dois valores individuais */
        sub,       /* subtração dos dois valores individuais */
        valor1,    /* pega o char individual e transforma em int */
        valor2,    /* pega o char individual e transforma em int */
        resultado, /* considerando o carry */
        maior_tam, /* qual numerão é maior */
        menor_tam, /* qual numerão é menor */
        maior_n;   /* quem é o maior numerão, 1 ou 2? */
    carry = 0;

    verifica_maior(numero1, numero2, tam_num1, tam_num2, &maior_tam, &menor_tam, &maior_n);

    if (tam_num1 != tam_num2)
    {
        completa_numero(numero1, numero2, tam_num1, tam_num2, maior_n);
    }

    if (!(*numero1 - '0') && !(*numero2 - '0')) /* a+b */
    {
        for (i = 1; i <= maior_tam; i++)
        {
            valor1 = *(numero1 + i) - '0';
            valor2 = *(numero2 + i) - '0';
            sum = valor1 + valor2 + carry;
            carry = (sum >= 10) ? 1 : 0;
            resultado = (sum >= 10) ? sum - 10 : sum;
            *(numero1 + i) = resultado + '0';
        }
        if (carry == 1)
        {
            *(numero1 + i) = 1 + '0';
            *(numero1 + i + 1) = '\0';
            maior_tam++;
        }
        inverte_numero(numero1, maior_tam);
        imprime(numero1, maior_tam);
    }
    else if (!(*numero1 - '0') && (*numero2 - '0')) /* a-b */
    {
        for (i = 1; i <= maior_tam; i++)
        {
            valor1 = (maior_n == 1) ? *(numero1 + i) - '0' - carry : *(numero2 + i) - '0' - carry;
            valor2 = (maior_n == 1) ? *(numero2 + i) - '0' : *(numero1 + i) - '0';
            sub = valor1 - valor2;
            carry = (sub < 0) ? 1 : 0;
            resultado = (sub < 0) ? sub + 10 : sub;
            *(numero1 + i) = resultado + '0';
        }

        if (*(numero1 + i - 1) == '0')
        {
            *(numero1 + i - 1) = '\0';
            maior_tam--;
        }
        *numero1 = (maior_n == 1) ? '0' : '1';

        inverte_numero(numero1, maior_tam);
        imprime(numero1, maior_tam);
    }
    else if (*numero1 - '0' && !(*numero2 - '0')) /* -(a-b) */
    {
        for (i = 1; i <= maior_tam; i++)
        {
            valor1 = (maior_n == 1) ? *(numero1 + i) - '0' - carry : *(numero2 + i) - '0' - carry;
            valor2 = (maior_n == 1) ? *(numero2 + i) - '0' : *(numero1 + i) - '0';
            sub = valor1 - valor2;
            carry = (sub < 0) ? 1 : 0;
            resultado = (sub < 0) ? sub + 10 : sub;
            *(numero1 + i) = resultado + '0';
        }

        if (*(numero1 + i - 1) == '0')
        {
            *(numero1 + i - 1) = '\0';
            maior_tam--;
        }
        *numero1 = (maior_n == 1) ? '1' : '0';

        inverte_numero(numero1, maior_tam);
        imprime(numero1, maior_tam);
    }
    else /* -(a+b) */
    {
        for (i = 1; i <= maior_tam; i++)
        {
            valor1 = *(numero1 + i) - '0';
            valor2 = *(numero2 + i) - '0';
            sum = valor1 + valor2 + carry;
            carry = (sum >= 10) ? 1 : 0;
            resultado = (sum >= 10) ? sum - 10 : sum;
            *(numero1 + i) = resultado + '0';
        }
        if (carry == 1)
        {
            *(numero1 + i) = 1 + '0';
            *(numero1 + i + 1) = '\0';
            maior_tam++;
        }
        *numero1 = '1';
        inverte_numero(numero1, maior_tam);
        imprime(numero1, maior_tam);
    }
}

/*
 * Recebe como parâmetro os dois numerões e seus tamanhos. Verifica caso a caso, LEVANDO EM CONTA
 * OS SINAIS DE CADA NUMERÃO. Devolve a subtração dos dois numerões.
 */
void subtracao(char *numero1, char *numero2, int tam_num1, int tam_num2)
{
    int i,         /* contador do for */
        carry,     /* referente ao "sobe um" da adição no papel */
        sum,       /* soma dos dois valores individuais */
        sub,       /* subtração dos dois valores individuais */
        valor1,    /* pega o char individual e transforma em int */
        valor2,    /* pega o char individual e transforma em int */
        resultado, /* considerando o carry */
        maior_tam, /* qual numerão é maior */
        menor_tam, /* qual numerão é menor */
        maior_n;   /* quem é o maior numerão, 1 ou 2? */
    carry = 0;

    verifica_maior(numero1, numero2, tam_num1, tam_num2, &maior_tam, &menor_tam, &maior_n);

    if (tam_num1 != tam_num2)
    {
        completa_numero(numero1, numero2, tam_num1, tam_num2, maior_n);
    }

    if (!(*numero1 - '0') && !(*numero2 - '0')) /* a-b */
    {
        for (i = 1; i <= maior_tam; i++)
        {
            valor1 = (maior_n == 1) ? *(numero1 + i) - '0' - carry : *(numero2 + i) - '0' - carry;
            valor2 = (maior_n == 1) ? *(numero2 + i) - '0' : *(numero1 + i) - '0';
            sub = valor1 - valor2;
            carry = (sub < 0) ? 1 : 0;
            resultado = (sub < 0) ? sub + 10 : sub;
            *(numero1 + i) = resultado + '0';
        }

        if (*(numero1 + i - 1) == '0' && *(numero1 + i - 2) != '0')
        {
            *(numero1 + i - 1) = '\0';
            maior_tam--;
        }
        *numero1 = (maior_n == 1) ? '0' : '1';

        inverte_numero(numero1, maior_tam);
        imprime(numero1, maior_tam);
    }
    else if (!(*numero1 - '0') && *numero2 - '0') /* a+b */
    {
        for (i = 1; i <= maior_tam; i++)
        {
            valor1 = *(numero1 + i) - '0';
            valor2 = *(numero2 + i) - '0';
            sum = valor1 + valor2 + carry;
            carry = (sum >= 10) ? 1 : 0;
            resultado = (sum >= 10) ? sum - 10 : sum;
            *(numero1 + i) = resultado + '0';
        }
        if (carry == 1)
        {
            *(numero1 + i) = 1 + '0';
            *(numero1 + i + 1) = '\0';
            maior_tam++;
        }
        inverte_numero(numero1, maior_tam);
        imprime(numero1, maior_tam);
    }
    else if (*numero1 - '0' && !(*numero2 - '0')) /* -(a+b) */
    {
        for (i = 1; i <= maior_tam; i++)
        {
            valor1 = *(numero1 + i) - '0';
            valor2 = *(numero2 + i) - '0';
            sum = valor1 + valor2 + carry;
            carry = (sum >= 10) ? 1 : 0;
            resultado = (sum >= 10) ? sum - 10 : sum;
            *(numero1 + i) = resultado + '0';
        }
        if (carry == 1)
        {
            *(numero1 + i) = 1 + '0';
            *(numero1 + i + 1) = '\0';
            maior_tam++;
        }
        *numero1 = '1';
        inverte_numero(numero1, maior_tam);
        imprime(numero1, maior_tam);
    }
    else /* -(a-b) */
    {
        for (i = 1; i <= maior_tam; i++)
        {
            valor1 = (maior_n == 1) ? *(numero1 + i) - '0' - carry : *(numero2 + i) - '0' - carry;
            valor2 = (maior_n == 1) ? *(numero2 + i) - '0' : *(numero1 + i) - '0';
            sub = valor1 - valor2;
            carry = (sub < 0) ? 1 : 0;
            resultado = (sub < 0) ? sub + 10 : sub;
            *(numero1 + i) = resultado + '0';
        }

        if (*(numero1 + i - 1) == '0')
        {
            *(numero1 + i - 1) = '\0';
            maior_tam--;
        }
        *numero1 = (maior_n == 1) ? '1' : '0';

        inverte_numero(numero1, maior_tam);
        imprime(numero1, maior_tam);
    }
}

/*
 * Recebe como parâmetro uma string e devolve seu tamanho, sem contar o \0.
 */
int tamanho(char *numero)
{
    int i; /* contador do for */
    for (i = 0; *(numero + i) != '\0'; i++)
        ;
    return i;
}

/*
 * Recebe como parâmetro uma string e a imprime.
 */
void imprime(char *numero, int tam_num)
{
    int i;   /* contador do for */
    char *v; /* vetor auxiliar */

    if (*numero == '1')
    {
        if (*(numero + 1) == '0')
            printf("0\n");
        else
        {
            *numero = '-';
            printf("%s\n", numero);
        }
    }
    else
    {
        if (*(numero + 1) == '0')
        {
            printf("0\n");
        }
        else
        {
            v = malloc(tam_num * sizeof(char));
            for (i = 0; i < tam_num; i++)
            {
                *(v + i) = *(numero + i + 1);
            }
            for (i = 0; i < tam_num; i++)
            {
                *(numero + i) = *(v + i);
            }
            *(numero + i) = '\0';
            printf("%s\n", numero);
        }
    }
}

/*
 * Recebe como parâmetro os tamanhos dos numerões e os endereços de memória de três variáveis.
 * Devolve qual numerão tem o maior tamanho. Se eles possuem o mesmo tamanho, devolve que o
 * segundo numerão é o maior, só por convenção mesmo.
 */
void verifica_maior(char *numero1, char *numero2, int tam_num1, int tam_num2, int *maior_tam, int *menor_tam, int *maior_n)
{
    int i,     /* contador do while */
        maior; /* qual o maior número */
    i = tam_num1 + 1;
    if (tam_num1 > tam_num2)
    {
        *maior_tam = tam_num1;
        *menor_tam = tam_num2;
        maior = 1;
    }
    else if (tam_num2 > tam_num1)
    {
        *maior_tam = tam_num2;
        *menor_tam = tam_num1;
        maior = 2;
    }
    else
    {
        do
        {
            i--;
            maior = ((*(numero1 + i) - '0') > (*(numero2 + i) - '0')) ? 1 : 2;
        } while ((*(numero1 + i)) == (*(numero2 + i)));
        *maior_tam = tam_num1;
        *menor_tam = tam_num2;
    }
    *maior_n = maior;
}

/*
 * Recebe como parâmetro os dois numerões, seus respectivos tamanhos e qual deles é o maior.
 * Esta função só é chamada quando os tamanhos são diferentes, uma vez que ela simplesmente
 * completa o menor numerão. Exemplo: 12+6 ficaria 12+06. Tudo isso só para facilitar na
 * função da soma.
 */
void completa_numero(char *numero1, char *numero2, int tam_num1, int tam_num2, int maior_n)
{
    int i; /* contador do for */
    switch (maior_n)
    {
    case 1:
        for (i = (tam_num2 + 1); i <= tam_num1; i++)
        {
            *(numero2 + i + 1) = '\0';
            *(numero2 + i) = '0';
        }
        break;
    case 2:
        for (i = (tam_num1 + 1); i <= tam_num2; i++)
        {
            *(numero1 + i + 1) = '\0';
            *(numero1 + i) = '0';
        }
        break;
    }
}

void multiplicacao(char *numero1, char *numero2, int tam_num1, int tam_num2)
{
    int i,              /* percorre o menor tamanho */
        j,              /* percorre o maior tamanho */
        n,              /* analisa em qual etapa da multiplicação a função está */
        k,              /* posição no vetor resultado */
        maior_tam,      /* tamanho do maior número */
        menor_tam,      /* tamanho do menor número */
        maior_n,        /* diz quem é o maior número */
        valor1,         /* valor atual do maior número */
        valor2,         /* valor atual do menor número */
        mult,           /* resultado da multiplicação entre valor1 e valor2*/
        carry,          /* corresponde ao "vai um" da conta da multiplicação */
        is_negative,    /* verifica se o resultado da multiplicação será positivo ou negativo */
        tam_final,      /* recebe o tamanho real do resultado após as contas */
        ultimo,         /* último número colocado no vetor resultado */
        aux;            /* auxiliar para somar uma multiplicação na outra */
    char *resultado,    /* string que armazena os resultados */
        auxChar;

    verifica_maior(numero1, numero2, tam_num1, tam_num2, &maior_tam, &menor_tam, &maior_n);
    is_negative = (*numero1 == *numero2)? 0: 1;
    resultado = (char *) calloc((tam_num1+tam_num2+2), sizeof(char));
    
    i = 0;
    j = 0;
    k = 0;
    aux = 0;
    ultimo = 0;
    carry = 0;
    n = 0;
    ultimo = 1;
    *resultado = is_negative + '0';
    for(i=1; i<=menor_tam; i++)
    {
        k = 1;
        for(j=1; j<=maior_tam; j++)
        {
            if(maior_n == 1)
            {
                valor1 = *(numero1+j) - '0';
                valor2 = *(numero2+i) - '0';
            }
            else
            {
                valor1 = *(numero2+j) - '0';
                valor2 = *(numero1+i) - '0';
            }
            mult = valor1*valor2;
            mult += carry;
            carry = 0;
            while(mult >= 10)
            {
                mult -= 10;
                carry++;
            }
            if(n == 0 || (k+n-1) == ultimo) 
            {
                *(resultado+k+n) = mult + '0';
                ultimo = k+n;
            }
            else 
            {
                aux = *(resultado+k+n) - '0';
                /*printf("Aux: %d\n", aux);*/
                aux += mult;
                /*printf("Res parcial: %c\n", *(resultado+k+n));*/
                /*printf("Aux: %d\n", aux);*/
                /*printf("Mult: %d\n", mult);*/
                while(aux >= 10)
                {
                    aux -= 10;
                    carry++;
                }
                auxChar = aux + '0';
                /*printf("Aux char: %c\n", auxChar);*/
                *(resultado+k+n) = auxChar;
            }
            k++;
        }

        /*printf("Carry: %d\n", carry);*/
        /*printf("K: %d\n", k);*/
        if(carry != 0)
        {
            mult = carry;
            /*printf("Mult após carry: %d\n", mult);*/
            *(resultado+k+n) = mult + '0';
            /*printf("Última casa: %c\n", *(resultado+k+n));*/
            /*printf("%s\n", resultado);*/
            ultimo = k+n;
            /*printf("Último: %d\n", ultimo);*/
        }
        else ultimo = k+n-1;

        n++;
        carry = 0;
    }
    tam_final = tamanho(resultado);
    inverte_numero(resultado, tam_final-1);
    imprime(resultado, tam_final);
}
