#ifndef avlRevisoes_H
#define avlRevisoes_H

/**
----------------------------------------------ESTRUTURAS-------------------------------------------------
**/

/**
------------------------------------- 1)Estruturas da Avl de Revisoes. -----------------------------------
*/

/**
1.1) Estrutura de um nodo da AVL.
*/

typedef struct avl_node_s_revisao avl_node_t_revisao;

/**
1.2) Estrutura da cabeça da AVL
*/

typedef struct avl_tree_s_revisao avl_tree_t_revisao;

/**
---------------------------------- FUNÇÕES MANIPULADORAS DAS ESTRUTURAS --------------------------------------
*/

/**
---------------------------------------------- Avl de Revisões ----------------------------------------------
*/

/**
Funçao para alocar memória para uma nova cabeça da Avl.
*/

avl_tree_t_revisao* avl_create_revisao();

/**
Função para alocar memória para a criação de um nodo da Avl.
*/

avl_node_t_revisao* avl_create_node_revisao();

/**
Função para calcular a altura de um nodo da Avl, recursivamente. 
*/

int avl_node_height_revisao( avl_node_t_revisao* node );

/**
Função para calcular o nivel de balanceamento de um nodo.
*/

int avl_balance_factor_revisao( avl_node_t_revisao *node );

/**
Função para executar uma dupla rotação á esquerda.
*/

avl_node_t_revisao *avl_rotate_leftleft_revisao( avl_node_t_revisao *node );

/**
Função para executar uma rotação simples á esquerda e depois a direita.
*/

avl_node_t_revisao *avl_rotate_leftright_revisao( avl_node_t_revisao *node );

/**
Função para executar uma rotação simples a direita e depois a esquerda.
*/

avl_node_t_revisao *avl_rotate_rightleft_revisao( avl_node_t_revisao *node );

/**
Função para executar uma rotação dupla a direita.
*/

avl_node_t_revisao *avl_rotate_rightright_revisao( avl_node_t_revisao *node );

/**
Função para executar o balanceamento de uma arvore.
*/

void avl_balance_revisao( avl_tree_t_revisao *tree );

/**
Função para fazer uma inserção na Avl.
*/

int avl_insert_revisao( avl_tree_t_revisao *tree,long idRevisao, char* timeStamp);

/**
Função para libertar a memoria de uma Avl.
*/

void free_tree_revisoes( avl_tree_t_revisao *tree );

/**
----------------------------------------------------- QUERIES ----------------------------------------------
*/

/*
Função para fazer a procura de uma revisao na arvore, dado um id da revisão.
Retorna NULL, caso nao exista;
*/

avl_node_t_revisao *avl_find_revisao( avl_tree_t_revisao *tree, long id );

/**
Querie10.
Retorna uma determinada revisao de um determinado artigo, dado um id de artigo e um id de revisao.
Função Auxiliar que vai devolver o timeStamp pretendido de uma determinada revisão.
*/

char* querie10Aux(avl_tree_t_revisao *tree, long id);


#endif