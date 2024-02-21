package poo.java.data;


public class ShoppingCart 
{
     public int id, number,productId;
     public String nameProd, nameUser;
     @Override
     public String toString()
     {
        return "id= "+id+" , number= "+number+" , product id= "+productId+" , name of product= "+nameProd+" , name of user= "+nameUser; 
     }
}
