#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// Estrutura para representar os territórios do jogo
typedef struct
{
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// Protótipos das funções
void limparBuffer();
void cadastrarTerritorio(Territorio *t, int i);
void exibirMapa(Territorio *mapa, int total);
void atacar(Territorio *atacante, Territorio *defensor, int minTropas);
void gerarMissaoDinamica(char *destino, Territorio *mapa, int total, char *corAtacante);
int verificarVitoria(char *missao, Territorio *mapa, int total);

int main()
{
    Territorio *war = NULL;
    char missaoAtiva[100]; // Vetor estático para a missão
    char corJogador[10];
    int numTerritorios, opcao, idxAtk, idxDef;
    int minTropasAtaque = 2; // Regra fixada em 2 conforme solicitado

    srand(time(NULL));

    printf("=====================================\n");
    printf("   WAR ESTRUTURADO - VERSAO FINAL    \n");
    printf("=====================================\n");

    // 1. Configuração de Territórios
    printf("Informe o numero total de territorios: ");
    scanf("%d", &numTerritorios);
    limparBuffer();

    if (numTerritorios < 2)
    {
        printf("Minimo de 2 territorios para jogar.\n");
        return 1;
    }

    // 2. Alocação e Cadastro
    war = (Territorio *)calloc(numTerritorios, sizeof(Territorio));
    if (war == NULL)
        return 1;

    for (int i = 0; i < numTerritorios; i++)
    {
        cadastrarTerritorio(&war[i], i);
    }

    // 3. Geração da Missão
    gerarMissaoDinamica(missaoAtiva, war, numTerritorios, corJogador);

    // 4. Loop Principal com Menu de Ações
    int jogoAtivo = 1;
    while (jogoAtivo)
    {
        exibirMapa(war, numTerritorios);

        printf("\n--- SUA MISSAO (Exercito %s) ---\n", corJogador);
        printf("%s.\n", missaoAtiva);

        printf("\n--- MENU DE ACOES ---\n");
        printf("1 - Atacar\n");
        printf("2 - Verificar Missao\n");
        printf("0 - Sair\n");
        printf("Escolha sua acao: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao)
        {
        case 1:
            printf("\n--- FASE DE ATAQUE ---\n");
            printf("ID do atacante (1 a %d): ", numTerritorios);
            scanf("%d", &idxAtk);
            printf("ID do defensor (1 a %d): ", numTerritorios);
            scanf("%d", &idxDef);

            if (idxAtk < 1 || idxAtk > numTerritorios || idxDef < 1 || idxDef > numTerritorios)
            {
                printf("[ERRO] Indices invalidos!\n");
            }
            else
            {
                Territorio *atq = &war[idxAtk - 1];
                Territorio *def = &war[idxDef - 1];

                if (strcmp(atq->cor, corJogador) != 0)
                {
                    printf("[ERRO] Voce so comanda o exercito %s!\n", corJogador);
                }
                else if (strcmp(atq->cor, def->cor) == 0)
                {
                    printf("[ERRO] Nao pode atacar seu proprio exercito!\n");
                }
                else
                {
                    atacar(atq, def, minTropasAtaque);
                }
            }
            break;

        case 2:
            if (verificarVitoria(missaoAtiva, war, numTerritorios))
            {
                printf("\nOBJETIVO CONCLUIDO! Voce eliminou o alvo.\n");
                jogoAtivo = 0;
            }
            else
            {
                printf("\nA missao ainda nao foi cumprida. Continue lutando!\n");
            }
            break;

        case 0:
            jogoAtivo = 0;
            break;

        default:
            printf("Opcao invalida!\n");
        }

        // Verificação automática de vitória
        if (opcao == 1 && verificarVitoria(missaoAtiva, war, numTerritorios))
        {
            printf("\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
            printf("VITORIA! O exercito %s cumpriu sua missao!\n", corJogador);
            printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
            jogoAtivo = 0;
        }
    }

    free(war);
    return 0;
}

// Implementação das Funções Auxiliares

void gerarMissaoDinamica(char *destino, Territorio *mapa, int total, char *corAtacante)
{
    int r = rand() % total;
    strcpy(corAtacante, mapa[r].cor);

    char corInimiga[10];
    strcpy(corInimiga, "Neutro");
    for (int i = 0; i < total; i++)
    {
        if (strcmp(mapa[i].cor, corAtacante) != 0)
        {
            strcpy(corInimiga, mapa[i].cor);
            break;
        }
    }
    sprintf(destino, "Destruir o exercito %s", corInimiga);
}

int verificarVitoria(char *missao, Territorio *mapa, int total)
{
    char corAlvo[10];
    sscanf(missao, "Destruir o exercito %s", corAlvo);
    for (int i = 0; i < total; i++)
    {
        if (strcmp(mapa[i].cor, corAlvo) == 0)
            return 0;
    }
    return 1;
}

void atacar(Territorio *atacante, Territorio *defensor, int minTropas)
{
    if (atacante->tropas < minTropas)
    {
        printf("\n[AVISO] %s precisa de pelo menos %d tropas para atacar.\n", atacante->nome, minTropas);
        return;
    }

    int dAtk = (rand() % 6) + 1;
    int dDef = (rand() % 6) + 1;

    printf("\nCOMBATE: %s (%d) vs %s (%d)\n", atacante->nome, dAtk, defensor->nome, dDef);

    if (dAtk > dDef)
    {
        defensor->tropas--;
        if (defensor->tropas <= 0)
        {
            printf("CONQUISTA! %s agora e' %s.\n", defensor->nome, atacante->cor);
            strcpy(defensor->cor, atacante->cor);
            defensor->tropas = atacante->tropas / 2;
            atacante->tropas -= defensor->tropas;
        }
    }
    else
    {
        atacante->tropas--;
        printf("O ataque falhou! Perdeu 1 tropa.\n");
    }
}

void cadastrarTerritorio(Territorio *t, int i)
{
    printf("\n--- Territorio %d ---\n", i + 1);
    printf("Nome: ");
    scanf("%s", t->nome);
    printf("Cor: ");
    scanf("%s", t->cor);
    printf("Tropas: ");
    scanf("%d", &t->tropas);
    limparBuffer();
}

void exibirMapa(Territorio *mapa, int total)
{
    printf("\n--- MAPA DO MUNDO ---\n");
    for (int i = 0; i < total; i++)
    {
        printf("%d. %-12s | Exercito: %-10s | Tropas: %d\n", i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

void limparBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}