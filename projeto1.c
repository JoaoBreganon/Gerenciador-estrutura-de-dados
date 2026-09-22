#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "lista.h"

int main()
{
    
    setlocale(LC_ALL,"portuguese");
    int escolha;
    while(escolha != 0)
    {
        printf("====================================================");
        printf("Gerenciador de manutenção de equipamentos de um laboratório");
        printf("")
        scanf("%d",&escolha);
        switch(escolha){
        case 1:
            break;
        
        case 2:
            break;

        case 3:
            break;

        case 4:
            break;

        case 5:
            break;

        case 6:
            break;

        case 0:
            break;

        default:
            break;
        }
    return 0;
    }
}