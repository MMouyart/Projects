package poo.java.data;


public class Transaction 
{
    public int userId, productId, quantity, mounth, year,id;
    public double price;
    @Override
    public String toString()
    {
     return "user id= "+userId+", product id= "+productId+" , quantity= "+quantity+" , month= "+mounth+" , year= "+year+" , id= "+id+" , price= "+price;   
    }
}
