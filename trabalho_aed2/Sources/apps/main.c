#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "test.h"

int main(int argc, char **argv){
    char nomep[30], produto_comprado[100], chave[100], compras[100];
	int num=0, op=0, quantidade=0, opcao_exibicao=0, id=0, qtd_insere=0;
    float preco=0, nota=0;
    noarv *arvore;
    LISTA *lista_filtrada = NULL;


    arvore = NULL;

    do {  
        menu();
        scanf("%d",&op);
        getchar();

        switch (op) {
            case 1:
                id += 1;
                printf("insira o preco do produto\n");
                scanf("%f", &preco);
                getchar();
                printf("insira a quantidade do produto\n");
                scanf("%d", &quantidade);
                getchar();
                printf("Insira a nota de qualidade do produto\n");
                scanf("%f", &nota);
                getchar();
                printf("insira o nome do produto!!\n");
                scanf("%[^\n]", nomep);
                getchar();
                arvore = insere(arvore, id, nomep, preco, quantidade, nota);
                printf("\n");
                
                break;
                        
            case 2: 
                printf("Insira o ID do item a ser removido!\n");
                scanf("%d", &num);
                arvore = pop(arvore, num);
                printf("\n");
                break;

            case 3: 
                printf("insira o nome do produto a buscar:\n");
                scanf("%[^\n]", produto_comprado);
                noarv* encontrado = buscarProduto(arvore, produto_comprado);
                if (encontrado != NULL) {
                    printf("Informacoes do produto\n");
                    printf("ID: %d\n", encontrado->p.id);
                    printf("Nome: %s\n", encontrado->p.nome_produto);
                    printf("Preço: %.2f\n", encontrado->p.preco);
                    printf("Quantidade em estoque: %d\n", encontrado->p.qtd_produto);
                    printf("Nota: %.2f\n", encontrado->p.nota);
                } else {
                    printf("O produto %s não foi encontrado.\n", produto_comprado);
                }
                break;

            case 4:
                printf("Insira o item a ser alterado!!\n");
                scanf("%[^\n]", chave);
                getchar();
                noarv* resultado2 = alterar_no(arvore, chave);
                if (resultado2 != NULL) {
                    printf("ALTERAÇÃO CONCLUIDA COM SUCESSO\n");
                    printf("Novas Informacoes do produto\n");
                    printf("ID: %d\n", resultado2->p.id);
                    printf("Nome: %s\n", resultado2->p.nome_produto);
                    printf("Preço: %.2f\n", resultado2->p.preco);
                    printf("Quantidade em estoque: %d\n", resultado2->p.qtd_produto);
                    printf("Nota: %.2f\n", resultado2->p.nota);
                }else{
                    printf("Produto não encontrado\n");
                }
                break;
            case 5:
                lista_filtrada = iniciar_lista();
                inserir_nos(lista_filtrada, arvore);
                opcao_exibicao = 1;
                organizar_lista(lista_filtrada->inicio, lista_filtrada, opcao_exibicao);
                printf("\nORDEM ALFABETICA (A-Z)");
                imprimir_lista(lista_filtrada->inicio); // maior estoque
                resetar_lista(lista_filtrada->inicio);
                printf("\n");
                break;

            case 6:
                lista_filtrada = iniciar_lista();
                inserir_nos(lista_filtrada, arvore);
                opcao_exibicao = 2;
                organizar_lista(lista_filtrada->inicio, lista_filtrada, opcao_exibicao); //nota
                printf("\nMAIOR NOTA");
                imprimir_lista(lista_filtrada->inicio);
                resetar_lista(lista_filtrada->inicio);
                printf("\n");
                break;
                
            case 7:
                lista_filtrada = iniciar_lista();
                printf("Digite 3 para mostrar os maiores precos ou 4 para exibir os menores\n");
                scanf("%d", &opcao_exibicao);
                if(opcao_exibicao==3 || opcao_exibicao==4){
                    if(opcao_exibicao==3) printf("\nMAIOR PRECO");
                    else printf("\nMENOR PRECO");
                    inserir_nos(lista_filtrada, arvore);
                    organizar_lista(lista_filtrada->inicio, lista_filtrada, opcao_exibicao);
                    imprimir_lista(lista_filtrada->inicio);
                    resetar_lista(lista_filtrada->inicio);  //maior/menor preco
                }
                printf("\n");
                break;

            case 8:
                lista_filtrada = iniciar_lista();
                printf("Digite 5 para mostrar os produtos com maior estoque ou 6 para exibir os com menor estoque\n");
                scanf("%d", &opcao_exibicao);
                if(opcao_exibicao==5 || opcao_exibicao==6){
                    if(opcao_exibicao==5) printf("\nMAIOR ESTOQUE");
                    else printf("\nMENOR ESTOQUE");
                    printf("%d\n", opcao_exibicao);
                    inserir_nos(lista_filtrada, arvore);
                    organizar_lista(lista_filtrada->inicio, lista_filtrada, opcao_exibicao);
                    imprimir_lista(lista_filtrada->inicio);
                    resetar_lista(lista_filtrada->inicio); 
                }
                printf("\n");
                break;

            case 9: 
                printf("Entre com o nome do produto:\n");
                scanf("%s", compras);
                compra(arvore, compras);
                break;
            case 10: 
                printf("\n Obrigado por usar nosso produto!!\n");
                erase(arvore);
                arvore = NULL;
                //criar_arqui(S);
                break;
        }

    }while (op!=10);

    return 0;
}
