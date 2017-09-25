#ifndef interface_H
#define interface_H


typedef struct TCD_istruct* TAD_istruct;


TAD_istruct init();
TAD_istruct load(TAD_istruct qs, int nsnaps, char* snaps_paths[]); 

	/*Querie1 -------------------------------------------------------------check*/
long all_articles(TAD_istruct qs);

	/*Querie2 -------------------------------------------------------------check*/
long unique_articles(TAD_istruct qs);

	/*Querie3 -------------------------------------------------------------check*/
long all_revisions(TAD_istruct qs);

	/*Querie4 -------------------------------------------------------------check*/
long* top_10_contributors(TAD_istruct qs);

	/*Querie5 -------------------------------------------------------------check*/
char* contributor_name(long contributor_id, TAD_istruct qs);

	/*Querie6 -------------------------------------------------------------check*/
long* top_20_largest_articles(TAD_istruct qs);

	/*Querie7 -------------------------------------------------------------check*/
char* article_title (long article_id, TAD_istruct qs);

	/*Querie8 -------------------------------------------------------------check*/
long* top_N_articles_with_more_words(int n, TAD_istruct qs);

	/*Querie9*/
char** titles_with_prefix (char* prefix, TAD_istruct qs);

	/*Querie10 -------------------------------------------------------------check*/
char* article_timestamp(long article_id, long revision_id, TAD_istruct qs);


TAD_istruct clean(TAD_istruct qs);

#endif