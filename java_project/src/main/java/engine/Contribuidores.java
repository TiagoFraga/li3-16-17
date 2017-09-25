package engine;

import java.util.HashMap;

public class Contribuidores {
    
    /*---------------------------------VARIAVEIS DA CLASSE------------------------------------*/
    private long quantos;
    private HashMap<Long, Contribuidor> contribuidores;

    
    /*------------------------------------CONSTRUTORES----------------------------------------*/
    
    public Contribuidores() {
        this.quantos = 0;
        this.contribuidores = new HashMap<>();
    }
   
    public Contribuidores(Contribuidores c){
        this.quantos = c.getQuantos();
        this.contribuidores = c.getContribuidores();
    }

    /*-------------------------------- GET'S & SET'S ----------------------------------------*/
    
     //getters and setters
    public long getQuantos() {
        return quantos;
    }

    public void setQuantos(long quantos) {
        this.quantos = quantos;
    }

    public HashMap<Long, Contribuidor> getContribuidores() {
        HashMap<Long,Contribuidor> nova = new HashMap<>();
        contribuidores.values().forEach((c) -> {
            nova.put(c.getIdUsername(),c);
        });
        return nova;
    }
    
    /*-----------------------------------METODOS----------------------------------------------*/
    
    public void insereContribuidor(Contribuidor contribuidor){
        
        boolean contributorExits = this.contribuidores.containsKey(contribuidor.getIdUsername());
        
        if(contributorExits == false){
            this.contribuidores.put(contribuidor.getIdUsername(), contribuidor);
            
            this.quantos++;
        }
        else{
            Contribuidor contribuidorFromHash= this.contribuidores.get(contribuidor.getIdUsername());
            long result = contribuidorFromHash.getQuantidade() + 1;
            contribuidorFromHash.setQuantidade(result);
        }
    }
    
    public Contribuidor getContribuidor(long id){    
        return this.contribuidores.get(id);
    }
    
    public boolean equals(Object o){
        if(o == this)
            return true;
        if(o == null || o.getClass() != this.getClass())
            return false;
        Contribuidores c = (Contribuidores)o;
        return (c.getQuantos() == this.quantos && c.getContribuidores().equals(this.contribuidores));
                
    }
    
    public String toString(){
        StringBuilder sb = new StringBuilder();
        sb.append("Numero de Contribuidores");
        sb.append(this.quantos);
        sb.append("Contribuidores");
        sb.append(this.contribuidores.toString());
        return sb.toString();
    }
    
    public Contribuidores toClone(){
        return new Contribuidores(this);
    }
}
