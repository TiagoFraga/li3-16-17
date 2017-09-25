package engine;

import java.util.HashMap;

public class Revisoes {
    
    /*---------------------------------VARIAVEIS DA CLASSE------------------------------------*/
    
    private long quantos;
    private HashMap<Long,Revisao> revisoes;

    /*------------------------------------CONSTRUTORES----------------------------------------*/
    
    public Revisoes() {
        this.quantos = 0;
        this.revisoes = new HashMap<>();
    }
   
    public Revisoes(Revisoes r){
        this.quantos = r.getQuantos();
        this.revisoes = r.getRevisoes();
    }
    
    /*-------------------------------- GET'S & SET'S ----------------------------------------*/
  
    public long getQuantos() {
        return quantos;
    }

    public void setQuantos(long quantos) {
        this.quantos = quantos;
    }

    public HashMap<Long,Revisao> getRevisoes() {
        HashMap<Long,Revisao> nova = new HashMap<>();
        revisoes.values().forEach((r) -> {
            nova.put(r.getIdRevisao(), r);
        });
        return revisoes;
    }
    
    
    /*-----------------------------------METODOS----------------------------------------------*/
    
    public boolean insereRevisao(Revisao revisao){
        boolean revisaoExits = this.revisoes.containsKey(revisao.getIdRevisao());
        
        if(!revisaoExits){
            this.revisoes.put(revisao.getIdRevisao(), revisao);
            this.quantos++;
        } 
        return revisaoExits;
    }
    
    public Revisao getRevisao(long idRevisao){
        return this.revisoes.get(idRevisao);
    }
    
    public boolean equals(Object o){
        if(o == this)
            return true;
        if(o == null || o.getClass() != this.getClass())
            return false;
        Revisoes r = (Revisoes)o;
        return (r.getQuantos() == this.quantos && r.getRevisoes().equals(this.revisoes));
                
    }
    
    
    public String toString(){
        StringBuilder sb = new StringBuilder();
        sb.append("Numero de Revisoes");
        sb.append(this.quantos);
        sb.append("Revisoes");
        sb.append(this.revisoes.toString());
        return sb.toString();
    }
    
    public Revisoes toClone(){
        return new Revisoes(this);
    }
}
