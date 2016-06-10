

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
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
public class Hipermercado implements Serializable {

    private ArrayList<Venda> vendasCarr;
    private ArrayList<Venda> vendasValid;
    private HashMap<String, Cliente> listaclientes;
    private TreeMap<String, Produto> listaprodutos;
    private TreeMap<String, ArrayList<Venda>> vendascliente;
    public TreeMap<Integer, ArrayList<Venda>> comprasmes;
    private TreeSet<Venda> semrepetidos;

    public Hipermercado() {
        this.vendasCarr = new ArrayList<>();
        this.vendasValid = new ArrayList<>();
        this.listaclientes = new HashMap<>();
        this.listaprodutos = new TreeMap<>();
        this.vendascliente = new TreeMap<>();
    }

    public void addProduto(String text) {
        this.listaprodutos.put(text, new Produto(text));
    }

    public void addCliente(String text) {
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

    public int nvendasValidas() {
        return this.vendasValid.size();
    }

    public void vendasInvalidas() {
        int i = 0;
        ArrayList<Venda> invalidas = new ArrayList<>();

        for (Venda v : this.vendasCarr) {
            if (!(this.listaclientes.containsKey(v.getCodC()) && this.listaprodutos.containsKey(v.getCodP()))) {
                invalidas.add(v.clone());
            }
        }

        System.out.println("/*** Vendas inválidas: " + invalidas.size() + "                                                                                                    ***\\");
    }

    public void addVenda(Venda v) {
        this.vendasCarr.add(v);
    }

    public int vendasUnidades() {
        int i = 0;
        for (Venda v : this.vendasValid) {
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

        TreeMap<String, Produto> novo = this.listaprodutos;
        Produto p = new Produto();

        for (Venda v : this.vendasValid) {
            p.setCodP(v.getCodP());
            novo.remove(v.getCodP(), p);

        }

        return novo.size();

    }

    public int nProds() {
        return this.listaprodutos.size();
    }

    public int nClie() {
        return this.listaclientes.size();
    }

    public int vendasDup() {
        Set<Venda> novo = new HashSet<>();
        int total;

        novo.addAll(this.vendasCarr);

        total = (this.vendasCarr.size() - novo.size());

        return total;
    }

    public boolean existeProduto(Produto p) {
        return this.listaprodutos.values().contains(p);
    }
    
  

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

    public ParQuery1 querie1() {
        int total;
        ParQuery1 c = new ParQuery1();

        TreeMap<String, Produto> novo = this.listaprodutos;
        Produto p = new Produto();

        for (Venda v : this.vendasValid) {
            p.setCodP(v.getCodP());
            novo.remove(v.getCodP(), p);

        }

        total = novo.size();
        c.setTotal(total);
        c.setListaprodutos(novo);

        return c;

    }
    
    public float factAux(ArrayList<Venda> vendas){
        float fact=0.0f;
        
        for(Venda v: vendas)
            fact+=v.getPreco()*v.getUni();
    
        return fact;
    }

    public ParQuery4 query4(String codP) {
        ParQuery4 p4= new ParQuery4();
        int ncompm;
        int nprod=0;
        int i = 1;
        float fact = 0.0f;
        float facta=0.0f;
        ArrayList<Integer> nvcompras = new ArrayList<>();
        ArrayList<Integer> clidis = new ArrayList<>();
        ArrayList<Float> factmes = new ArrayList<>();
      
        ArrayList<Venda> ven = new ArrayList<>();
        ArrayList<Venda> vCodp = new ArrayList<>();
        HashSet<String> clidt = new HashSet<>();


        for (Integer c : this.comprasmes.keySet()) {
            ven = this.comprasmes.get(c);

            for (Venda v : ven) {
                if (v.getCodP().equals(codP)) {
                    vCodp.add(v.clone());
                    clidt.add(v.getCodC());
                    
                    
                }
                
               
                nprod = clidt.size();
            }
            fact=factAux(vCodp);
            factmes.add(fact);
            clidt=new HashSet<>();
            ncompm = vCodp.size();
            nvcompras.add(ncompm);
            
            clidis.add(nprod);
            vCodp = new ArrayList<>();
            
        }

        

      

        
        for (Float a : factmes) {
            facta += a;
        }

        p4 = new ParQuery4(nvcompras, clidis, factmes, facta);

        return p4;
    }

    public ParQuery3 Query3(String cliente) {
        ParQuery3 p3= new ParQuery3();
       int ncompm = 0;
        int nprod = 0;
        int i = 1;
        float fact = 0.0f;
        float facta = 0.0f;
        ArrayList<Integer> nvcompras = new ArrayList<>();
        ArrayList<Integer> prodis = new ArrayList<>();
        ArrayList<Float> factmes = new ArrayList<>();
        float t_facturado = 0.0f;
        ArrayList<Venda> ven = new ArrayList<>();
        ArrayList<Venda> vCodp = new ArrayList<>();
        HashSet<String> prodt = new HashSet<>();


        for (Integer c : this.comprasmes.keySet()) {
            ven = this.comprasmes.get(c);

            for (Venda v : ven) {
                if (v.getCodC().equals(cliente)) {
                    vCodp.add(v.clone());
                    prodt.add(v.getCodP());
                    
                    
                }
                nprod = prodt.size();
            }
            fact=factAux(vCodp);
            factmes.add(fact);
        
            prodt=new HashSet<>();
            ncompm = vCodp.size();
            nvcompras.add(ncompm);
            
            prodis.add(nprod);
            vCodp = new ArrayList<>();

        }
        
        for(Float f: factmes){
            facta+=f;
        }

        

        p3 = new ParQuery3(nvcompras, prodis,facta);

        return p3;
    }
    
    
   

    public TreeMap<Integer, ParQuery2> query2(int mes) {
        TreeMap<Integer, ParQuery2> tree = new TreeMap<>();
        ParQuery2 par = new ParQuery2();
        Cliente c = new Cliente();
        HashSet<Cliente> cli = new HashSet<>();
        ArrayList<Venda> ven = new ArrayList<>();
        int totvemes = 0;

        if (this.comprasmes.containsKey(mes)) {
            ven = this.comprasmes.get(mes);
            totvemes = ven.size();

            for (Venda v : ven) {
                c = new Cliente(v.getCodC());
                cli.add(c.clone());
            }
        }
        par = new ParQuery2(cli.size(), totvemes);
        tree.put(mes, par);

        return tree;
    }
    
    public int quantAux(ArrayList<Venda> vendas){
        int qt=0;
            for(Venda v: vendas)
                qt+=v.getUni();
            
            return qt;
    }
    
    

}
