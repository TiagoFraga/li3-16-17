#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "avlArtigos.h"
#include "parser.h"



int main(int argc, char* argv[]){
	avl_tree_t *tree = NULL;
	
	tree = avl_create();	
	
	parseDoc(tree,"snapshot_jan17");
	printf("\n \n \n ------------------------------TROCA DE FICHEIROS-------------------------------\n \n \n");
	parseDoc(tree,"snapshot_dec16");
	printf("\n \n \n ------------------------------TROCA DE FICHEIROS-------------------------------\n \n \n");
	parseDoc(tree,"snapshot_fev17");
	printf("\n \n \n ------------------------------TROCA DE FICHEIROS-------------------------------\n \n \n");

	printQuantos(tree);
	//printArtigosUnicos(tree);

	//avl_traverse_dfs(tree);

	
	return 0;
}