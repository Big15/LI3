
import java.io.*;
import static java.lang.System.out;
import java.util.*;

public class Leitura {

    public static void print(TreeSet<String> cenas) {
        TreeSet<String> aux = cenas;

        for (String s : aux) {
            System.out.println(s);
        }
    }
    
    

    
    


    public static TreeSet<String> lerFiles(String file_path) {
        String path;
        TreeSet<String> prod = new TreeSet<String>();
        path = file_path;
        try {
            BufferedReader reader = new BufferedReader(new FileReader(path));

            String cod;
            Crono.start();
            while ((cod = reader.readLine()) != null) {                
                prod.add(cod);                
            }
            Crono.stop();
        } catch (IOException e) {
            out.println(e.getMessage());
            return null;
        }
        System.out.println("Ficheiro Vendas_3M (Buffer)");
        System.out.println("Lidas e guardadas " + prod.size() + " linhas");
        System.out.println("Tempo: " + Crono.print() + " segundos");
        return prod;
    }

}
  