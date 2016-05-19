
import java.io.*;
import java.util.*;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author João
 */
public class Leitura {
    

public static void print (TreeSet<String> cenas){
    TreeSet<String> aux = cenas;
   
    for(String s: aux){
    System.out.println(s);
    }
    System.out.println("Número Total de Elementos:");
    System.out.println(aux.size());

}
    
public static TreeSet<String> lerProd(String file_path){
    String path;
    TreeSet<String> prod =  new TreeSet<String>();
    path = file_path;
    try{
    BufferedReader reader = new BufferedReader(new FileReader(path));
   
    String cod;
    while((cod=reader.readLine())!= null){
    
    prod.add(cod);
    
    }
    return prod;
    }catch (Exception e){
    System.err.format("IOException: %s%n", e);
            return null;
    }

    

}
/*
public static TreeSet<String> lerProd2(String file_path){
    String path;
    String cod;
    TreeSet<String> prod =  new TreeSet<String>();
    path = file_path;
      try {
          Scanner input = new Scanner(path);
       
    while (input.hasNext()){
        cod = Input.lerString();
        prod.add(cod);
    }    
      
        return prod;
      }catch (Exception e) {
          System.err.format("IOException: %s%n", e);
            return null;
    }
    

}*/

public static TreeSet<String> lerClie(String file_path){
    String path;
    TreeSet<String> clie =  new TreeSet<String>();
    path = file_path;
    try{
    BufferedReader reader = new BufferedReader(new FileReader(path));
    String cod;
    while((cod=reader.readLine())!= null){
    
       clie.add(cod);
    
    }
    return clie;
    }catch (Exception e){
    System.err.format("IOException: %s%n", e);
            return null;
    }

}

public static TreeSet<String> lerVen(String file_path){
    String path;
    TreeSet<String> ven =  new TreeSet<String>();
    path = file_path;
    try{
    BufferedReader reader = new BufferedReader(new FileReader(path));
    String cod;
    while((cod=reader.readLine())!= null){
    
    ven.add(cod);
    
    }
    return ven;
    }catch (Exception e){
    System.err.format("IOException: %s%n", e);
            return null;
    }

}
    
}
  