#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "test.h"

void menu() { 
      printf("1 - Insira o produto\n");
      printf("2 - Remova o produto\n");
      printf("3 - Buscar o produto\n");
      printf("4 - Alterar o produto\n");
      printf("5 - Mostra os produtos com maior estoque\n");
      printf("6 - Mostra os produtos com maior notas\n");
      printf("7 - Mostra os produtos com maior preco/menor preco\n");
      printf("8 - Mostrar produtos com maior preco/menor preco\n");
      printf("9 - Comprar produto\n");
      printf("10 - Sair\n");
      printf("Entre com a opcao desejada: \n");
}

void erase(noarv *arvore){
	if (arvore){
		erase(arvore->esquerda);
		erase(arvore->direita);
		free(arvore);
		arvore = NULL;
	}
}

noarv* busca(noarv *arvore, int chave){

    if (!arvore){
        // se a arvore está vazia, retorna NULL
        return NULL; 
    }

    if (arvore->p.id == chave){
         // se o valor chave for igual ao valor da raiz,
         // retorna o ponteiro para a raiz.
        return arvore;
    }

    // se a chave não foi encontrada,
    // a busca continuará p/ direta ou esquerda.
    if (arvore->p.id < chave){ 
        return busca(arvore->direita, chave);
    }
    else{
        return busca(arvore->esquerda, chave);
    }
}


noarv * acharmaior(noarv *arvore){
	if(!arvore){
		return NULL;
    }
	else if (!arvore->direita){
		return arvore;
    }
	else{
		return acharmaior(arvore->direita);
    }
}

// calcula a altura da arvore (maior caminho da raiz até um nó folha).
int altura(noarv *arvore){ 
    if(arvore == NULL){
        return -1;
    }
    
    int altura_esq = altura(arvore->esquerda);

    int altura_dir = altura(arvore->direita);

    if(altura_esq > altura_dir){
        // incrementa 1 toda vez que a chamada recursiva acontece,
        // obtendo a altura da subarvore a esquerda
        return altura_esq + 1; 
    }else{
        // incrementa 1 toda vez que a chamada recursiva acontece, 
        // obtendo a altura da subarvore a direita
        return altura_dir + 1; 
    }
}

/**
 * Retorna o balanceamento da árvore através de recursão
 * Percorre toda a subárvore a esquerda e a direita, calculando a diferença entre ambas
 * Balanceamento = (Altura Direita) - (Altura Esquerda)
 * Se o resultado balanceamento for diferente do intervalo [-1,1], a árvore está desbalanceada
*/
int fatorBalanceamento(noarv *arvore){
    return altura(arvore->direita) - altura(arvore->esquerda);
}

// Função de rotação da árvore para a direita
noarv *rotacaoEsquerda(noarv *arvore){
     // cria uma variável do tipo filho que recebe
     // o conteúdo do nó da árvore a direita
    noarv *nofilho = arvore->direita;
    // o nó da árvore a direita recebe o nó filho a esquerda
    arvore->direita = nofilho->esquerda; 
    // o nó filho a esquerda passa a apontar
    // para o conteúdo da raíz da subarvore (ou arvore)
    nofilho->esquerda = arvore;
    // retorna o novo nó 
    return nofilho; 
}

// Função de rotação dos nós da árvore para a direita
noarv *rotacaoDireita(noarv *arvore){
    // cria uma variável do tipo filho que recebe
     // o conteúdo do nó da árvore a esquerda
    noarv *nofilho = arvore->esquerda;
    // o nó da árvore a esquerda recebe o nó filho a direita
    arvore->esquerda = nofilho->direita;
    // o nó filho a direita passa a apontar
    // para o conteúdo da raíz da subarvore (ou arvore)
    nofilho->direita = arvore;
    // retorna o novo nó 
    return nofilho;
}

// Balanceia a árvore
noarv* balanceamentoArvore(noarv *arvore){

    int balanceamento = fatorBalanceamento(arvore); 

    if(balanceamento<-1){ // verifica se a subárvore a esquerda está desbalanceada
        if(fatorBalanceamento(arvore->esquerda) > 0){
            // Rotação dupla
            // Essa função rotaciona uma subárvore que esteja com nós desbalanceados a direita
            arvore->esquerda =  rotacaoEsquerda(arvore->esquerda);
        }
        // Função de rotação da arvore para a direita
        arvore = rotacaoDireita(arvore);
    }else if (balanceamento > 1){ // verifica se a subárvore a direita está desbalanceada
        if(fatorBalanceamento(arvore->direita) < 0){
            // Rotação dupla
            // Essa função rotaciona uma subárvore que esteja com nós desbalanceados a esquerda
            arvore->direita = rotacaoDireita(arvore->direita);
        }
        // Função de rotação da arvore para a esquerda
        arvore = rotacaoEsquerda(arvore);
    }
    
    return arvore;
}

//parte exibição JOÃO VITOR ALVES DOS REIS 202201697 ALGORITHM 2023 - PATENTED - BUBBLE JAO

//função de inserir item na arvore
noarv *insere(noarv *arvore, int numero, char nomep[], float preco, int quantidade_produto, float nota){ // função de inserir na arvore atualizada para tambem inserir na lista
    if(!arvore){
        arvore = (noarv *)malloc(sizeof(noarv));
        arvore->p.id = numero;
        arvore->p.preco = preco;
        arvore->p.qtd_produto = quantidade_produto;
        arvore->p.nota = nota;
        strcpy(arvore->p.nome_produto, nomep);
        arvore->esquerda = arvore->direita = NULL;
    }
    else{ 
        if(arvore->p.id > numero){
            arvore->esquerda = insere(arvore->esquerda, numero, nomep, preco, quantidade_produto, nota);
        }
        else {
            arvore->direita = insere(arvore->direita, numero, nomep, preco, quantidade_produto, nota);
        }
        arvore = balanceamentoArvore(arvore);   
    }

    return arvore;    
}

LISTA* iniciar_lista(){
    LISTA* lista = (LISTA*)malloc(sizeof(LISTA));
    lista->inicio = NULL;
    lista->fim=NULL;
    lista->tamanho=0;
    
    return lista;
} 

void inserir_na_lista(noarv *arvore, LISTA *lista){ 
    // insere cada nó adicionado na lista
    ELEM *novo_elemento = (ELEM*)malloc(sizeof(ELEM));
    novo_elemento->dado = *arvore;
    novo_elemento->proximo = NULL;

    if(lista->inicio!=NULL){
        lista->fim->proximo = novo_elemento;
    } else {
        lista->inicio = novo_elemento;
       
    }
    lista->fim = novo_elemento;
    lista->tamanho += 1;
}
 
void resetar_lista(ELEM* elemento_lista){ //free na lista inteira
    if(elemento_lista!=NULL){
        resetar_lista(elemento_lista->proximo);
        elemento_lista = NULL;
        free(elemento_lista);
    }
}

void inserir_nos(LISTA *lista, noarv *arvore){ // insere os nós na lista
    if(arvore!=NULL){
        inserir_na_lista(arvore, lista);
        inserir_nos(lista, arvore->esquerda);
        inserir_nos(lista, arvore->direita);
    }
}


noarv * pop(noarv *arvore, int x){

	noarv *tmp;
	if (!arvore){
		return NULL;
    }
	else if (arvore->p.id > x){
		arvore->esquerda = pop(arvore->esquerda, x);
    }
	else if (arvore->p.id < x){
		arvore->direita = pop(arvore->direita, x);
    }
	else if (arvore->esquerda && arvore->direita){
		tmp = acharmaior(arvore->esquerda);
		arvore->p.id = tmp->p.id;
		arvore->esquerda = pop(arvore->esquerda, arvore->p.id);
	}
	else
	{
		tmp = arvore;
		if (!arvore->esquerda){
			arvore = arvore->direita;
        }
		else if (!arvore->direita){
			arvore = arvore->esquerda;
        }
		free(tmp);
	}

	return arvore;
}

// Bubble_sort na lista criada para exibir com base no filtro
void organizar_lista(ELEM* inicio, LISTA* LISTA, int opcao){
    ELEM* atual, *proximo;
    noarv aux;
    int ordenado=0;
    atual = NULL;
    proximo=NULL;
     
     if(inicio!=NULL){
        atual = inicio;
        while (ordenado<LISTA->tamanho) {
            while(atual->proximo!=NULL){
                proximo = atual->proximo;
                //case 1 numero de vendas, case 2 notas, case 3/4 maior/menor preços;
                switch(opcao){
                    case 1:
                        if(atual->dado.p.qtd_produto<proximo->dado.p.qtd_produto){
                            aux = proximo->dado;
                            proximo->dado = atual->dado;
                            atual->dado = aux;
                        }
                        break;
                    case 2:
                        if(atual->dado.p.nota<proximo->dado.p.nota){
                            aux = proximo->dado;
                            proximo->dado = atual->dado;
                            atual->dado = aux;
                        }
                        break;
                    case 3:
                        if(atual->dado.p.preco<proximo->dado.p.preco){
                            aux = proximo->dado;
                            proximo->dado = atual->dado;
                            atual->dado = aux;
                        }
                        break;
                    case 4:
                        if(atual->dado.p.preco>proximo->dado.p.preco){
                            aux = proximo->dado;
                            proximo->dado = atual->dado;
                            atual->dado = aux;
                        }
                        break;
                    case 5:
                        if(atual->dado.p.qtd_produto<proximo->dado.p.qtd_produto){
                            aux = proximo->dado;
                            proximo->dado = atual->dado;
                            atual->dado = aux;
                        }
                        break;
                    case 6:
                        if(atual->dado.p.qtd_produto>proximo->dado.p.qtd_produto){
                            aux = proximo->dado;
                            proximo->dado = atual->dado;
                            atual->dado = aux;
                        }
                        break;
                }
                atual = atual->proximo;
            }
            atual = inicio;
            ordenado += 1;
        }
    }
}

void imprimir_lista(ELEM* elemento){
    ELEM* aux = elemento;
    int continuar=1, count=25;
    while(aux!=NULL && continuar!=0){
        while(count-- && aux!=NULL){
            
            printf("| %d\t %s - R$ %.2f \tQTD: %-6d  NOTA: %.2f\n", aux->dado.p.id, aux->dado.p.nome_produto, aux->dado.p.preco, aux->dado.p.qtd_produto, aux->dado.p.nota);
            aux = aux->proximo;
        }
    }
    if(aux!=NULL){
        printf("\nDeseja exibir a proxima pagina?\nDigite 1 para sim e 0 para nao\n");
        scanf("%d", &continuar);
        count = 25;
    }
}

noarv* alterar_no(noarv* arvore, const char* produto_alterado) {
    int opc, qtd;
    float preco, nota;
    char nome[100];
    noarv* resultado = buscarProduto(arvore, produto_alterado);
    if(resultado != NULL){
    printf("Informacoes do produto\n");
    printf("ID: %d\n", resultado->p.id);
    printf("1 - Nome: %s\n", resultado->p.nome_produto);
    printf("2 - Preço: %.2f\n", resultado->p.preco);
    printf("3 - Quantidade em estoque: %d\n", resultado->p.qtd_produto);
    printf("4 - Nota: %.2f\n", resultado->p.nota);
    printf("==#entra com a opção que deseja alterar#==\n");
    scanf("%d", &opc);

    if (opc == 1) {
        printf("Digite o novo nome: ");
        scanf("%s", nome);
        strcpy(resultado->p.nome_produto, nome);
    }
    else if (opc == 2) {
        printf("Digite o novo preço: ");
        scanf("%f", &preco);
        resultado->p.preco = preco;
    }
    else if (opc == 3) {
        printf("Digite a nova quantidade: ");
        scanf("%d", &qtd);
        resultado->p.qtd_produto = qtd;
    }
    else if (opc == 4) {
        printf("Digite a nova nota: ");
        scanf("%f", &nota);
        resultado->p.nota = nota;
    }
    else {
        printf("Opção inválida.\n");
    }

    return resultado;
    }else{
        printf("produto não encontrado");
        return NULL;
    }
}

noarv* buscarProduto(noarv* arvore, const char* produto_comprado) {
    if (arvore == NULL) {
        return NULL;
    }

    if (strcmp(produto_comprado, arvore->p.nome_produto) == 0) {
        return arvore;
    }

    noarv* encontrado_esquerda = buscarProduto(arvore->esquerda, produto_comprado);
    if (encontrado_esquerda != NULL) {
        return encontrado_esquerda;
    }

    noarv* encontrado_direita = buscarProduto(arvore->direita, produto_comprado);
    if (encontrado_direita != NULL) {
        return encontrado_direita;
    }

    return NULL;
}

noarv* compra(noarv* arvore, const char* produto_alterado) {
    int qtd;
    
    
    noarv* resultado = buscarProduto(arvore, produto_alterado);
    printf("Insira a quantidade de produtos que deseja comprar: ");
    scanf("%d", &qtd);
        if(resultado->p.qtd_produto - qtd >= 0){
            resultado->p.qtd_produto = resultado->p.qtd_produto - qtd;
            printf("PRODUTO COMPRADO COM SUCESSO\n");
            printf("quantidade do produto em estoque: %d\n", resultado->p.qtd_produto);
            
        }else{
            printf("Quantidade de produtos insuficiente no estoque!\nQuantidade total: %d\n", resultado->p.qtd_produto);
        }
    if(resultado->p.qtd_produto == 0){
        pop(arvore, resultado->p.id);
        printf("PRODUTO ZEROU O ESTOQUE\n");
    }

    return resultado;
}
