#ifndef avlContribuidores_H
#define avlContribuidores_H

/**
----------------------------------------------ESTRUTURAS-------------------------------------------------
**/

/**
------------------------------------- 1)Estruturas da Avl de Contribuidores. -----------------------------------
*/

/**
1.1) Estrutura de um nodo da AVL.
*/

typedef struct avl_node_s_contribuidor avl_node_t_contribuidor;

/**
1.2) Estrutura da cabeça da AVL
*/

typedef struct avl_tree_s_contribuidor avl_tree_t_contribuidor;

/** 
--------------------------------- 2) Estruturas Auxiliares usadas nas Queries. ----------------------------
*/

/**
2.1) Estrutura Auxiliar usada na Querie4.
*/

typedef struct contribuidoresAndCount CAC;

/**
---------------------------------- FUNÇÕES MANIPULADORAS DAS ESTRUTURAS --------------------------------------
*/

/**
---------------------------------------------- Avl de Contribuidores ----------------------------------------------
*/

/**
Funçao para alocar memória para uma nova cabeça da Avl.
*/

avl_tree_t_contribuidor* avl_create_contribuidor();

/**
Função para alocar memória para a criação de um nodo da Avl.
*/

avl_node_t_contribuidor* avl_create_node_contribuidor();

/**
Função para calcular a altura de um nodo da Avl, recursivamente. 
*/

int avl_node_height_contribuidor( avl_node_t_contribuidor* node );

/**
Função para calcular o nivel de balanceamento de um nodo.
*/

int avl_balance_factor_contribuidor( avl_node_t_contribuidor *node );

/**
Função para executar uma dupla rotação á esquerda.
*/

avl_node_t_contribuidor *avl_rotate_leftleft_contribuidor( avl_node_t_contribuidor *node );

/**
Função para executar uma rotação simples á esquerda e depois a direita.
*/

avl_node_t_contribuidor *avl_rotate_leftright_contribuidor( avl_node_t_contribuidor *node );

/**
Função para executar uma rotação simples a direita e depois a esquerda.
*/

avl_node_t_contribuidor *avl_rotate_rightleft_contribuidor( avl_node_t_contribuidor *node );

/**
Função para executar uma rotação dupla a direita.
*/

avl_node_t_contribuidor *avl_rotate_rightright_contribuidor( avl_node_t_contribuidor *node );

/**
Função para executar o balanceamento de um nodo.
*/

avl_node_t_contribuidor *avl_balance_node_conrtibuidor( avl_node_t_contribuidor *node );

/**
Função para executar o balanceamento de uma arvore.
*/

void avl_balance_contribuidor( avl_tree_t_contribuidor *tree );

/**
Função para fazer uma inserção na Avl.
*/

void avl_insert_contribuidor( avl_tree_t_contribuidor *tree, char* username, long idUsername );

/**
Função para libertar a memoria de um nodo.
*/

void free_tree_root_contribuidores(avl_node_t_contribuidor *node);

/**
Função para libertar a memoria de uma Avl.
*/

void free_tree_contribuidores( avl_tree_t_contribuidor *tree );

/**
----------------------------------------------------- QUERIES ----------------------------------------------
*/

/*
Função para fazer a procura de um contribuidor na arvore, dado um id.
*/

avl_node_t_contribuidor *avl_find_contribuidor( avl_tree_t_contribuidor *tree, long id );

/**
Querie4.
Retorna o Top10 de contribuidores.
*/

long* querie4(avl_tree_t_contribuidor* tree);

/**
Querie5.
Retorna o username de um contribuidor, dado um id.
*/

char* querie5(avl_tree_t_contribuidor* tree, long id);


#endif