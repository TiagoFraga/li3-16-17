#ifndef avlContribuidores_H
#define avlContribuidores_H

typedef struct avl_node_s avl_node_t;
typedef struct avl_tree_s avl_tree_t;

avl_tree_t* avl_create();
avl_node_t* avl_create_node();
int avl_node_height( avl_node_t* node );
int avl_balance_factor( avl_node_t *node );
avl_node_t *avl_rotate_leftleft( avl_node_t *node );
avl_node_t *avl_rotate_rightleft( avl_node_t *node );
avl_node_t *avl_rotate_rightright( avl_node_t *node );
avl_node_t *avl_balance_node( avl_node_t *node );
void avl_balance( avl_tree_t *tree );
void avl_insert( avl_tree_t *tree, char* username, long idUsername );
avl_node_t *avl_find( avl_tree_t *tree, long id );
void adicionaQuantidade(avl_node_t *node);

#endif