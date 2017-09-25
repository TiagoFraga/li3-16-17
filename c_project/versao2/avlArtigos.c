#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <assert.h>
#include "avlArtigos.h"
#include "avlRevisoes.h"

/**
----------------------------------------------ESTRUTURAS-------------------------------------------------
**/

/**
------------------------------------- 1)Estruturas da Avl de Artigos. -----------------------------------
*/

/**
1.1) Estrutura de um nodo da AVL.
*/

struct avl_node_s {
	struct avl_node_s *left;
	struct avl_node_s *right;
	
	char* titulo;
	long idTitulo;
	long ncaracteres;
	long npalavras;

	struct avl_tree_s_revisao *revisoes;

};

/**
1.2) Estrutura da cabeça da AVL
*/

struct avl_tree_s {
	struct avl_node_s *root;
	long total;
	long unicos;
	long allrevisions;

};

/** 
--------------------------------- 2) Estruturas Auxiliares usadas nas Queries. ----------------------------
*/

/**
2.1) Estrutura Auxiliar usada na Querie6.
*/

struct id_caracteres
{
    long idTitulo;
    long ncaracteres;
};

/**
2.2) Estrutura Auxiliar Usada na Querie8.
*/

struct artigoAndIdentifier{
	long id;
	int length;
};

/**
2.3) Estrutura Auxiliar Usada na Querie9 (Lista Ligada).
*/

/**
2.3.1) Estrutura do nodo da lista ligada.
*/

struct linkedList_node_s{
	char* value;
	struct linkedList_node_s *next;
};

/**
2.3.2) Estrutura da cabeça da lista ligada.
*/

struct linkedList_s{
	struct linkedList_node_s *root;
	int length;
};

/**
---------------------------------- FUNÇÕES MANIPULADORAS DAS ESTRUTURAS --------------------------------------
*/

/**
--------------------------------------------- Lista Ligada (Querie9) ----------------------------------------
*/

/**
Função para alocar memoria para a criação da cabeça da Lista Ligada
*/

linkedList_t* linkedList_create(){
	linkedList_t* lista = NULL;
	if( ( lista = malloc( sizeof( linkedList_t ) ) ) == NULL ) {
		return NULL;
	}

	lista->root = NULL;
	lista->length=0;
	return lista;
}


/**
Função para alocar memoria para a criaçao de um nodo da Lista Ligada.
*/

linkedList_node_t* linkedList_create_node(){
	linkedList_node_t *node = NULL;
	

	if( ( node = malloc( sizeof( linkedList_node_t ) ) ) == NULL ) {
		return NULL;
	}

	node->value = NULL;
	node->next = NULL;
	return node;
}

/**
Funçao para libertar a memoria de uma Lista Ligada.
*/

void free_linkedList_node( linkedList_node_t* node ) {

	if(!node){
		return;
	}
	linkedList_node_t* next;
	while(node!= NULL){
		next = node;
		node = node->next;
		free(next->value);
		free(next);	
	}
	free(node);
}

/**
Função para libertar a memoria da cabeça de uma Lista Ligada.
*/

void free_LinkedList( linkedList_t *tree ) {

	if(!tree){
		return;
	}

	free_linkedList_node(tree->root);
	free(tree);
}

/**
Função para fazer a inserção de um valor na Lista Ligada.
*/

void insertNodeL(linkedList_t* lista, char* value){
	linkedList_node_t* node = NULL;
	linkedList_node_t *nodo = NULL;

	/* Well, there must be a first case */ 	
	if( lista->root == NULL ) {
		node = linkedList_create_node();
		node->value = strndup(value,strlen(value));
		
		lista->root = node;
		lista->length = lista->length + 1;
		return;

	}else{
		nodo = lista->root;
		
		while(nodo->next!=NULL){
			nodo = nodo->next;
		}

		node = linkedList_create_node();
		node->value = strndup(value,strlen(value));

		nodo->next = node;

		lista->length= lista->length + 1;
	}

}

/**
---------------------------------------------- Avl de Artigos ----------------------------------------------
*/

/**
Funçao para alocar memória para uma nova cabeça da Avl.
*/

avl_tree_t* avl_create() {
	avl_tree_t* tree = NULL;

	if( ( tree = malloc( sizeof( avl_tree_t ) ) ) == NULL ) {
		return NULL;
	}

	tree->root = NULL;
	tree->total = 0;
	tree->unicos = 0;
	tree->allrevisions = 0;


	return tree;
}

/**
Função para alocar memória para a criação de um nodo da Avl.
*/

avl_node_t* avl_create_node() {
	avl_node_t *node = NULL;
	

	if( ( node = malloc( sizeof( avl_node_t ) ) ) == NULL ) {
		return NULL;
	}

	node->left = NULL;
	node->right = NULL;

	node->titulo = NULL;
	node->idTitulo = 0;
	node->ncaracteres = 0;
	node->npalavras = 0;
	node->revisoes = avl_create_revisao();

	
	return node;	
}

/**
Função para calcular a altura de um nodo da Avl, recursivamente. 
*/

int avl_node_height( avl_node_t* node ) {
	int height_left = 0;
	int height_right = 0;

	if( node->left ) height_left = avl_node_height( node->left );
	if( node->right ) height_right = avl_node_height( node->right );

	return height_right > height_left ? ++height_right : ++height_left;
}

/**
Função para calcular o nivel de balanceamento de um nodo.
*/

int avl_balance_factor( avl_node_t *node ) {
	int bf = 0;

	if( node->left  ) bf += avl_node_height( node->left );
	if( node->right ) bf -= avl_node_height( node->right );

	return bf ;
}

/**
Função para executar uma dupla rotação á esquerda.
*/

avl_node_t *avl_rotate_leftleft( avl_node_t *node ) {
 	avl_node_t *a = node;
	avl_node_t *b = a->left;
	
	a->left = b->right;
	b->right = a;

	return( b );
}

/**
Função para executar uma rotação simples á esquerda e depois a direita.
*/

avl_node_t *avl_rotate_leftright( avl_node_t *node ) {
	avl_node_t *a = node;
	avl_node_t *b = a->left;
	avl_node_t *c = b->right;
	
	a->left = c->right;
	b->right = c->left; 
	c->left = b;
	c->right = a;

	return( c );
}

/**
Função para executar uma rotação simples a direita e depois a esquerda.
*/

avl_node_t *avl_rotate_rightleft( avl_node_t *node ) {
	avl_node_t *a = node;
	avl_node_t *b = a->right;
	avl_node_t *c = b->left;
	
	a->right = c->left;
	b->left = c->right; 
	c->right = b;
	c->left = a;

	return( c );
}

/**
Função para executar uma rotação dupla a direita.
*/

avl_node_t *avl_rotate_rightright( avl_node_t *node ) {
	avl_node_t *a = node;
	avl_node_t *b = a->right;
	
	a->right = b->left;
	b->left = a; 

	return( b );
}

/**
Função para executar o balanceamento de um nodo.
*/

avl_node_t *avl_balance_node( avl_node_t *node ) {
	avl_node_t *newroot = NULL;

	/* Balancear os filhos, caso existam */
	if( node->left )
		node->left  = avl_balance_node( node->left  );
	if( node->right ) 
		node->right = avl_balance_node( node->right );

	int bf = avl_balance_factor( node );

	if( bf >= 2 ) {
		/* Arvore balanceada a esquerda */	

		if( avl_balance_factor( node->left ) <= -1 ) 
			newroot = avl_rotate_leftright( node );
		else 
			newroot = avl_rotate_leftleft( node );

	} else if( bf <= -2 ) {
		/* Arvore balanceada a direita */

		if( avl_balance_factor( node->right ) >= 1 )
			newroot = avl_rotate_rightleft( node );
		else 
			newroot = avl_rotate_rightright( node );

	} else {
		/* O nodo esta balanceado! */

		newroot = node;
	}

	return( newroot );	
}

/**
Função para executar o balanceamento de uma arvore.
*/

void avl_balance( avl_tree_t *tree ) {

	avl_node_t *newroot = NULL;

	newroot = avl_balance_node( tree->root );

	if( newroot != tree->root )  {
		tree->root = newroot; 
	}
}

/**
Função para fazer uma inserção na Avl.
*/

int avl_insert( avl_tree_t *tree, char* titulo, long idTitulo,long ncaracteres,long npalavras, long idRevisao, char* data ) {
	avl_node_t *node = NULL;
	avl_node_t *next = NULL;
	avl_node_t *last = NULL;
	int r=0;
	
	/* Primeiro caso, quando a Avl ainda nao tem artigos*/ 	
	if( tree->root == NULL ) {
		node = avl_create_node();
		node->titulo = strndup(titulo,strlen(titulo));
		
		node->idTitulo= idTitulo;
		node->ncaracteres = ncaracteres;
		node->npalavras = npalavras;
		
		r = avl_insert_revisao(node->revisoes,idRevisao,data);
		tree->allrevisions = tree->allrevisions +1;
		tree->root = node;
		tree->total = tree->total + 1;
		tree->unicos = tree->unicos + 1;
		

	/* Ja temos artigos inseridos, logo temos de definir onde colocar os proximos. */
	} else {
		next = tree->root;

		while( next != NULL ) {
			last = next;

			if( idTitulo < next->idTitulo ) {
				next = next->left;
				

			} else if( idTitulo > next->idTitulo ) {
				next = next->right;
				

			/* Quando o artigo que pretendemos inserir, ja se encontra na Avl.*/
			} else if( idTitulo == next->idTitulo ) {
				tree->total= tree->total + 1;
				if(strcmp(next->titulo, titulo)== 0){
					free(next->titulo);
					next->titulo = strndup(titulo,strlen(titulo));
				}

				if(next->ncaracteres < ncaracteres) next->ncaracteres = ncaracteres;
				if(next->npalavras < npalavras) next->npalavras = npalavras;

				r = avl_insert_revisao(next->revisoes, idRevisao,data);
				
				if(r==0){
					tree->allrevisions = tree->allrevisions + 1;
				}
				return r;
			}
		}

		
			node = avl_create_node();

			node->titulo = strndup(titulo,strlen(titulo));
			node->idTitulo = idTitulo;
			node->ncaracteres = ncaracteres;
			node->npalavras = npalavras;
			r = avl_insert_revisao(node->revisoes, idRevisao,data);
			tree->allrevisions = tree->allrevisions + 1;

			if( idTitulo < last->idTitulo ) last->left = node;
			if( idTitulo > last->idTitulo ) last->right = node;
		

		tree->total= tree->total + 1;
		tree->unicos = tree->unicos + 1;

	} 
	
	avl_balance( tree );
	return r;
}

/**
Função para libertar a memoria de um nodo.
*/

void free_tree_root_artigos( avl_node_t *node ) {

	if(!node){
		return;
	}

	free(node->titulo);
	free_tree_revisoes(node->revisoes);

	free_tree_root_artigos(node->left);
	free_tree_root_artigos(node->right);
	free(node);
}

/**
Função para libertar a memoria de uma Avl.
*/

void free_tree_artigos( avl_tree_t *tree ) {

	if(!tree){
		return;
	}

	free_tree_root_artigos(tree->root);
	free(tree);
}

/**
----------------------------------------------------- QUERIES ----------------------------------------------
*/

/*
Função para fazer a procura de um artigo na arvore, dado um id do titulo.
Retorna NULL, caso nao exista;
*/

avl_node_t *avl_find_artigo( avl_tree_t *tree, long idTitulo ) {
	avl_node_t *current = tree->root;

	while( current && current->idTitulo != idTitulo ) {
		if( idTitulo > current->idTitulo )
			current = current->right;
		else
			current = current->left;
	}

	return current;
}

/**
Querie1.
Retorna o numero total de artigos.
*/

long querie1(avl_tree_t* tree){
	return tree->total;
}

/**
Querie2.
Retorna o numero de artigos únicos.
*/

long querie2(avl_tree_t* tree){
	return tree->unicos;
}

/**
Querie3.
Retorna o numero de revisoes unicas.
*/

long querie3(avl_tree_t* tree){
	return tree->allrevisions;
}

/**
Querie6.
Retorna os 20 maiores artigos, em termos de numero de caracteres.
*/

 
int compare6(const void* a, const void* b){
    idchar* id_chars1 = (idchar*) a;
    idchar* id_chars2 = (idchar*) b;
 
    int result = id_chars1->ncaracteres - id_chars2->ncaracteres;
 
    if(result ==0){
        result = id_chars1->idTitulo - id_chars2->idTitulo;
    }
 
    return result;
}
 
void insert_struct(avl_node_t *node,idchar* id_chars,long size){
 
    if(id_chars[0].ncaracteres < node->ncaracteres){
        id_chars[0].idTitulo = node->idTitulo;
        id_chars[0].ncaracteres = node->ncaracteres;
 
    }
   
 
    qsort(id_chars,size,sizeof(idchar),compare6);
   
}
 
void querie6_aux(avl_node_t *node, idchar* id_chars, long size){
    if(!node){
        return;
    }
 
    insert_struct(node, id_chars, size);
    querie6_aux(node->left, id_chars, size);
    querie6_aux(node->right, id_chars, size);
}
 
long* querie6(avl_tree_t* artigos){
    long size = 20;
    long* largest_articles = malloc(sizeof(long)*size);
    idchar* id_chars = malloc(sizeof(idchar)*size);
   
 
    int i,j=0;
    for(i=0;i<size;i++){
        largest_articles[i] = -1;
        id_chars[i].ncaracteres = -1;
    }
 
    querie6_aux(artigos->root,id_chars,size);
 
    for(i=size-1; i>=0;i--){
        largest_articles[j] = id_chars[i].idTitulo;
        j++;
    }
   	free(id_chars);
    return largest_articles;
 
}

/**
Querie7.
Retorna o titulo de um artigo, dado um id.
*/

char* querie7(avl_tree_t* tree, long id){
	avl_node_t* nodo = avl_find_artigo(tree,id);
	if(nodo == NULL){
		return NULL;
	}else{
		return nodo->titulo;
	}
}

/**
Querie8.
Retorna os artigos com mais palavras.
*/

int compare(const void* a, const void* b){
	AAI* aaiA = (AAI*) a;
	AAI* aaiB = (AAI*) b;

	int result = aaiA->length - aaiB->length;

	if(result==0){
		result = aaiA->id - aaiB->id;
	}

	return result;
}

void populateNArticles(avl_node_t *node, AAI* nArticles, int size){

	if(nArticles[0].length<node->npalavras){
		nArticles[0].length=node->npalavras;
		nArticles[0].id=node->idTitulo;
	}

	qsort(nArticles, size, sizeof(AAI), compare);
}

void querie8_aux(avl_node_t *node, AAI* nArticles, int size){
	if(!node){
		return;
	}

	populateNArticles(node, nArticles, size);
	querie8_aux(node->left, nArticles, size);
	querie8_aux(node->right, nArticles, size);
}

long* querie8(avl_tree_t* tree, int size){
	long *nArticles = (long *)malloc(sizeof(long)*size);
	AAI *aaiList = (AAI *)malloc(sizeof(AAI)*size);
	
	int i,j=0;

	for(i=0;i<size;i++){
		nArticles[i]=-1;
		aaiList[i].length=-1;
	}

	querie8_aux(tree->root, aaiList, size);

	for(i=size-1;i>=0;i--){
		nArticles[j] = aaiList[i].id;
		j++;
	}
	free(aaiList);
	return nArticles;
}

/**
Querie9.
Retorna todos uns artigos que começam com um prefixo dado.
*/

int startsWith(const char* prefix, const char *str){
	int lenpre, lenstr; 
	lenpre = strlen(prefix);
	lenstr = strlen(str);

	if(lenstr<lenpre) return 0;
	
	return strncmp(prefix,str,lenpre) == 0;
}

void querie9_aux(avl_node_t *node, linkedList_t* lista, char* prefix){
	if(!node){
		return;
	}
	
	char* lastName = malloc((strlen(node->titulo))*sizeof(char));
	strcpy(lastName,node->titulo);
	
	if(startsWith(prefix,lastName)){
		insertNodeL(lista, lastName);
	}

	querie9_aux(node->left, lista, prefix);
	querie9_aux(node->right, lista, prefix);
}
 
int compare9 (const void* a, const void * b)
{
    return strcmp (*(const char **) a, *(const char **) b);
}


char** querie9(avl_tree_t* tree, char* prefix){
	int i=0;
	linkedList_t* lista = linkedList_create();
	
	querie9_aux(tree->root, lista, prefix);
	
	int r = lista->length +1;
	
	char** result = (char**)malloc(r*sizeof(char*));
	
	linkedList_node_t* nodo = lista->root;
	
	while(nodo!=NULL){
		result[i] = strndup(nodo->value,(strlen(nodo->value)));
		i++;
		qsort(result, i, sizeof(char *), compare9);
		nodo= nodo->next;
		
	}
	result[i] = NULL;
	
	free_LinkedList(lista);

	return result;
}

/**
Querie10.
Retorna um timeStamp de uma determinada revisao de um determinado artigo, dado um id de artigo e um id de revisao.
*/

char* querie10(avl_tree_t* tree, long article_id, long revision_id){
	avl_node_t* nodo = avl_find_artigo(tree,article_id);
	if(nodo == NULL){
		return NULL;
	}
	else{
		char* time;
		time = querie10Aux(nodo->revisoes,revision_id);
		return time;
	}
}



