package engine;

import java.util.ArrayList;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.UnsupportedEncodingException;
import java.util.Iterator;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.xml.stream.XMLEventReader;
import javax.xml.stream.XMLInputFactory;
import javax.xml.stream.XMLStreamConstants;
import javax.xml.stream.XMLStreamException;
import javax.xml.stream.events.Attribute;
import javax.xml.stream.events.Characters;
import javax.xml.stream.events.EndElement;
import javax.xml.stream.events.StartElement;
import javax.xml.stream.events.XMLEvent;

public class Parser {
    
    private Contribuidores contribuidores;
    private Artigos artigos;

    public Parser(Artigos artigos, Contribuidores contribuidores) {
        this.artigos = artigos;
        this.contribuidores = contribuidores;
    }

    public void load(ArrayList<String> snaps_paths) {
      boolean bpage = false;
      boolean bTitle = false;
      boolean bIdTitle = false;
      boolean bText = false;

      boolean bRevision = false;
      boolean bIdRevision = false;
      boolean bTimeStamp = false;

      boolean bContributor = false; 
      boolean bUsername = false;
      boolean bIdUsername = false;
      
      
    
    for(int i=0; i<snaps_paths.size();i++){
        long words = 0, chars = 0;
        String title = null, idTitle = null, 
                
                idRevision = null, timeStamp = null, 
                
                username = null, idUsername = null;

    
        try {
         
         XMLInputFactory factory = XMLInputFactory.newInstance();
         factory.setProperty(XMLInputFactory.IS_COALESCING, true);
         XMLEventReader eventReader = factory.createXMLEventReader(new FileReader(snaps_paths.get(i)));

            while(eventReader.hasNext()){
               
               XMLEvent event = eventReader.nextEvent();
               
               switch(event.getEventType()){
                  
                  case XMLStreamConstants.START_ELEMENT:
                     
                     StartElement startElement = event.asStartElement();
                     String qName = startElement.getName().getLocalPart();
                     
                     if (qName.equalsIgnoreCase("page") && bContributor == false && bRevision == false) {
                     }  else if (qName.equalsIgnoreCase("title") && bContributor == false && bRevision == false ) {
                        bTitle = true;
                     }  else if (qName.equalsIgnoreCase("id") && bContributor == false && bRevision == false) {
                        bIdTitle = true;
                     }  else if (qName.equalsIgnoreCase("revision") && bContributor == false) {
                        bRevision = true;
                     }  else if (qName.equalsIgnoreCase("text")) {
                        bText = true;
                     }  else if (qName.equalsIgnoreCase("id") && bRevision == true && bContributor == false) {
                        bIdRevision = true;
                     }  else if (qName.equalsIgnoreCase("timestamp") && bRevision == true && bContributor == false) {
                        bTimeStamp = true;
                     }  else if (qName.equalsIgnoreCase("contributor")) {
                        bRevision = false;
                        bContributor = true;
                     }  else if (qName.equalsIgnoreCase("username") && bRevision == false && bContributor == true) {
                        bUsername = true;
                     }  else if (qName.equalsIgnoreCase("id") && bRevision == false && bContributor == true) {
                        bIdUsername= true;
                     } else if (qName.equalsIgnoreCase("ip") && bRevision == false && bContributor == true) {
                        bIdUsername= false;
                     }  	 			        
                     break;
                  
                  case XMLStreamConstants.CHARACTERS:
                     
                     Characters characters = event.asCharacters();
                     
                     if(bTitle){
                        title = characters.getData();
                        bTitle = false;
                     }
                     if(bIdTitle){
                        idTitle = characters.getData();
                        bIdTitle = false;
                     }
                     
                     if(bIdRevision){
                        idRevision = characters.getData();
                        bIdRevision = false;
                     }
                     if(bText){
                        try{
                            String text = characters.getData();
                            byte[] bytes = text.getBytes("UTF-8");
                            chars = bytes.length;
                            words = (countWords(characters.getData()));
                            bText = false;
                        } catch (UnsupportedEncodingException ex) {
                            Logger.getLogger(Parser.class.getName()).log(Level.SEVERE, null, ex);
                        }       
                     }
                     if(bTimeStamp){
                        timeStamp = characters.getData();
                        bTimeStamp = false;
                     }
                     if(bUsername){
                        username = characters.getData(); 
                        bUsername = false;
                     }
                     if(bIdUsername){
                        idUsername = characters.getData();
                        bIdUsername = false;
                     }
                    break;
                     

                  case  XMLStreamConstants.END_ELEMENT:
                     
                     EndElement endElement = event.asEndElement();
                     
                     if(endElement.getName().getLocalPart().equalsIgnoreCase("page")){
                        bContributor = false;
                        bRevision = false;
                        Artigo artigo = new Artigo (title, Long.parseLong(idTitle),chars,words);
                        Contribuidor contribuidor = new Contribuidor(username, Long.parseLong(idUsername),1);
                        
                        boolean inseriu = artigos.insereArtigo(artigo,Long.parseLong(idRevision),timeStamp);
                        if(inseriu == false){
                            contribuidores.insereContribuidor(contribuidor);
                        }        
                     }
                     break;
                }
            }
         
         } catch (FileNotFoundException e) {
            e.printStackTrace();
         } catch (XMLStreamException e) {
            e.printStackTrace();
      }
   }
    
}

    public long countWords(String s){

    long wordCount = 0;

    boolean word = false;
    int endOfLine = s.length() - 1;

    for (int i = 0; i < s.length(); i++) {
        // if the char is a letter, word = true.
        if (Character.isWhitespace(s.charAt(i)) && i != endOfLine) {
            word = true;
            // if char isn't a letter and there have been letters before,
            // counter goes up.
        } else if (!Character.isWhitespace(s.charAt(i)) && word) {
            wordCount++;
            word = false;
            // last word of String; if it doesn't end with a non letter, it
            // wouldn't count without this.
        } else if (Character.isWhitespace(s.charAt(i)) && i == endOfLine) {
            wordCount++;
        }
    }
    return wordCount;
}

}




