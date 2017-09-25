#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "interface.h"



int main(int argc, char* argv[]){
	TAD_istruct livro = NULL;
	int i;
	int j,k;
	char* snapPaths[3] ={"snapshot_dec16","snapshot_jan17","snapshot_fev17"}; 
	long allArticles,uniqueArticles,allRevisions;
	
	

	livro = init();
	livro = load(livro,3,snapPaths);
	printf("Init e Load feito.\n\n" );
	

	/* Querie 1 */
	allArticles = all_articles(livro);
	printf("Numero de Artigos: %ld\n\n",allArticles);

	/* Querie 2 */ 
	uniqueArticles =  unique_articles(livro);
	printf("Numero de Artigos Unicos: %ld\n\n",uniqueArticles);

	/* Querie 3 */
	allRevisions =  all_revisions(livro);

	printf("Numero de Revisoes: %ld\n\n",allRevisions);

	/* Querie 4 */	
	long* top10 =  top_10_contributors(livro);
	for(i=0; i<10;i++){
		printf("Rank %d Contribuidores: %ld\n",i,top10[i]);
	}
	printf("\n");

	/* Querie 5 */
	char* name = contributor_name(1000,livro);
	printf("Nome do Contribuidor: %s\n\n",name);
	
	/* Querie 6 */
	long* top20 = top_20_largest_articles(livro);
	for(j=0; j<20;j++){
		printf("Rank %d Artigos: %ld\n",j,top20[j]);
	}
	printf("\n");

	/* Querie 7 */
	char* titulo = article_title(580,livro);
	printf("Titulo Artigo: %s\n\n",titulo);

	/* Querie 8 */
	long* topN = top_N_articles_with_more_words(15,livro);
	for(k=0; k<15;k++){
		printf("Rank %d Artigos: %ld\n",k,topN[k]);
	}
	printf("\n");

	/* Querie 9 */
	char** prefix_list = titles_with_prefix("Anax",livro);
	i=0;
    while(prefix_list[i]!=NULL){
    	printf("Prefixo: %s\n",prefix_list[i]);
    	i++;
    }
    printf("\n");

	/* Querie 10 */
	char* timestamp = article_timestamp(580,756927412,livro);
	printf("Timestamp: %s\n\n",timestamp);

	clean(livro);
	printf("Clean Feito\n");
	return 0;
}

