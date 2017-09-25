#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "parser.h"

/**
------------------------------------------------ Parser do XML ---------------------------------------------
*/

/**
Função Auxiliar que é chamada quando só preciso descer um nivel, nas tags do xml.
*/

char* parseSecondLevel(xmlDocPtr doc, xmlNodePtr cur,char* codigo) {

	xmlChar *key;
	char* string;
	
	cur = cur->xmlChildrenNode;
	while (cur != NULL) {
	    if ((!xmlStrcmp(cur->name, (const xmlChar *)codigo))) {
		    key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);

		    if(key != NULL){
		    	string = malloc(sizeof(char)*1024);
		    	string = (char*)key;
		  	}
		}
		if((!xmlStrcmp(cur->name, (const xmlChar *)"ip"))){
			string = "-1";
			return string;
		}
	cur = cur->next;
	}
    return string;
}

/**
Função Auxiliar que é chamada quando é preciso descer dois niveis, nas tags do xml.
*/

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

/**
Função Auxiliar que é chamada quando é preciso descer três niveis, nas tags do xml.
*/

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

/**
Função principal que faz o parser do XML.
A casa iteração nos artigos do XML, é feita as inserções nas Avl's.
*/

void parseDoc(avl_tree_t *artigos,avl_tree_t_contribuidor *contribuidores, char *docname) {
    xmlDocPtr doc;
    xmlNodePtr cur;
    int r;
   
 
    char* titulo;
    char* username;
    char* data;
    char* texto;   
 
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
            titulo = strndup(title,strlen(title));
 
            long idT = atol(parseSecondLevel(doc,cur,"id"));
           
            long idR = atof(parseThirdLevel(doc,cur,"revision","id"));
           
            char* timeStamp = parseThirdLevel(doc,cur,"revision","timestamp");
            data = strndup(timeStamp,strlen(timeStamp));
       
            long idU = atof(parseFourthLevel(doc,cur,"revision","contributor","id"));
           
            char* user = parseFourthLevel(doc,cur,"revision","contributor","username");
            username = strndup(user,strlen(user));
 
            char* text = parseThirdLevel(doc,cur,"revision","text");
            texto = strndup(text,strlen(text));
 
 
            long conta[2];
            palavras_and_length(texto,conta);
            
            //FILE *fdFile = fopen("lengths.txt", "a");
            //fprintf(fdFile, "%lu;%lu;%lu\n", idT, conta[0], conta[1]);
            //fclose(fdFile);
           
            r = avl_insert(artigos,titulo,idT,conta[0],conta[1],idR,data);
 
            if( (strcmp(username,"-1")!= 0) && (idU != (-1)) && (r == 0)){  
                avl_insert_contribuidor(contribuidores, username, idU);
 
            }
            
            free(titulo);
            free(texto);   
            free(data);
            free(username);
           
        }
    cur = cur->next;
    }
 
    xmlFreeDoc(doc);
}

/**
---------------------------------------- FUNÇÕES AUXILIARES -------------------------------------------------
*/

/**
Função que guarda num array de duas posiçoões, 
o numero de caracteres e o numero de palavras de um artigo.
*/

void palavras_and_length(char* text,long* conta){
    long palavras = 0;
    long i;
 
    for(i = 0; text[i] ; ++i){ 
        if(isspace(text[i]) == 0 && (isspace(text[i+1]) > 0 || text[i+1] == '\0'))
            ++palavras;
    }
    conta[0] = i;
    conta[1] = palavras;   
}

