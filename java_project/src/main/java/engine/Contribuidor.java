package engine;

public class Contribuidor {
    
    /*---------------------------------VARIAVEIS DA CLASSE------------------------------------*/
    
    private String username;
    private long idUsername;
    private long quantidade;
    
    /*------------------------------------CONSTRUTORES----------------------------------------*/

    public Contribuidor(){
        this.username = "";
        this.idUsername = 0;
        this.quantidade = 0;
    }
   
    public Contribuidor(String username, long idUsername, long quantidade) {
        this.username = username;
        this.idUsername = idUsername;
        this.quantidade = quantidade;
    }
   
    public Contribuidor(Contribuidor c){
        this.username = c.getUsername();
        this.idUsername = c.getIdUsername();
        this.quantidade = c.getQuantidade();
    }
    
    /*-------------------------------- GET'S & SET'S ----------------------------------------*/

    public String getUsername() {
        return username;
    }

    public void setUsername(String username) {
        this.username = username;
    }

    public long getIdUsername() {
        return idUsername;
    }

    public void setIdUsername(long idUsername) {
        this.idUsername = idUsername;
    }

    public long getQuantidade() {
        return quantidade;
    }

    public void setQuantidade(long quantidade) {
        this.quantidade = quantidade;
    }
    
    // equals,toString,toClone();
    public boolean equals(Object o){
        if(o == this)
            return true;
        if(o == null || o.getClass() != this.getClass())
            return false;
        Contribuidor c = (Contribuidor)o;
        return (c.getUsername().equals(this.username) && c.getIdUsername() == this.idUsername
                && c.getQuantidade() == this.quantidade);
                
    }
    
    
    public String toString(){
        StringBuilder sb = new StringBuilder();
        sb.append("Id");
        sb.append(this.idUsername);
        sb.append("Username");
        sb.append(this.username);
        sb.append("Numero de Contribuicoes");
        sb.append(this.quantidade);
        return sb.toString();
    }
    
    public Contribuidor toClone(){
        return new Contribuidor(this);
    }
    
}
