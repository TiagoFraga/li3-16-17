package engine.comparators;

import engine.Artigo;

public class ArticleCharacters {
    private final long characters;
    private final long id;

    public ArticleCharacters(long characters, long id) {
        this.characters = characters;
        this.id = id;
    }

    public ArticleCharacters(Artigo art) {
        this.id = art.getIdTitulo();
        this.characters = art.getnCaracteres();
    }

    public long getWords() {
        return characters;
    }

    public long getId() {
        return id;
    }
}
