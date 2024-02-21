package poo.java;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

import java.util.ArrayList;
import java.util.logging.Level;
import java.util.logging.Logger;

import poo.java.data.Product;
import poo.java.data.ShoppingCart;
import poo.java.data.Transaction;
import poo.java.data.User;

public class DAO {
    private DataBase                maBaseDonnées;
    private SearchDataBase          mySearch;
    private ArrayList<Product>      pListe;
    private ArrayList<User>         uListe;
    private ArrayList<Transaction>  tListe;
    private ArrayList<ShoppingCart> sListe;

    public DAO() throws ClassNotFoundException {
        maBaseDonnées = new DataBase();
        mySearch      = new SearchDataBase(maBaseDonnées);
        pListe        = new ArrayList();
        sListe        = new ArrayList();
        uListe        = new ArrayList();
        tListe        = new ArrayList();
    }

    public void addProduct(Product p)    // / Ajoute à la table Product un élément
    {
        maBaseDonnées.queryUpdate(
            "INSERT INTO product ( id, sold, stocks, amountDiscount, name, type, price, discount ) Values (" + p.id
            + " , " + p.sold + " , " + p.stocks + " , " + p.amountDiscount + " , '" + p.name + "' , '" + p.type
            + "' , " + p.price + " , " + p.discount + " )");
    }

    public void addShopingCart(ShoppingCart s)    // / Ajoute à la table ShopingCart un élément
    {
        maBaseDonnées.queryUpdate("INSERT INTO ShopingCart (nameProd, nameUser, number, id, productId) Values ( '"
                                  + s.nameProd + "' , '" + s.nameUser + "' , " + s.number + " , " + s.id + ", '"
                                  + s.productId + "' )");
    }

    public void addTransaction(Transaction t)    // / Ajoute à la table User un élément
    {
        maBaseDonnées.queryUpdate(
            "INSERT INTO transaction ( userId, productId, quantity, month, year, price, id) Values (" + t.userId
            + " , " + t.productId + " , " + t.quantity + " , " + t.mounth + " , " + t.year + " , " + t.price + ",'"
            + t.id + "' )");
    }

    public void addUser(User c)    // / Ajoute à la table User un élément
    {
        maBaseDonnées.queryUpdate("INSERT INTO user ( passWord, userName, access, id) Values ('" + c.pwd + "' , '"
                                  + c.name + "' , " + c.access + " , " + c.id + " )");
    }

    public void deleteProduct(Product p)    // / Ajoute à la table Product un élément
    {
        maBaseDonnées.queryUpdate("DELETE FROM product WHERE id = '" + p.id + "'");
    }

    public void deleteShopingCart(ShoppingCart s)    // / Modifie la table ShopingCart avec le critère id
    {
        maBaseDonnées.queryUpdate("DELETE FROM ShopingCart WHERE id = '" + s.id + "'");
    }

    public void deleteShopingCartAll(String s) throws SQLException {
        Connection con    = maBaseDonnées.getConnection();
        Statement  stmt   = con.createStatement();
        ResultSet  result = stmt.executeQuery("SELECT * FROM shopingcart");

        while (result.next()) {
            if (result.getString(3).equals(s)) {
                maBaseDonnées.queryUpdate("DELETE FROM ShopingCart  WHERE id=' " + result.getInt(5) + "'");
            }
        }
    }

    public void deleteTransaction(Transaction t) {
        maBaseDonnées.queryUpdate("DELETE FROM transaction WHERE id='" + t.id + "'");
    }

    public void deleteUser(User c)    // / Ajoute à la table User un élément
    {
        maBaseDonnées.queryUpdate("DELETE FROM user WHERE id = '" + c.id + "'");
    }

    public void modifyProdcut(Product p)    // / Modifie la table Product avec le critère id
    {
        deleteProduct(p);
        addProduct(p);
    }

    public void modifyShopingCart(ShoppingCart s)    // / Modifie la table User avec le critère id
    {
        deleteShopingCart(s);
        addShopingCart(s);
    }

    public void modifyUser(User c)    // / Modifie la table User avec le critère id
    {
        deleteUser(c);
        addUser(c);
    }

    public Product searchOneProduct(String criteria) throws SQLException    // /  Décompose la table Product qui a été retournée en liste d'objet de type Product. Avec un élément de l'array List par ligne de la table
    {
        ResultSet set = mySearch.search(criteria, "product");
        Product   p   = new Product();
pListe=new ArrayList();
        if (set.next()) {
            try {
                p.amountDiscount = set.getInt(4);
                p.discount       = set.getInt(8);
                p.id             = set.getInt(1);
                p.name           = set.getString(5);
                p.price          = set.getInt(7);
                p.sold           = set.getInt(2);
                p.stocks         = set.getInt(3);
                p.type           = set.getString(6);

                if (p.stocks != 0) {    // / Si le produit est en stock on l'ajoute
                    pListe.add(p);
                }

                return pListe.get(0);
            } catch (SQLException ex) {
                Logger.getLogger(DAO.class.getName()).log(Level.SEVERE, null, ex);
            }
        }

        return pListe.get(0);
    }

    public ArrayList<Product> searchProduct(String criteria)    // /  Décompose la table Product qui a été retournée en liste d'objet de type Product. Avec un élément de l'array List par ligne de la table
    {
        ResultSet set = mySearch.search(criteria, "product");

        pListe = new ArrayList<Product>();

        try {
            while (set.next()) {
                Product p = new Product();

                p.amountDiscount = set.getInt(4);
                p.discount       = set.getInt(8);
                p.id             = set.getInt(1);
                p.name           = set.getString(5);
                p.price          = set.getInt(7);
                p.sold           = set.getInt(2);
                p.stocks         = set.getInt(3);
                p.type           = set.getString(6);

                if (p.stocks != 0) {    // / Si le produit est en stock on l'ajoute
                    pListe.add(p);
                }
            }

            return pListe;
        } catch (SQLException ex) {
            Logger.getLogger(DAO.class.getName()).log(Level.SEVERE, null, ex);
        }

        return pListe;
    }

    public ArrayList<ShoppingCart> searchShopingCart(String criteria) throws SQLException    // / Décompose la table User qui a été retournée en liste d'objet de type user. Avec un élément de l'array List par ligne de la table
    {
        Connection              con    = maBaseDonnées.getConnection();
        Statement               stmt   = con.createStatement();
        ResultSet               set    = stmt.executeQuery("SELECT  * FROM shopingcart");
        ArrayList<ShoppingCart> sliste = new ArrayList<ShoppingCart>();

        try {
            while (set.next()) {
                ShoppingCart s = new ShoppingCart();

                s.nameProd  = set.getString(1);
                s.id        = set.getInt(5);
                s.nameUser  = set.getString(3);
                s.number    = set.getInt(4);
                s.productId = set.getInt(2);
                sliste.add(s);
            }

            if (sliste != null) {
                for (ShoppingCart sListe1 : sliste) {
                    System.out.println(sListe1.toString());
                }
            }

            return sliste;
        } catch (SQLException ex) {
            Logger.getLogger(DAO.class.getName()).log(Level.SEVERE, null, ex);
        }

        return sliste;
    }

    public ArrayList<Transaction> searchTransaction(String criteria)    // / Décompose la table User qui a été retournée en liste d'objet de type user. Avec un élément de l'array List par ligne de la table
    {
        ResultSet set = mySearch.search(criteria, "transaction");

        tListe = new ArrayList<Transaction>();

        try {
            while (set.next()) {
                Transaction t = new Transaction();

                t.userId    = set.getInt(1);
                t.productId = set.getInt(2);
                t.quantity  = set.getInt(3);
                t.mounth    = set.getInt(4);
                t.year      = set.getInt(5);
                t.price     = set.getDouble(6);
                t.id        = set.getInt(7);
                tListe.add(t);
            }
        } catch (SQLException ex) {
            Logger.getLogger(DAO.class.getName()).log(Level.SEVERE, null, ex);
        }

        return tListe;
    }

    public ArrayList<User> searchUser(String criteria) throws SQLException    // / Décompose la table User qui a été retournée en liste d'objet de type user. Avec un élément de l'array List par ligne de la table
    {
        ResultSet set = mySearch.search(criteria, "user");

        uListe = new ArrayList<User>();

        try {
            while (set.next()) {
                User c = new User();

                c.pwd    = set.getString(1);
                c.id     = set.getInt(4);
                c.name   = set.getString(2);
                c.access = set.getBoolean(3);
                uListe.add(c);
            }

            return uListe;
        } catch (SQLException ex) {
            Logger.getLogger(DAO.class.getName()).log(Level.SEVERE, null, ex);
        }

        return uListe;
    }

    public DataBase getDb() {
        return maBaseDonnées;
    }

    public ArrayList<Product> getProduct() {
        return pListe;
    }

    public ArrayList<ShoppingCart> getShoppingCart() {
        return sListe;
    }

    public ArrayList<Transaction> getTransaction() {
        return tListe;
    }

    public ArrayList<User> getUser() {
        return uListe;
    }
}


//~ Formatted by Jindent --- http://www.jindent.com
