
import java.util.TreeSet;



public class Test {

    private Leitura ler;
    private Venda ven;
    
    
    public static void main(String[] args) {
        
        //String path = "C:\\Users\\João\\Documents\\NetBeansProjects\\GereVendas\\Produtos.txt";
        //TreeSet<String> shit = new TreeSet<String>();
        //shit = Leitura.lerProd(path);
        //Leitura.print(shit);
      
        
        //String path2 = "C:\\Users\\João\\Documents\\NetBeansProjects\\GereVendas\\Clientes.txt";
        //TreeSet<String> shit2 = new TreeSet<String>();
        //shit2 = Leitura.lerClie(path2);
        //Leitura.print(shit2);
        
        String path3 = "C:\\Users\\João\\Documents\\NetBeansProjects\\GereVendas\\Vendas_3M.txt";
        TreeSet<String> shit3 = new TreeSet<String>();
        shit3 = Leitura.lerFiles(path3);
        Leitura.print(shit3);
         
        
    }
    
}
