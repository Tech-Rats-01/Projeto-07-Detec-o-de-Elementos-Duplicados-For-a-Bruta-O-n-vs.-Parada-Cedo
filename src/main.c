#include <inttypes.h> /* Fornece PRIu64, usado para imprimir uint64_t. */
#include <stdio.h>    /* Fornece printf para escrever no terminal. */
#include <stdlib.h>   /* Fornece EXIT_SUCCESS e EXIT_FAILURE. */

/* Dá acesso à função de detecção e aos tipos declarados em seu cabeçalho. */
#include "duplicatas.h"

/*
 * Executa e apresenta um caso, recebendo seu nome, o vetor e o tamanho.
 * Os dois últimos parâmetros informam a detecção e a contagem esperadas.
 *
 * O retorno indica se o caso produziu os resultados esperados. Isso é
 * diferente de indicar se existe duplicata: um vetor sem repetição também
 * está correto quando essa era a resposta esperada.
 *
 * static limita o uso desta função auxiliar a este arquivo.
 */
static bool executar_caso(const char *nome, const int vetor[], size_t n,
                         bool duplicata_esperada, uint64_t comparacoes_esperadas)
{
    /*
     * Esta variável recebe a contagem. &comparacoes fornece seu endereço,
     * permitindo que tem_duplicado preencha o valor durante a busca.
     */
    uint64_t comparacoes = 0;
    bool encontrada = tem_duplicado(vetor, n, &comparacoes);
    /* O caso só passa se a detecção e a contagem estiverem corretas. */
    bool correto = encontrada == duplicata_esperada
                   && comparacoes == comparacoes_esperadas;

    /* %s insere o nome recebido; \n representa uma quebra de linha. */
    printf("\n%s\n", nome);
    /*
     * Mostra o vetor na ordem original. A vírgula é impressa antes de cada
     * elemento a partir do segundo, evitando uma vírgula extra nas pontas.
     * Esse laço serve apenas à apresentação e não altera o contador da busca.
     */
    printf("Vetor: [");
    for (size_t i = 0; i < n; i++) {
        if (i > 0) {
            printf(", ");
        }
        printf("%d", vetor[i]); /* %d apresenta um valor do tipo int. */
    }
    printf("]\n");

    /*
     * %zu é o formato para size_t. Nas linhas seguintes, o operador ?: escolhe
     * o texto a exibir: condição ? texto_se_verdadeiro : texto_se_falso.
     */
    printf("Tamanho: %zu\n", n);
    printf("Duplicata encontrada: %s\n", encontrada ? "sim" : "nao");
    printf("Duplicata esperada: %s\n", duplicata_esperada ? "sim" : "nao");
    /*
     * PRIu64 fornece o formato adequado para uint64_t nesta plataforma.
     * O C reúne as partes da string de formato durante a compilação.
     */
    printf("Comparacoes obtidas: %" PRIu64 "\n", comparacoes);
    printf("Comparacoes esperadas: %" PRIu64 "\n", comparacoes_esperadas);
    printf("Conferencia: %s\n", correto ? "OK" : "FALHA");

    /* Devolve à main se tanto a detecção quanto a contagem passaram. */
    return correto;
}

/* A execução começa em main; void indica que ela não recebe argumentos. */
int main(void)
{
    /* A primeira comparação encontra os dois zeros e encerra o melhor caso. */
    const int melhor[] = {0, 0, 2, 3, 4, 5, 6, 7, 8, 9};
    /* Com todos os valores distintos, a busca precisa examinar todos os pares. */
    const int pior[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    /*
     * sizeof vetor informa o total de bytes, e sizeof vetor[0], os bytes de
     * um elemento. A divisão fornece a quantidade de elementos.
     * O cálculo é feito aqui, onde os vetores estão declarados como arrays.
     */
    const size_t tamanho_melhor = sizeof melhor / sizeof melhor[0];
    const size_t tamanho_pior = sizeof pior / sizeof pior[0];

    /*
     * Calcula a contagem esperada para um vetor sem repetição: n(n - 1) / 2.
     * Para os dez elementos acima, esperamos 45 comparações.
     * A conversão para uint64_t ocorre antes da multiplicação, feita em 64 bits.
     */
    const uint64_t comparacoes_pior =
        (uint64_t)tamanho_pior * (uint64_t)(tamanho_pior - 1) / 2;

    printf("Deteccao de elementos duplicados por comparacao de pares\n");

    /*
     * No melhor caso esperamos duplicata e uma comparação; no pior, nenhuma
     * duplicata e a contagem calculada acima. Cada retorno registra se o caso
     * passou. As chamadas separadas garantem que os dois sejam executados,
     * mesmo que o primeiro falhe na conferência.
     */
    bool melhor_correto = executar_caso("Melhor caso", melhor, tamanho_melhor,
                                      true, 1);
    bool pior_correto = executar_caso("Pior caso", pior, tamanho_pior,
                                    false, comparacoes_pior);

    /* && exige que os dois casos tenham passado nas conferências. */
    if (melhor_correto && pior_correto) {
        printf("\nOs dois casos produziram os resultados esperados.\n");
        return EXIT_SUCCESS; /* Informa conclusão bem-sucedida ao sistema: zero. */
    }

    /* Algum caso divergiu; a mensagem e o código de saída sinalizam a falha. */
    printf("\nFoi encontrada uma divergencia na demonstracao.\n");
    return EXIT_FAILURE; /* Informa falha ao sistema com um valor diferente de zero. */
}
