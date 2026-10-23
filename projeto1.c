#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include "lista.h"

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    setlocale(LC_ALL,"portuguese.UTF-8");
    lista *l = Inicialista();
    l = Criarlista();

    int escolha = 1;
    while(escolha != 0)
    {
        system("cls");
        printf("\n====================================================================");
        printf("\n    GERENCIADOR DE MANUTENÇÃO DE EQUIPAMENTOS DE UM LABORATÓRIO     ");
        printf("\n====================================================================");
        printf("\n  1 - Inserir uma Solicitação de Manutenção");
        printf("\n  2 - Remover uma Solicitação");
        printf("\n  3 - Consultar uma Solicitação");
        printf("\n  4 - Alterar a prioridade e/ou período de uma Solicitação");
        printf("\n  5 - Exibir a ordem de realização da manutenção");
        printf("\n  6 - Exibir todas as solicitações");
        printf("\n  0 - Finalizar");
        printf("\n====================================================================");
        printf("\n  Escolha uma opção: ");
        scanf("%d",&escolha);
        switch(escolha){
        case 0:
            system("cls");
            printf("\nEncerrando...\n");
            break;
        case 1:
            system("cls");
            inserirSolicitacao(l);
            break;

        case 2:
            system("cls");
            Remove(l);
            break;

        case 3:
            system("cls");
            consulta_sol(l);
            break;

        case 4:
            system("cls");
            OPP(l);
            break;

        case 5:
            system("cls");
            ExibirManun(l);
            break;

        case 6:
            system("cls");
            ExibirTudo(l);
            break;
            
        default:
            printf("\n\tOpção inválida! Tente novamente.\n");
            break;
        }
        if(escolha != 0 && escolha != 4){
            printf("\n");
            system("pause");
        }
    }
    liberalista(l);
    return 0;
}
