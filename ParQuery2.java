


/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


public class ParQuery2 {
        private int totclientes;
        private int totvendas;

        public ParQuery2() {
            this.totclientes = 0;
            this.totvendas = 0;
        }

        public ParQuery2(int totc, int totv) {
            this.totclientes = totc;
            this.totvendas = totv;
        }
        
        public ParQuery2(ParQuery2 p){
            this.totclientes = p.getTotclientes();
            this.totvendas = p.getTotvendas();
        }
        
        public int getTotclientes() {
            return this.totclientes;
        }

        public int getTotvendas() {
            return this.totvendas;
        }

        public void setClientes(int totc) {
            this.totclientes = totc;
        }

        public void setTotal(int total2) {
            this.totvendas = total2;
        }

        public String toString() {
            StringBuilder s = new StringBuilder();
            
            s.append(" Total de Vendas:" + this.getTotvendas() + "\n");
            s.append(" Total de Clientes diferentes:" + this.getTotclientes()+ "\n");
           
            return s.toString();
        }

    }

