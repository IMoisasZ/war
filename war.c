
// Bibliotecas
#include <stdio.h>
#include <string.h>

// Molde/Strutura - Estrutura para a criação dos territórios
struct Territorio
{
    char nome[30];
    char cor[10];
    int tropas;
};

// Constantes
#define MAX_TERRITORIOS 2 // Definir a quantidade de territorios

// Função para limpar o buffer
void limparBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

// Função principal
int main()
{
    struct Territorio war[MAX_TERRITORIOS];
    int totalTerritorios = 0;

    printf("=========================================================\n");
    printf("\nVamos cadastrar os %d territorios iniciais do nosso mundo.\n\n", MAX_TERRITORIOS);

    // Laço para inclusão da quantidade de territórios
    do
    {
        printf("--- Cadastrando Territorio %d ---\n", totalTerritorios + 1);

        printf("Nome do territorio: ");
        scanf(" %s", war[totalTerritorios].nome);
        limparBuffer(); // Limpar o enter que ficou devido o uso do scanf

        printf("Cor do exercito (ex: Azul, Verde): ");
        fgets(war[totalTerritorios].cor, 10, stdin);
        war[totalTerritorios].cor[strcspn(war[totalTerritorios].cor, "\n")] = '\0';

        printf("Numero de tropas: ");
        scanf("%d", &war[totalTerritorios].tropas);
        limparBuffer(); // Limpar o enter que ficou devido o uso do scanf

        totalTerritorios++;
        printf("\n");
    } while (totalTerritorios < MAX_TERRITORIOS);

    printf("=========================================================\n");
    printf("             MAPA DO MUNDO - ESTADO ATUAL                \n");
    printf("=========================================================\n\n");

    // Laço para mostrar os territórios cadastrados
    for (int i = 0; i < MAX_TERRITORIOS; i++)
    {
        printf("TERRITORIO %d\n", i + 1);
        printf(" - Nome: %s\n", war[i].nome);
        printf(" - Dominado por: Exercito %s\n", war[i].cor);
        printf(" - Tropas: %d\n\n", war[i].tropas);
    }

    printf("=========================================================\n");
    printf("Territorios cadastrados com sucesso!\n");
    printf("Pressione ENTER para fechar esta janela...");

    getchar();

    return 0;
}