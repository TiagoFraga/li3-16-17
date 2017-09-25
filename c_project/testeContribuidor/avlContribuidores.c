#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <assert.h>
#include "avlContribuidores.h"
#include "parser.h"

struct avl_node_s {
	struct avl_node_s *left;
	struct avl_node_s *right;
	char* username;
	long idUsername;
	long quantidade;

};



struct avl_tree_s {
	struct avl_node_s *root;
	long quantos;
};




/* Create a new AVL tree. */
avl_tree_t* avl_create() {
	avl_tree_t* tree = NULL;

	if( ( tree = malloc( sizeof( avl_tree_t ) ) ) == NULL ) {
		return NULL;
	}

	tree->root = NULL;
	tree->quantos = 0;

	return tree;
}

/* Initialize a new node. */
avl_node_t* avl_create_node() {
	avl_node_t *node = NULL;
	

	if( ( node = malloc( sizeof( avl_node_t ) ) ) == NULL ) {
		return NULL;
	}

	node->left = NULL;
	node->right = NULL;

	node->username = malloc(500*sizeof(char));
	node->idUsername = 0;
	node->quantidade = 0;


	return node;	
}

/* Find the height of an AVL node recursively */
int avl_node_height( avl_node_t* node ) {
	int height_left = 0;
	int height_right = 0;

	if( node->left ) height_left = avl_node_height( node->left );
	if( node->right ) height_right = avl_node_height( node->right );

	return height_right > height_left ? ++height_right : ++height_left;
}

/* Find the balance of an AVL node */
int avl_balance_factor( avl_node_t *node ) {
	int bf = 0;

	if( node->left  ) bf += avl_node_height( node->left );
	if( node->right ) bf -= avl_node_height( node->right );

	return bf ;
}

/* Left Left Rotate */
avl_node_t *avl_rotate_leftleft( avl_node_t *node ) {
 	avl_node_t *a = node;
	avl_node_t *b = a->left;
	
	a->left = b->right;
	b->right = a;

	return( b );
}

/* Left Right Rotate */
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

/* Right Left Rotate */
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

/* Right Right Rotate */
avl_node_t *avl_rotate_rightright( avl_node_t *node ) {
	avl_node_t *a = node;
	avl_node_t *b = a->right;
	
	a->right = b->left;
	b->left = a; 

	return( b );
}

/* Balance a given node */
avl_node_t *avl_balance_node( avl_node_t *node ) {
	avl_node_t *newroot = NULL;

	/* Balance our children, if they exist. */
	if( node->left )
		node->left  = avl_balance_node( node->left  );
	if( node->right ) 
		node->right = avl_balance_node( node->right );

	int bf = avl_balance_factor( node );

	if( bf >= 2 ) {
		/* Left Heavy */	

		if( avl_balance_factor( node->left ) <= -1 ) 
			newroot = avl_rotate_leftright( node );
		else 
			newroot = avl_rotate_leftleft( node );

	} else if( bf <= -2 ) {
		/* Right Heavy */

		if( avl_balance_factor( node->right ) >= 1 )
			newroot = avl_rotate_rightleft( node );
		else 
			newroot = avl_rotate_rightright( node );

	} else {
		/* This node is balanced -- no change. */

		newroot = node;
	}

	return( newroot );	
}

/* Balance a given tree */
void avl_balance( avl_tree_t *tree ) {

	avl_node_t *newroot = NULL;

	newroot = avl_balance_node( tree->root );

	if( newroot != tree->root )  {
		tree->root = newroot; 
	}
}

void adicionaQuantidade(avl_node_t *node){
	node->quantidade = node->quantidade + 1;
	printf("JA EXISTE, CONSTRIBUIDOR: %s\n", node->username );
	printf("QUANTIDADE: %ld\n \n",node->quantidade );
}

/* Insert a new node. */
void avl_insert( avl_tree_t *tree, char* username, long idUsername ) {
	avl_node_t *node = NULL;
	avl_node_t *next = NULL;
	avl_node_t *last = NULL;
	avl_node_t *current = avl_find(tree, idUsername);

	
	if (current == NULL){

		


		/* Well, there must be a first case */ 	
		if( tree->root == NULL ) {
			node = avl_create_node();
			
			strcpy(node->username,username);
			node->idUsername= idUsername;
			node->quantidade = 1;
			
			printf("Contribuidor: %s\n",node->username );
			printf("id: %ld\n", node->idUsername);
		
			tree->root = node;
			tree->quantos = tree->quantos + 1;
		

		/* Okay.  We have a root already.  Where do we put this? */
		
		} else {
			next = tree->root;

			while( next != NULL ) {
				last = next;

				if( idUsername < next->idUsername ) {
					next = next->left;

				} else if( idUsername > next->idUsername ) {
					next = next->right;

				} 
			}

			node = avl_create_node();

			strcpy(node->username,username);
			node->idUsername = idUsername;
			node->quantidade = 1;
			
			printf("Contribuidor: %s\n",node->username );
			printf("id: %ld\n", node->idUsername);
			printf("NOVO NODO\n \n");
			
			tree->quantos= tree->quantos + 1;

			if( idUsername < last->idUsername ) last->left = node;
			if( idUsername > last->idUsername ) last->right = node;
		
		}	
		avl_balance( tree );
	
	}

	else{
		/*current!=NULL*/
		adicionaQuantidade(current);

	}

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


/* Find the node containing a given idUsername */

avl_node_t *avl_find( avl_tree_t *tree, long id ) {
	avl_node_t *current = tree->root;

	while( current && current->idUsername != id ) {
		if( id > current->idUsername )
			current = current->right;
		else
			current = current->left;
	}

	return current;
}

/*

void avl_traverse_node_dfs( avl_node_t *node, int depth ) {
	int i = 0;

	if( node->left ) avl_traverse_node_dfs( node->left, depth + 2 );

	for( i = 0; i < depth; i++ ) putchar( ' ' );
	printf( "%d: %d\n", node->idUsername, avl_balance_factor( node ) );

	if( node->right ) avl_traverse_node_dfs( node->right, depth + 2 );
}


void avl_traverse_dfs( avl_tree_t *tree ) {
	avl_traverse_node_dfs( tree->root, 0 );
}

*/

