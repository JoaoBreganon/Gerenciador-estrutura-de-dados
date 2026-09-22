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

void Remove(lista* l){
    if(VerificaLista(l)){
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