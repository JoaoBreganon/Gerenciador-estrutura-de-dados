typedef struct manutencao{
    int cod_solicitacao;
    char cod_equipamento[6];
    char nome_equipamento[20];
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
    free(L->inicio);
    return NULL;
}

//Função de inserção ordenada baseada no código de solicitação 
no *InsereOrdenado(no *antigo,Manutencao var )
{
    no *novo,*aux,*aux1;
    novo=(no*)malloc(sizeof(no));
    novo->info=var;
    novo = antigo;
    aux = NULL;
    aux1= antigo;
    while (aux1 !=NULL && var.cod_solicitacao < aux1->info.cod_solicitacao)
    {
        aux = aux1;
        aux1 = aux1->prox;
    }
    if(aux == NULL){
        novo->prox=aux1;
        antigo = novo;
        return antigo;
    }
    aux->prox= novo;
    novo->prox= aux1;
    return antigo;

}

//Função de Inserção de uma Solicitação, em que se pede as informações da tal
void inserirSolitacao(lista*l){
    Manutencao aux;

    do{
        printf("Digite o código de solicitação:");
        scanf("%d",aux.cod_solicitacao);
    }while(aux.cod_solicitacao >= 1000 && aux.cod_solicitacao <= 9999);

    int contnum=0,contletter=0;

    do{
        printf("\nDigite o código de equipamento no formato adequado exemplo(AAA111):");
        fgets(aux.cod_equipamento, sizeof(aux.cod_equipamento), stdin);
        aux.cod_equipamento[strcspn(aux.cod_equipamento,"\n")]= '\0';
        for (int i = 0; i < 3 ; i++) {
            if(isalpha(aux.cod_equipamento[i])){
                contletter++;
            }
        }
        for (int i = 3; i < 6 ; i++) {
            if (isdigit(aux.cod_equipamento[i])){
                contnum ++;
            }
        }
    }while(contnum != 3 && contletter!= 3);

    printf("\nDigite o nome do equipamento:");
    fgets(aux.nome_equipamento, sizeof(aux.nome_equipamento), stdin);
    aux.nome_equipamento[strcspn(aux.nome_equipamento,"\n")]= '\0';
    

    do{
        printf("\nDigite a prioridade:");
        scanf("%d",aux.prioridade);
    }while(aux.prioridade <= 3 && aux.prioridade > 0);

    switch(aux.prioridade)
    {
    case 1:
        do{
            printf("\nDigite o período necessário para manutenção(1-7 dias):");
            scanf("%d",aux.periodo);
        }while(aux.periodo<1 && aux.periodo>7);
        break;

    case 2:
        do{
            printf("\nDigite o período necessário para manutenção(1-15 dias):");
            scanf("%d",aux.periodo);
        }while(aux.periodo<1 && aux.periodo>15);
        break;
    
    case 3:
        do{
            printf("\nDigite o período necessário para manutenção(1-20 dias):");
            scanf("%d",aux.periodo);
        }while(aux.periodo<1 && aux.periodo>20);
        break;
    
    default:
        break;
    }  
    
    
    l->inicio = InsereOrdenado(l->inicio,aux);
}

//Função de remoção de um elemento na lista baseado no código de solicitação, utilizando a lógica de remoção em qualquer lugar
void Remove(lista* l){
    if(VerificaLista(l)){
        //Temos que lembrar de implementar em todos os listas vazias a volta pro programa original
        printf("\tLISTA VAZIA!!!!");
    }
    else{
        int cod,flag=0;
        printf("Digite o código de solicitação que deseja remover:");
        scanf("%d",&cod);
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
        if(aux == NULL){
            apag = aux1;
            aux1 = aux1->prox;
            free(apag);
        }
        else{
            apag= aux1;
            aux1 = aux1 -> prox;
            aux->prox= aux1;
            free(apag); 
        }
        
    }
}

//Função de Buscar um elemento na lista baseado no código passado por parâmetro, retornando o ponteiro apontando pra aquele elemento
no *BuscaLista(lista *l,int cod)
{
    no *aux;
    aux = l -> inicio;
    while (aux != NULL && aux->info.cod_solicitacao != cod)
    {
        aux = aux -> prox;
    }
    if(aux -> info.cod_solicitacao == cod){
        return aux;
    }
    return NULL;
    
}

//Função de Printar todas as informações de um elemento, utilizando um ponteiro apontando pra ele
void PrintaInfo(no *elemento)
{
    printf("\n\tCódigo de solicitação: %d",elemento -> info.cod_solicitacao);
    printf("\n\tCódigo de equipamento %c",elemento -> info.cod_equipamento);
    printf("\n\tNome do equipamento %c", elemento -> info.nome_equipamento);
    printf("\n\tPrioridade do equipamento %d",elemento -> info.prioridade);
    printf("\n\tPeríodo do equipamento %d", elemento -> info.periodo);
    
}

//Consulta uma solicitação baseado no seu código de solicitação, utilizando conjuntamente as funções de BuscaLista e PrintaInfo
void consulta_sol(lista *l)
{
    if (VerificaLista(l))
    {
        printf("\tLISTA VAZIA!!!!");
    }
    else
    {
        int cod;
        no *aux;
        printf("\n\tForneça o código de solicitação do equipamento desejado:");
        scanf("%d",&cod);
        aux = BuscaLista(l,cod);
        if (aux == NULL)
        {
           printf("\n\tO código fornecido não existe.");
        }
        else
        {
            PrintaInfo(aux);
        }
    }
}

void OPP(lista *l)
{
    int input,cod;
    no *aux;
    do
    {
        printf("\t1 - Digite o código:\n");
        printf("\t2 - Voltar ao menu principal\n:");
        printf("\tDigite seu input:");
        scanf("%d",&input);
        if (input == 1)
        {
            do{
                printf("\nDigite o código de solicitação:");
                scanf("%d",&cod);
                aux = BuscaLista(l,cod);
                if (aux == NULL)
                {
                    printf("\nCódigo não foi encontrado");
                }
            }while(aux == NULL);
            
            AlteraPriPe(l,aux);
        }
        if (input < 1 && input > 2)
        {
            printf("O seu input digitado foi errado.");
        }
    } while (input != 2);
    
}

//terminar essa função
void AlteraPriPe(lista *l,no *aux){
    if(!VerificaLista(l)){
        printf("\tLISTA VAZIA!!!!");
    }
    else{
        int control,troca,a = 1;
        no* aux;
        do
        {
            printf("Deseja alterar");
            printf("\n1-Alterar prioridade");
            printf("\n2-Alterar periodo");
            printf("\n3-Alterar prioridade e periodo");
            printf("\n4- Sair");
            printf("\nDigite sua opção:");
            scanf("%d",&control);

            switch (control){
            case 1:
                printf("\nDigite a nova prioridade:");
                scanf("%d",&troca);
                if(troca == aux->info.prioridade){
                    printf("Esse já é o código atual ou está fora do intervalo (1-3)");
                    do
                    {
                        printf("Digite uma nova prioridade:");
                        scanf("%d",&troca);
                    } while (troca == aux->info.prioridade && (troca < 1 || troca > 3));

                }
                else{
                    aux->info.prioridade = troca;
                }
                break;

            case 2:
                printf("\nDigite o novo período:");
                scanf("%d",&troca);
                if(troca == aux->info.periodo){
                    printf("Esse já é o código atual");
                    do
                    {
                        printf("Digite um novo período:");
                        scanf("%d",&troca);
                    } while (troca == aux->info.periodo);
                }
                else{
                    switch(aux -> info.prioridade)
                    {
                    case 1:
                        do{
                            printf("\nDigite o período necessário para manutenção(1-7 dias):");
                            scanf("%d",aux -> info.periodo);
                        }while(aux -> info.periodo<1 && aux -> info.periodo>7);
                        break;

                    case 2:
                        do{
                            printf("\nDigite o período necessário para manutenção(1-15 dias):");
                            scanf("%d",aux -> info.periodo);
                        }while(aux -> info.periodo<1 && aux -> info.periodo>15);
                        break;

                    case 3:
                        do{
                            printf("\nDigite o período necessário para manutenção(1-20 dias):");
                            scanf("%d",aux -> info.periodo);
                        }while(aux -> info.periodo<1 && aux -> info.periodo>20);
                        break;

                    default:
                        break;
                    }

                    
                }
                break;
            case 3:
                do{
                    printf("\nDigite a nova prioridade:");
                    scanf("%d",aux -> info.prioridade);
                }while(aux -> info.prioridade <= 3 && aux -> info.prioridade > 0);

                switch(aux -> info.prioridade)
                {
                case 1:
                    do{
                        printf("\nDigite o período necessário para manutenção(1-7 dias):");
                        scanf("%d",aux -> info.periodo);
                    }while(aux -> info.periodo<1 && aux -> info.periodo>7);
                    break;

                case 2:
                    do{
                        printf("\nDigite o período necessário para manutenção(1-15 dias):");
                        scanf("%d",aux -> info.periodo);
                    }while(aux -> info.periodo<1 && aux -> info.periodo>15);
                    break;

                case 3:
                    do{
                        printf("\nDigite o período necessário para manutenção(1-20 dias):");
                        scanf("%d",aux -> info.periodo);
                    }while(aux -> info.periodo<1 && aux -> info.periodo>20);
                    break;

                default:
                    break;
                }
                break;
            case 4:
                a = 0;
                break;
            default:
                printf("Seu código está inválido");
                break;
            }
        } while (a != 0);
    }
}


//Função que printa todas as solicitações
void ExibirTudo(lista *l)
{
    no *aux;
    aux = l -> inicio;
    while (aux != NULL)
    {
        PrintaInfo(aux);
        aux = aux -> prox;
        printf("\n");
    }
    

}