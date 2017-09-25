package engine.comparators;

import engine.Contribuidor;

public class ContributorsCount {
    private final long idUsername;
    private final long quantidade;
    
    public ContributorsCount(long idUsername, long quantidade) {
        this.idUsername = idUsername;
        this.quantidade = quantidade;
    }

    public ContributorsCount(Contribuidor contribuidor) {
        this.idUsername = contribuidor.getIdUsername();
        this.quantidade = contribuidor.getQuantidade();
    }

    public long getIdUsername() {
        return idUsername;
    }

    public long getQuantidade() {
        return quantidade;
    }   
}
