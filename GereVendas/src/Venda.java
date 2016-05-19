
import java.util.*;

public class Venda {

    private String codP;
    private String codC;
    private double preco;
    private int filial;
    private int uni;
    private int mes;
    private String promo;

    public Venda(String codP, double preco, int uni, String p, String codC, int mes, int filial){
        this.codP = codP;
        this.codC = codC;
        this.preco = preco;
        this.filial = filial;
        this.uni = uni;
        this.mes = mes;
        this.promo = p;
    }

    public Venda() {
        this.codP = new String();
        this.codC = new String();
        this.preco = 0.0;
        this.filial = 0;
        this.uni = 0;
        this.mes = 0;
        this.promo = null;
    }

    public Venda(Venda v) {
        this.codP = v.getCodP();
        this.codC = v.getCodC();
        this.preco = v.getPreco();
        this.filial = v.getFilial();
        this.uni = v.getUni();
        this.mes = v.getMes();
        this.promo = v.getPromo();
    }

    public String getCodP() {
        return codP;
    }

    public String getCodC() {
        return codC;
    }

    public double getPreco() {
        return preco;
    }

    public int getFilial() {
        return filial;
    }

    public int getUni() {
        return uni;
    }

    public int getMes() {
        return mes;
    }

    public String getPromo() {
        return promo;
    }
    
    public boolean equals(Object o) {
        
        if (this == o) {
            return true;
        }

        if ((o == null) || (this.getClass() != o.getClass())) {
            return false;
        } else {
            Venda v = (Venda) o;
            return (this.getCodP().equals(v.getCodP()) && this.getCodC().equals(v.getCodC()) && this.getPreco() == (v.getPreco())
                    && this.getFilial() == (v.getFilial()) && this.getUni() == (v.getUni()) && this.getMes() == (v.getMes()) && this.getPromo().equals(v.getPromo()));
        }
    }

    public String toString() {
        StringBuilder s = new StringBuilder("-----Venda-----\n");

        s.append(" Código do Produto:" + this.getCodP() + "\n");
        s.append(" Código do Cliente:" + this.getCodC() + "\n");
        s.append(" Filial:" + this.getFilial() + "\n");
        s.append(" Preço:" + this.getPreco() + "\n");
        s.append(" Promoção(P) ou Normal(N):" + this.getPromo()+"\n");
        s.append(" Unidades vendidas:" + this.getUni() + "\n");
        s.append(" Mês da Venda:" + this.getMes() + "\n");

        return s.toString();
    }

    public Venda clone() {
        return new Venda(this);
    }
    
   /*
   public static Venda parseLinhaVenda(String linha) {
        Venda v = new Venda();
        int i = 0; 
        while (linha != null){
         for(String s: linha.split(" ",6))
         switch (i) {
                    case 0: 
                        codP = s;
                        break;
                    case 1: 
                        preco = Double.parseDouble(s);
                        break;
                    case 2: 
                        uni = Integer.parseInt(s);
                        break;
                    case 3: 
                        promo = promo;
                        break;
                    case 4: 
                        codC = codC;
                        break;
                    case 5: 
                        mes = Integer.parseInt(s);
                        break;
                    case 6: 
                        filial = Integer.parseInt(s);
                        break;
                }
        i++;
       
        }
        return v;
    }
/*
    public static ArrayList<Venda> parseAllLinhas(ArrayList<String> linhas) {
        ArrayList<Venda> aux = new ArrayList<Venda>();

        return aux;
    }*/

}
