package li3;

import java.util.ArrayList;

public interface Interface {
    
    //check
    void init();
    
    //check
    void load(int nsnaps, ArrayList<String> snaps_paths);
    
    //check
    long all_articles();
    
    //check
    long unique_articles();

    //check
    long all_revisions();

    ArrayList<Long> top_10_contributors();

    //check
    String contributor_name(long contributor_id);

    ArrayList<Long> top_20_largest_articles();
    
    //check
    String article_title(long article_id);

    ArrayList<Long> top_N_articles_with_more_words(int n);

    //check
    ArrayList<String> titles_with_prefix(String prefix);
    
    //check
    String article_timestamp(long article_id, long revision_id);
    
    //check
    void clean();

}