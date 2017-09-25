package engine;

public class Revisao {
    
    /*---------------------------------VARIAVEIS DA CLASSE------------------------------------*/
    
    private long idRevisao;
    private String timeStamp;
    
    /*------------------------------------CONSTRUTORES----------------------------------------*/
    
    public Revisao(){
        this.idRevisao = 0;
        this.timeStamp = "";
    }
   
    public Revisao(long idRevisao, String timeStamp) {
        this.idRevisao = idRevisao;
        this.timeStamp = timeStamp;
    }
   
    public Revisao(Revisao r){
        this.idRevisao = r.getIdRevisao();
        this.timeStamp = r.getTimeStamp();
    }
    
    /*-------------------------------- GET'S & SET'S ----------------------------------------*/
    
    public long getIdRevisao() {
        return idRevisao;
    }

    public void setIdRevisao(long idRevisao) {
        this.idRevisao = idRevisao;
    }

    public String getTimeStamp() {
        return timeStamp;
    }

    public void setTimeStamp(String timeStamp) {
        this.timeStamp = timeStamp;
    }
 
    // equals,toString,toClone();
    public boolean equals(Object o){
        if(o == this)
            return true;
        if(o == null || o.getClass() != this.getClass())
            return false;
        Revisao r = (Revisao)o;
        return (r.getIdRevisao() == this.idRevisao && r.getTimeStamp().equals(this.timeStamp));
                
    }
    
    
    public String toString(){
        StringBuilder sb = new StringBuilder();
        sb.append("Id");
        sb.append(this.idRevisao);
        sb.append("TimeStamp");
        sb.append(this.timeStamp);
        return sb.toString();
    }
    
    public Revisao toClone(){
        return new Revisao(this);
    }
}
