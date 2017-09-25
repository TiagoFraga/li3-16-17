#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <assert.h>
#include "avlContribuidores.h"

/**
----------------------------------------------ESTRUTURAS-------------------------------------------------
**/

/**
------------------------------------- 1)Estruturas da Avl de Contribuidores. -----------------------------------
*/

/**
1.1) Estrutura de um nodo da AVL.
*/

struct avl_node_s_contribuidor {
	struct avl_node_s_contribuidor *left;
	struct avl_node_s_contribuidor *right;
	char* username;
	long idUsername;
	long quantidade;

};

/**
1.2) Estrutura da cabeça da AVL
*/

struct avl_tree_s_contribuidor {
	struct avl_node_s_contribuidor *root;
	long quantos;
};

/** 
--------------------------------- 2) Estruturas Auxiliares usadas nas Queries. ----------------------------
*/

/**
2.1) Estrutura Auxiliar usada na Querie4.
*/

struct contribuidoresAndCount{
	long id;
	int count;
};

/**
---------------------------------- FUNÇÕES MANIPULADORAS DAS ESTRUTURAS --------------------------------------
*/

/**
---------------------------------------------- Avl de Contribuidores ----------------------------------------------
*/

/**
Funçao para alocar memória para uma nova cabeça da Avl.
*/

avl_tree_t_contribuidor* avl_create_contribuidor() {
	avl_tree_t_contribuidor* tree = NULL;

	if( ( tree = malloc( sizeof( avl_tree_t_contribuidor ) ) ) == NULL ) {
		return NULL;
	}

	tree->root = NULL;
	tree->quantos = 0;

	return tree;
}

/**
Função para alocar memória para a criação de um nodo da Avl.
*/

avl_node_t_contribuidor* avl_create_node_contribuidor() {
	avl_node_t_contribuidor *node = NULL;
	

	if( ( node = malloc( sizeof( avl_node_t_contribuidor ) ) ) == NULL ) {
		return NULL;
	}

	node->left = NULL;
	node->right = NULL;

	node->username = NULL;
	node->idUsername = 0;
	node->quantidade = 0;


	return node;	
}

/**
Função para calcular a altura de um nodo da Avl, recursivamente. 
*/

int avl_node_height_contribuidor( avl_node_t_contribuidor* node ) {
	int height_left = 0;
	int height_right = 0;

	if( node->left ) height_left = avl_node_height_contribuidor( node->left );
	if( node->right ) height_right = avl_node_height_contribuidor( node->right );

	return height_right > height_left ? ++height_right : ++height_left;
}

/**
Função para calcular o nivel de balanceamento de um nodo.
*/

int avl_balance_factor_contribuidor( avl_node_t_contribuidor *node ) {
	int bf = 0;

	if( node->left  ) bf += avl_node_height_contribuidor( node->left );
	if( node->right ) bf -= avl_node_height_contribuidor( node->right );

	return bf ;
}

/**
Função para executar uma dupla rotação á esquerda.
*/

avl_node_t_contribuidor *avl_rotate_leftleft_contribuidor( avl_node_t_contribuidor *node ) {
 	avl_node_t_contribuidor *a = node;
	avl_node_t_contribuidor *b = a->left;
	
	a->left = b->right;
	b->right = a;

	return( b );
}

/**
Função para executar uma rotação simples á esquerda e depois a direita.
*/

avl_node_t_contribuidor *avl_rotate_leftright_contribuidor( avl_node_t_contribuidor *node ) {
	avl_node_t_contribuidor *a = node;
	avl_node_t_contribuidor *b = a->left;
	avl_node_t_contribuidor *c = b->right;
	
	a->left = c->right;
	b->right = c->left; 
	c->left = b;
	c->right = a;

	return( c );
}

/**
Função para executar uma rotação simples a direita e depois a esquerda.
*/

avl_node_t_contribuidor *avl_rotate_rightleft_contribuidor( avl_node_t_contribuidor *node ) {
	avl_node_t_contribuidor *a = node;
	avl_node_t_contribuidor *b = a->right;
	avl_node_t_contribuidor *c = b->left;
	
	a->right = c->left;
	b->left = c->right; 
	c->right = b;
	c->left = a;

	return( c );
}

/**
Função para executar uma rotação dupla a direita.
*/

avl_node_t_contribuidor *avl_rotate_rightright_contribuidor( avl_node_t_contribuidor *node ) {
	avl_node_t_contribuidor *a = node;
	avl_node_t_contribuidor *b = a->right;
	
	a->right = b->left;
	b->left = a; 

	return( b );
}

/**
Função para executar o balanceamento de um nodo.
*/

avl_node_t_contribuidor *avl_balance_node_contribuidor( avl_node_t_contribuidor *node ) {
	avl_node_t_contribuidor *newroot = NULL;

	/* Balancear os filhos, caso existam */
	if( node->left )
		node->left  = avl_balance_node_contribuidor( node->left  );
	if( node->right ) 
		node->right = avl_balance_node_contribuidor( node->right );

	int bf = avl_balance_factor_contribuidor( node );

	if( bf >= 2 ) {
		/* Arvore balanceada a esquerda */		

		if( avl_balance_factor_contribuidor( node->left ) <= -1 ) 
			newroot = avl_rotate_leftright_contribuidor( node );
		else 
			newroot = avl_rotate_leftleft_contribuidor( node );

	} else if( bf <= -2 ) {
		/* Arvore balanceada a direita */

		if( avl_balance_factor_contribuidor( node->right ) >= 1 )
			newroot = avl_rotate_rightleft_contribuidor( node );
		else 
			newroot = avl_rotate_rightright_contribuidor( node );

	} else {
		/* O nodo esta balanceado! */

		newroot = node;
	}

	return( newroot );	
}

/**
Função para executar o balanceamento de uma arvore.
*/

void avl_balance_contribuidor( avl_tree_t_contribuidor *tree ) {

	avl_node_t_contribuidor *newroot = NULL;

	newroot = avl_balance_node_contribuidor( tree->root );

	if( newroot != tree->root )  {
		tree->root = newroot; 
	}
}


/**
Função para fazer uma inserção na Avl.
*/

void avl_insert_contribuidor( avl_tree_t_contribuidor *tree, char* username, long idUsername ) {
	avl_node_t_contribuidor *node = NULL;
	avl_node_t_contribuidor *next = NULL;
	avl_node_t_contribuidor *last = NULL;


	/* Primeiro caso, quando a Avl ainda nao tem contribuidores*/ 	
	if( tree->root == NULL ) {
		node = avl_create_node_contribuidor();
			
		node->username = strndup(username,strlen(username));
		node->idUsername= idUsername;
		node->quantidade = 1;
			
		tree->root = node;
		tree->quantos = tree->quantos + 1;
	
	/* Ja temos artigos inseridos, logo temos de definir onde colocar os proximos. */	
	} else {
		next = tree->root;

		while( next != NULL ) {
			last = next;

			if( idUsername < next->idUsername ) {
				next = next->left;

			} else if( idUsername > next->idUsername ) {
				next = next->right;

			/* Quando o contribuidor que pretendemos inserir, ja se encontra na Avl.*/
			}else if( idUsername == next->idUsername){
				next->quantidade = next->quantidade + 1;
				return;
			} 
		}

		node = avl_create_node_contribuidor();

		node->username = strndup(username,strlen(username));
		node->idUsername = idUsername;
		node->quantidade = 1;
			
			
		tree->quantos= tree->quantos + 1;

		if( idUsername < last->idUsername ) last->left = node;
		if( idUsername > last->idUsername ) last->right = node;
	}	
	avl_balance_contribuidor( tree );
}

/**
Função para libertar a memoria de um nodo.
*/

void free_tree_root_contribuidores( avl_node_t_contribuidor *node ) {

	if(!node){
		return;
	}

	free(node->username);

	free_tree_root_contribuidores(node->left);
	free_tree_root_contribuidores(node->right);
	free(node);
}

/**
Função para libertar a memoria de uma Avl.
*/

void free_tree_contribuidores( avl_tree_t_contribuidor *tree ) {

	if(!tree){
		return;
	}

	free_tree_root_contribuidores(tree->root);
	free(tree);
}

/**
----------------------------------------------------- QUERIES ----------------------------------------------
*/

/*
Função para fazer a procura de um contribuidor na arvore, dado um id.
Retorna NULL, caso nao exista;
*/

avl_node_t_contribuidor *avl_find_contribuidor( avl_tree_t_contribuidor *tree, long id ) {
	avl_node_t_contribuidor *current = tree->root;

	while( current && current->idUsername != id ) {
		if( id > current->idUsername )
			current = current->right;
		else
			current = current->left;
	}

	return current;
}

/**
Querie4.
Retorna o Top10 de contribuidores.
*/

int compareContribuidor(const void* a, const void* b){
	CAC* aaiA = (CAC*) a;
	CAC* aaiB = (CAC*) b;

	int result = aaiA->count - aaiB->count;

	if(result==0){
		result = aaiA->id - aaiB->id;
	}

	return result;
}

void populateNContributors(avl_node_t_contribuidor *node, CAC* aaiList){
	int size = 10;

	if(aaiList[0].count<node->quantidade){
		aaiList[0].count=node->quantidade;
		aaiList[0].id=node->idUsername;
	}

	qsort(aaiList, size, sizeof(CAC), compareContribuidor);
}

void querie4_aux(avl_node_t_contribuidor *node, CAC* aaiList){
	if(!node){
		return;
	}

	populateNContributors(node, aaiList);
	querie4_aux(node->left, aaiList);
	querie4_aux(node->right, aaiList);
}

long* querie4(avl_tree_t_contribuidor* tree){
	int size = 10;
	long *nContribuidores = (long *)malloc(sizeof(long)*size);
	CAC *aaiList = (CAC *)malloc(sizeof(CAC)*size);
	
	int i,j=0;

	for(i=0;i<size;i++){
		nContribuidores[i]=-1;
		aaiList[i].count=-1;
	}

	querie4_aux(tree->root, aaiList);

	for(i=size-1;i>=0;i--){
		nContribuidores[j] = aaiList[i].id;
		j++;
	}

	return nContribuidores;
}

/**
Querie5.
Retorna o username de um contribuidor, dado um id.
*/

char* querie5(avl_tree_t_contribuidor* tree, long id){
	avl_node_t_contribuidor *nodo = avl_find_contribuidor(tree,id);
	return nodo->username;
}







