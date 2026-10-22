/*
 * Este cabeçalho declara a função usada pelos outros arquivos do programa.
 * A implementação fica em duplicatas.c.
 *
 * A proteção abaixo evita processar estas declarações mais de uma vez no
 * mesmo arquivo fonte, caso o cabeçalho seja incluído novamente.
 */
#ifndef DUPLICATAS_H
#define DUPLICATAS_H

#include <stdbool.h> /* Fornece bool e os valores true e false. */
#include <stddef.h>  /* Fornece size_t, usado para tamanhos e índices. */
#include <stdint.h>  /* Fornece uint64_t, um inteiro sem sinal de 64 bits. */

/*
 * Verifica se existe algum par de elementos iguais no vetor.
 * Retorna true na primeira duplicata e false se os elementos forem distintos.
 *
 * Parâmetros:
 * - vetor: elementos que serão examinados. const impede que a função altere
 *   esses valores por meio deste parâmetro.
 * - n: quantidade de elementos do vetor. size_t é um tipo inteiro sem sinal,
 *   apropriado para representar tamanhos e índices.
 * - comparacoes: endereço do contador que a função vai preencher. O ponteiro
 *   permite escrever o resultado em uma variável de quem chamou a função.
 *   O valor armazenado é uint64_t, com 64 bits para a contagem.
 *
 * A contagem começa em zero a cada chamada e inclui apenas comparações entre
 * elementos. Para n igual a zero ou um, retorna false com zero comparações,
 * pois não existe um par de posições para examinar.
 *
 * Quem chama deve fornecer um ponteiro válido para comparacoes e, quando n > 0,
 * um vetor com pelo menos n elementos. Para n == 0, vetor pode ser NULL.
 */
bool tem_duplicado(const int vetor[], size_t n, uint64_t *comparacoes);

#endif /* Fim da proteção DUPLICATAS_H. */
