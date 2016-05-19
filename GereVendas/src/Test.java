
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import static java.lang.System.out;
import java.util.*;

public class Test {

    public static ArrayList<String> readLinesWithBuff(String fich) {
        ArrayList<String> linhas = new ArrayList<>();
        BufferedReader inStream = null;
        String linha = null;
        try {
            inStream = new BufferedReader(new FileReader(fich));
            while ((linha = inStream.readLine()) != null) {
                linhas.add(linha);
            }
        } catch (IOException e) {
            out.println(e.getMessage());
            return null;
        };        
        return linhas;
    }

    public static ArrayList<String> readLinesArrayWithScanner(String ficheiro) {
        ArrayList<String> linhas = new ArrayList<>();
        Scanner scanFile = null;
        try {
            scanFile = new Scanner(new FileReader(ficheiro));
            scanFile.useDelimiter("\n\r");
            while (scanFile.hasNext()) {
                linhas.add(scanFile.nextLine());
            }
        } catch (IOException ioExc) {
            out.println(ioExc.getMessage());
            return null;
        } finally {
            if (scanFile != null) {
                scanFile.close();
            }
        }
        System.out.println("Lidas e guardadas " + linhas.size() + " linhas");
        System.out.println("Tempo: " + Crono.print() + " segundos");
        return linhas;
    }

    public static Venda parseLinhaVenda(String linha) {
        String[] line = null;
        line = linha.split(" ");
        for(int i=0; i < 7; i++)
            line[i].trim();
        Venda v = new Venda(line[0], Double.parseDouble(line[1]), Integer.parseInt(line[2]), line[3], line[4], Integer.parseInt(line[5]), Integer.parseInt(line[6]));
        return v;
    }

    public static ArrayList<Venda> parseAllLinhas(ArrayList<String> linhas) {
        ArrayList<Venda> array = new ArrayList<>();

        for (String s : linhas) {     
            array.add(parseLinhaVenda(s));           
        }

        return array;
    }

    public static HashSet<Venda> parseAllLinhasToSet(ArrayList<String> linhas) {
        HashSet<Venda> array = new HashSet<Venda>();

        for (String s : linhas) {            
            array.add(parseLinhaVenda(s));
        }

        return array;
    }

    public static int totalcompras(ArrayList<Venda> array, int filial) {
        int total = 0;
        for (Venda v : array) {
            if (v.getFilial() == filial) {
                total++;
            }
        }
        return total;
    }
    
    public static int vendas00(ArrayList<Venda> array){
        int total = 0;
        for(Venda v: array)
            if(v.getPreco() == 0.0)
                total++;
                
        return total;
    }
    
    public static int vendasDup(ArrayList<Venda> array){
        int total = 0, aux;
        for(Venda v: array){
            aux = 0;
            for(Venda v2: array){
                if(v.equals(v2))
                    aux++;
            if(aux > 1)          
                total++;
            }
        }
        return total;
    }

    public static void main(String[] args) {

        String path3 = "Vendas_3M.txt";
        ArrayList<String> cenas = new ArrayList<String>();
        Crono.start();
        //cenas = Leitura.readLinesArrayWithScanner(path3);
        cenas = readLinesWithBuff(path3);
        Crono.stop();

        ArrayList<Venda> array = parseAllLinhas(cenas);
        /*
         HashSet<Venda> hashs = parseAllLinhasToSet(cenas);
        
         if(array.size() == hashs.size())
         System.out.println("Não há linhas repetidas");
         else
         System.out.println("Há linhas repetidas");
         */
        /*for (Venda v : array) {
            System.out.println(v.toString());
        }
        System.out.println(array.size());*/
        System.out.println("Total de compras realizadas na filial 1: " + totalcompras(array, 1));
        System.out.println("Total de compras de preço 0.0: " + vendas00(array));
        System.out.println("Total de compras repetidas: " + vendasDup(array));
        

    }

}
