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

    private ArrayList<Venda> vendasCarr;
    private HashMap<String, Cliente> listaclientes;
    private HashMap<String, Produto> listaprodutos;
    private TreeMap<String, ArrayList<Venda>> vendascliente;
    private TreeMap<Integer, ArrayList<Venda>> comprasmes;

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

    public static HashMap<String, Produto> carrega_produtos(String string) {
        HashMap<String, Produto> novo = new HashMap<>();
        BufferedReader inStream = null;

        try {
            inStream = new BufferedReader(new FileReader(string));
            String text = null;

            while ((text = inStream.readLine()) != null) {
                novo.put(text, new Produto(text));

            }
        } catch (IOException e) {
            System.out.println(e.getMessage());

        };
        return novo;

    }

    public static ArrayList<String> carrega_vendas(String string) {
        ArrayList<String> novo = new ArrayList<>();
        BufferedReader inStream = null;

        try {
            inStream = new BufferedReader(new FileReader(string));
            String text = null;

            while ((text = inStream.readLine()) != null) {
                novo.add(text);
            }

        } catch (IOException e) {
            System.out.println(e.getMessage());

        };
        return novo;
    }

    public static HashMap<String, Cliente> carrega_clientes(String string) {
        HashMap<String, Cliente> novo = new HashMap<>();
        BufferedReader inStream = null;

        try {
            inStream = new BufferedReader(new FileReader(string));
            String text = null;

            while ((text = inStream.readLine()) != null) {

                novo.put(text, new Cliente(text));
            }
        } catch (IOException e) {
            System.out.println(e.getMessage());

        };
        return novo;

    }

    public static ArrayList<Venda> vendasValidas(ArrayList<Venda> vendas, HashMap<String, Cliente> clientes, HashMap<String, Produto> produtos) {
        int i = 0;
        ArrayList<Venda> vendasValidas = new ArrayList<>();

        for (Venda v : vendas) {
            if (clientes.containsKey(v.getCodC()) && produtos.containsKey(v.getCodP())) {
                vendasValidas.add(v.clone());
            }
        }
        return vendasValidas;

    }

    public static Venda parseLinhaVenda(String linha, HashMap<String, Cliente> clientes, HashMap<String, Produto> produtos) {

        String[] line = null;

        line = linha.split(" ");

        for (int i = 0; i < 7; i++) {
            line[i].trim();
        }

        Venda v = new Venda(line[0], Float.parseFloat(line[1]), Integer.parseInt(line[2]), line[3], line[4], Integer.parseInt(line[5]), Integer.parseInt(line[6]));

       
        return v;
    }

    public static int vendasUnidades(ArrayList<Venda> vendas, HashMap<String, Cliente> clientes, HashMap<String, Produto> produtos) {
        int i = 0;
        ArrayList<Venda> totalvendas = vendasValidas(vendas, clientes, produtos);

        for (Venda v : totalvendas) {
            i += v.getUni();
        }

        return i;
    }

    public static float factTotal(ArrayList<Venda> vendas, HashMap<String, Cliente> clientes, HashMap<String, Produto> produtos) {
        float i = 0.0f;
        ArrayList<Venda> totalvendas = vendasValidas(vendas, clientes, produtos);

        for (Venda v : totalvendas) {
            i += v.getPreco();
        }

        return i;
    }

    public int preco0(ArrayList<Venda> vendas, HashMap<String, Cliente> clientes, HashMap<String, Produto> produtos) {
        ArrayList<Venda> totalvendas = vendasValidas(vendas, clientes, produtos);
        int i = 0;

        for (Venda v : totalvendas) {
            if (v.getPreco() == 0) {
                i++;

            }
        }
        return i;

    }

    public static int cliDif(ArrayList<Venda> vendas, HashMap<String, Cliente> clientes, HashMap<String, Produto> produtos) {
        ArrayList<Venda> totalvendas = vendasValidas(vendas, clientes, produtos);
        TreeSet<String> novo = new TreeSet<>();
        for (Venda v : totalvendas) {
            novo.add(v.getCodC());
        }
        return novo.size();
    }

    public static int cliCompras(ArrayList<Venda> vendas, HashMap<String, Cliente> clientes, HashMap<String, Produto> produtos) {
        ArrayList<Venda> totalvendas = vendasValidas(vendas, clientes, produtos);
        TreeSet<String> novo = new TreeSet<>();

        for (Venda v : totalvendas) {
            novo.add(v.getCodC());
        }

        return novo.size();

    }

    public static int cliNcompras(ArrayList<Venda> vendas, HashMap<String, Cliente> clientes, HashMap<String, Produto> produtos) {

        return cliCompras(vendas, clientes, produtos) - clientes.size();
    }

    public static int prodDif(ArrayList<Venda> vendas, HashMap<String, Cliente> clientes, HashMap<String, Produto> produtos) {
        ArrayList<Venda> totalvendas = vendasValidas(vendas, clientes, produtos);
        TreeSet<String> aux = new TreeSet<>();

        for (Venda v : totalvendas) {
            aux.add(v.getCodP());
        }

        return aux.size();

    }

    public static int prodNcomprados(ArrayList<Venda> vendas, HashMap<String, Cliente> clientes, HashMap<String, Produto> produtos) {
        ArrayList<Venda> totalvendas = vendasValidas(vendas, clientes, produtos);
        TreeSet<String> aux = new TreeSet<>();

        for (Venda v : totalvendas) {
            aux.add(v.getCodP());
        }

        return produtos.size() - aux.size();

    }

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
        main.vendasCarr = new ArrayList<>();

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
                System.out.println("//***********************************************************************************************************************************\\");
                System.out.println("//***********************************************************************************************************************************\\");
                System.out.println("//***                                                          Estatísticas                                                          ***\\");
                System.out.println("//***********************************************************************************************************************************\\");

                System.out.println("Ficheiro " + fileProdutos);
                Crono.start();
                main.listaprodutos = main.carrega_produtos(fileProdutos);
                Crono.stop();
                System.out.println("Tempo: " + Crono.print() + " segundos");
                System.out.println("Ficheiro " + fileClientes);
                Crono.start();

                main.listaclientes = main.carrega_clientes(fileClientes);
                Crono.stop();
                System.out.println("Tempo: " + Crono.print() + " segundos");
                System.out.println("Ficheiro " + fileVendas);
                Crono.start();
                vendas = main.carrega_vendas(fileVendas);
                Crono.stop();
                System.out.println("Tempo: " + Crono.print() + " segundos");
                main.vendasCarr = parseAllLinhas(vendas, main.listaclientes, main.listaprodutos);
                System.out.println("Vendas válidas: " + vendasValidas(main.vendasCarr, main.listaclientes, main.listaprodutos).size());
                System.out.println("Número Total de Produtos: " + main.listaprodutos.size());
                System.out.println("Número Total de Clientes: " + main.listaclientes.size());
                System.out.println("Total de Clientes que compraram: " + main.cliCompras(main.vendasCarr, main.listaclientes, main.listaprodutos));
                System.out.println("Total de Clientes que nunca compraram: " + main.cliNcompras(main.vendasCarr, main.listaclientes, main.listaprodutos));
                System.out.println("Total de Clientes diferentes: " + main.cliDif(main.vendasCarr, main.listaclientes, main.listaprodutos));
                //  System.out.println("Número de Unidades vendidas: " + main.vendasUnidades());
                System.out.println("Total facturado: " + main.factTotal(main.vendasCarr, main.listaclientes, main.listaprodutos));
                System.out.println("Total de compras preço = 0.0 : " + main.preco0(main.vendasCarr, main.listaclientes, main.listaprodutos));
                System.out.println("Total de produtos nunca comprados: " + main.prodNcomprados(main.vendasCarr, main.listaclientes, main.listaprodutos));
                System.out.println("Total de Produtos diferentes comprados: " + main.prodDif(main.vendasCarr, main.listaclientes, main.listaprodutos));
                System.out.println("//***********************************************************************************************************************************\\");
                
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
