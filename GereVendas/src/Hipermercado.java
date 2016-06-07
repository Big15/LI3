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
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import static java.lang.System.out;
import java.util.*;


/**
 *
 * @author Demo
 */
public class Hipermercado {
    
    private ArrayList<Cliente> listaclientes;
    private ArrayList<Produto> listaprodutos;
    private TreeMap<String,Venda> listavendas;
    
    
    
    public ArrayList<Produto> getListaProdutos(){
        ArrayList<Produto> novo= new ArrayList<>();
        listaprodutos.forEach(produto->novo.add(produto.clone()));
        return novo;
    }
    
    public ArrayList<Cliente> getListaClientes(){
         ArrayList<Cliente> novo= new ArrayList<>();
         listaclientes.forEach(cliente-> novo.add(cliente.clone()));
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

    
    
    
public static ArrayList<Cliente> carrega_cli(String fich) {
        ArrayList<Cliente> linhas = new ArrayList<>();
        BufferedReader inStream = null;
        
        try {
            inStream = new BufferedReader(new FileReader(fich));
            String linha;
            Cliente text = new Cliente();
             
    while ((linha = inStream.readLine()) != null) {
        text.setCodC(linha);
        linhas.add(text);
    }
        
    }catch (IOException e) {
            out.println(e.getMessage());
            return null;
        };
        
       
        return linhas;
    }


  
     



     public static ArrayList<Produto> carrega_Pro(String fich) {
         ArrayList<Produto> linhas = new ArrayList<>();
        BufferedReader inStream = null;
        
        try {
            inStream = new BufferedReader(new FileReader(fich));
            String linha;
            Produto text = new Produto();
             
    while ((linha = inStream.readLine()) != null) {
        text.setCodP(linha);
        linhas.add(text);
    }
        
    }catch (IOException e) {
            out.println(e.getMessage());
            return null;
        };
        
       
        return linhas;
    }
   
     
    public static ArrayList carrega_Vendas(String fich) {
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
       
        return linhas;
    }
 
    
    
     public static Venda parseLinhaVenda(String linha) {
         
        String[] line = null;
        double preco;
        int uni, mes,filial;
        line = linha.split(" ");
        for (int i = 0; i < 7; i++) {
            line[i].trim();
        }
        try {
             preco = Double.parseDouble(line[1]);
        } catch (NullPointerException | NumberFormatException e) {
            return null;
        }

        try {
             uni = Integer.parseInt(line[2]);
        } catch (NullPointerException | NumberFormatException e) {
            return null;
        }

        try {
             mes = Integer.parseInt(line[5]);
        } catch (NullPointerException | NumberFormatException e) {
            return null;
        }

        try {
             filial = Integer.parseInt(line[6]);
        } catch (NullPointerException | NumberFormatException e) {
            return null;
        }

        Venda v = new Venda(line[0], preco, uni, line[3], line[4], mes, filial);

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

   public static TreeMap<String,Venda> parseAllLinhasToSet(ArrayList<Venda> linhas) {
        TreeMap<String,Venda> array = new TreeMap<String,Venda>();

        for (Venda s : linhas) {
            array.put(s.getCodC(), s.clone());
        }
        System.out.println("Tempo: " + Crono.print() + " segundos");
        return array;
    }
    
    public static void main(String[] args) throws IOException, ClassNotFoundException {
        int lifetime=1, load=0;
        ArrayList<String> vendas= new ArrayList<>();
        ArrayList<Venda> lvendas=new ArrayList<>();
        InputStreamReader reader = new InputStreamReader(System.in);
        BufferedReader input = new BufferedReader(reader);
        String aux;
        String fileClientes = null, fileVendas = null, fileProdutos = null;
        Hipermercado main = new Hipermercado();
        main.listaclientes=new ArrayList<>();
        main.listaprodutos=new ArrayList<>();
        main.listavendas=new TreeMap<>();
       
 
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
            fileVendas = "Vendas_3M.txt";
            
           
        } else if (aux.equals("n")) {
            System.out.println("//***********************************************************************************************************************************\\");
            System.out.println("//***********************************************************************************************************************************\\");
            System.out.println("//***                                                          GEREVENDAS                                                          ***\\");
            System.out.println("//***********************************************************************************************************************************\\");
            System.out.println("//***                                          Introduza o nome do ficheiro para as Vendas                                     ***\\");
            System.out.println("//***********************************************************************************************************************************\\");
            fileVendas = input.readLine();
        
        }
        
         while(lifetime==1){
             if(load==0){
            System.out.println("Ficheiro " + fileProdutos);
            Crono.start();
            main.listaprodutos = carrega_Pro(fileProdutos);
            Crono.stop();
            System.out.println("Tempo: " + Crono.print() + " segundos");
            System.out.println("Ficheiro " + fileClientes);
            Crono.start();
            main.listaclientes = carrega_cli(fileClientes);
            Crono.stop();
            System.out.println("Tempo: " + Crono.print() + " segundos");
             System.out.println("Ficheiro " + fileVendas);
            Crono.start();
            vendas = main.carrega_Vendas(fileVendas);
            Crono.stop();
            lvendas=parseAllLinhas(vendas);
           try{
               main.listavendas=parseAllLinhasToSet(lvendas);
           } catch(ClassCastException e){
               System.out.println(e.getMessage());
           }
            
            System.out.println("Tempo: " + Crono.print() + " segundos");
             
                    }
         
         
         
          System.out.println("//***********************************************************************************************************************************\\");
                System.out.println("//***********************************************************************************************************************************\\");
                System.out.println("//***                                                          GEREVENDAS                                                          ***\\");
                System.out.println("//***********************************************************************************************************************************\\");
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
               
               switch(aux){
                   case "1":
                      // for(Cliente c: main.listaclientes)
                        //   System.out.println(c);
                          
                       for(Venda v: main.listavendas.values())
                           System.out.println(v);
               }
               }
         }
           
    }
