/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author Manny
 */
public class ParStringDouble {
    private String texto;
    private Double valor;
    
    public ParStringDouble(){
        this.texto = "";
        this.valor = 0.0;
    }
    
    public ParStringDouble(String t, Double d){
        this.texto = t;
        this.valor = d;
    }
    
    public ParStringDouble(ParStringDouble p){
        this.texto = p.getTexto();
        this.valor = p.getValor();
    }
    
    public String getTexto(){
        return this.texto;
    }
    
    public Double getValor(){
        return this.valor;
    }
    
}
