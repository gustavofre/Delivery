/*INSTITUTO FEDERAL DE SÃO PAULO  - CAMPUS SÃO PAULO 
TECNOLOGIA EM ANÁLISE E DESENVOLVUMENTO DE SISTEMAS 
PROJETO DE LÓGICA DE PROGRAMAÇÃO I - LG1A1
CRIAÇÃO DE UMA DRIVE THRU CONFORME EMENTA  
ALUNO: GUSTAVO LOURENÇO DE FREITAS SP3049566
ALUNA: HELENA DE BRITO SP3048802*/

/*Declaração de bibliotecas*/
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <locale.h>
#include <string.h>

#include "bibliotecastruct.h"
//#include "bibliotecafuncao.h"

/*Constantes*/
#define  listaProduto 		"PRODUTOS.DAT"
#define  arquivoPagamento	"PAGAMENTO.DAT"
#define  arquivoPedido		"TICKET.TXT"
#define  arquivoCartao		"CARTOES.DAT"

/*Variáveis globais*/
char inicializacao, fazerPedido;
int cdFilaProduto, itens = 0, nmPedido, qt, opcaoPagamento, indiceCartao, tamanhoCartao ;
int *pedidoPonteiro;
float totalVenda = 0, totalPagar = 0; 
char flag;
//RegistroPedido.cdPagamento 


/*Variáveis globais Structs*/
pedido ReturnPedido;  //Pedido 
meioPagamento RegistroPedido; //Pagemento
cartao CartaoDados; 
/*Funções*/

/*Cadastra os produtos*/
void cadastroProduto (void){
	
	produto DATA[8] = 
	{	
	{1, "X-salada", 10.0},
	{2, "X-Bacon", 12.0},
	{3, "X-tudo", 15.0}, 
	{4, "Refrigerante", 7.0},
	{5, "Batata frita", 6.0},
	{6, "Nuggets", 10.0},
	{7, "Molhos", 2.0},
	};	

	FILE * arq = fopen (listaProduto, "w");
	if (arq == NULL){
		printf ("Falha ao abrir o arquivo");
	} else {
		fwrite(&DATA, sizeof(DATA), 1, arq);
		if (ferror(arq)){
			printf("Falha ao gravar o arquivo");
		}
	} fclose(arq);	
}

/*Tela de inicialização*/
void bemVindo (void){
	inicioBemVindo:
	printf("\n\t\t====================================================================\n");
	printf("\t\t\t\tBEM VINDO AO MICKEY E DONALS\n");
	printf("\t\t\t\t DESEJA FAZER ALGUM PEDIDO?\n");
	printf("\t\t\t\t     [S] SIM OU [N] NÃO\n");
	scanf("\t\t\t\t%c", &inicializacao);
	printf("\n\t\t====================================================================\n");
	
	if (inicializacao == 's' || inicializacao == 'S'){
			system("cls");
			printf("\n\n\t\tVAMOS MOSTRAR O MENU PARA PROSSEGUIR COM O PEDIDO\n\n");
			printf("\t\t APERTE ENTER\n\n");
			getch();
			system("cls");
		} else if (inicializacao == 'n' || inicializacao == 'N'){
			system("cls");
			printf("\n\n\n\t\t\t\t OBRIGADO VOLTE LOGO\n\n\n");
			exit(0);
		 
		} else if(inicializacao != 's' || inicializacao != 'S' || inicializacao != 'n' || inicializacao!= 'N'){
			printf("\t\t\t\t OPÇÃO INVÁLIDA, TENTE NOVAMENTE");
			getch();
			system("cls");
			goto inicioBemVindo;
		}
}


/*Lista os arquivos cadastrados*/
void listaMenu (void){
	FILE * arq;
	produto Return;
	Return.cdProduto = 0;
	arq = fopen (listaProduto, "r");
	if (arq == NULL){
		printf("Falha ao abrir o arquivo");
	} else {
		printf("\t\t\t ================================\n");
		printf("\t\t\t\t\t MENU\n");
		printf("\t\t\t=================================\n");
		while(!feof (arq)){
			fread(&Return, sizeof(Return), 1 , arq);
			if(ferror(arq)){
				printf("Falha ao abrir o arquivo");
			} else if (!feof(arq)) {
				printf("\t\t\t %d %s R$%.2f\n", Return.cdProduto, Return.nomeProduto, Return.precoProduto);
			}
		} fclose(arq);
		//return (Return.cdProduto);
	}
	
}

/*Arquivo para leitura do Menu*/
void vendaProdutoMenu (produto * Return){
	
	FILE * arq; 
	produto ProdutoMenu;
	arq = fopen (listaProduto, "r");
	if(arq == NULL){
		printf("Falha ao abrir o arquivo");
	} else {
		while (!feof (arq)){
			fread(&ProdutoMenu, sizeof(ProdutoMenu), 1, arq);
			if (ferror(arq)){
				printf("Falha ao abrir o arquivo");
			} if(!feof(arq)){
				if (Return->cdProduto == ProdutoMenu.cdProduto){
					*Return = ProdutoMenu;	
				}
			}
		} fclose(arq);
	}
}

/*Adiciona os valores do cd pedido*/
int adicionaRegistros (char *nomeArq){
	FILE * calculaRegistro;
	meioPagamento RegistroPedido;
	int registroNumeros;
	
	calculaRegistro = fopen (nomeArq, "r");
	if (calculaRegistro == NULL){
		registroNumeros = 0; 
	} else {
		if (fseek (calculaRegistro, 0, SEEK_END)){
			printf ("Erro no cálculo do tamanho do arquivo");
			getch();
			registroNumeros = -1;
		} else {
			registroNumeros = ftell(calculaRegistro) / sizeof (RegistroPedido);
		} fclose (calculaRegistro);
	} 
	 return (registroNumeros);	
}

/*Mostra os itens colocados no carrinho*/
void acumuloPedido (int nmPedido, int qt, pedido ReturnPedido, 	float totalVenda, char flag) {
	
	FILE * listaVenda; 
	
	if(qt == 1){
		listaVenda = fopen(arquivoPedido, "w"); 
	} else {
		listaVenda = fopen(arquivoPedido, "a"); 
	}
	if (arquivoPedido == NULL){
		printf("Erro");
	}  else{
		if( qt == 1){
				//fprintf(listaVenda, "\n\n=======================================================================\n\n");
				fprintf(listaVenda, "\n\t\t NÚMERO PEDIDO: %i", nmPedido);
				fprintf(listaVenda, "\n\n\t\t QT PEDIDA \t PRODUTO \t\t PREÇO UNITÁRIO \t");
		} if( flag == '1'){
				
		} else {
				fprintf(listaVenda, "\n\t\t %i \t\t %s \t\t %2.f", ReturnPedido.quantidadePedido, ReturnPedido.Produto.nomeProduto, ReturnPedido.Produto.precoProduto);
				//fprintf(listaVenda, "\n\t\t TOTAL ITEM: \t %.2f\n", totalVenda);
				//fprintf(listaVenda, "\n\n=======================================================================\n\n");
				fprintf(listaVenda, "\n\t\t TOTAL DO PEDIDO %.2f ", totalVenda);
				//fprintf(listaVenda, "\n=======================================================================\n");	
		} 
		fclose(listaVenda);		
	}	
}


/*Módulo venda*/
void venda (void){
	
	RegistroPedido.cdPagamento = adicionaRegistros(arquivoPagamento)+1;
	
	do{
		do{
			printf("\n\n");
			//escolhaProduto:
				
		//	listaMenu();
			
			printf("\n\t\t ESOLHA O CÓDIGO DO PRODUTO: ");
			scanf ("%i", &ReturnPedido.Produto.cdProduto);
			
			if(ReturnPedido.Produto.cdProduto < 1 || ReturnPedido.Produto.cdProduto > 8){
				printf("\t\t\t ESCOLHA INCORRETA, TENTE NOVAMENTE");
			} 
		} while (ReturnPedido.Produto.cdProduto < 1 || ReturnPedido.Produto.cdProduto > 8);
		
			
		itens++;
		//printf("\n\t\t Código do Pedido %i", itens);
		vendaProdutoMenu (&ReturnPedido.Produto);
		
		do {
			printf("\n\t\t QUANTOS PRODUTOS DESEJA: ");
			fflush(stdin);
			scanf("%i", &ReturnPedido.quantidadePedido);
			if(ReturnPedido.quantidadePedido <1){
				printf("\n\n\t\t QUANTIDADE INVÁLIDA");
				getch();
				//goto escolhaProduto;
			}
		}	while(ReturnPedido.quantidadePedido < 1);
		fflush (stdin);	
		ReturnPedido.precoProduto = ReturnPedido.quantidadePedido * ReturnPedido.Produto.precoProduto;
		totalPagar = totalPagar + ReturnPedido.precoProduto;
		acumuloPedido (RegistroPedido.cdPagamento, itens, ReturnPedido, totalPagar, '0');
		system("TYPE TICKET.TXT");
		printf("\n\n\t\t DESEJA ALGO MAIS?: [S] SIM E [N] NÃO ");
		scanf("%c", &fazerPedido);		
	} while(fazerPedido == 'S' || fazerPedido == 's');
	system("cls");	
	} 

/*Módulo Pagamento*/	
void pagamento (int *pedidoPonteiro){
		
		FILE * arquivo_Pedido;
		RegistroPedido.cdPagamento = adicionaRegistros(arquivoPagamento)+1;
		
		arquivo_Pedido = fopen (arquivoPagamento, "a");
		if (arquivo_Pedido == NULL){
			printf("Problema ao abrir o arquivo");
		} else {
				system("cls");
				printf("\n\n\t\t\tTELA DE PAGAMENTO DO PEDIDO: %d", RegistroPedido.cdPagamento);
				printf("\n\t\t================================================");
				printf("\n\t\t\t FORMAS DE PAGAMENTO ");
				printf("\n\t\t=================================================");
				printf("\n\t\t\t\t 1. DINHEIRO");
				printf("\n\t\t\t\t 2. CARTÃO DÉBITO E CRÉDITO");
				printf("\n\t\t\t\t 3. CHEQUE \n");
				fflush(stdin);
				scanf("%d", &opcaoPagamento);
				
				switch (opcaoPagamento) {
					
					case 1: 
					
					system("cls");
					printf("\n\n\t\t================================================");
					printf("\n\n\t\t\tPEDIDO: %d PAGO EM DINHEIRO", RegistroPedido.cdPagamento);
					printf("\n\t\t\tVALOR TOTAL DO PAGAMENTO: R$%.2f", totalPagar);
					printf("\n\n\t\t================================================");
					getch();
					entregaDinheiro();
					break;
					
					
					case 2:
					system("cls");	
					FILE * arqCartao; 
					//CartaoDados.nmCartao = 2;
					cartao CartaoDados;
					
					arqCartao = fopen(arquivoCartao, "a");
					if (arquivoCartao == NULL){
						printf("Problemas ao abrir o arquivo");
					} else {
					system("cls");
					printf("\n\n\t\t\t================================================");
					printf("\n\t\t\t PEDIDO: %d PAGO EM CARTÃO DE DEBITO E CRÉDITO", RegistroPedido.cdPagamento);
					printf("\n\t\t\t VALOR TOTAL DO PAGAMENTO: R$%.2f", totalPagar);
					getch();
					
					
					do { 
						
						printf("\n\n\n\t\t\t  DIGITE O NÚMERO DO CARTÃO: ");
						gets(CartaoDados.nmCartao);
						tamanhoCartao = strlen(CartaoDados.nmCartao);
						
						if (tamanhoCartao == 16) { 
							for (indiceCartao = 0; indiceCartao < tamanhoCartao; indiceCartao++){
								if(indiceCartao >3 && indiceCartao < 12){
									CartaoDados.nmCartao[indiceCartao] = '*';	
								}
							} printf("\n\n\t\t\tCARTÃO VALIDADO"); getch();	
							  entregaCartao();
							  exit(0);					
						} else if(tamanhoCartao != 16) {
								//	printf("\n\n\t\t\tCARTÃO INVÁLIDO");
							}	
						fwrite(&CartaoDados, sizeof(CartaoDados),1 ,arqCartao);						
						getch();
					}while ( tamanhoCartao != 16);
					fclose(arqCartao);
					break; 
					
					case 3: 
					system("cls");
					printf("\n\n\t\t\t================================================");
					printf("\n\t\t\t\t PEDIDO: %d PAGO EM CHEQUE", RegistroPedido.cdPagamento);
					printf("\n\t\t\t\tVALOR TOTAL DO PAGAMENTO: R$%.2f", totalPagar);
					getch();
					entregaCheque();
					break;
					
					default:
	                system("cls");
	                printf("Opção inválida!");
	                getch();
	                break; 
					}
		} 
		fwrite (&RegistroPedido, sizeof(RegistroPedido), 1, arquivo_Pedido); 
	} fclose(arquivo_Pedido);

}

/*Modulo entrega dinheiro */
void entregaDinheiro (void){
	system("cls");
	system("color 02");
	printf("\n\n\n\t\t\tPEDIDO PAGO EM DINHEIRO E RETIRADO");
}

/*Modulo entrega cartao*/
void entregaCartao (void){
	system("cls");
	system("color 05");
	printf("\n\n\n\t\t\tPEDIDO PAGO EM CARTÃO E RETIRADO");
}

/*Modulo entrega cheque*/ 
void entregaCheque (void){
	system("cls");
	system("color 01");
	printf("\n\n\n\t\t\tPEDIDO PAGO EM CHEQUE E RETIRADO");
}



int main (void) {
	setlocale(LC_ALL,"Portuguese");

	cadastroProduto();
	bemVindo();
	listaMenu();
	venda();
	pagamento(pedidoPonteiro);	
	return (0);
}

