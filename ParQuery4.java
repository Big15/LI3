
import java.util.ArrayList;



public class ParQuery4 {

    private ArrayList<Integer> total_compras ;
    private ArrayList<Integer> clientes_distintos;
    private ArrayList<Float> facturado_mes;
    private float total_facturado;

    public ParQuery4() {
        this.total_compras = null;
        this.clientes_distintos = null;
        this.facturado_mes = null;
        this.total_facturado = 0.0f;
    }

    public ParQuery4(ArrayList<Integer> total_compras, ArrayList<Integer> clientes_distintos, ArrayList<Float> facturado_mes, float total_facturado) {
        this.total_compras = total_compras;
        this.clientes_distintos = clientes_distintos;
        this.facturado_mes = facturado_mes;
        this.total_facturado = total_facturado;
    }

    public ArrayList<Integer> getTotalCompras() {
        return this.total_compras;
    }

    public ArrayList<Integer> getClientes_distintos() {
        return this.clientes_distintos;
    }

    public ArrayList<Float> getFacturadoMes() {
        return this.facturado_mes;
    }

    public float getTotalFacturado() {
        return this.total_facturado;
    }

    public void setTotal_compras(ArrayList<Integer> total_compras) {
        this.total_compras = total_compras;
    }

    public void setClientes_distintos(ArrayList<Integer> clientes_distintos) {
        this.clientes_distintos = clientes_distintos;
    }

    public void setFacturado_mes(ArrayList<Float> facturado_mes) {
        this.facturado_mes = facturado_mes;
    }

    public void setTotal_facturado(float total_facturado) {
        this.total_facturado = total_facturado;
    }
        
     public String toString() {
            StringBuilder s = new StringBuilder();
           int i=1;
           int c=1;
            
            for(Integer a: this.getTotalCompras()){
                s.append(" Total de compras mês "+i+": " +a+ "\n");
                i++;
            }
            s.append("\n");
            for(Integer b: this.getClientes_distintos()){
            s.append(" Clientes diferentes no mês "+c+": " + b+ "\n");
            c++;
            }
            s.append("\n");
            for(Float f: this.getFacturadoMes()){
            s.append(" Total facturado no mês: " + f + "\n");}
            s.append("\n");
            s.append(" Total Facturado Anual: " + this.getTotalFacturado() + "\n");
            
            return s.toString();
        }
    
}

