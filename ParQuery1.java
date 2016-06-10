
import java.io.Serializable;
import java.util.TreeMap;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author Demo
 */
public class ParQuery1 implements Serializable {
    private TreeMap<String, Produto> listaprodutos;
    private int total;

    
    public ParQuery1(TreeMap<String, Produto> listaprodutos, int total) {
        this.listaprodutos = listaprodutos;
        this.total = total;
    }
    
    public ParQuery1(){
        this.listaprodutos= new TreeMap<>();
        this.total=0;
    }

    public TreeMap<String, Produto> getListaprodutos() {
        TreeMap<String,Produto> novo= new TreeMap<>();
        
        for(Produto p: listaprodutos.values())
            novo.put(p.getCodP(), p.clone());
        
        return novo;
    }

    public void setListaprodutos(TreeMap<String, Produto> listaprodutos) {
        this.listaprodutos = listaprodutos;
    }

    public int getTotal() {
        return total;
    }

    public void setTotal(int total) {
        this.total = total;
    }
    
    public String toString() {
       StringBuilder s= new StringBuilder();
   
       s.append(this.getListaprodutos().values() + "\n");
       s.append("Total de produtos não comprados: " + this.getTotal());
        return s.toString();
        
    }
    
    
}
