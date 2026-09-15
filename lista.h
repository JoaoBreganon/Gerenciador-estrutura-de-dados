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


no* AuxInsere(no*antigo,Manutencao aux){
    no *novo;
    novo=(no*)malloc(sizeof(no));
    novo->info=aux;
    novo->prox=antigo;
    return novo;
}


void inserirSolitacao(lista*l){
    Manutencao aux;
    no *Naux;
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
    
    Naux=l->inicio;
    while (aux.cod_solicitacao)
    {
        /* code */
    }
    
    l->inicio= AuxInsere(l->inicio, aux);

}