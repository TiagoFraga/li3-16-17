#ifndef parser_H
#define parser_H
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include "avlArtigos.h"
#include "avlContribuidores.h"

/**
------------------------------------------------ Parser do XML ---------------------------------------------
*/

/**
Função Auxiliar que é chamada quando só preciso descer um nivel, nas tags do xml.
*/

char* parseSecondLevel(xmlDocPtr doc, xmlNodePtr cur,char* codigo);

/**
Função Auxiliar que é chamada quando é preciso descer dois niveis, nas tags do xml.
*/

char* parseThirdLevel(xmlDocPtr doc, xmlNodePtr cur,char* codigo1, char* codigo2);

/**
Função Auxiliar que é chamada quando é preciso descer três niveis, nas tags do xml.
*/

char* parseFourthLevel(xmlDocPtr doc, xmlNodePtr cur,char* codigo1, char* codigo2, char* codigo3);

/**
Função principal que faz o parser do XML.
A casa iteração nos artigos do XML, é feita as inserções nas Avl's.
*/

void parseDoc(avl_tree_t *artigos,avl_tree_t_contribuidor *contribuidores, char *docname);

/**
---------------------------------------- FUNÇÕES AUXILIARES -------------------------------------------------
*/

/**
Função que guarda num array de duas posiçoões, 
o numero de caracteres e o numero de palavras de um artigo.
*/

void palavras_and_length(char* text,long* conta);


#endif





