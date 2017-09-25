package engine;

import java.util.HashMap;
public class Artigo {
    
    /*---------------------------------VARIAVEIS DA CLASSE------------------------------------*/
    
    private String titulo;
    private long idTitulo;
    private long nCaracteres;
    private long nPalavras;
    private Revisoes revisoes;

    /*------------------------------------CONSTRUTORES----------------------------------------*/
    
    public Artigo(){
        this.titulo = "";
        this.idTitulo = 0;
        this.nCaracteres = 0;
        this.nPalavras = 0;
        this.revisoes = new Revisoes();
    }
 
    public Artigo(String titulo, long idTitulo, long nCaracteres, long nPalavras) {
        this.titulo = titulo;
        this.idTitulo = idTitulo;
        this.nCaracteres = nCaracteres;
        this.nPalavras = nPalavras;
    }
   
    public Artigo(Artigo a){
        this.titulo = a.getTitulo();
        this.idTitulo = a.getIdTitulo();
        this.nCaracteres = a.getnCaracteres();
        this.nPalavras = a.getnPalavras();
        this.revisoes = a.getRevisoes();
    }
    /*-------------------------------- GET'S & SET'S ----------------------------------------*/
    
    public String getTitulo() {
        return titulo;
    }

    public void setTitulo(String titulo) {
        this.titulo = titulo;
    }

    public long getIdTitulo() {
        return idTitulo;
    }

    public void setIdTitulo(long idTitulo) {
        this.idTitulo = idTitulo;
    }

    public long getnCaracteres() {
        return nCaracteres;
    }

    public void setnCaracteres(long nCaracteres) {
        this.nCaracteres = nCaracteres;
    }

    public long getnPalavras() {
        return nPalavras;
    }

    public void setnPalavras(long nPalavras) {
        this.nPalavras = nPalavras;
    }

    public Revisoes getRevisoes() {
        return revisoes;
    }

    public void setRevisoes(Revisoes revisoes) {
        this.revisoes = revisoes;
    } 

    /*-----------------------------------METODOS----------------------------------------------*/
   
    public void insereMapRevisaoArtigo(Revisoes mapRevisoes) {
        this.revisoes = new Revisoes(mapRevisoes);
    }
    
    // equals,toString,toClone();
    public boolean equals(Object o){
        if(o == this)
            return true;
        if(o == null || o.getClass() != this.getClass())
            return false;
        Artigo a = (Artigo)o;
        return (a.getTitulo().equals(this.titulo) && a.getIdTitulo() == this.idTitulo 
                && a.getnCaracteres() == this.nCaracteres
                && a.getnPalavras() == this.nPalavras
                && a.getRevisoes().equals(this.revisoes));
                
    }
    
    public String toString(){
        StringBuilder sb = new StringBuilder();
        sb.append("Id");
        sb.append(this.idTitulo);
        sb.append("Titulo");
        sb.append(this.titulo);
        sb.append("Numero de Caracteres");
        sb.append(this.nCaracteres);
        sb.append("Numero de Palavras");
        sb.append(this.nPalavras);
        sb.append("Revisoes");
        sb.append(this.revisoes.toString());
        return sb.toString();
    }
    
    public Artigo toClone(){
        return new Artigo(this);
    }
    
}

