#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "test.h"


int main(){
    char nomep[100], produto_comprado[100], chave[100], compras[100];
    //unsigned short i;
	int num, op, quantidade, opcao_exibicao, id=0;
    float preco, nota;
    //unsigned short qtdcaso, caso = 0, qtdnos;
    noarv *arvore = NULL;
    LISTA *lista_filtrada;
    
    do {  
        menu();
        scanf("%d",&op);
        switch (op) {
        case 1:
            id += 1;
            printf("insira o preco do produto\n");
            scanf("%f", &preco);
            printf("insira a quantidade do produto\n");
            scanf("%d", &quantidade);
            printf("Insira a nota de qualidade do produto\n");
            scanf("%f", &nota);
            printf("insira o nome do produto!!\n");
            scanf("%s", nomep);
            
            if(busca(arvore, id)){
                printf("%d id ja cadastrado existe\n", id);
            }
            else{
                arvore = insere(arvore, id, nomep, preco, quantidade, nota);
            } 
            printf("\n");
            break;
                    
            case 2: 
                printf("insira o item a ser apagado!\n");
                scanf("%d", &num);
                arvore = pop(arvore, num);
                printf("\n");
                break;

            case 3: 
                printf("insira o nome do produto a buscar:\n");
                scanf("%s", produto_comprado);
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
                printf("insira o item a ser alterado!!\n");
                scanf("%s", chave);
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
                imprimir_lista(lista_filtrada->inicio); // maior estoque
                resetar_lista(lista_filtrada->inicio);
                printf("\n");
            break;

            case 6:
                lista_filtrada = iniciar_lista();
                inserir_nos(lista_filtrada, arvore);
                opcao_exibicao = 2;
                organizar_lista(lista_filtrada->inicio, lista_filtrada, opcao_exibicao); //nota
                imprimir_lista(lista_filtrada->inicio);
                resetar_lista(lista_filtrada->inicio);
                printf("\n");
            break;
            
             case 7:
                lista_filtrada = iniciar_lista();
                printf("Digite 3 para mostrar os maiores preços ou 4 para exibir os menores\n");
                scanf("%d", &opcao_exibicao);
                if(opcao_exibicao==3 || opcao_exibicao==4){
                    printf("%d\n", opcao_exibicao);
                    inserir_nos(lista_filtrada, arvore);
                    organizar_lista(lista_filtrada->inicio, lista_filtrada, opcao_exibicao);
                    imprimir_lista(lista_filtrada->inicio);
                    resetar_lista(lista_filtrada->inicio);  //maior/menor preco
                }
                printf("\n");
            break;

            case 8:
                lista_filtrada = iniciar_lista();
                printf("Digite 5 para mostrar os os produtos com maior quantidade ou 6 para exibir os produtos com menores quantidade\n");
                scanf("%d", &opcao_exibicao);
                if(opcao_exibicao==5 || opcao_exibicao==6){
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
	
