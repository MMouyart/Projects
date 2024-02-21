package poo.java.data;


public class User 
{
    public String pwd, name;
    public boolean access;
    public int id;
    @Override
    public String toString()
    {
       return " password= "+pwd+" , name= "+name+" , access= "+access+" , id= "+id; 
    }
}
