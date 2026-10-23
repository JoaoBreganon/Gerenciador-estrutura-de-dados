# 🛠️ Sistema de Gerenciamento de Solicitações de Manutenção

Sistema desenvolvido em **Linguagem C** para o controle, cadastro e priorização de solicitações de manutenção de equipamentos utilizando **Listas Simplesmente Encadeadas Dinâmicas**.

---

## 📋 Sobre o Projeto

O programa gerencia uma fila/lista de ordens de serviço de equipamentos industriais ou comerciais. As solicitações são armazenadas de forma dinâmica na memória e mantidas ordenadas pelo código de solicitação, permitindo também a geração de relatórios ordenados por critérios de urgência (prioridade e prazo).

Todo o fluxo de entrada de dados conta com **tratamento de buffer**, **validação contra caracteres inválidos** em leituras numéricas e **opção de cancelamento (`-1`)** em tempo real durante qualquer etapa das operações.

---

## ⚙️ Funcionalidades

* **Inserção Ordenada (`inserirSolicitacao` / `InsereOrdenado`):** Cadastra uma nova solicitação mantendo a lista principal ordenada de forma crescente pelo `cod_solicitacao`.
* **Remoção de Solicitação (`Remove`):** Remove um elemento específico da lista (no início, meio ou fim) a partir do código de solicitação e libera a memória correspondente.
* **Consulta Individual (`consulta_sol` / `BuscaLista`):** Realiza uma busca na lista pelo código da solicitação e exibe todos os detalhes do equipamento.
* **Alteração de Prioridade e Período (`OPP` / `AlteraPriPe`):** Permite atualizar a prioridade, o período de manutenção ou ambos. Caso a nova prioridade tenha um teto de dias menor que o período atual do equipamento, o sistema exige o reajuste automático do prazo.
* **Relatório por Ordem de Prioridade (`ExibirManun` / `InsereManun`):** Cria uma lista auxiliar temporária ordenada por três critérios de desempate:
  1. **Maior urgência** (Prioridade 1 > 2 > 3)
  2. **Menor prazo** (`periodo` em dias)
  3. **Menor código de solicitação** (`cod_solicitacao`)
  *Após exibir os dados ordenados, a lista auxiliar é totalmente desalocada da memória.*
* **Listagem Geral (`ExibirTudo`):** Exibe todas as solicitações cadastradas na ordem padrão da lista principal (por código de solicitação).

---

## 📏 Regras de Negócio e Validações

| Campo | Formato / Regra | Validação Aplicada |
| :--- | :--- | :--- |
| **Código de Solicitação** | `1000` a `9999` (`int`) | Impede códigos duplicados na lista e valores fora do intervalo. |
| **Código do Equipamento** | `AAA111` (`char[7]`) | Exige exatamente 3 letras seguidas de 3 números (6 caracteres). |
| **Nome do Equipamento** | Até 20 caracteres (`char[21]`) | Não permite nomes em branco e limpa excessos no buffer. |
| **Prioridade** | `1`, `2` ou `3` (`int`) | `1` (Alta), `2` (Média), `3` (Baixa). |
| **Período (Dias)** | Depende da prioridade (`int`) | • **Prioridade 1:** 1 a 7 dias<br>• **Prioridade 2:** 1 a 15 dias<br>• **Prioridade 3:** 1 a 20 dias |

### 🛡️ Proteções de Entrada
* **Cancelamento de Operação:** Digitar `-1` em qualquer etapa de cadastro, remoção, busca ou alteração aborta a ação atual com segurança (controlado via flags e blocos condicionais, sem interrupções abruptas).
* **Blindagem contra Letras (`ler_inteiro`):** Caso o usuário digite letras em campos numéricos, o buffer (`stdin`) é limpo automaticamente e a entrada é solicitada novamente, evitando loops infinitos do `scanf`.

---

## 🧱 Estrutura de Dados

O projeto utiliza três estruturas principais:

```c
typedef struct manutencao {
    int cod_solicitacao;
    char cod_equipamento[7];
    char nome_equipamento[21];
    int prioridade;
    int periodo;
} Manutencao;

typedef struct no {
    Manutencao info;
    struct no* prox;
} no;

typedef struct lista {
    no* inicio;
} lista;