/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package gerevendas;


public class Cliente {
    private String codC;
    
      public Cliente() {
        this.codC = "";
    }
    
    public Cliente(String codC) {
        this.codC = codC;
    }
    
    public Cliente(Cliente c) {
        this.codC = c.getCodC();
    }

    public String getCodC() {
        return codC;
    }

    public void setCodC(String codC) {
        this.codC = codC;
    }

   
    public String toString() {
        return "Cliente{" + "codC=" + codC + '}';
    }
    
     public boolean equals(Object o){
        
   if(this == o) return true;
   
   if((o==null)||(this.getClass() != o.getClass()))
   return false;
   else { Cliente c = (Cliente) o;
       return ( this.getCodC().equals(c.getCodC()));
    }
    
}
     
   public Cliente clone(){
    return new Cliente (this);
} 
    
}
