/* Importa a declaração da função e os tipos usados em seus parâmetros. */
#include "duplicatas.h"

bool tem_duplicado(const int vetor[], size_t n, uint64_t *comparacoes)
{
    /*
     * O ponteiro recebido indica onde está o contador de quem chamou a função.
     * O * acessa esse valor e o zera para não acumular buscas anteriores.
     */
    *comparacoes = 0;

    /*
     * i escolhe o primeiro elemento de cada par. A última posição não precisa
     * ser escolhida, pois não existe nenhum elemento depois dela.
     *
     * Para n >= 2, i + 1 < n equivale a i <= n - 2. Essa forma também encerra
     * o laço imediatamente quando n é zero ou um. Como size_t não representa
     * números negativos, evitamos calcular n - 2 para esses tamanhos.
     */
    for (size_t i = 0; i + 1 < n; i++) {
        /*
         * j percorre apenas as posições seguintes a i. Assim, não comparamos
         * uma posição consigo mesma nem repetimos um par na ordem inversa.
         * Por exemplo, depois de comparar (0, 1), não comparamos (1, 0).
         */
        for (size_t j = i + 1; j < n; j++) {
            /*
             * Registramos a comparação vetor[i] == vetor[j] feita logo abaixo.
             * Os testes de controle dos laços não entram neste contador.
             * Os parênteses fazem o ++ incrementar o valor apontado por
             * comparacoes, mantendo o ponteiro no mesmo endereço.
             */
            (*comparacoes)++;

            if (vetor[i] == vetor[j]) {
                /*
                 * A igualdade já comprova a duplicata. return encerra a função
                 * inteira, interrompendo os dois laços: esta é a parada cedo.
                 */
                return true;
            }
        }
    }

    /*
     * Chegar até aqui significa que nenhum par igual foi encontrado.
     * O mesmo retorno atende aos vetores vazios ou com um único elemento.
     */
    return false;
}
