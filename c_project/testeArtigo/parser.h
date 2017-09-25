#ifndef parser_H
#define parser_H
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>


char* parseSecondLevel(xmlDocPtr doc, xmlNodePtr cur,char* codigo);
//char* parseThirdLevel(xmlDocPtr doc, xmlNodePtr cur,char* codigo1, char* codigo2);
//char* parseFourthLevel(xmlDocPtr doc, xmlNodePtr cur,char* codigo1, char* codigo2, char* codigo3);
void parseDoc(avl_tree_t *tree, char *docname);

#endif