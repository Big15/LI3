/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package gerevendas;

import static gerevendas.Test.parseLinhaVenda;
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
import static java.lang.System.out;
import java.util.*;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author Demo
 */
public class Hipermercado {

    private ArrayList<Venda> totalvendas;
    private HashMap<String, Cliente> listaclientes;
    private HashMap<String, Produto> listaprodutos;
    private ArrayList<Venda> vendasInvalidas;
    private TreeMap<String, ArrayList<Venda>> vendascliente;
    private TreeMap<Integer, ArrayList<Venda>> comprasmes;

    public TreeMap<Integer, ArrayList<Venda>> getComprasMes() {
        TreeMap<Integer, ArrayList<Venda>> novo = new TreeMap<>();
        ArrayList<Venda> vendas = new ArrayList<>();

        totalvendas.stream().map((v) -> {
            vendas.add(v.clone());
            return v;
        }).forEach((v) -> {
            novo.put(v.getMes(), vendas);
        });

        return novo;
    }

    public void gravaObj(String fich) throws IOException {
        try (ObjectOutputStream oos = new ObjectOutputStream(new FileOutputStream(fich))) {
            oos.writeObject(this);

            oos.flush();
        }
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
        try {
            imo = Hipermercado.leObj("estado.tabemp");
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

    public void carrega_produtos(String string) {

        BufferedReader inStream = null;

        try {
            inStream = new BufferedReader(new FileReader(string));
            String text = null;

            while ((text = inStream.readLine()) != null) {
                listaprodutos.put(text, new Produto(text));

            }
        } catch (IOException e) {
            System.out.println(e.getMessage());

        };

    }

    public void carrega_vendas(String string) {

        BufferedReader inStream = null;

        try {
            inStream = new BufferedReader(new FileReader(string));
            String text = null;

            while ((text = inStream.readLine()) != null) {

                parseLinhaVenda(text);
            }

        } catch (IOException e) {
            System.out.println(e.getMessage());

        };

    }

    public void carrega_clientes(String string) {

        BufferedReader inStream = null;

        try {
            inStream = new BufferedReader(new FileReader(string));
            String text = null;

            while ((text = inStream.readLine()) != null) {

                listaclientes.put(text, new Cliente(text));
            }
        } catch (IOException e) {
            System.out.println(e.getMessage());

        };

    }

    public void parseLinhaVenda(String linha) {
      
        String[] line = null;

        line = linha.split(" ");

        for (int i = 0; i < 7; i++) {
            line[i].trim();
        }

        Venda v = new Venda(line[0], Float.parseFloat(line[1]), Integer.parseInt(line[2]), line[3], line[4], Integer.parseInt(line[5]), Integer.parseInt(line[6]));

        
         if ((existeProduto(line[0]) && existeCliente(line[4]))){
          this.totalvendas.add(v.clone());
          
         }
        
     /*else{
          if (!(existeProduto(line[0]) && existeCliente(line[4]))){
            validas.add(v.clone());
            this.vendasInvalidas=erradas;
          }
          }*/
      
               
    
    }

    
    public int vendasUnidades(){
        int i=0;
        
        for(Venda v: totalvendas)
        i+=v.getUni();
        
        return i;
    }

    public float factTotal(){
        float i=0.0f;
        
        for(Venda v: totalvendas)
            i+=v.getPreco();
        
        return i;
    }
    
    public int preco0(){
            
            int i=0;
            
            for(Venda v: totalvendas){
              if(v.getPreco()==0){
                i++;
            
        }
            }
        return i;
        
    }
    
    
    
    public int clientes00(){
        int i=0;
        
        for(Venda v: totalvendas){
            if(listaclientes.containsKey(v.getCodC())){
                if(v.getUni()==0)
                    i++;
            }
        }
        return i;
                
}
    public int prodDif(){
// WHAT THE FUCK!?!?! EU TAVA A FAZER OS PRODUTOS DIFERENTES E DEU-ME OS PRODUTOS NÃO COMPRADOS. COMO?
        
        TreeSet<String> aux= new TreeSet<>();
        
 
            for(Venda v: totalvendas){
                aux.add(v.getCodP());
            }
        
                
        
        return listaprodutos.size()-aux.size();
        
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

    public static TreeMap<Integer, ArrayList<Venda>> parseAllLinhasToMap(ArrayList<Venda> linhas) {
        TreeMap<Integer, ArrayList<Venda>> array = new TreeMap<>();
        ArrayList<Venda> novo = new ArrayList<>();

        for (Venda s : linhas) {
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

    public static int vendasDup(ArrayList<Venda> array) {
        Set<Venda> novo = new HashSet<>();
        int total;

        novo.addAll(array);

        total = (array.size() - novo.size());

        return total;
    }

    public boolean existeCliente(String cliente) {
        return this.listaclientes.containsKey(cliente);
    }

    public boolean existeProduto(String produto) {
        return this.listaprodutos.containsKey(produto);
    }

    public static void main(String[] args) throws IOException, ClassNotFoundException {
        int lifetime = 1, load = 0;
        ArrayList<String> vendas = new ArrayList<>();

        InputStreamReader reader = new InputStreamReader(System.in);
        BufferedReader input = new BufferedReader(reader);
        String aux;
        String fileClientes = null, fileVendas = null, fileProdutos = null;
        Hipermercado main = new Hipermercado();
        main.listaclientes = new HashMap<>();
        main.listaprodutos = new HashMap<>();
        main.vendascliente = new TreeMap<>();
        main.comprasmes = new TreeMap<>();
        main.totalvendas = new ArrayList<>();

        System.out.println("//***********************************************************************************************************************************\\");
        System.out.println("//***********************************************************************************************************************************\\");
        System.out.println("//***                                                          GEREVENDAS                                                          ***\\");
        System.out.println("//***********************************************************************************************************************************\\");
        System.out.println("//***                                           Deseja carregar os ficheiros default? (s/n)                                       ***\\");
        System.out.println("//***********************************************************************************************************************************\\");
        aux = input.readLine();
        if (aux.equals("s")) {
            fileClientes = "Clientes.txt";
            fileProdutos = "Produtos.txt";
            fileVendas = "Vendas_1M.txt";

        } else if (aux.equals("n")) {
            System.out.println("//***********************************************************************************************************************************\\");
            System.out.println("//***********************************************************************************************************************************\\");
            System.out.println("//***                                                          GEREVENDAS                                                          ***\\");
            System.out.println("//***********************************************************************************************************************************\\");
            System.out.println("//***                                          Introduza o nome do ficheiro para as Vendas                                     ***\\");
            System.out.println("//***********************************************************************************************************************************\\");
            fileVendas = input.readLine();

        }

        while (lifetime == 1) {
            if (load == 0) {
                System.out.println("Ficheiro " + fileProdutos);
                Crono.start();
                main.carrega_produtos(fileProdutos);
                Crono.stop();
                System.out.println("Tempo: " + Crono.print() + " segundos");
                System.out.println("Ficheiro " + fileClientes);
                Crono.start();

                main.carrega_clientes(fileClientes);
                Crono.stop();
                System.out.println("Tempo: " + Crono.print() + " segundos");
                System.out.println("Ficheiro " + fileVendas);
                Crono.start();
                main.carrega_vendas(fileVendas);
                Crono.stop();
                System.out.println("Tempo: " + Crono.print() + " segundos");
                System.out.println("Vendas validadas: " + main.totalvendas.size());
                System.out.println("Número Total de Produtos: " + main.listaprodutos.size());
                System.out.println("Número Total de Clientes: " + main.listaclientes.size());
                System.out.println("Total de Clientes que nunca compraram: " + main.clientes00());
                System.out.println("Número de Unidades vendidas: " + main.vendasUnidades());
                System.out.println("Total facturado: " + main.factTotal());
                System.out.println("Total de compras preço = 0.0 : " + main.preco0());
                System.out.println("Total de Produtos diferentes comprados: " + main.prodDif());
                
                
               // System.out.println("Vendas Erradas: " + main.vendasInvalidas.size());
                
                

               /* try {
                    main.comprasmes = parseAllLinhasToMap(main.totalvendas);
                } catch (ClassCastException e) {
                    System.out.println(e.getMessage());
                }

                try {
                    main.vendascliente = parseAllLinhasToSet(main.totalvendas);
                } catch (ClassCastException e) {
                    System.out.println(e.getMessage());
                }*/

            }

            System.out.println("//***********************************************************************************************************************************\\");
            System.out.println("//***********************************************************************************************************************************\\");
            System.out.println("//***                                                          GEREVENDAS                                                          ***\\");
            System.out.println("//***********************************************************************************************************************************\\");
            System.out.println("//*** 0- Estatísticas: ");
            System.out.println("//*** 1- Lista ordenada com os códigos dos produtos nunca comprados e respectivo total.                                           ***\\");
            System.out.println("//*** 2- Lista ordenada com os códigos dos clientes que nunca compraram e seu total.                                              ***\\");
            System.out.println("//*** 3- Dado um mês válido, determinar o número total de compras e o total de clientes distintos que as realizaram.              ***\\");
            System.out.println("//*** 4- Para um cliente, determinar, para cada mês, quantas compras fez, quantos produtos distintos comprou E quanto gastou.     ***\\");
            System.out.println("//*** 5- Para um produto, determinar, mês a mês, quantas vezes foi comprado, por quantos clientes diferentes e o total facturado. ***\\");
            System.out.println("//*** 6- Para um produto, determinar, mês a mês, quantas vezes foi comprado em modo N e em modo P e respectivas facturações.      ***\\");
            System.out.println("//*** 7- Dado o código de um cliente determinar a lista de códigos de produtos que mais comprou (e quantos).                      ***\\");
            System.out.println("//*** 8- Determinar os X produtos mais vendidos em todo o ano e o número total de distintos clientes que o compraram.             ***\\");
            System.out.println("//*** 9- Determinar os X clientes que compraram um maior número de diferentes produtos indicando quantos.                         ***\\");
            System.out.println("//*** 10- Dado o código de um produto, determinar o conjunto dos X clientes que mais o compraram.                                 ***\\");
            System.out.println("//***********************************************************************************************************************************\\");
            System.out.println("//***********************************************************************************************************************************\\");

            aux = input.readLine();

            switch (aux) {
                case "0":
                    int c = 0;

                    for (Integer i : main.comprasmes.keySet()) {
                        ArrayList<Venda> novo = new ArrayList<>();
                        novo = main.comprasmes.get(i);
                        for (Venda v : novo) {
                            if (v.getMes() == 12) {
                                c++;
                            }

                        }
                    }
                    System.out.println(c);

                    /*int i=0;
                       for(Venda v : main.totalvendas){
                       if(v.getMes()==1){
                           i++;
                           System.out.println(v.getMes());
                        }
                       System.out.println(i);
                       } */
                    break;

                case "1":
                // for(Cliente c: main.listaclientes)
                //   System.out.println(c);

            }
        }
    }

}
