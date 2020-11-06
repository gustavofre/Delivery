/*Biblioteca com Structs*/

/*Structs*/

/*Produtos*/
typedef struct {
	int cdProduto; 
	char nomeProduto[50];
	float precoProduto;
} produto; 

/*Pedido*/
typedef struct {
	produto Produto;
	int quantidadePedido;
	float precoProduto; 
} pedido;

/*Forma de pagamento*/
typedef struct {
	int cdPagamento;
	char formaPagamento;
	float valorPagamento;
} meioPagamento;

/*Cartão*/
typedef struct {
	int cdPagamento;
	char nmCartao[16];
} cartao;


