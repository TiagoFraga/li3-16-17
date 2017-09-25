/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package engine;

/**
 *
 * @author gomes
 */
import java.util.Comparator;
public class ComparatorArtigoPalavras implements Comparator<Artigo> {
    public int compare(Artigo a1, Artigo a2){
        if(a1.getnPalavras() > a2.getnPalavras())
            return -1;
        if(a1.getnPalavras() < a2.getnPalavras())
            return 1;
        return 0;
    }
}
