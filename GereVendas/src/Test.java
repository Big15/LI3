
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import static java.lang.System.out;
import java.util.*;

class MyComparator implements Comparator<String> {
  public int compare(String a, String b) {
    String aStr, bStr;

    aStr = a;
    bStr = b;

    return bStr.compareTo(aStr);
  }
  // No need to override equals.
}

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
        System.out.println("Lidas e guardadas " + linhas.size() + " linhas");
        System.out.println("Tempo: " + Crono.print() + " segundos");
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
        for (int i = 0; i < 7; i++) {
            line[i].trim();
        }
        Venda v = new Venda(line[0], Double.parseDouble(line[1]), Integer.parseInt(line[2]), line[3], line[4], Integer.parseInt(line[5]), Integer.parseInt(line[6]));
        return v;
    }

    public static ArrayList<Venda> parseAllLinhas(ArrayList<String> linhas) {
        ArrayList<Venda> array = new ArrayList<>();

        for (String s : linhas) {
            array.add(parseLinhaVenda(s));
        }
        System.out.println("Tempo: " + Crono.print() + " segundos");
        return array;
    }

    public static HashSet<Venda> parseAllLinhasToSet(ArrayList<String> linhas) {
        HashSet<Venda> array = new HashSet<Venda>();

        for (String s : linhas) {
            array.add(parseLinhaVenda(s));
        }
        System.out.println("Tempo: " + Crono.print() + " segundos");
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

    public static int vendas00(ArrayList<Venda> array) {
        int total = 0;
        for (Venda v : array) {
            if (v.getPreco() == 0.0) {
                total++;
            }
        }

        return total;
    }

    public static int vendasDup(ArrayList<Venda> array) {
        int total = 0, aux;
        for (Venda v : array) {
            aux = 0;
            for (Venda v2 : array) {
                if (v.equals(v2)) {
                    aux++;
                }
                if (aux > 1) {
                    total++;
                }
            }
        }
        return total;
    }

    public static int produtosLetra(ArrayList<Venda> array, String c) {
        int total = 0;
        for (Venda v : array) {
            String vc = v.getCodP().substring(0, 1);
            if (vc.equals(c)) {
                total++;
            }
        }
        return total;
    }

    public static Set<String> clientepfilial(ArrayList<Venda> array, int filial) {
        //Set<String> nova = new HashSet<String>();
        Comparator<String> ordemDecStrings = (s1, s2) -> s1.compareTo(s2);
        Set<String> nova = new TreeSet<>(ordemDecStrings);
        for (Venda v : array) {
            if (v.getFilial() == filial) {
                nova.add(v.getCodC());
            }
        }
        return nova;
    }    

    

    public static void main(String[] args) {

        String path3 = "Vendas_3M.txt";
        ArrayList<String> cenas = new ArrayList<String>();
        Crono.start();
        //cenas = Leitura.readLinesArrayWithScanner(path3);
        cenas = readLinesWithBuff(path3);
        Crono.stop();
        Crono.start();
        //HashSet<Venda> hashs = parseAllLinhasToSet(cenas);
        ArrayList<Venda> array = parseAllLinhas(cenas);
        Crono.stop();
        /*
         
        
         if(array.size() == hashs.size())
         System.out.println("Não há linhas repetidas");
         else
         System.out.println("Há linhas repetidas");
         */
        /*for (Venda v : array) {
         System.out.println(v.toString());
         }
         System.out.println(array.size());*/
        //System.out.println("Total de compras realizadas na filial 1: " + totalcompras(array, 1));
        //System.out.println("Total de compras de preço 0.0: " + vendas00(array));
        //System.out.println("Total de compras repetidas: " + vendasDup(array));
        //System.out.println("Total de Produtos começados por A: " + produtosLetra(array, "A"));
        //System.out.println("Total de Cliente da filial 1: " + clief.size());
        Crono.start();
        Set<String> clief = clientepfilial(array, 1);
        //Set<String> ts = new TreeSet<String>(new MyComparator());
        System.out.println("Total de Cliente da filial 1: " + clief.size());
        System.out.println("Tempo: " + Crono.print() + " segundos");
        Crono.stop();
    }

}
