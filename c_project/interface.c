#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <assert.h>
#include "parser.h"
#include "avlArtigos.h"
#include "avlContribuidores.h"
#include "interface.h"

typedef struct TCD_istruct{

	avl_tree_t *artigos;
	avl_tree_t_contribuidor *contribuidores;
	
}TCD_istruct;



TAD_istruct init(){
	TAD_istruct livro = NULL;

	livro = malloc(sizeof(TCD_istruct));

	livro->artigos = avl_create();
	livro->contribuidores = avl_create_contribuidor();

	return livro;
}


TAD_istruct load(TAD_istruct qs, int nsnaps, char* snaps_paths[]){
	int i;
	for(i=0; i<nsnaps; i++){
		parseDoc(qs->artigos,qs->contribuidores,snaps_paths[i]);
	}
	return qs;

}

/* Querie 1 */
long all_articles(TAD_istruct qs){
	return querie1(qs->artigos);
}

/* Querie 2 */
long unique_articles(TAD_istruct qs){
	return querie2(qs->artigos);
}

/* Querie 3 */
long all_revisions (TAD_istruct qs){
	return querie3(qs->artigos);
}

/* Querie 4 */
long* top_10_contributors(TAD_istruct qs){
	return querie4(qs->contribuidores);
}

/* Querie5 */
char* contributor_name(long contributor_id, TAD_istruct qs){
	return querie5(qs->contribuidores, contributor_id);
}

/*Querie6*/
long* top_20_largest_articles(TAD_istruct qs){
    return querie6(qs->artigos);
}

/* Querie7 */
char* article_title (long article_id, TAD_istruct qs){ 
	return querie7(qs->artigos,article_id);
}

/* Querie8 */
long* top_N_articles_with_more_words(int n, TAD_istruct qs){	
	return querie8(qs->artigos,n);
}

/*Querie9 */
char** titles_with_prefix (char* prefix, TAD_istruct qs){
	return querie9(qs->artigos,prefix);
}

/* Querie 10*/
char* article_timestamp(long article_id, long revision_id, TAD_istruct qs){
	return querie10(qs->artigos,article_id,revision_id);
}


TAD_istruct clean(TAD_istruct qs){
	
	free_tree_contribuidores(qs->contribuidores);
	free_tree_artigos(qs->artigos);
	free(qs);

	return qs;
}

