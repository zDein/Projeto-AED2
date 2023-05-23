#ifndef TEST_H_INCLUDED
#define TEST_H_INCLUDED

//criando o struct do produto
typedef struct produto{
    int id;
    int qtd_produto;
  //  int qtd_vendas;
    char horario[40];
    float preco;
    float nota;
    char nome_produto[30];
}produto;

//criando o struct da arvore
typedef struct noarv{
    produto p;
    struct noarv * direita;
    struct noarv * esquerda;
}noarv;

void menu();

//tipo de dado lista e elemento da lista para exibir com base no filtro desejado
typedef struct elemento_lista{
    noarv dado;
    struct elemento_lista *proximo;
}ELEM;

typedef struct lista{ //lista->inicio->dado
    ELEM *inicio;
    ELEM *fim;
    int tamanho;
}LISTA;

//inserindo inteiro nó na arvore
noarv* insere(noarv *, int, char[], float, int, float);

//limpando arvore
void erase(noarv *);

//visualizar posordem
void viewPost(noarv *);

//visualizar inordem
void viewin(noarv *);

//visualizar preordem 
void viewpre(noarv *);

//buscando p.id na arvore
noarv* busca(noarv *arvore, int);

//achar o maior p.id na arvore
noarv * acharmaior(noarv *arvore);

//função para remover determinado item da arvore
noarv * pop(noarv *arvore, int);

int altura(noarv *arvore);

int fatorBalanceamento(noarv *arvore);

noarv *rotacaoEsquerda(noarv *arvore);

noarv *rotacaoDireita(noarv *arvore);

noarv* balanceamentoArvore(noarv *arvore);

void inserir_na_lista(noarv*, LISTA*);

void organizar_lista(ELEM*, LISTA*, int);//case 1 numero de vendas, case 2 notas, case 3/4 maior/menor preços;

LISTA* iniciar_lista();

void resetar_lista();

void imprimir_lista(ELEM*);

noarv * alterar_no(noarv *arvore, const char*);

noarv* buscarProduto(noarv* arvore, const char*);

noarv* compra(noarv* arvore, const char*);

void inserir_nos(LISTA*, noarv*);

#endif // TEST_H_INCLUDED
