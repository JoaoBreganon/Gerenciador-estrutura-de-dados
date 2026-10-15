#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <ctype.h>
#include "lista.h"

int main()
{
    lista *l = Inicialista();
    l = Criarlista();
    setlocale(LC_ALL,"portuguese");
    int escolha = 1;
    while(escolha != 0)
    {
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
        case 1:
            inserirSolicitacao(l);
            break;
        
        case 2:
            Remove(l);
            break;

        case 3:
            consulta_sol(l);
            break;

        case 4:
            OPP(l);
            break;

        case 5:
            ExibirManun(l);
            break;

        case 6:
            ExibirTudo(l);
            break;
        default:
            printf("\n\tOpção inválida! Tente novamente.");
            break;
        }
    }
    liberalista(l);
    return 0;
}