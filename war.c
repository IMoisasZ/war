#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct
{
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

void limparBuffer();
void cadastrarTerritorio(Territorio *t, int i);
void exibirMapa(Territorio *mapa, int total);
// Adicionamos o parâmetro minTropas para a função conhecer a regra escolhida
void atacar(Territorio *atacante, Territorio *defensor, int minTropas);
void liberarMemoria(Territorio *mapa);

int main()
{
    Territorio *war = NULL;
    int numTerritorios = 0;
    int minTropasAtaque = 0; // Variável que substituirá a constante
    int idxAtk, idxDef;

    srand(time(NULL));

    printf("=====================================\n");
    printf("   WAR ESTRUTURADO - CADADSTRO   \n");
    printf("=====================================\n");

    // Configuração de Territórios
    printf("Informe o numero total de territorios: ");
    scanf("%d", &numTerritorios);
    limparBuffer();

    if (numTerritorios < 2)
    {
        printf("Minimo de 2 territorios para jogar.\n");
        return 1;
    }

    // Configuração de Regras
    printf("\n--- REGRAS DE COMBATE ---\n");
    printf("No War real, um territorio precisa de 2 tropas para atacar\n");
    printf("(1 fica protegendo a base e a outra sai para a batalha).\n");
    printf("Quantas tropas minimas voce deseja para permitir um ataque? ");
    scanf("%d", &minTropasAtaque);
    limparBuffer();

    war = (Territorio *)calloc(numTerritorios, sizeof(Territorio));
    if (war == NULL)
    {
        printf("Erro ao alocar memoria.\n");
        return 1;
    }

    for (int i = 0; i < numTerritorios; i++)
    {
        cadastrarTerritorio(&war[i], i);
    }

    int continuar = 1;
    while (continuar)
    {
        exibirMapa(war, numTerritorios);

        printf("\n--- FASE DE ATAQUE (Minimo para atacar: %d) ---\n", minTropasAtaque);
        printf("Escolha o territorio atacante (1 a %d, ou 0 para sair): ", numTerritorios);
        scanf("%d", &idxAtk);

        if (idxAtk == 0)
        {
            continuar = 0;
            break;
        }

        printf("Escolha o territorio defensor (1 a %d): ", numTerritorios);
        scanf("%d", &idxDef);

        if (idxAtk < 1 || idxAtk > numTerritorios || idxDef < 1 || idxDef > numTerritorios)
        {
            printf("Indice invalido!\n");
        }
        else if (idxAtk == idxDef)
        {
            printf("Um territorio nao pode atacar a si mesmo!\n");
        }
        else if (strcmp(war[idxAtk - 1].cor, war[idxDef - 1].cor) == 0)
        {
            printf("Voce nao pode atacar sua propria cor!\n");
        }
        else
        {
            // Passamos a regra escolhida para a função
            atacar(&war[idxAtk - 1], &war[idxDef - 1], minTropasAtaque);
        }
    }

    liberarMemoria(war);
    return 0;
}

void atacar(Territorio *atacante, Territorio *defensor, int minTropas)
{
    // Validação baseada na escolha do usuário
    if (atacante->tropas < minTropas)
    {
        printf("\n[AVISO] %s tem %d tropas. O minimo para atacar e' %d.\n",
               atacante->nome, atacante->tropas, minTropas);
        return;
    }

    int dadoAtk = (rand() % 6) + 1;
    int dadoDef = (rand() % 6) + 1;

    printf("\n--- BATALHA: %s (%d) vs %s (%d) ---\n",
           atacante->nome, dadoAtk, defensor->nome, dadoDef);

    if (dadoAtk > dadoDef)
    {
        defensor->tropas--;
        printf("Vitoria do ataque! %s perdeu 1 tropa.\n", defensor->nome);

        if (defensor->tropas <= 0)
        {
            printf("CONQUISTA! %s agora pertence aos %s.\n", defensor->nome, atacante->cor);
            strcpy(defensor->cor, atacante->cor);
            defensor->tropas = atacante->tropas / 2;
            atacante->tropas -= defensor->tropas;
        }
    }
    else
    {
        atacante->tropas--;
        printf("O defensor venceu! %s perdeu 1 tropa.\n", atacante->nome);
    }
}

// ... (Funções cadastrarTerritorio, exibirMapa, liberarMemoria e limparBuffer permanecem iguais)

void cadastrarTerritorio(Territorio *t, int i)
{
    printf("\n--- Cadastrando Territorio %d ---\n", i + 1);
    printf("Nome do Territorio: ");
    scanf("%s", t->nome);
    limparBuffer();
    printf("Cor do Territorio: ");
    scanf("%s", t->cor);
    limparBuffer();
    printf("Numero de Tropas: ");
    scanf("%d", &t->tropas);
    limparBuffer();
}

void exibirMapa(Territorio *mapa, int total)
{
    printf("\n=====================================\n");
    printf("          MAPA - ESTADO ATUAL          \n");
    printf("=====================================\n");
    for (int i = 0; i < total; i++)
    {
        printf("%d. %s | Exercito: %s | Tropas: %d\n",
               i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

void liberarMemoria(Territorio *mapa)
{
    if (mapa != NULL)
    {
        free(mapa);
        printf("\nMemoria liberada. Ate a proxima!\n");
    }
}

void limparBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}