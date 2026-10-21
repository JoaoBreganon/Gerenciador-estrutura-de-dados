typedef struct manutencao{
    int cod_solicitacao;
    char cod_equipamento[7];
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

void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
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

    do {
        flag = 1; // Reseta a flag a cada nova tentativa
        percorre = l->inicio;
        
        printf("Digite o código de solicitação (1000 a 9999): ");
        scanf("%d", &aux.cod_solicitacao);
        
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
        
    // Repete se fora do intervalo OU se a flag for 0 (repetido)
    } while ((aux.cod_solicitacao < 1000 || aux.cod_solicitacao > 9999) || flag == 0);
    
    int contletter,contnum;
    
    do {
        contletter = 0;
        contnum = 0;
        limpar_buffer();
        printf("\nDigite o código de equipamento (ex: AAA111): ");
        fgets(aux.cod_equipamento, sizeof(aux.cod_equipamento), stdin);
        aux.cod_equipamento[strcspn(aux.cod_equipamento, "\n")] = '\0';
        
        for (int i = 0; i < 3; i++) {
            if (isalpha(aux.cod_equipamento[i])) contletter++;
        }
        for (int i = 3; i < 6; i++) {
            if (isdigit(aux.cod_equipamento[i])) contnum++;
        }

        if (contnum != 3 || contletter != 3) {
            printf("Erro: O formato deve conter exatamente 3 letras seguidas de 3 números!\n");
        }
    } while (contnum != 3 || contletter != 3);

    limpar_buffer();
    printf("\nDigite o nome do equipamento:");
    fgets(aux.nome_equipamento, sizeof(aux.nome_equipamento), stdin);
    aux.nome_equipamento[strcspn(aux.nome_equipamento,"\n")]= '\0';
    
    do {
        printf("\nDigite a prioridade (1 a 3): ");
        scanf("%d", &aux.prioridade);
        
        if (aux.prioridade < 1 || aux.prioridade > 3) {
            printf("Erro: A prioridade deve estar entre 1 e 3!\n");
        }
    } while (aux.prioridade < 1 || aux.prioridade > 3);

    switch(aux.prioridade)
    {
    case 1:
        do{
            printf("\nDigite o período necessário para manutenção(1-7 dias):");
            scanf("%d",&aux.periodo);
        }while(aux.periodo<1 || aux.periodo>7);
        break;

    case 2:
        do{
            printf("\nDigite o período necessário para manutenção(1-15 dias):");
            scanf("%d",&aux.periodo);
        }while(aux.periodo<1 || aux.periodo>15);
        break;
    
    case 3:
        do{
            printf("\nDigite o período necessário para manutenção(1-20 dias):");
            scanf("%d",&aux.periodo);
        }while(aux.periodo<1 || aux.periodo>20);
        break;
    
    default:
        break;
    }  
    
    
    l->inicio = InsereOrdenado(l->inicio,aux);
}

//Função de remoção de um elemento na lista baseado no código de solicitação, utilizando a lógica de remoção em qualquer lugar
void Remove(lista* l){
    if(VerificaLista(l)){
        printf("\nErro: A lista de solicitações está vazia!\n");
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
        if (flag == 0)
        {
            printf("O código não foi encontrado!");
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
        }
    }
}

//Função de Buscar um elemento na lista baseado no código passado por parâmetro, retornando o ponteiro apontando pra aquele elemento
no *BuscaLista(lista *l,int cod)
{
    if (l == NULL || l -> inicio == NULL)
    {
        printf("\n\tLista vazia!");
        return NULL;
    }
    else
    {
        no *aux;
        aux = l -> inicio;
        while (aux != NULL && aux->info.cod_solicitacao != cod)
        {
            aux = aux -> prox;
        }
        if( aux != NULL && aux -> info.cod_solicitacao == cod)
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
    printf("\n\tCódigo de equipamento %s",elemento -> info.cod_equipamento);
    printf("\n\tNome do equipamento %s", elemento -> info.nome_equipamento);
    printf("\n\tPrioridade do equipamento %d",elemento -> info.prioridade);
    printf("\n\tPeríodo do equipamento %d", elemento -> info.periodo);
    
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

void AlteraPriPe(lista *l, no *aux);

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
       if (input < 1 || input > 2) {
            printf("Erro: Opção inválida! Digite 1 ou 2.\n");
        }
    } while (input != 2);
    
}


void AlteraPriPe(lista *l, no *aux) {
    if (VerificaLista(l)) {
        printf("\nErro: A lista de solicitações está vazia!\n");
        return; 
    }

    int control, troca, a = 1;
    do {
        printf("\n--- Menu de Alteração ---");
        printf("\n1 - Alterar prioridade");
        printf("\n2 - Alterar período");
        printf("\n3 - Alterar prioridade e período");
        printf("\n4 - Sair");
        printf("\nDigite sua opção: ");
        scanf("%d", &control);

        switch (control) {
            case 1:
                do {
                    printf("\nDigite a nova prioridade (1-3): ");
                    scanf("%d", &troca);
                    
                    if (troca < 1 || troca > 3) {
                        printf("Erro: Prioridade fora do intervalo permitido (1 a 3)!\n");
                    } else if (troca == aux->info.prioridade) {
                        printf("Erro: Essa já é a prioridade atual!\n");
                    }
                    
                } while (troca < 1 || troca > 3 || troca == aux->info.prioridade);
                
                aux->info.prioridade = troca;
                printf("Prioridade atualizada com sucesso!\n");
                break;

            case 2:
                do {
                    int max_dias = (aux->info.prioridade == 1) ? 7 : (aux->info.prioridade == 2) ? 15 : 20;
                    
                    printf("\nDigite o novo período (1-%d dias): ", max_dias);
                    scanf("%d", &troca);
                    
                    if (troca < 1 || troca > max_dias) {
                        printf("Erro: Período fora do limite permitido para a prioridade %d!\n", aux->info.prioridade);
                    } else if (troca == aux->info.periodo) {
                        printf("Erro: Esse já é o período atual!\n");
                    }
                    
                } while (troca < 1 || troca > ((aux->info.prioridade == 1) ? 7 : (aux->info.prioridade == 2) ? 15 : 20) || troca == aux->info.periodo);
                
                aux->info.periodo = troca;
                printf("Período atualizado com sucesso!\n");
                break;

            case 3:
                do {
                    int nova_pri, novo_per, max_dias;
                    
                    printf("\nDigite a nova prioridade (1-3): ");
                    scanf("%d", &nova_pri);
                    
                    if (nova_pri < 1 || nova_pri > 3) {
                        printf("Erro: Prioridade fora do intervalo (1 a 3)!\n");
                        continue; 
                    }

                    max_dias = (nova_pri == 1) ? 7 : (nova_pri == 2) ? 15 : 20;
                    
                    printf("Digite o novo período (1-%d dias): ", max_dias);
                    scanf("%d", &novo_per);

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
                break;

            case 4:
                a = 0;
                break;

            default:
                printf("Opção inválida!\n");
                break;
        }
    } while (a != 0);
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
        no *apag;
        while (l2->inicio != NULL)
        {
            apag = l2->inicio;
            l2->inicio = l2->inicio->prox;
            free(apag);
        }
        free(l2);
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

//Falta terminar o main, dar free no que for necessario, deixar o programa mais agradavel e corrigir bugs como um geral. 