#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct manutencao{
    int cod_solicitacao;
    char cod_equipamento[7];
    char nome_equipamento[21];
    int prioridade;
    int periodo;
}Manutencao;

typedef struct no{
    Manutencao info;
    struct no* prox;
}no;

typedef struct lista{
    no*inicio;
}lista;

void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}   

//  função para ler inteiros sem travar caso digite letras
int ler_inteiro() {
    int valor;
    while (scanf("%d", &valor) != 1) {
        limpar_buffer(); // Remove as letras que travariam o buffer
        printf("Erro: Entrada inválida! Digite apenas números: ");
    }
    limpar_buffer(); 
    return valor;
}

lista* Inicialista(){
    return NULL;
}

lista* Criarlista(){
    lista*aux;
    aux=(lista*)malloc(sizeof(lista));
    aux->inicio = NULL;
    return aux;   
}

int VerificaLista(lista*L){
    if (L->inicio==NULL) {
       return 1;
    }
    return 0;
}

lista* liberalista(lista*L){
    no *apag;
    while (L->inicio!= NULL){
       apag=L->inicio;
       L->inicio=L->inicio->prox;
       free(apag);
    }
    free(L);
    return NULL;
}

//Função de inserção ordenada baseada no código de solicitação 
no *InsereOrdenado(no *antigo,Manutencao var )
{
    no *novo,*aux,*aux1;
    novo=(no*)malloc(sizeof(no));
    novo->info=var;
    aux = NULL;
    aux1= antigo;
    if(aux1 == NULL){
        novo->prox=aux1;
        antigo = novo;
        return antigo;
    }

    while (aux1 !=NULL && var.cod_solicitacao > aux1->info.cod_solicitacao)
    {
        aux = aux1;
        aux1 = aux1->prox;
    }

    if (aux == NULL)
    {
        novo->prox=aux1;
        antigo = novo;
        return antigo;
    }
    
    aux->prox= novo;
    novo->prox= aux1;
    return antigo;
}

void inserirSolicitacao(lista* l) {
    Manutencao aux;
    no* percorre;
    int flag;
    int cancelar = 0;

    do {
        flag = 1; // Reseta a flag a cada nova tentativa
        percorre = l->inicio;
        
        printf("Digite o código de solicitação (1000 a 9999) ou -1 para cancelar: ");
        aux.cod_solicitacao = ler_inteiro();
        
        if (aux.cod_solicitacao == -1) {
            cancelar = 1;
        } else {
            // Verifica se o código já existe na lista
            while (percorre != NULL) {
                if (aux.cod_solicitacao == percorre->info.cod_solicitacao) {
                    flag = 0; // Código repetido encontrado
                    printf("Erro: Este código já existe!\n");
                    break; // Pode parar a busca, já achou repetido
                }
                percorre = percorre->prox;
            }
            
            // Avisa se estiver fora do limite
            if (aux.cod_solicitacao < 1000 || aux.cod_solicitacao > 9999) {
                printf("Erro: O código deve estar entre 1000 e 9999!\n");
            }
        }
        
    // Repete se não cancelou E (fora do intervalo OU se a flag for 0)
    } while (cancelar == 0 && ((aux.cod_solicitacao < 1000 || aux.cod_solicitacao > 9999) || flag == 0));
    
    if (cancelar == 0) {
        int contletter, contnum, excesso;
        
        do {
            contletter = 0;
            contnum = 0;
            excesso = 0;
            
            printf("\nDigite o código de equipamento (ex: AAA111) ou -1 para cancelar: ");
            fgets(aux.cod_equipamento, sizeof(aux.cod_equipamento), stdin);
            
            // Se não achou o '\n', o usuário digitou mais de 6 caracteres; limpa o que sobrou
            if (strchr(aux.cod_equipamento, '\n') == NULL) {
                limpar_buffer();
                excesso = 1;
            } else {
                aux.cod_equipamento[strcspn(aux.cod_equipamento, "\n")] = '\0';
            }
            
            if (strcmp(aux.cod_equipamento, "-1") == 0 && excesso == 0) {
                cancelar = 1;
            } else {
                if (excesso == 0 && strlen(aux.cod_equipamento) == 6) {
                    for (int i = 0; i < 3; i++) {
                        if (isalpha((unsigned char)aux.cod_equipamento[i])) contletter++;
                    }
                    for (int i = 3; i < 6; i++) {
                        if (isdigit((unsigned char)aux.cod_equipamento[i])) contnum++;
                    }
                }

                if (contnum != 3 || contletter != 3 || excesso == 1) {
                    printf("Erro: O formato deve conter exatamente 3 letras seguidas de 3 números!\n");
                }
            }
        } while (cancelar == 0 && (contnum != 3 || contletter != 3 || excesso == 1));

        if (cancelar == 0) {
            do {
                printf("\nDigite o nome do equipamento ou -1 para cancelar: ");
                fgets(aux.nome_equipamento, sizeof(aux.nome_equipamento), stdin);
                
                if (strchr(aux.nome_equipamento, '\n') == NULL) {
                    limpar_buffer();
                } else {
                    aux.nome_equipamento[strcspn(aux.nome_equipamento, "\n")] = '\0';
                }

                if (strlen(aux.nome_equipamento) == 0) {
                    printf("Erro: O nome do equipamento não pode ser vazio!\n");
                }
            } while (strlen(aux.nome_equipamento) == 0);
            
            if (strcmp(aux.nome_equipamento, "-1") == 0) {
                cancelar = 1;
            } else {
                do {
                    printf("\nDigite a prioridade (1 a 3) ou -1 para cancelar: ");
                    aux.prioridade = ler_inteiro();
                    
                    if (aux.prioridade == -1) {
                        cancelar = 1;
                    } else if (aux.prioridade < 1 || aux.prioridade > 3) {
                        printf("Erro: A prioridade deve estar entre 1 e 3!\n");
                    }
                } while (cancelar == 0 && (aux.prioridade < 1 || aux.prioridade > 3));

                if (cancelar == 0) {
                    switch(aux.prioridade)
                    {
                    case 1:
                        do{
                            printf("\nDigite o período necessário para manutenção (1-7 dias) ou -1 para cancelar: ");
                            aux.periodo = ler_inteiro();
                            if (aux.periodo == -1) {
                                cancelar = 1;
                            } else if (aux.periodo < 1 || aux.periodo > 7) {
                                printf("Erro: Para prioridade 1, o período deve ser entre 1 e 7 dias!\n");
                            }
                        }while(cancelar == 0 && (aux.periodo<1 || aux.periodo>7));
                        break;

                    case 2:
                        do{
                            printf("\nDigite o período necessário para manutenção (1-15 dias) ou -1 para cancelar: ");
                            aux.periodo = ler_inteiro();
                            if (aux.periodo == -1) {
                                cancelar = 1;
                            } else if (aux.periodo < 1 || aux.periodo > 15) {
                                printf("Erro: Para prioridade 2, o período deve ser entre 1 e 15 dias!\n");
                            }
                        }while(cancelar == 0 && (aux.periodo<1 || aux.periodo>15));
                        break;
                    
                    case 3:
                        do{
                            printf("\nDigite o período necessário para manutenção (1-20 dias) ou -1 para cancelar: ");
                            aux.periodo = ler_inteiro();
                            if (aux.periodo == -1) {
                                cancelar = 1;
                            } else if (aux.periodo < 1 || aux.periodo > 20) {
                                printf("Erro: Para prioridade 3, o período deve ser entre 1 e 20 dias!\n");
                            }
                        }while(cancelar == 0 && (aux.periodo<1 || aux.periodo>20));
                        break;
                    
                    default:
                        break;
                    }  
                    
                    if (cancelar == 0) {
                        l->inicio = InsereOrdenado(l->inicio,aux);
                        printf("\nSolicitação cadastrada com sucesso!\n");
                    }
                }
            }
        }
    }

    if (cancelar == 1) {
        printf("\nOperação cancelada!\n");
    }
}

//Função de remoção de um elemento na lista baseado no código de solicitação, utilizando a lógica de remoção em qualquer lugar
void Remove(lista* l){
    if(VerificaLista(l)){
        printf("\nErro: A lista de solicitações está vazia!\n");
    }
    else{
        int cod,flag=0;
        printf("\nDigite o código de solicitação que deseja remover (ou -1 para cancelar): ");
        cod = ler_inteiro();
        
        if (cod == -1) {
            printf("\nOperação cancelada!\n");
        }
        else {
            no *aux = NULL, *aux1,*apag;
            aux1 = l->inicio;
            while (aux1 != NULL && flag != 1)
            {
               if(aux1->info.cod_solicitacao == cod)
               {
                flag = 1;
                break;
               }
               aux = aux1;
               aux1 = aux1 -> prox;
            }
            if (flag == 0)
            {
                printf("\nO código não foi encontrado!\n");
            }
            else
            {
                if(aux == NULL){
                    apag = aux1;
                    aux1 = aux1->prox;
                    l->inicio = aux1;
                    free(apag);
                }
                else{
                    if (flag == 1)
                    {
                        apag= aux1;
                        aux1 = aux1 -> prox;
                        aux->prox= aux1;
                        free(apag); 
                    }
                } 
                printf("\nSolicitação removida com sucesso!\n");
            }
        }
    }
}

//Função de Buscar um elemento na lista baseado no código passado por parâmetro, retornando o ponteiro apontando pra aquele elemento
no *BuscaLista(lista *l, int cod)
{
    if (l == NULL || l->inicio == NULL)
    {
        return NULL;
    }
    else
    {
        no *aux;
        aux = l->inicio;
        while (aux != NULL && aux->info.cod_solicitacao != cod)
        {
            aux = aux->prox;
        }
        if (aux != NULL && aux->info.cod_solicitacao == cod)
        {
            return aux;
        }
        return NULL; 
    }
}

//Função de Printar todas as informações de um elemento, utilizando um ponteiro apontando pra ele
void PrintaInfo(no *elemento)
{
    printf("\n\tCódigo de solicitação: %d",elemento -> info.cod_solicitacao);
    printf("\n\tCódigo de equipamento: %s",elemento -> info.cod_equipamento);
    printf("\n\tNome do equipamento: %s", elemento -> info.nome_equipamento);
    printf("\n\tPrioridade do equipamento: %d",elemento -> info.prioridade);
    printf("\n\tPeríodo do equipamento: %d dias\n", elemento -> info.periodo);
}

//Consulta uma solicitação baseado no seu código de solicitação, utilizando conjuntamente as funções de BuscaLista e PrintaInfo
void consulta_sol(lista *l)
{
    if (VerificaLista(l))
    {
        printf("\nErro: A lista de solicitações está vazia!\n");
    }
    else
    {
        int cod;
        no *aux;
        printf("\n\tForneça o código de solicitação do equipamento desejado (ou -1 para cancelar): ");
        cod = ler_inteiro();
        
        if (cod == -1)
        {
            printf("\n\tOperação cancelada!\n");
        }
        else
        {
            aux = BuscaLista(l,cod);
            if (aux == NULL)
            {
               printf("\n\tO código fornecido não existe.\n");
            }
            else
            {
                PrintaInfo(aux);
            }
        }
    }
}

void AlteraPriPe(lista *l, no *aux);

void OPP(lista *l)
{
    if(VerificaLista(l))
    {
        printf("\nLista vazia!\n");
        system("pause");
    }
    else
    {
        int input,cod;
        no *aux;
        do
        {
            system("cls");
            printf("\t1 - Digite o código:\n");
            printf("\t2 - Voltar ao menu principal (ou -1):\n");
            printf("\tDigite sua opção: ");
            input = ler_inteiro();
            if (input == 1)
            {
                int flag = 1;
                do{
                    printf("\nDigite o código de solicitação, ou se quiser cancelar digite -1 (ou 0): ");
                    cod = ler_inteiro();
                    if(cod == 0 || cod == -1){
                        flag = 0;
                        break;
                    }
                    aux = BuscaLista(l,cod);
                    if (aux == NULL)
                    {
                        printf("\nCódigo não foi encontrado\n");
                    }
                }while(aux == NULL);
                
                if(flag == 1 && aux != NULL){
                    AlteraPriPe(l,aux);
                }
            }
            if ((input < 1 || input > 2) && input != -1) {
                printf("Erro: Opção inválida! Digite 1 ou 2.\n");
                system("pause");
            }
        } while (input != 2 && input != -1);
    }
}

void AlteraPriPe(lista *l, no *aux) {
    if (VerificaLista(l)) {
        printf("\nErro: A lista de solicitações está vazia!\n");
        system("pause");
    } 
    else {
        int control, troca, a = 1;
        int cancelar;
        int max_dias;
        
        do {
            cancelar = 0;
            system("cls");
            printf("\n--- Menu de Alteração ---");
            printf("\n1 - Alterar prioridade");
            printf("\n2 - Alterar período");
            printf("\n3 - Alterar prioridade e período");
            printf("\n4 - Sair (ou -1)");
            printf("\nDigite sua opção: ");
            control = ler_inteiro();

            switch (control) {
                case 1:
                    do {
                        printf("\nDigite a nova prioridade (1-3) ou -1 para cancelar: ");
                        troca = ler_inteiro();
                        
                        if (troca == -1) {
                            cancelar = 1;
                        } else if (troca < 1 || troca > 3) {
                            printf("Erro: Prioridade fora do intervalo permitido (1 a 3)!\n");
                        } else if (troca == aux->info.prioridade) {
                            printf("Erro: Essa já é a prioridade atual!\n");
                        }

                    } while (cancelar == 0 && (troca < 1 || troca > 3 || troca == aux->info.prioridade));
                    
                    if (cancelar == 0) {
                        int novo_per = aux->info.periodo;
                        
                        if (troca == 1 && aux->info.periodo > 7) {
                            printf("\nO período atual excede o limite permitido para a prioridade 1 (1-7 dias)!");
                            do {
                                printf("\nDigite o novo período (1-7 dias) ou -1 para cancelar: ");
                                novo_per = ler_inteiro();
                                if (novo_per == -1) {
                                    cancelar = 1;
                                } else if (novo_per < 1 || novo_per > 7) {
                                    printf("Erro: O período deve ser entre 1 e 7 dias!\n");
                                }
                            } while (cancelar == 0 && (novo_per < 1 || novo_per > 7));
                        } else if (troca == 2 && aux->info.periodo > 15) {
                            printf("\nO período atual excede o limite permitido para a prioridade 2 (1-15 dias)!");
                            do {
                                printf("\nDigite o novo período (1-15 dias) ou -1 para cancelar: ");
                                novo_per = ler_inteiro();
                                if (novo_per == -1) {
                                    cancelar = 1;
                                } else if (novo_per < 1 || novo_per > 15) {
                                    printf("Erro: O período deve ser entre 1 e 15 dias!\n");
                                }
                            } while (cancelar == 0 && (novo_per < 1 || novo_per > 15));
                        }

                        if (cancelar == 0) {
                            aux->info.prioridade = troca;
                            aux->info.periodo = novo_per;
                            printf("Prioridade atualizada com sucesso!\n");
                        } else {
                            printf("Alteração cancelada!\n");
                        }
                    } else {
                        printf("Alteração cancelada!\n");
                    }
                    system("pause");
                    break;

                case 2:
                    if (aux->info.prioridade == 1) {
                        max_dias = 7;
                    } else if (aux->info.prioridade == 2) {
                        max_dias = 15;
                    } else {
                        max_dias = 20;
                    }

                    do {
                        printf("\nDigite o novo período (1-%d dias) ou -1 para cancelar: ", max_dias);
                        troca = ler_inteiro();
                        
                        if (troca == -1) {
                            cancelar = 1;
                        } else if (troca < 1 || troca > max_dias) {
                            printf("Erro: Período fora do limite permitido para a prioridade %d!\n", aux->info.prioridade);
                        } else if (troca == aux->info.periodo) {
                            printf("Erro: Esse já é o período atual!\n");
                        }
                        
                    } while (cancelar == 0 && (troca < 1 || troca > max_dias || troca == aux->info.periodo));
                    
                    if (cancelar == 0) {
                        aux->info.periodo = troca;
                        printf("Período atualizado com sucesso!\n");
                    } else {
                        printf("Alteração cancelada!\n");
                    }
                    system("pause");
                    break;

                case 3:
                    do {
                        int nova_pri, novo_per;
                        
                        printf("\nDigite a nova prioridade (1-3) ou -1 para cancelar: ");
                        nova_pri = ler_inteiro();
                        
                        if (nova_pri == -1) {
                            cancelar = 1;
                            break;
                        }

                        if (nova_pri < 1 || nova_pri > 3) {
                            printf("Erro: Prioridade fora do intervalo (1 a 3)!\n");
                            continue; 
                        }

                        if (nova_pri == 1) {
                            max_dias = 7;
                        } else if (nova_pri == 2) {
                            max_dias = 15;
                        } else {
                            max_dias = 20;
                        }
                        
                        printf("Digite o novo período (1-%d dias) ou -1 para cancelar: ", max_dias);
                        novo_per = ler_inteiro();

                        if (novo_per == -1) {
                            cancelar = 1;
                            break;
                        }

                        if (novo_per < 1 || novo_per > max_dias) {
                            printf("Erro: Período fora do limite permitido para essa prioridade!\n");
                            continue; 
                        }

                        if (nova_pri == aux->info.prioridade && novo_per == aux->info.periodo) {
                            printf("Erro: A prioridade e o período informados são exatamente iguais aos atuais!\n");
                            continue; 
                        }

                        aux->info.prioridade = nova_pri;
                        aux->info.periodo = novo_per;
                        printf("Prioridade e período atualizados com sucesso!\n");
                        break; 
                        
                    } while (1); 
                    
                    if (cancelar == 1) {
                        printf("Alteração cancelada!\n");
                    }
                    system("pause");
                    break;

                case 4:
                case -1:
                    a = 0;
                    break;

                default:
                    printf("Opção inválida!\n");
                    system("pause");
                    break;
            }
        } while (a != 0);
    }
}

//Essa função ordena a lista auxiliar com base na forma que as manutenções tem de ser exibidas
no *InsereManun(no *aux, no *antigo)
{
    int flag = 0;
    no *novo,*aux1,*aux2;
    novo = (no*)malloc(sizeof(no));
    novo -> info = aux -> info;
    aux1 = NULL;
    aux2 = antigo;
    while (aux2 != NULL)
    {
        flag = 0;
        if (novo -> info.prioridade < aux2 -> info.prioridade)
        {
            flag = 1;
        }
        else if (novo -> info.prioridade == aux2 -> info.prioridade)
        {
            if (novo -> info.periodo < aux2 -> info.periodo )
            {
                flag = 1;
            }
            else if (novo -> info.periodo == aux2 -> info.periodo)
            {
                if (novo -> info.cod_solicitacao < aux2 -> info.cod_solicitacao)
                {
                    flag = 1;
                }
            }
        }
        if (flag == 1)
        {
            break;
        }
        aux1 = aux2;
        aux2 = aux2 -> prox;
    }
    if (aux1 == NULL)
    {
        novo -> prox = aux2;
        antigo = novo;
        return antigo;
    }
    else
    {
        novo -> prox = aux2;
        aux1 -> prox = novo;
    }
    return antigo;
}

void ExibirTudo(lista *l);

//Essa função primeiramente recebe a lista original, cria uma nova e chama a outra função pra ordenar essa nova lista baseado nos parâmetros, e por ultimo printa e da free nela
void ExibirManun(lista *l)
{
    if(VerificaLista(l)){
        printf("\nErro: A lista de solicitações está vazia!\n");
    }
    else
    {
        lista *l2 = Inicialista();
        l2 = Criarlista();
        no *aux = l -> inicio;
        while (aux != NULL)
        {
            l2 -> inicio = InsereManun(aux, l2 -> inicio);
            aux = aux -> prox;
        }
        ExibirTudo(l2);
        liberalista(l2);
    }
}

//Função que printa todas as solicitações
void ExibirTudo(lista *l)
{   
    if(VerificaLista(l)){
        printf("\nErro: A lista está vazia!\n");
    }
    else{
        no *aux;
        aux = l -> inicio;
        while (aux != NULL)
        {
            PrintaInfo(aux);
            aux = aux -> prox;
            printf("\n");
        }
    }
}