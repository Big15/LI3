import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.Serializable;
import static java.lang.System.out;
import java.util.*;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author Demo
 */
public class Hipermercado implements Serializable{

    private ArrayList<Venda> vendasCarr;
    private ArrayList<Venda> vendasValid;
    private HashMap<String, Cliente> listaclientes;
    private HashMap<String, Produto> listaprodutos;
    private TreeMap<String, ArrayList<Venda>> vendascliente;


   
    
    public Hipermercado(){
        this.vendasCarr = new ArrayList<>();
        this.vendasValid = new ArrayList<>();
        this.listaclientes = new HashMap<>();
        this.listaprodutos = new HashMap<>();
        this.vendascliente = new TreeMap<>();              
    }
    
    
    
     public void gravaObj(String fich) throws IOException {
        ObjectOutputStream oos = new ObjectOutputStream(new FileOutputStream(fich));
        oos.writeObject(this);
        
        
        oos.flush();
        oos.close();
    }
    
    
    

    public static Hipermercado leObj(String fich) throws IOException, ClassNotFoundException {
        Hipermercado te;
        try (ObjectInputStream ois = new ObjectInputStream(new FileInputStream(fich))) {
            te = (Hipermercado) ois.readObject();
        }
        return te;
    }

    public static Hipermercado initApp() {
        Hipermercado imo;
        String fileClientes = null, fileVendas = null, fileProdutos = null;
        try {
            imo = Hipermercado.leObj("estado.tabemp");
            fileClientes="Clientes.txt";
            fileProdutos="Produtos.txt";
            fileVendas="Vendas_1M";
        } catch (IOException e) {
            imo = new Hipermercado();
            System.out.println("Não existem dados gravados|\nErro de leitura.");
        } catch (ClassNotFoundException e) {
            imo = new Hipermercado();
            System.out.println("Não é possível ler os dados!\nFicheiro com formato desconhecido.");
        } catch (ClassCastException e) {
            imo = new Hipermercado();
            System.out.println("Não é possível ler os dados!\nErro de formato.");
        }
        return imo;
    }
   

    public void addProduto(String text){
        this.listaprodutos.put(text, new Produto(text));
    }
    
    public void addCliente(String text){
        this.listaclientes.put(text, new Cliente(text));
    }

    public void vendasValidas() {
        int i = 0;
        this.vendasValid = new ArrayList<>();

        for (Venda v : this.vendasCarr) {
            if (this.listaclientes.containsKey(v.getCodC()) && this.listaprodutos.containsKey(v.getCodP())) {
                this.vendasValid.add(v.clone());
            }
        }
    }
    
    public int nvendasValidas(){
        return this.vendasValid.size();
    }
    
    public void addVenda(Venda v){
        this.vendasCarr.add(v);
    }

    public int vendasUnidades() {
        int i = 0;
        for(Venda v: this.vendasValid){
            i += v.getUni();
        }
        return i;
    }

    public float factTotal() {
        float i = 0.0f;

        for (Venda v : this.vendasValid) {
            i += v.getPreco();
        }

        return i;
    }

    public int preco0() {
        int i = 0;

        for (Venda v : this.vendasValid) {
            if (v.getPreco() == 0) {
                i++;

            }
        }
        return i;

    }

    public int cliCompras() {
        TreeSet<String> novo = new TreeSet<>();

        for (Venda v : this.vendasValid) {
            novo.add(v.getCodC());
        }

        return novo.size();

    }

    public int cliNcompras() {

        return cliCompras() - this.listaclientes.size();
    }

    public int prodDif() {
        TreeSet<String> aux = new TreeSet<>();

        for (Venda v : this.vendasValid) {
            aux.add(v.getCodP());
        }

        return aux.size();

    }

    public int prodNcomprados() {
        TreeSet<String> aux = new TreeSet<>();

        for (Venda v : this.vendasValid) {
            aux.add(v.getCodP());
        }

        return this.listaprodutos.size() - aux.size();

    }
    
    public int nProds(){
        return this.listaprodutos.size();
    }
    
    public int nClie(){
        return this.listaclientes.size();
    }
    
/*
    public static ArrayList<Venda> parseAllLinhas(ArrayList<String> linhas, HashMap<String, Cliente> clientes, HashMap<String, Produto> produtos) {
        ArrayList<Venda> array = new ArrayList<>();

        for (String s : linhas) {
            array.add(parseLinhaVenda(s, clientes, produtos));
        }
        System.out.println("Tempo: " + Crono.print() + " segundos");
        return array;
    }

    public static TreeMap<String, ArrayList<Venda>> parseAllLinhasToSet(ArrayList<Venda> linhas) {
        TreeMap<String, ArrayList<Venda>> array = new TreeMap<>();
        ArrayList<Venda> novo = new ArrayList<>();

        for (Venda s : linhas) {
            novo.add(s.clone());
            array.put(s.getCodC(), novo);
        }
        System.out.println("Tempo: " + Crono.print() + " segundos");
        return array;
    }
*/
    public TreeMap<Integer, ArrayList<Venda>> parseAllLinhasToMap() {
        TreeMap<Integer, ArrayList<Venda>> array = new TreeMap<>();
        ArrayList<Venda> novo = new ArrayList<>();
        for (Venda s : this.vendasValid) {
            if (array.containsKey(s.getMes())) {
                novo = array.get(s.getMes());
                novo.add(s.clone());
                array.put(s.getMes(), novo);
            } else {
                novo = new ArrayList<>();
                novo.add(s.clone());
                array.put(s.getMes(), novo);
            }
        }
        //System.out.println("Tempo: " + Crono.print() + " segundos");
        return array;
    }

    public int vendasDup() {
        Set<Venda> novo = new HashSet<>();
        int total;

        novo.addAll(this.vendasCarr);

        total = (this.vendasCarr.size() - novo.size());

        return total;
    }
    
  //Estatísticas para registados nas estruturas:
/*
    public void comprasMes(){
        TreeMap<Integer, ArrayList<Venda>> comprasmes = hiper.parseAllLinhasToMap(totalvendas);
        int count=0;
        int i=1;
           
                
                    for(ArrayList<Venda> cena: comprasmes.values()){
                    for(Venda v: cena){
                        if(v.getMes()==i)
                            count++;
                    
                    else{
                           System.out.println("Mês " +i + ":"+ count); 
                           count=1;
                           i++;
                            }
                    }
                }
                    System.out.println("Mês " +i + ":"+ count); 
                
                 
                
    
    }
*/
}