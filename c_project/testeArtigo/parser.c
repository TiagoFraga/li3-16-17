#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "avlArtigos.h"
#include "parser.h"


char* parseSecondLevel(xmlDocPtr doc, xmlNodePtr cur,char* codigo) {

	xmlChar *key;
	char* string;
	
	cur = cur->xmlChildrenNode;
	while (cur != NULL) {
	    if ((!xmlStrcmp(cur->name, (const xmlChar *)codigo))) {
		    key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
		    string = (char*)key;
		    xmlFree(key);
		}
	cur = cur->next;
	}
    return string;
}
/*
char* parseThirdLevel(xmlDocPtr doc, xmlNodePtr cur,char* codigo1, char* codigo2) {

	char* string;

	cur = cur->xmlChildrenNode;
	while (cur != NULL) {
	    if ((!xmlStrcmp(cur->name, (const xmlChar *)codigo1))) {
	    	string = parseSecondLevel(doc,cur,codigo2);
 	    }
	cur = cur->next;
	}
    return string;
}

char* parseFourthLevel(xmlDocPtr doc, xmlNodePtr cur,char* codigo1, char* codigo2, char* codigo3) {

	char* string;

	cur = cur->xmlChildrenNode;
	while (cur != NULL) {
	    if ((!xmlStrcmp(cur->name, (const xmlChar *)codigo1))) {
		    string = parseThirdLevel(doc,cur,codigo2,codigo3);
 	    }
	cur = cur->next;
	}
    return string;
}
*/

void parseDoc(avl_tree_t *tree, char *docname) {
	xmlDocPtr doc;
	xmlNodePtr cur;
	char* titulo = malloc(500*sizeof(char));
	
	


	doc = xmlParseFile(docname);
	
	if (doc == NULL ) {
		perror("Documento nao fez o parse correto");
		return;
	}
	
	cur = xmlDocGetRootElement(doc);
	
	if (cur == NULL) {
		perror("Documento Vazio");
		xmlFreeDoc(doc);
		return;
	}
	
	if (xmlStrcmp(cur->name, (const xmlChar *) "mediawiki")) {
		perror("Documento do tipo errado");
		xmlFreeDoc(doc);
		return;
	}
	
	cur = cur->xmlChildrenNode;
	
	while (cur != NULL) {
		
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"page"))){
			
			char* title = parseSecondLevel(doc,cur,"title");
			strcpy(titulo,title);

			long idT = atol(parseSecondLevel(doc,cur,"id"));
			

			//long idR = atof(parseThirdLevel(doc,cur,"revision","id"));
			//char* data = parseThirdLevel(doc,cur,"revision","timestamp");
			//char* user = parseFourthLevel(doc,cur,"revision","contributor","username");
			//long idU = atof(parseFourthLevel(doc,cur,"revision","contributor","id"));
			//printf("PARSER TITULO: %s\n", titulo);
			//printf("PARSER ID Titulo: %ld\n",idT );
			avl_insert(tree,titulo,idT);
		}
		cur = cur->next;
	}
	free(titulo);
	xmlFreeDoc(doc);
}




