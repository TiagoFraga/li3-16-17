package engine.comparators;

import engine.Artigo;

public class ArticleWords {
    private final long words;
    private final long id;

    public ArticleWords(long words, long id) {
        this.words = words;
        this.id = id;
    }

    public ArticleWords(Artigo art) {
        this.id = art.getIdTitulo();
        this.words = art.getnPalavras();
    }

    public long getWords() {
        return words;
    }

    public long getId() {
        return id;
    }
}
