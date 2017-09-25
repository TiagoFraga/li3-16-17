#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <assert.h>
#include "avlRevisoes.h"
#include "avlNodeRevisao.h"
#include "parser.h"

struct avl_node_s_node_revisao {
	struct avl_node_s_node_revisao *left;
	struct avl_node_s_node_revisao *right;
	
	long idRevisao;
	char* timeStamp;

};



struct avl_tree_s_node_revisao {
	struct avl_node_s_node_revisao *root;
	long quantos;
};




/* Create a new AVL tree. */
avl_tree_t_node_revisao* avl_create_node_revisao() {
	avl_tree_t_node_revisao* tree = NULL;

	if( ( tree = malloc( sizeof( avl_tree_t_node_revisao ) ) ) == NULL ) {
		return NULL;
	}

	tree->root = NULL;
	tree->quantos = 0;

	return tree;
}

/* Initialize a new node. */
avl_node_t_node_revisao* avl_create_node_node_revisao() {
	avl_node_t_node_revisao *node = NULL;
	

	if( ( node = malloc( sizeof( avl_node_t_node_revisao ) ) ) == NULL ) {
		return NULL;
	}

	node->idRevisao = 0;
	node->timeStamp = malloc(500*sizeof(char));

	node->left = NULL;
	node->right = NULL;

	return node;	
}

/* Find the height of an AVL node recursively */
int avl_node_height_node_revisao( avl_node_t_node_revisao* node ) {
	int height_left = 0;
	int height_right = 0;

	if( node->left ) height_left = avl_node_height_node_revisao( node->left );
	if( node->right ) height_right = avl_node_height_node_revisao( node->right );

	return height_right > height_left ? ++height_right : ++height_left;
}

/* Find the balance of an AVL node */
int avl_balance_factor_node_revisao( avl_node_t_node_revisao *node ) {
	int bf = 0;

	if( node->left  ) bf += avl_node_height_node_revisao( node->left );
	if( node->right ) bf -= avl_node_height_node_revisao( node->right );

	return bf ;
}

/* Left Left Rotate */
avl_node_t_node_revisao *avl_rotate_leftleft_node_revisao( avl_node_t_node_revisao *node ) {
 	avl_node_t_node_revisao *a = node;
	avl_node_t_node_revisao *b = a->left;
	
	a->left = b->right;
	b->right = a;

	return( b );
}

/* Left Right Rotate */
avl_node_t_node_revisao *avl_rotate_leftright_node_revisao( avl_node_t_node_revisao *node ) {
	avl_node_t_node_revisao *a = node;
	avl_node_t_node_revisao *b = a->left;
	avl_node_t_node_revisao *c = b->right;
	
	a->left = c->right;
	b->right = c->left; 
	c->left = b;
	c->right = a;

	return( c );
}

/* Right Left Rotate */
avl_node_t_node_revisao *avl_rotate_rightleft_node_revisao( avl_node_t_node_revisao *node ) {
	avl_node_t_node_revisao *a = node;
	avl_node_t_node_revisao *b = a->right;
	avl_node_t_node_revisao *c = b->left;
	
	a->right = c->left;
	b->left = c->right; 
	c->right = b;
	c->left = a;

	return( c );
}

/* Right Right Rotate */
avl_node_t_node_revisao *avl_rotate_rightright_node_revisao( avl_node_t_node_revisao *node ) {
	avl_node_t_node_revisao *a = node;
	avl_node_t_node_revisao *b = a->right;
	
	a->right = b->left;
	b->left = a; 

	return( b );
}

/* Balance a given node */
avl_node_t_node_revisao *avl_balance_node_node_revisao( avl_node_t_node_revisao *node ) {
	avl_node_t_node_revisao *newroot = NULL;

	/* Balance our children, if they exist. */
	if( node->left )
		node->left  = avl_balance_node_node_revisao( node->left  );
	if( node->right ) 
		node->right = avl_balance_node_node_revisao( node->right );

	int bf = avl_balance_factor_node_revisao( node );

	if( bf >= 2 ) {
		/* Left Heavy */	

		if( avl_balance_factor_node_revisao( node->left ) <= -1 ) 
			newroot = avl_rotate_leftright_node_revisao( node );
		else 
			newroot = avl_rotate_leftleft_node_revisao( node );

	} else if( bf <= -2 ) {
		/* Right Heavy */

		if( avl_balance_factor_node_revisao( node->right ) >= 1 )
			newroot = avl_rotate_rightleft_node_revisao( node );
		else 
			newroot = avl_rotate_rightright_node_revisao( node );

	} else {
		/* This node is balanced -- no change. */

		newroot = node;
	}

	return( newroot );	
}

/* Balance a given tree */
void avl_balance_node_revisao( avl_tree_t_node_revisao *tree ) {

	avl_node_t_node_revisao *newroot = NULL;

	newroot = avl_balance_node_node_revisao( tree->root );

	if( newroot != tree->root )  {
		tree->root = newroot; 
	}
}


/* Insert a new node. */
void avl_insert_node_revisao( avl_tree_t_node_revisao *tree, long idRevisao, char* timeStamp) {
	avl_node_t_node_revisao *node = NULL;
	avl_node_t_node_revisao *next = NULL;
	avl_node_t_node_revisao *last = NULL;
	


		/* Well, there must be a first case */ 	
		if( tree->root == NULL ) {
			
			node = avl_create_node_node_revisao();
			
			node->idRevisao = idRevisao;
			strcpy(node->timeStamp,timeStamp);
			printf("Revisao: %ld\n",node->idRevisao );
			printf("TimeStamp: %s\n",node->timeStamp );
			
			
			
		
			tree->root = node;
			tree->quantos = tree->quantos + 1;
		

		/* Okay.  We have a root already.  Where do we put this? */
		} else {
			next = tree->root;

			while( next != NULL ) {
				last = next;

				if( idRevisao < next->idRevisao ) {
					next = next->left;

				} else if( idRevisao > next->idRevisao ) {
					next = next->right;

				/* Have we already inserted this node? */
				} else if( idRevisao == next->idRevisao ) {
					/* This shouldn't happen. */	
				}
			}

			node = avl_create_node_node_revisao();

			node->idRevisao = idRevisao;
			strcpy(node->timeStamp,timeStamp);
			printf("Revisao: %ld\n",node->idRevisao );
			printf("TimeStamp: %s\n",node->timeStamp );	



			tree->quantos= tree->quantos + 1;

			if( idRevisao < last->idRevisao ) last->left = node;
			if( idRevisao > last->idRevisao ) last->right = node;
		
		}	
		avl_balance_node_revisao( tree );
		
}

/*

void avl_traverse_node_dfs( avl_node_t *node, int depth ) {
	int i = 0;

	if( node->left ) avl_traverse_node_dfs( node->left, depth + 2 );

	for( i = 0; i < depth; i++ ) putchar( ' ' );

	if( node->right ) avl_traverse_node_dfs( node->right, depth + 2 );
}


void avl_traverse_dfs( avl_tree_t *tree ) {
	avl_traverse_node_dfs( tree->root, 0 );
}

*/


/* Find the node containing a given idRevisao 

avl_node_t *avl_find( avl_tree_t *tree, long id ) {
	avl_node_t *current = tree->root;

	while( current && current->idRevisao != id ) {
		if( id > current->idRevisao )
			current = current->right;
		else
			current = current->left;
	}

	return current;
}

*/

/*

void avl_traverse_node_dfs( avl_node_t *node, int depth ) {
	int i = 0;

	if( node->left ) avl_traverse_node_dfs( node->left, depth + 2 );

	for( i = 0; i < depth; i++ ) putchar( ' ' );
	

	if( node->right ) avl_traverse_node_dfs( node->right, depth + 2 );
}


void avl_traverse_dfs( avl_tree_t *tree ) {
	avl_traverse_node_dfs( tree->root, 0 );
}

*/
