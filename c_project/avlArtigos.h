#ifndef avlArtigos_H
#define avlArtigos_H

/**
----------------------------------------------ESTRUTURAS-------------------------------------------------
**/

/**
------------------------------------- 1)Estruturas da Avl de Artigos. -----------------------------------
*/

/**
1.1) Definiçao da estrutura de um nodo da AVL.
*/

typedef struct avl_node_s avl_node_t;

/**
1.2) Definição da estrutura da cabeça da AVL
*/

typedef struct avl_tree_s avl_tree_t;

/** 
--------------------------------- 2) Estruturas Auxiliares usadas nas Queries. ----------------------------
*/

/**
2.1) Definição da Estrutura Auxiliar usada na Querie6.
*/

typedef struct artigoAndIdentifier AAI;

/**
2.2) Definição da Estrutura Auxiliar Usada na Querie8.
*/

typedef struct id_caracteres idchar;

/**
2.3) Definição da Estrutura Auxiliar Usada na Querie9 (Lista Ligada).
*/

/**
2.3.1) Definição da Estrutura do nodo da lista ligada.
*/

typedef struct linkedList_node_s linkedList_node_t;

/**
2.3.2) Definição da Estrutura da cabeça da lista ligada.
*/

typedef struct linkedList_s linkedList_t;

/**
---------------------------------- FUNÇÕES MANIPULADORAS DAS ESTRUTURAS --------------------------------------
*/

/**
--------------------------------------------- Lista Ligada (Querie9) ----------------------------------------
*/

/**
Função para alocar memoria para a criação da cabeça da Lista Ligada
*/

linkedList_t* linkedList_create();

/**
Função para alocar memoria para a criaçao de um nodo da Lista Ligada.
*/

linkedList_node_t* linkedList_create_node();

/**
Função para fazer a inserção de um valor na Lista Ligada.
*/

void insertNodeL(linkedList_t* lista, char* value);


/**
---------------------------------------------- Avl de Artigos ----------------------------------------------
*/

/**
Funçao para alocar memória para uma nova cabeça da Avl.
*/

avl_tree_t* avl_create();

/**
Função para alocar memória para a criação de um nodo da Avl.
*/

avl_node_t* avl_create_node();

/**
Função para calcular a altura de um nodo da Avl, recursivamente. 
*/

int avl_node_height( avl_node_t* node );

/**
Função para calcular o nivel de balanceamento de um nodo.
*/

int avl_balance_factor( avl_node_t *node );

/**
Função para executar uma dupla rotação á esquerda.
*/

avl_node_t *avl_rotate_leftleft( avl_node_t *node );

/**
Função para executar uma rotação simples á esquerda e depois a direita.
*/

avl_node_t *avl_rotate_leftright( avl_node_t *node );

/**
Função para executar uma rotação simples a direita e depois a esquerda.
*/

avl_node_t *avl_rotate_rightleft( avl_node_t *node );

/**
Função para executar uma rotação dupla a direita.
*/

avl_node_t *avl_rotate_rightright( avl_node_t *node );

/**
Função para executar o balanceamento de uma arvore.
*/

void avl_balance( avl_tree_t *tree );

/**
Função para fazer uma inserção na Avl.
*/

int avl_insert( avl_tree_t *tree, char* titulo, long idTitulo,long ncaracteres,long npalavras, long idRevisao, char* data );

/**
Função para libertar a memoria de uma Avl.
*/

void free_tree_artigos( avl_tree_t *tree );

/**
----------------------------------------------------- QUERIES ----------------------------------------------
*/

/*
Função para fazer a procura de um artigo na arvore, dado um id do titulo.
*/

avl_node_t *avl_find_artigo( avl_tree_t *tree, long idTitulo );

/**
Querie1.
Retorna o numero total de artigos.
*/

long querie1(avl_tree_t* tree);

/**
Querie2.
Retorna o numero de artigos únicos.
*/

long querie2(avl_tree_t* tree);

/**
Querie3.
Retorna o numero de revisoes unicas.
*/

long querie3(avl_tree_t* tree);

/**
Querie6.
Retorna os 20 maiores artigos, em termos de numero de caracteres.
*/

long* querie6(avl_tree_t* artigos);

/**
Querie7.
Retorna o titulo de um artigo, dado um id.
*/

char* querie7(avl_tree_t* tree, long id);

/**
Querie8.
Retorna os artigos com mais palavras.
*/

long* querie8(avl_tree_t* tree, int size);

/**
Querie9.
Retorna todos uns artigos que começam com um prefixo dado.
*/

char** querie9(avl_tree_t* tree, char* prefix);

/**
Querie10.
Retorna uma determinada revisao de um determinado artigo, dado um id de artigo e um id de revisao.
*/

char* querie10(avl_tree_t* tree, long article_id, long revision_id);

#endif