package engine;

import engine.comparators.ArticleWords;
import java.util.ArrayList;
import java.util.List;
import java.util.Collection;
import java.util.Collections;
import java.util.HashMap;

public class Artigos {
    
    /*---------------------------------VARIAVEIS DA CLASSE------------------------------------*/
    
    private long total;
    private long unicos;
    private long allRevisions;
    private HashMap<Long, Artigo> artigosPorTitulo;

    /*------------------------------------CONSTRUTORES----------------------------------------*/
    
     public Artigos() {
        this.total = 0;
        this.unicos = 0;
        this.allRevisions = 0;
        this.artigosPorTitulo = new HashMap<>();
    }
   
    public Artigos(Artigos a){
        this.total = a.getTotal();
        this.unicos = a.getUnicos();
        this.allRevisions = a.getAllRevisions();
        this.artigosPorTitulo = a.getArtigosPorTitulo();
    }
    
    /*-------------------------------- GET'S & SET'S ----------------------------------------*/
    
    public long getTotal() {
        return total;
    }

    public void setTotal(long total) {
        this.total = total;
    }

    public long getUnicos() {
        return unicos;
    }

    public void setUnicos(long unicos) {
        this.unicos = unicos;
    }

    public long getAllRevisions() {
        return allRevisions;
    }

    public void setAllRevisions(long allRevisions) {
        this.allRevisions = allRevisions;
    }

    public HashMap<Long, Artigo> getArtigosPorTitulo() {
        HashMap<Long,Artigo> nova = new HashMap<>();
        artigosPorTitulo.values().forEach((a) -> {
            nova.put(a.getIdTitulo(),a);
        });
        return nova;
    }

    public void setArtigosPorTitulo(HashMap<Long, Artigo> artigosPorTitulo) {
        this.artigosPorTitulo = artigosPorTitulo;
    }
    
    /*-----------------------------------METODOS----------------------------------------------*/
    
    public boolean insereArtigo(Artigo artigo, long idRevisao, String data){
        boolean inseriu = false;
        boolean articleExits = this.artigosPorTitulo.containsKey(artigo.getIdTitulo());
        
        if(articleExits == false){
            Revisao revisao = new Revisao(idRevisao,data);
            Revisoes mapRevisoes = new Revisoes();
            mapRevisoes.insereRevisao(revisao);
            artigo.insereMapRevisaoArtigo(mapRevisoes);
            this.artigosPorTitulo.put(artigo.getIdTitulo(), artigo);
            this.total++;
            this.unicos++;
            this.allRevisions++;
            inseriu = false;
        }else{
            Artigo artg = this.artigosPorTitulo.get(artigo.getIdTitulo());
            artg.setTitulo(artigo.getTitulo());
            if(artigo.getnCaracteres() > artg.getnCaracteres()){
                artg.setnCaracteres(artigo.getnCaracteres());
            }
            if(artigo.getnPalavras() > artg.getnPalavras()){
                artg.setnPalavras(artigo.getnPalavras());
            }
            Revisao revisao = new Revisao(idRevisao,data);
            inseriu = artg.getRevisoes().insereRevisao(revisao);
            if(inseriu == false){
                this.allRevisions++;
            }
            this.total++;
        }
        return inseriu;
    }
    
    public List<String> getTitulosComPrefixo(String prefix) {
        List<String> result = new ArrayList<>();

        for(Artigo artigo : this.artigosPorTitulo.values()) {
            if(artigo.getTitulo().startsWith(prefix)){
                result.add(artigo.getTitulo());
            }
        }
        
        return result;
    }
    
    public boolean equals(Object o){
        if(o == this)
            return true;
        if(o == null || o.getClass() != this.getClass())
            return false;
        Artigos a = (Artigos)o;
        return (a.getTotal() == this.total && a.getUnicos() == this.unicos 
                && a.getAllRevisions() == this.allRevisions 
                && a.getArtigosPorTitulo().equals(this.artigosPorTitulo));
    }
    
    
    public String toString(){
        StringBuilder sb = new StringBuilder();
        sb.append("Total de Artigos");
        sb.append(this.total);
        sb.append("Artigos Unicos");
        sb.append(this.unicos);
        sb.append("Numero de Revisoes");
        sb.append(this.allRevisions);
        sb.append("Artigos");
        sb.append(this.artigosPorTitulo.toString());
        return sb.toString();
    }
    
    public Artigos toClone(){
        return new Artigos(this);
    }
}
