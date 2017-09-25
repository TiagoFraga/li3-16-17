#ifndef avlRevisoesNodeRevisao_H
#define avlRevisoesNodeRevisao_H

typedef struct avl_node_s_node_revisao avl_node_t_node_revisao;
typedef struct avl_tree_s_node_revisao avl_tree_t_node_revisao;

avl_tree_t_node_revisao* avl_create_node_revisao();
avl_node_t_node_revisao* avl_create_node_node_revisao();
int avl_node_height_node_revisao( avl_node_t_node_revisao* node );
int avl_balance_factor_node_revisao( avl_node_t_node_revisao *node );
avl_node_t_node_revisao *avl_rotate_leftleft_node_revisao( avl_node_t_node_revisao *node );
avl_node_t_node_revisao *avl_rotate_rightleft_node_revisao( avl_node_t_node_revisao *node );
avl_node_t_node_revisao *avl_rotate_rightright_node_revisao( avl_node_t_node_revisao *node );
avl_node_t_node_revisao *avl_balance_node_node_revisao( avl_node_t_node_revisao *node );
void avl_balance_node_revisao( avl_tree_t_node_revisao *tree );
void avl_insert_node_revisao( avl_tree_t_node_revisao *tree,long idRevisao, char* timeStamp);
//avl_node_t_node_revisao *avl_find_node_revisao( avl_tree_t_node_revisao *tree, long id );


#endif