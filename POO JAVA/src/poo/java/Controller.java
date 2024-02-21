package poo.java;

import java.sql.SQLException;

import java.util.ArrayList;
import java.util.Scanner;

import poo.java.data.Product;
import poo.java.data.ShoppingCart;
import poo.java.data.Transaction;
import poo.java.data.User;
import poo.java.view.View;

public class Controller {
    private User                    user;
    private Model                   model;
    private View                    view;
    private ArrayList<Product>      pListe;
    private ArrayList<User>         uListe;
    private ArrayList<Transaction>  tListe;
    private ArrayList<ShoppingCart> sListe;

    public Controller() throws ClassNotFoundException {
        model  = new Model(this);
      
        pListe = new ArrayList();
        sListe = new ArrayList();
        uListe = new ArrayList();
        tListe = new ArrayList();
    }
    public Model getModel()
    {
        return model;
    }
    
    

    public void addCart() throws SQLException {
        

        Scanner scan = new Scanner(System.in);

        System.out.println("select one the product te be added");

        int     id       = scan.nextInt();
        int     quantity = 0;
        Product p        = model.loadProduct(id).get(0);

        while ((quantity == 0) || (quantity > p.stocks)) {
            System.out.println("what quantity ? The available stock is of : " + p.stocks);
            quantity = scan.nextInt();
        }

        model.addItemShopingCart(p, user, quantity);
        System.out.println("you bought : " + quantity + "  " + p.name);
    }

    public void addToCart(Product p) {

        // view.viewShoppingCart(model.loadShoppingCart(user.name), model.priceTotalShopingCart(user.name));
    }

    public void buy() {
       
    }

    public void confirmBuy() throws SQLException {
        model.payment(user);
        pListe = model.sortPopular(model.loadAllProduct());
       

        ArrayList<ShoppingCart> shoppingCart = model.loadShoppingCart(user.name);

        
    }

    public void connect(String name, String pwd) throws SQLException {
        
        User u = model.connect(name, pwd);

        if (u == null) {

            // /Appeler une fonction de view qui écrit que l'user n'a pas réussi à se connecter
            pListe = model.sortPopular(model.loadAllProduct());
        } else {
            user   = u;
            sListe = model.loadShoppingCart(name);
            //view.viewShoppingCart(sListe, model.priceTotalShopingCart(user.name));

            // /Afficher  le panier à l'écran
        }
        System.out.println(user.toString());
    }
public Product getOneProduct(String s)
{Product p=new Product();
    pListe=model.loadAllProduct();
    for(int i=0;i<pListe.size();i++)
    {
        if(s.equals(pListe.get(i).name)) p=pListe.get(i);
    }
    return p;
}
public ShoppingCart getOneSC(String s) throws SQLException
{
    ShoppingCart sc=new ShoppingCart();
    sListe=model.getallShoppingCart();
    for(int i=0;i<sListe.size();i++)
    {
        if(s.equals(sListe.get(i).nameProd)) sc=sListe.get(i);
    }
    return sc;
}
    public void deleteProduct() {
        Scanner scan = new Scanner(System.in);

        pListe = model.loadAllProduct();

        int id = 0;

        if (pListe != null) {
            for (int i = 0; i < pListe.size(); i++) {
                System.out.println(pListe.get(i).toString());
            }

            System.out.println("choose one id for the product to delete it");
            id = scan.nextInt();
            model.deleteProduct(id);
        }
    }

    public void deleteShopingCart(ShoppingCart s) throws SQLException {
        
            model.deleteShopingCart(s.id);
        }
    

    public void deleteTransaction() {
        tListe = model.loadAllTransactions();

        int     id   = 0;
        Scanner scan = new Scanner(System.in);

        if (tListe != null) {
            for (int i = 0; i < tListe.size(); i++) {
                System.out.println(tListe.get(i).toString());
            }

            System.out.println("choose one id for the transaction to delete it");
            id = scan.nextInt();
            model.deleteTransaction(id);
        }
    }

    public void deleteUser() throws SQLException {
        if (user != null) {
            model.deleteUser(user.id);
        }
    }

    public void start() throws SQLException {
        pListe = model.sortPopular(model.loadAllProduct());
        
    }

    public ArrayList<Product> getProduct() throws SQLException{
        pListe=model.loadAllProduct();
        return pListe;
    }

    public ArrayList<ShoppingCart> getShoppingCart() throws SQLException {
        sListe=model.getallShoppingCart();
        return sListe;
    }

    public ArrayList<Transaction> getTransaction() throws SQLException {
        tListe=model.loadAllTransactions();
        return tListe;
    }

    public ArrayList<User> getUser() throws SQLException {
        uListe=model.loadAllUser();
        return uListe;
    }
    public void addUser(String name, String pwd) throws SQLException{
    User u=new User();
    boolean access=false;
    
   u.access=access;
   u.id=0;
   u.name=name;
   u.pwd=pwd;
  user= model.createUser(u);
  System.out.println(user.toString());
    }
    public void addTransaction() throws SQLException
    {
      Transaction t=new Transaction();
      t.id=0;
      t.mounth=12;
      t.price=10;
      t.productId=109;
      t.quantity=10;
      t.userId=109;
      t.year=2020;
      model.addTransaction(t);
    }
    public void addShoppingCart(Product p) throws SQLException
    {
     ShoppingCart c=new ShoppingCart();
     c.id=0;
     c.nameProd=p.name;
     c.nameUser=user.name;
     c.number=1;
     c.productId=p.id;
     model.addShoppingCart(c);
    }
    public void  addProduct(Product p) throws SQLException
    {
     
     model.addProduct(p);
    }
    public void addUser(User u) throws SQLException
    {
        model.addUser(u);
    }
    public void deleteTransaction(Transaction t)
    {
        model.deleteT(t);
    }
    public void deleteProduct(Product p)
    {
        model.deleteP(p);
    }
    public void deleteUser(User u)
    {
        model.deleteU(u);
    }
    public Transaction searchTransaction(int id)
    {
     return model.searchT(id);
    }
    public Product SearchProduct(String name)
    {
     return model.searchP(name);
    }
    public ShoppingCart SearchShoppingCart(String name)
    {
      return model.searchS(name);
    }
    public User SearchUser(String name)
    {
        return model.searchU(name);
    }
   
}


//~ Formatted by Jindent --- http://www.jindent.com
