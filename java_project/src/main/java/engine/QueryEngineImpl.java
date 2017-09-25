package engine;

import li3.Interface;
import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.List;
import java.util.stream.Collectors;

public class QueryEngineImpl implements Interface {

    private Contribuidores contribuidores;
    private Artigos artigos;

    public void init() {
        this.contribuidores = new Contribuidores();
        this.artigos = new Artigos();
    }

    public void load(int nsnaps, ArrayList<String> snaps_paths) {
        Parser parser = new Parser(this.artigos, this.contribuidores);
        parser.load(snaps_paths);
    }

    public long all_articles() {
        return this.artigos.getTotal();
    }

    public long unique_articles() {
        return this.artigos.getUnicos();
    }

    public long all_revisions() {
        return this.artigos.getAllRevisions();
    }

    public ArrayList<Long> top_10_contributors() {
        List<Contribuidor> tmp;     
        HashMap<Long,Contribuidor> allContributors = contribuidores.getContribuidores();
        
        tmp = allContributors.values().stream()
              .sorted(new ComparatorContribuidor())
              .limit(10)
              .collect(Collectors.toList());

        ArrayList<Long> top_10 = new ArrayList<>(); 
        for(Contribuidor c: tmp){
            top_10.add(c.getIdUsername());
        }
        return top_10;
    }

    public String contributor_name(long contribuidor_id) {
        Contribuidor c = this.contribuidores.getContribuidores().get(contribuidor_id);
        return c.getUsername();
    }

    public ArrayList<Long> top_20_largest_articles() {
        List<Artigo> tmp;     
        HashMap<Long,Artigo> allArticles = artigos.getArtigosPorTitulo();
        
        tmp = allArticles.values().stream()
              .sorted(new ComparatorArtigoCaracteres())
              .limit(20)
              .collect(Collectors.toList());
        
 
        ArrayList<Long> top_20 = new ArrayList<>(); 
        for(Artigo a: tmp){
            top_20.add(a.getIdTitulo());
        }
        return top_20;
    }

    public String article_title(long article_id) {
       HashMap <Long,Artigo> lista = this.artigos.getArtigosPorTitulo();
       
       return lista.get(article_id).getTitulo();
    }

    public ArrayList<Long> top_N_articles_with_more_words(int n) {
        List<Artigo> tmp;     
        HashMap<Long,Artigo> allArticles = artigos.getArtigosPorTitulo();
        
        tmp = allArticles.values().stream()
              .sorted(new ComparatorArtigoPalavras())
              .limit(n)
              .collect(Collectors.toList());
        
        ArrayList<Long> top_N = new ArrayList<>(); 
        for(Artigo a: tmp){
            top_N.add(a.getIdTitulo());
        }
        return top_N;
    }

    public ArrayList<String> titles_with_prefix(String prefix) {
        List<String> tmp;
        tmp = this.artigos.getTitulosComPrefixo(prefix);
        Collections.sort(tmp,String.CASE_INSENSITIVE_ORDER);
        ArrayList<String> result = new ArrayList<>();
        tmp.forEach((s) -> {
            result.add(s);
        });
        return result;
    }

    public String article_timestamp(long article_id, long revision_id) {
        HashMap <Long,Artigo> lista = this.artigos.getArtigosPorTitulo();
        Artigo artg = lista.get(article_id);
        Revisoes rev = artg.getRevisoes();
        HashMap<Long,Revisao> maps = rev.getRevisoes();
        return maps.get(revision_id).getTimeStamp();
    }

    public void clean() {
        this.artigos = null;
        this.contribuidores = null;
    }
}
