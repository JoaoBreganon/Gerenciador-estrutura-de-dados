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
    printf("Digite o código de solicitação:");
    scanf("%d",aux.cod_solicitacao);
   
    printf("\nDigite o código de equipamento:");
    fgets(aux.cod_equipamento, sizeof(aux.cod_equipamento), stdin);

    printf("\nDigite o nome do equipamento:");
    fgets(aux.nome_equipamento, sizeof(aux.nome_equipamento), stdin);
    
    printf("\nDigite a prioridade:");
    scanf("%d",aux.prioridade);
    
    printf("\nDigite o período necessário para manutenção:");
    scanf("%d",aux.periodo);
    
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
    return aux;
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