#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <assert.h>
#include "avlRevisoes.h"

/**
----------------------------------------------ESTRUTURAS-------------------------------------------------
**/

/**
------------------------------------- 1)Estruturas da Avl de Revisoes. -----------------------------------
*/

/**
1.1) Estrutura de um nodo da AVL.
*/

struct avl_node_s_revisao {
	struct avl_node_s_revisao *left;
	struct avl_node_s_revisao *right;
	
	long idRevisao;
	char* timeStamp;

};

/**
1.2) Estrutura da cabeça da AVL
*/

struct avl_tree_s_revisao {
	struct avl_node_s_revisao *root;
	long quantos;
};

/**
---------------------------------- FUNÇÕES MANIPULADORAS DAS ESTRUTURAS --------------------------------------
*/

/**
---------------------------------------------- Avl de Revisões ----------------------------------------------
*/

/**
Funçao para alocar memória para uma nova cabeça da Avl.
*/

avl_tree_t_revisao* avl_create_revisao() {
	avl_tree_t_revisao* tree = NULL;

	if( ( tree = malloc( sizeof( avl_tree_t_revisao ) ) ) == NULL ) {
		return NULL;
	}

	tree->root = NULL;
	tree->quantos = 0;

	return tree;
}

/**
Função para alocar memória para a criação de um nodo da Avl.
*/

avl_node_t_revisao* avl_create_node_revisao() {
	avl_node_t_revisao *node = NULL;
	

	if( ( node = malloc( sizeof( avl_node_t_revisao ) ) ) == NULL ) {
		return NULL;
	}

	node->idRevisao = 0;
	node->timeStamp = NULL;

	node->left = NULL;
	node->right = NULL;

	return node;	
}

/**
Função para calcular a altura de um nodo da Avl, recursivamente. 
*/

int avl_node_height_revisao( avl_node_t_revisao* node ) {
	int height_left = 0;
	int height_right = 0;

	if( node->left ) height_left = avl_node_height_revisao( node->left );
	if( node->right ) height_right = avl_node_height_revisao( node->right );

	return height_right > height_left ? ++height_right : ++height_left;
}

/**
Função para calcular o nivel de balanceamento de um nodo.
*/

int avl_balance_factor_revisao( avl_node_t_revisao *node ) {
	int bf = 0;

	if( node->left  ) bf += avl_node_height_revisao( node->left );
	if( node->right ) bf -= avl_node_height_revisao( node->right );

	return bf ;
}

/**
Função para executar uma dupla rotação á esquerda.
*/

avl_node_t_revisao *avl_rotate_leftleft_revisao( avl_node_t_revisao *node ) {
 	avl_node_t_revisao *a = node;
	avl_node_t_revisao *b = a->left;
	
	a->left = b->right;
	b->right = a;

	return( b );
}

/**
Função para executar uma rotação simples á esquerda e depois a direita.
*/

avl_node_t_revisao *avl_rotate_leftright_revisao( avl_node_t_revisao *node ) {
	avl_node_t_revisao *a = node;
	avl_node_t_revisao *b = a->left;
	avl_node_t_revisao *c = b->right;
	
	a->left = c->right;
	b->right = c->left; 
	c->left = b;
	c->right = a;

	return( c );
}

/**
Função para executar uma rotação simples a direita e depois a esquerda.
*/

avl_node_t_revisao *avl_rotate_rightleft_revisao( avl_node_t_revisao *node ) {
	avl_node_t_revisao *a = node;
	avl_node_t_revisao *b = a->right;
	avl_node_t_revisao *c = b->left;
	
	a->right = c->left;
	b->left = c->right; 
	c->right = b;
	c->left = a;

	return( c );
}

/**
Função para executar uma rotação dupla a direita.
*/

avl_node_t_revisao *avl_rotate_rightright_revisao( avl_node_t_revisao *node ) {
	avl_node_t_revisao *a = node;
	avl_node_t_revisao *b = a->right;
	
	a->right = b->left;
	b->left = a; 

	return( b );
}

/**
Função para executar o balanceamento de um nodo.
*/

avl_node_t_revisao *avl_balance_node_revisao( avl_node_t_revisao *node ) {
	avl_node_t_revisao *newroot = NULL;

	/* Balance our children, if they exist. */
	if( node->left )
		node->left  = avl_balance_node_revisao( node->left  );
	if( node->right ) 
		node->right = avl_balance_node_revisao( node->right );

	int bf = avl_balance_factor_revisao( node );

	if( bf >= 2 ) {
		/* Left Heavy */	

		if( avl_balance_factor_revisao( node->left ) <= -1 ) 
			newroot = avl_rotate_leftright_revisao( node );
		else 
			newroot = avl_rotate_leftleft_revisao( node );

	} else if( bf <= -2 ) {
		/* Right Heavy */

		if( avl_balance_factor_revisao( node->right ) >= 1 )
			newroot = avl_rotate_rightleft_revisao( node );
		else 
			newroot = avl_rotate_rightright_revisao( node );

	} else {
		/* This node is balanced -- no change. */

		newroot = node;
	}

	return( newroot );	
}

/**
Função para executar o balanceamento de uma arvore.
*/

void avl_balance_revisao( avl_tree_t_revisao *tree ) {

	avl_node_t_revisao *newroot = NULL;

	newroot = avl_balance_node_revisao( tree->root );

	if( newroot != tree->root )  {
		tree->root = newroot; 
	}
}


/**
Função para fazer uma inserção na Avl.
*/

int avl_insert_revisao( avl_tree_t_revisao *tree, long idRevisao, char* timeStamp) {
	avl_node_t_revisao *node = NULL;
	avl_node_t_revisao *next = NULL;
	avl_node_t_revisao *last = NULL;
	


		/* Primeiro caso, quando a Avl ainda nao tem revisões*/ 	
		if( tree->root == NULL ) {
			
			node = avl_create_node_revisao();
			
			node->idRevisao = idRevisao;
			node->timeStamp = strndup(timeStamp,strlen(timeStamp));
			
			
		
			tree->root = node;
			tree->quantos = tree->quantos + 1;
		

		/* Ja temos revisoes inseridas, logo temos de definir onde colocar as proximas. */
		} else {
			next = tree->root;

			while( next != NULL ) {
				last = next;

				if( idRevisao < next->idRevisao ) {
					next = next->left;

				} else if( idRevisao > next->idRevisao ) {
					next = next->right;
					/* Quando a revisão que pretendemos inserir, ja se encontra na Avl.*/
				} else if(idRevisao == next->idRevisao){
					return 1;
				} 
			}

			node = avl_create_node_revisao();

			node->idRevisao = idRevisao;
			node->timeStamp = strndup(timeStamp,strlen(timeStamp));



			tree->quantos= tree->quantos + 1;

			if( idRevisao < last->idRevisao ) last->left = node;
			if( idRevisao > last->idRevisao ) last->right = node;
		
		}	
		avl_balance_revisao( tree );
		return 0;
		
}

/**
Função para libertar a memoria de um nodo.
*/

void free_tree_root_revisoes( avl_node_t_revisao *node ) {

	if(!node){
		return;
	}

	free(node->timeStamp);

	free_tree_root_revisoes(node->left);
	free_tree_root_revisoes(node->right);
	free(node);
}

/**
Função para libertar a memoria de uma Avl.
*/

void free_tree_revisoes( avl_tree_t_revisao *tree ) {

	if(!tree){
		return;
	}

	free_tree_root_revisoes(tree->root);
	free(tree);
}

/**
----------------------------------------------------- QUERIES ----------------------------------------------
*/

/*
Função para fazer a procura de uma revisao na arvore, dado um id da revisão.
Retorna NULL, caso nao exista;
*/


avl_node_t_revisao *avl_find_revisao( avl_tree_t_revisao *tree, long id ) {
	avl_node_t_revisao *current = tree->root;

	while( current && current->idRevisao != id ) {
		if( id > current->idRevisao )
			current = current->right;
		else
			current = current->left;
	}

	return current;
}

/**
Querie10.
Retorna uma determinada revisao de um determinado artigo, dado um id de artigo e um id de revisao.
Função Auxiliar que vai devolver o timeStamp pretendido de uma determinada revisão.
*/

char* querie10Aux(avl_tree_t_revisao *tree, long id){
	avl_node_t_revisao* nodo = avl_find_revisao(tree,id);
	if(nodo==NULL){
		return NULL;
	}
	else{
		return nodo->timeStamp;
	}
}


