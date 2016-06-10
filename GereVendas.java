/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.TreeMap;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

public class GereVendas {

    public static void tabelaEst(TreeMap<Integer, ArrayList<Venda>> comprasmes) {
        int count = 0;
        int i = 1;
        float valor = 0, f1 = 0, f2 = 0, f3 = 0;
        /*DecimalFormat df = new DecimalFormat();
        df.setMaximumFractionDigits(2);
        System.out.println(df.format(decimalNumber));*/
        System.out.println("Mês\tProdutos Comprados\tFacturacao Total\tFilial 1\tFilial 2\tFilial 3\tClientes");
        for (ArrayList<Venda> cena : comprasmes.values()) {
            for (Venda v : cena) {
                if (v.getMes() == i) {
                    count++;
                    valor += v.getPreco();
                    switch (v.getFilial()) {
                        case 1:
                            f1 += v.getPreco();
                            break;
                        case 2:
                            f2 += v.getPreco();
                            break;
                        case 3:
                            f3 += v.getPreco();
                            break;
                    }
                } else {
                    System.out.println(i + "\t     " + count + "\t     " + valor + "\t     " + f1 + "\t     " + f2 + "\t     " + f3 + "\t     ");
                    count = 1;
                    i++;
                    valor += v.getPreco();
                    switch (v.getFilial()) {
                        case 1:
                            f1 += v.getPreco();
                            break;
                        case 2:
                            f2 += v.getPreco();
                            break;
                        case 3:
                            f3 += v.getPreco();
                            break;
                    }
                }
            }
        }
        //System.out.println("Mês " + i + ":" + count);
    }

    public static Venda parseLinhaVenda(String linha) {

        String[] line = null;

        line = linha.split(" ");

        for (int i = 0; i < 7; i++) {
            line[i].trim();
        }

        Venda v = new Venda(line[0], Float.parseFloat(line[1]), Integer.parseInt(line[2]), line[3], line[4], Integer.parseInt(line[5]), Integer.parseInt(line[6]));

        return v;
    }

    public static void carrega_vendas(String string, Hipermercado main) {
        BufferedReader inStream = null;

        try {
            inStream = new BufferedReader(new FileReader(string));
            String text = null;

            while ((text = inStream.readLine()) != null) {
                main.addVenda(parseLinhaVenda(text));
            }
            main.vendasValidas();

        } catch (IOException e) {
            System.out.println(e.getMessage());

        };
    }

    public static void carrega_clientes(String string, Hipermercado main) {
        BufferedReader inStream = null;

        try {
            inStream = new BufferedReader(new FileReader(string));
            String text = null;

            while ((text = inStream.readLine()) != null) {

                main.addCliente(text);
            }
        } catch (IOException e) {
            System.out.println(e.getMessage());

        };

    }

    public static void carrega_produtos(String string, Hipermercado main) {
        BufferedReader inStream = null;
        try {
            inStream = new BufferedReader(new FileReader(string));
            String text = null;

            while ((text = inStream.readLine()) != null) {
                main.addProduto(text);

            }
        } catch (IOException e) {
            System.out.println(e.getMessage());

        };

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

    public static void main(String[] args) throws IOException, ClassNotFoundException {

        int lifetime = 1, load = 0;
        ArrayList<String> vendas = new ArrayList<>();
        InputStreamReader reader = new InputStreamReader(System.in);
        BufferedReader input = new BufferedReader(reader);
        String aux;
        String aux2;
        String fileClientes = null, fileVendas = null, fileProdutos = null;
        Hipermercado main = new Hipermercado();

        System.out.println("/***********************************************************************************************************************************\\");
        System.out.println("/***********************************************************************************************************************************\\");
        System.out.println("/***                                                          GEREVENDAS                                                         ***\\");
        System.out.println("/***********************************************************************************************************************************\\");
        System.out.println("/***                                           Deseja carregar os ficheiros default? (s/n)                                       ***\\");
        System.out.println("/***********************************************************************************************************************************\\");
        aux = input.readLine();
        if (aux.equals("s")) {
            fileClientes = "Clientes.txt";
            fileProdutos = "Produtos.txt";
            fileVendas = "Vendas_1M.txt";

        } else if (aux.equals("n")) {

        }

        while (lifetime == 1) {
            if (load == 0) {
                System.out.println("/***********************************************************************************************************************************\\");
                System.out.println("/***********************************************************************************************************************************\\");
                System.out.println("/***                                                          Estatísticas                                                       ***\\");
                System.out.println("/***********************************************************************************************************************************\\");
                System.out.println("/*** Ficheiro " + fileProdutos +"                                                                                                       ***\\");
                Crono.start();
                carrega_produtos(fileProdutos, main);
                Crono.stop();
                System.out.println("/*** Tempo: " + Crono.print() + " segundos  "+"                                                                                                ***\\");
                System.out.println("/*** Ficheiro " + fileClientes+"                                                                                                       ***\\");
                Crono.start();
                carrega_clientes(fileClientes, main);
                Crono.stop();
                System.out.println("/*** Tempo: " + Crono.print() + " segundos "+"                                                                                                ***\\");
                System.out.println("/*** Ficheiro " + fileVendas+"                                                                                                      ***\\");
                Crono.start();
                carrega_vendas(fileVendas, main);
                Crono.stop();
                 main.comprasmes = main.parseAllLinhasToMap();
                System.out.println("/*** Tempo: " + Crono.print() + " segundos  "+"                                                                                                ***\\");
                System.out.println("/*** Vendas válidas: " + main.nvendasValidas()+"                                                                                                      ***\\");
                main.vendasInvalidas();
               /* System.out.println("/*** Número Total de Produtos: " + main.nProds()+"                                                                                            ***\\");
                System.out.println("/*** Número Total de Clientes: " + main.nClie()+"                                                                                             ***\\");
                System.out.println("/*** Total de Clientes que compraram: " + main.cliCompras()+"                                                                                      ***\\");
                System.out.println("/*** Total de Clientes que nunca compraram: " + main.cliNcompras()+"                                                                                    ***\\");
                System.out.println("/*** Total de Clientes diferentes: " + main.cliCompras()+"                                                                                         ***\\");
                System.out.println("/*** Número de Unidades vendidas: " + main.vendasUnidades()+"                                                                                       ***\\");
                System.out.println("/*** Total facturado: " + main.factTotal()+"                                                                                               ***\\");
                System.out.println("/*** Total de compras preço = 0.0 : " + main.preco0()+"                                                                                           ***\\");
                System.out.println("/*** Total de produtos nunca comprados: " + main.prodNcomprados()+"                                                                                      ***\\");
                System.out.println("/*** Total de Produtos diferentes comprados: " + main.prodDif()+"                                                                              ***\\");
                tabelaEst(main.comprasmes);
                System.out.println("/***********************************************************************************************************************************\\");

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
            load = 1;
            System.out.println("/***********************************************************************************************************************************\\");
            System.out.println("/***********************************************************************************************************************************\\");
            System.out.println("/***                                                          GEREVENDAS                                                         ***\\");
            System.out.println("/***********************************************************************************************************************************\\");
            System.out.println("/*** 0- Gravar estado                                                                                                            ***\\");
            System.out.println("/*** 1- Lista ordenada alfabeticamente com os códigos dos produtos nunca comprados e o seu respectivo total.                     ***\\");
            System.out.println("/*** 2- Dado um mês válido, determinar o número total vendas realizadas e o número total de clientes distintos que as fizeram.   ***\\");
            System.out.println("/*** 3- Dado um cliente, determinar, para cada mês, quantas compras fez, quantos produtos distintos comprou e quanto gastou.     ***\\");
            System.out.println("/*** 4- Dado um produto, determinar, mês a mês, quantas vezes foi comprado, por quantos clientes diferentes e o total facturado. ***\\");
            System.out.println("/*** 5- Dado um cliente determinar a lista de códigos de produtos que mais comprou (e quantos).                                  ***\\");
            System.out.println("/*** 6- Determinar o conjunto dos X produtos mais vendidos em todo o ano e o número total de clientes que os compraram.          ***\\");
            System.out.println("/*** 7- Determinar, para cada filial, a lista dos três maiores compradores em termos de dinheiro facturado;                      ***\\");
            System.out.println("/*** 8- Determinar os códigos dos X clientes, que compraram mais produtos diferentes, indicando quantos.                         ***\\");
            System.out.println("/*** 9- Dado um produto, determinar o conjunto dos X clientes que mais o compraram e, para cada um, qual o valor gasto.          ***\\");
            System.out.println("/***********************************************************************************************************************************\\");
            System.out.println("/***********************************************************************************************************************************\\");

            aux = input.readLine();

            switch (aux) {
                case "0":
                    int c = 0;
                    
                    break;

                case "1":
                main.querie1();
                    break;
                case "2":
                    int mes = 0;
                    TreeMap<Integer,ParQuery2> q2 = new TreeMap<>();
                    ParQuery2 p = new ParQuery2();
                    System.out.println("/***********************************************************************************************************************************\\");
                    System.out.println("/***                                Introduza o mês que pretende visualizar.(1-Janeiro,...,12-Dezembro)                          ***\\");
                    System.out.println("/***********************************************************************************************************************************\\");
                    aux = input.readLine();
                    mes = Integer.parseInt(aux);
                    q2 = main.query2(mes);
                    if(q2.containsKey(mes)){
                        p = q2.get(mes);
                        System.out.println(p.toString());
                    }
                   
                    break;
                
                case "3":
                    String codC = new String();
                    ParQuery3 p3 = new ParQuery3();
                    System.out.println("/***********************************************************************************************************************************\\");
                    System.out.println("/***                                       Introduza o código de Cliente pretendido                                              ***\\");
                    System.out.println("/***********************************************************************************************************************************\\");
                    aux = input.readLine();
                    codC = aux;
                    p3 = main.Query3(codC);
                    System.out.println(p3);
                    
                    
                    
                    break;
                case "4":
                    String codP = new String();
                    ParQuery4 p4 = new ParQuery4();
                    System.out.println("/***********************************************************************************************************************************\\");
                    System.out.println("/***                                       Introduza o código de produto pretendido                                              ***\\");
                    System.out.println("/***********************************************************************************************************************************\\");
                    aux = input.readLine();
                    codP = aux;
                    p4 = main.query4(codP);
                    System.out.println(p4);
                    
                    break;
            }
        }
    }

}