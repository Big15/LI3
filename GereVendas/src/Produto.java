/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package gerevendas;


public class Produto {
    private String codP;

    public Produto() {
        this.codP = "";
    }

    public Produto(String codP) {
        this.codP = codP;
    }
    
    public Produto(Produto p){
        this.codP = p.getCodP();
}

    public String getCodP() {
        return codP;
    }

    public void setCodP(String codP) {
        this.codP = codP;
    }

   
    public String toString() {
        return "Produto{" + "codP=" + codP + '}';
    }
    
         public boolean equals(Object o){
        
   if(this == o) return true;
   
   if((o==null)||(this.getClass() != o.getClass()))
   return false;
   else { Produto p = (Produto) o;
       return ( this.getCodP().equals(p.getCodP()));
    }
    
}
     
   public Produto clone(){
    return new Produto (this);
} 
    
}
