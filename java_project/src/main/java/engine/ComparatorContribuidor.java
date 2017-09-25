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
public class ComparatorContribuidor implements Comparator<Contribuidor> {
       public int compare(Contribuidor c1,Contribuidor c2){
          return Long.compare(c2.getQuantidade(),c1.getQuantidade());
       }
}
