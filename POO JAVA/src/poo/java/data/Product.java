package poo.java.data;


public class Product 
{
    public int id, sold, stocks , amountDiscount;
    public String name ,type;
    public double price, discount;
    
    @Override
    public String toString()
    {
        return "id= "+id+" , sold= "+sold+" , stocks= "+stocks+" , amountDiscount= "+amountDiscount+" , name= "+name+" , type= "+type+" , price= "+price+" , discount= "+discount;
    }
}
