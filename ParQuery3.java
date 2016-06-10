
import java.io.Serializable;
import java.util.ArrayList;

public class ParQuery3 implements Serializable {
        private ArrayList<Integer> total_compras ;
        private ArrayList<Integer> produtos_distintos;
        private float total_facturado;

    
        
        
    public ArrayList<Integer> getTotal_compras() {
        ArrayList<Integer> novo= new ArrayList<>();
        for(Integer i: this.total_compras)
            novo.add(i);
    
        return novo;
    }

    public void setTotal_compras(ArrayList<Integer> total_compras) {
        this.total_compras = total_compras;
    }

    public ArrayList<Integer> getProdutos_distintos() {
        ArrayList<Integer> novo= new ArrayList<>();
        for(Integer i: this.produtos_distintos)
            novo.add(i);
    
        return novo;
    }

    public void setProdutos_distintos(ArrayList<Integer> produtos_distintos) {
        this.produtos_distintos = produtos_distintos;
    }

    public float getTotal_facturado() {
        return total_facturado;
    }

    public void setTotal_facturado(float total_facturado) {
        this.total_facturado = total_facturado;
    }

    public ParQuery3(ArrayList<Integer> total_compras, ArrayList<Integer> produtos_distintos, float total_facturado) {
        this.total_compras = total_compras;
        this.produtos_distintos = produtos_distintos;
        this.total_facturado = total_facturado;
    }
       
    public ParQuery3(){
        this.total_compras=new ArrayList<>();
        this.produtos_distintos=new ArrayList<>();
        this.total_facturado=0.0f;
    }    
        
        
        public String toString() {
            StringBuilder s = new StringBuilder();
            int i=1;
            int c=1;
            for(Integer a: this.getTotal_compras()){
               s.append(" Mês "+i+": " +a+ "\n");
                i++;
                }
            
            for(Integer b: this.getProdutos_distintos()){
            s.append(" Produtos diferentes no mês "+c+": " + b+ "\n");
            c++;
            }
           
            s.append(" Total Gasto: " + this.getTotal_facturado() + "\n");
            
            return s.toString();
        }
    
}
