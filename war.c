#include <stdio.h>
#include <string.h>
#include <stdlib.h> // Para malloc/calloc e rand
#include <time.h>   // Para inicializar a semente do rand

// Estrutura solicitada
struct Territorio
{
    char nome[30];
    char cor[10];
    int tropas;
};

// Protótipos das funções
void limparBuffer();
void cadastrarTerritorio(struct Territorio *t, int i);
void exibirMapa(struct Territorio *mapa, int total);
void atacar(struct Territorio *atacante, struct Territorio *defensor);
void liberarMemoria(struct Territorio *mapa);

int main()
{
    struct Territorio *war = NULL;
    int numTerritorios;

    // Semente para aleatoriedade
    srand(time(NULL));

    printf("Quantos territorios deseja cadastrar? ");
    scanf("%d", &numTerritorios);
    limparBuffer();

    // Alocação dinâmica conforme solicitado
    war = (struct Territorio *)calloc(numTerritorios, sizeof(struct Territorio));

    if (war == NULL)
    {
        printf("Erro ao alocar memoria.\n");
        return 1;
    }

    // Cadastro inicial
    for (int i = 0; i < numTerritorios; i++)
    {
        cadastrarTerritorio(&war[i], i);
    }

    // Exemplo de fluxo de ataque
    exibirMapa(war, numTerritorios);

    if (numTerritorios >= 2)
    {
        int idxAtk, idxDef;
        printf("\n--- INICIAR ATAQUE ---\n");
        printf("Indice do atacante (0 a %d): ", numTerritorios - 1);
        scanf("%d", &idxAtk);
        printf("Indice do defensor (0 a %d): ", numTerritorios - 1);
        scanf("%d", &idxDef);

        // Validação: Não pode atacar a própria cor
        if (strcmp(war[idxAtk].cor, war[idxDef].cor) == 0)
        {
            printf("\nERRO: Voce nao pode atacar um territorio da mesma cor (%s)!\n", war[idxAtk].cor);
        }
        else
        {
            atacar(&war[idxAtk], &war[idxDef]);
        }
    }

    exibirMapa(war, numTerritorios);

    // Finalização
    liberarMemoria(war);
    return 0;
}

// Implementação da função de ataque com lógica de conquista
void atacar(struct Territorio *atacante, struct Territorio *defensor)
{
    if (atacante->tropas <= 1)
    {
        printf("O atacante %s nao tem tropas suficientes (minimo 2).\n", atacante->nome);
        return;
    }

    int dadoAtk = (rand() % 6) + 1;
    int dadoDef = (rand() % 6) + 1;

    printf("\nBatalha: %s [%d] vs %s [%d]\n", atacante->nome, dadoAtk, defensor->nome, dadoDef);

    if (dadoAtk > dadoDef)
    {
        // Atacante vence a rodada
        defensor->tropas--;
        printf("Vitoria no ataque! %s perdeu 1 tropa.\n", defensor->nome);

        // Regra de Conquista: Se as tropas do defensor acabarem
        if (defensor->tropas <= 0)
        {
            printf("TERRITORIO CONQUISTADO! %s agora pertence ao exercito %s.\n", defensor->nome, atacante->cor);
            strcpy(defensor->cor, atacante->cor);    // Transfere a cor
            defensor->tropas = atacante->tropas / 2; // Transfere metade das tropas
            atacante->tropas -= defensor->tropas;    // Remove do atacante
        }
    }
    else
    {
        // Defensor vence ou empate
        atacante->tropas--;
        printf("O defensor resistiu! %s perdeu 1 tropa.\n", atacante->nome);
    }
}

// Função para liberar a memória alocada
void liberarMemoria(struct Territorio *mapa)
{
    if (mapa != NULL)
    {
        free(mapa);
        printf("\nMemoria liberada com sucesso.\n");
    }
}

void cadastrarTerritorio(struct Territorio *t, int i)
{
    printf("\nTerritorio %d - Nome: ", i);
    scanf(" %29[^\n]", t->nome);
    limparBuffer();
    printf("Cor: ");
    scanf(" %9s", t->cor);
    limparBuffer();
    printf("Tropas: ");
    scanf("%d", &t->tropas);
    limparBuffer();
}

void exibirMapa(struct Territorio *mapa, int total)
{
    printf("\n--- MAPA ATUAL ---\n");
    for (int i = 0; i < total; i++)
    {
        printf("[%d] %s | Cor: %s | Tropas: %d\n", i, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

void limparBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}