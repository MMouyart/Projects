package poo.java.view;

import java.sql.SQLException;
import java.util.concurrent.TimeUnit;
import poo.java.Controller;




public class View 
{private Controller c;
    public View(Controller c)
    {
        this.c=c;
    }
    public  void main(String[] args) throws SQLException, ClassNotFoundException, InterruptedException 
    { 
        
        Launcher fenetre = new Launcher(c);
        
        fenetre.setVisible(true);
        
        TimeUnit.SECONDS.sleep(15);
        if(c.getUser().get(0).access==false) {
        ClientView clientview=new ClientView(c.getUser().get(0), c.getProduct(), c.getShoppingCart(),c);
        clientview.setVisible(true);}
        if(c.getUser().get(0).access==true)
        {
            ViewEmployee viewE=new ViewEmployee(c.getUser().get(0),c.getProduct(),c.getUser(),c.getTransaction(),c);
            viewE.setVisible(true);
        }
        
            
        
    }
    
}
