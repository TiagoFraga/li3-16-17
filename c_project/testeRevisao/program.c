#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "avlRevisoes.h"
#include "avlNodeRevisao.h"
#include "parser.h"



int main(int argc, char* argv[]){
	avl_tree_t *tree = NULL;
	
	tree = avl_create();	
	
	parseDoc(tree,"snapshot_dec16");
	//parseDoc(tree,"snapshot_fev17");
	//parseDoc(tree,"snapshot_jan17");


	

	//avl_traverse_dfs(tree);

	
	return 0;
}