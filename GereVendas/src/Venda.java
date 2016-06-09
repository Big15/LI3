import java.io.Serializable;
import java.util.*;

public class Venda implements Serializable {

    private String codP;
    private String codC;
    private float preco;
    private int filial;
    private int uni;
    private int mes;
    private String promo;

    public Venda(String codP, float preco, int uni, String p, String codC, int mes, int filial){
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
        this.preco = 0.0f;
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

    public float getPreco() {
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
    
    /*
     
*/
    public String toString() {
        StringBuilder s = new StringBuilder("-----Venda-----\n");

        s.append(" Código do Produto:" + this.getCodP()+"\n");
        s.append(" Código do Cliente:" + this.getCodC() + "\n");
     //   s.append(" Filial:" + this.getFilial() + "\n");
     //   s.append(" Preço:" + this.getPreco() + "\n");
     //   s.append(" Promoção(P) ou Normal(N):" + this.getPromo()+"\n");
     //   s.append(" Unidades vendidas:" + this.getUni() + "\n");
        s.append(" Mês da Venda:" + this.getMes() + "\n");

        return s.toString();
    }

    public Venda clone() {
        return new Venda(this);
    }
}