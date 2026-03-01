
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct
{
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

/* -------- FUNÇÃO PARA CADASTRAR -------- */
void cadastrarTerritorios(Territorio *mapa, int quantidade)
{
    for (int i = 0; i < quantidade; i++)
    {
        printf("\n--- Cadastro do Territorio %d ---\n", i + 1);

        printf("Nome: ");
        scanf("%s", mapa[i].nome);

        printf("Cor do exercito: ");
        scanf("%s", mapa[i].cor);

        printf("Quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);
    }
}

/* -------- FUNÇÃO PARA EXIBIR -------- */
void exibirTerritorios(Territorio *mapa, int quantidade)
{
    printf("\n========== MAPA ATUAL ==========\n");

    for (int i = 0; i < quantidade; i++)
    {
        printf("\nTerritorio %d\n", i + 1);
        printf("Nome: %s\n", mapa[i].nome);
        printf("Cor: %s\n", mapa[i].cor);
        printf("Tropas: %d\n", mapa[i].tropas);
    }

    printf("\n================================\n");
}

/* -------- FUNÇÃO DE ATAQUE -------- */
void atacar(Territorio *atacante, Territorio *defensor)
{
    if (atacante->tropas <= 1)
    {
        printf("\nAtaque invalido! O territorio atacante precisa ter mais de 1 tropa.\n");
        return;
    }

    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("\n--- BATALHA ---\n");
    printf("Atacante rolou: %d\n", dadoAtacante);
    printf("Defensor rolou: %d\n", dadoDefensor);

    if (dadoAtacante > dadoDefensor)
    {
        printf("\nO atacante venceu!\n");

        int tropasTransferidas = atacante->tropas / 2;

        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = tropasTransferidas;

        atacante->tropas -= tropasTransferidas;
    }
    else
    {
        printf("\nO defensor venceu!\n");
        atacante->tropas -= 1;
    }
}

/* -------- LIBERAR MEMÓRIA -------- */
void liberarMemoria(Territorio *mapa)
{
    free(mapa);
}

/* -------- FUNÇÃO PRINCIPAL -------- */
int main()
{
    srand(time(NULL));

    int quantidade;

    printf("Quantos territorios deseja cadastrar? ");
    scanf("%d", &quantidade);

    Territorio *mapa = calloc(quantidade, sizeof(Territorio));

    if (mapa == NULL)
    {
        printf("Erro ao alocar memoria!\n");
        return 1;
    }

    cadastrarTerritorios(mapa, quantidade);

    int opcao = 1;

    while (opcao)
    {
        exibirTerritorios(mapa, quantidade);

        int atacanteIndex, defensorIndex;

        printf("\nEscolha o numero do territorio atacante (1 a %d): ", quantidade);
        scanf("%d", &atacanteIndex);

        printf("Escolha o numero do territorio defensor (1 a %d): ", quantidade);
        scanf("%d", &defensorIndex);

        if (atacanteIndex < 1 || atacanteIndex > quantidade ||
            defensorIndex < 1 || defensorIndex > quantidade ||
            atacanteIndex == defensorIndex)
        {
            printf("\nEscolha invalida!\n");
        }
        else
        {
            atacar(&mapa[atacanteIndex - 1], &mapa[defensorIndex - 1]);
        }

        printf("\nDeseja realizar outro ataque? (1 = Sim | 0 = Nao): ");
        scanf("%d", &opcao);
    }

    liberarMemoria(mapa);

    printf("\nMemoria liberada. Fim do jogo.\n");

    return 0;
}