package poo.java;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

import java.util.ArrayList;

import poo.java.data.Product;
import poo.java.data.ShoppingCart;
import poo.java.data.Transaction;
import poo.java.data.User;

public class Model {
    private DAO        monDAO;
    private User       user;
    private Controller c;

    public Model(Controller c) throws ClassNotFoundException {
        this.c = c;
        user   = new User();
        monDAO = new DAO();
    }
    public DAO getDao()
    {
        return monDAO;
    }

    public void addItemShopingCart(Product p, User u, int quantity) throws SQLException    // / modifier user
    {
        int                     id    = 0,
                                newId = 0;
        String                  name  = "";
        int                     pId   = 0;
        boolean                 exist = false;
        ArrayList<ShoppingCart> s     = monDAO.searchShopingCart("");

        for (int i = 0; i < s.size(); i++) {
            pId  = s.get(i).productId;
            name = s.get(i).nameUser;

            if ((pId == p.id) && u.name.equals(name)) {
                exist = true;
            }

            id = s.get(i).id;
        }

        newId = getMaxShoppingCart();

        if (exist == false)               // /On vérifie si il n'existe pas déja dans le panier de l'user
        {
            ShoppingCart sc = new ShoppingCart();

            sc.id        = newId;
            sc.productId = p.id;
            sc.number    = quantity;
            sc.nameProd  = p.name;
            sc.nameUser  = u.name;
            monDAO.addShopingCart(sc);    // / On le créer
        } else                            // /si il existe on modifie son nombre
        {
            s = monDAO.searchShopingCart("WHERE id='" + id + "'");

            ShoppingCart sc = s.get(0);

            sc.number = sc.number + quantity;
            monDAO.modifyShopingCart(sc);
        }
    }

    public boolean changeProduct(Product p) throws SQLException    // / modifier user
    {
        if (monDAO.searchUser("where  id = '" + p.id + "'").size() == 0)    // /On vérifie si il n'existe pas déja
        {
            monDAO.modifyProdcut(p);                                        // / On modifie

            return true;                                                    // /on retourne que ca a reussi
        } else {
            return false;    // /sinon on retourne qu'il existe déja un produit identique meme id
        }
    }

    public boolean changeUser(User u) throws SQLException    // / modifier user
    {
        if (monDAO.searchUser("where  id = '" + u.id + "'").size() == 0)    // /On vérifie si il n'existe pas déja
        {
            monDAO.modifyUser(u);                                           // / On modifie

            return true;                                                    // /on retourne que ca a reussi
        } else {
            return false;    // /sinon on retourne qu'il existe déja un produit identique meme id
        }
    }

    public User connect(String name, String pwd) throws SQLException    // /
    {
        String          n = "",
                        p = "";
        ArrayList<User> uAll = monDAO.searchUser("");    // / On a retrouve l'utilisateur
ArrayList<User> u=new ArrayList<User>();
for(int i=0;i<uAll.size();i++)
{n=uAll.get(i).name;
p=uAll.get(i).pwd;
    System.out.println(uAll.get(i).toString());
        if(name.equals(n)&&pwd.equals(p)) u.add(uAll.get(i));
    
}
        

        

        if (u.isEmpty()) {
            return null;
        }

        return u.get(0);
    }

    public boolean createProduct(Product p) throws SQLException    // / Ajouter un nouveau produit
    {
        if (monDAO.searchProduct("where  id = '" + p.id + "'").size() == 0)    // /On vérifie si il n'existe pas déja
        {
            p.id = getMaxIdProduct();
            monDAO.addProduct(p);                                              // / On l'ajoute

            return true;                                                       // /on retourne que ca a reussi
        } else {
            return false;    // /sinon on retourne qu'il existe déja un produit identique, meme id
        }
    }

    public User createUser(User u) throws SQLException    // / nouveau user
    {
        if (monDAO.searchUser("where  id =' " + u.id + "'").size() == 0)    // /On vérifie si il n'existe pas déja (meme id)
        {
            u.id = getMaxIdUser();
            monDAO.addUser(u);                                              // / On l'ajoute

            return u;                                                    // /on retourne que ca a reussi
        } else {
            return u;    // /sinon on retourne qu'il existe déja un produit identique, meme id
        }
    }

    public void deleteProduct(int id) {
        Product p = monDAO.searchProduct("WHERE id='" + id + "'").get(0);

        monDAO.deleteProduct(p);
    }

    public void deleteShopingCart(int id) throws SQLException {
        ShoppingCart s = monDAO.searchShopingCart("WHERE id='" + id + "'").get(0);

        System.out.println("you deleted " + s.toString());
        monDAO.deleteShopingCart(s);
    }

    public void deleteShopingCartName(String name) throws SQLException {
        monDAO.deleteShopingCartAll(name);
    }

    public void deleteTransaction(int id) {
        Transaction t = monDAO.searchTransaction("WHERE id='" + id + "'").get(0);

        monDAO.deleteTransaction(t);
    }

    public void deleteUser(int id) throws SQLException {
        User u = monDAO.searchUser("WHERE id='" + id + "'").get(0);

        monDAO.deleteUser(u);
    }

    public ArrayList<ShoppingCart> getallShoppingCart() throws SQLException {
        return monDAO.searchShopingCart("");
    }
    
    

    public ArrayList<Product> loadAllProduct()    // / Retourne tout les trucs en stocks
    {
        return monDAO.searchProduct(" ");
    }

    public ArrayList<Transaction> loadAllTransactions() {
        return monDAO.searchTransaction("");
    }

    public ArrayList<User> loadAllUser() throws SQLException {
        return monDAO.searchUser("");
    }

    public ArrayList<Product> loadProduct(int id)    // / Retoruenr tout les trucs en stocks
    {
        return monDAO.searchProduct("where id ='" + id + "'");
    }

    public Product loadProductId(int id) throws SQLException    // / Retoruenr tout les trucs en stocks
    {
        return monDAO.searchOneProduct("where id ='" + id + "'");
    }

    public ArrayList<ShoppingCart> loadShoppingCart(String name) throws SQLException    // /
    {
        ArrayList<ShoppingCart> s       = monDAO.searchShopingCart("");
        ArrayList<ShoppingCart> monShop = new ArrayList();

        for (int i = 0; i < s.size(); i++) {
            if (s.get(i).nameUser.equals(name)) {
                monShop.add(s.get(i));
            }
        }

        return monShop;    // / On a retrouve le panier mais avant on vérifie si tout est en stock sinon on supprime
    }

    public void payment(User user) throws SQLException    // / Payer le panier donc supprime le panier ,ajoute la transaction à la base de donnée, on supprime le produit acheter des stocks
    {
        ArrayList<ShoppingCart> shopingCart = monDAO.searchShopingCart(" where nameUser = '" + user.name + "'");

        System.out.println(shopingCart.size());

        Product     s             = new Product();
        Transaction t             = new Transaction();
        int         id            = 0,
                    idTransaction = 0;

        for (int i = 0; i < shopingCart.size(); i++) {
            ArrayList<Transaction> transaction = new ArrayList<Transaction>();

            id          = getMaxTransaction();
            t.userId    = user.id;    // /On associe le nom de la personne à son id et on met son id dans la transaction
            t.productId = shopingCart.get(i).productId;    // On recherche l'id du produit acheté et on le met son id dans la transaction
            t.quantity = shopingCart.get(i).number;    // On recherche le nombre de produit achetés de meme catégorie et on met ce nombre dans la transaction
            t.mounth = 12;
            t.year   = 2020;
            t.price  = priceShopingCart(shopingCart.get(i));    // /On veut le prix du panier
            t.id     = id;
            monDAO.addTransaction(t);                           // /On ajoute la transaction a la dataBase
            s = monDAO.searchProduct("where id = '" + shopingCart.get(i).productId + "'").get(0);

//          /On cherche les stock du produit dans le panier pour l'enlever
            s.stocks = s.stocks - shopingCart.get(i).number;
            s.sold   = s.sold + shopingCart.get(i).number;    // /On enleve 1 stock puisqu'on paye
            monDAO.modifyProdcut(s);                          // / On modifie dans la base de données le stock

            // /On add dans la trasaction
           
        }

        monDAO.deleteShopingCartAll(user.name);    // /On supprime le panier puisqu'il est payer
    }

    public double priceShopingCart(ShoppingCart s) {
        double totalPrice = 0;
        int    numberDiscount;
System.out.println(s.toString());
        numberDiscount = monDAO.searchProduct("where id = '" + s.productId + "'").get(0).amountDiscount;    // /On cherche le nombre d'article à acheter pour beneficier du rabais

        if (numberDiscount > s.number)    // /Si on en a pas assez pour avoir le rabais
        {
            totalPrice = totalPrice + monDAO.searchProduct("where id = '" + s.productId + "'").get(0).price * s.number;    // /(on cherche le prix du produit puis on l'ajoute au prix tottal
        } else {
            totalPrice = totalPrice
                         + monDAO.searchProduct("where id = '" + s.productId + "'").get(0).price
                           * (s.number % numberDiscount);    // /On prend l'excedant ( les articles qui n'ont pas de rabais)
            totalPrice = totalPrice
                         + monDAO.searchProduct("where id = '" + s.productId + "'").get(0).discount
                           * (s.number / numberDiscount);    // /On prend le rabais
        }

        return totalPrice;
    }

    public double priceTotalShopingCart(String name) throws SQLException {
        ArrayList<ShoppingCart> shopingCartAll = monDAO.searchShopingCart("");
        ArrayList<ShoppingCart> shopingCart=new ArrayList<ShoppingCart>();
      for(int i=0;i<shopingCartAll.size();i++)
      {
          if(name.equals(shopingCartAll.get(i).nameUser)) shopingCart.add(shopingCartAll.get(i));
      }
        double                  totalPrice  = 0;
        int                     numberDiscount;

        for (int i = 0; i < shopingCart.size(); i++) {
            numberDiscount = monDAO.searchProduct("where id = '" + shopingCart.get(i).productId + "'")
                                   .get(0).amountDiscount;    // /On cherche le nombre d'article à acheter pour beneficier du rabaias

            for (int j = 0; j < shopingCart.get(i).number; j++) {
                if (numberDiscount > shopingCart.get(i).number)    // /Si on en a pas assez pour avoir le rabais
                {
                    totalPrice = totalPrice
                                 + monDAO.searchProduct("where id = '" + shopingCart.get(i).id + "'").get(0).price
                                   * shopingCart.get(i).number;    // /(on cherche le prix du produit puis on l'ajoute au prix tottal
                } else {
                    totalPrice = totalPrice
                                 + monDAO.searchProduct("where id = '" + shopingCart.get(i).productId
                                                        + "'").get(0).price * (shopingCart.get(i).number
                                                                               % numberDiscount);    // /On prend l'excedant ( les articles qui n'ont pas de rabais)
                    totalPrice = totalPrice
                                 + monDAO.searchProduct("where id = '" + shopingCart.get(i).productId
                                                        + "'").get(0).discount * (shopingCart.get(i).number
                                                                                  / numberDiscount);    // /On prend le rabais
                }
            }
        }

        return totalPrice;
    }

    public void removeItemShopingCart(ShoppingCart s) throws SQLException    // / modifier user
    {
        if (monDAO.searchUser("where  id = '" + s.id + "'" + " AND nameUser = '" + s.nameUser + "'").get(0).id == 1)    // /On vérifie si il n'existe pas déja dans le panier
        {
            monDAO.deleteShopingCart(s);    // / On le créer
        } else {
            int numberItem = monDAO.searchUser("where  id = " + s.id + " AND nameUser = '" + s.nameUser + "'")
                                   .get(0).id + 1;    // /Si il existe deja un object avec cette id dans le panier on modifie juste son nombre

            s.id = numberItem;
            monDAO.modifyShopingCart(s);
        }
    }

    public ArrayList<Product> sortPopular(ArrayList<Product> p) {
        Product sortP = null;

        for (int i = 1; i < p.size() - 1; i++) {
            if (p.get(i - 1).sold > p.get(i).sold)    // / Tri à bulles pour trier dans l'odre du plus vendu
            {
                sortP = p.get(i - 1);
                p.set(i - 1, p.get(i));
                p.set(i, sortP);
            }
        }

        return p;    // / renvoie la liste trier dees objets
    }

    public ArrayList<Product> sortType(String type) {
        return monDAO.searchProduct("where  type = '" + type + "'");    // / On retourne que les produits trier "sale" ou "sucre"
    }

    public ArrayList<ShoppingCart> stockShoppingCart(ArrayList<ShoppingCart> s)    // /On vérifie si le produit qui est dans le panier est toujours en stocks sinon on le supprime du panier
    {
        for (int i = 0; i < s.size(); i++) {
            if (0 == monDAO.searchProduct("where id ='" + s.get(i).id + "'").get(0).stocks) {
                monDAO.deleteShopingCart(s.get(i));
            }
        }

        return s;
    }

    public int getMaxIdProduct() throws SQLException {
        int        id     = 0,
                   idp    = 0;
        DAO        newDao = monDAO;
        DataBase   db     = newDao.getDb();
        Connection con    = db.getConnection();
        Statement  stmt   = con.createStatement();
        ResultSet  result = stmt.executeQuery("SELECT * FROM product");

        while (result.next()) {
            idp = result.getInt(1);

            if (id < idp) {
                id = idp;
            }
        }

        if (id == 0) {
            id = 100;
        }

        id = id + 2;

        return id;
    }

    public int getMaxIdUser() throws SQLException {
        int        id     = 0,
                   idu    = 0;
        DAO        newDao = monDAO;
        DataBase   db     = newDao.getDb();
        Connection con    = db.getConnection();
        Statement  stmt   = con.createStatement();
        ResultSet  result = stmt.executeQuery("SELECT * FROM user");

        while (result.next()) {
            idu = result.getInt(4);

            if (id < idu) {
                id = idu;
            }
        }

        if (id == 0) {
            id = 100;
        }

        id = id + 2;

        return id;
    }

    public int getMaxShoppingCart() throws SQLException {
        int        id     = 0,
                   idSc   = 0;
        DAO        newDao = monDAO;
        DataBase   db     = newDao.getDb();
        Connection con    = db.getConnection();
        Statement  stmt   = con.createStatement();
        ResultSet  result = stmt.executeQuery("SELECT * FROM shopingcart");

        while (result.next()) {
            idSc = result.getInt(5);

            if (id < idSc) {
                id = idSc;
            }
        }

        if (id == 0) {
            id = 100;
        }

        id = id + 2;

        return id;
    }

    public int getMaxTransaction() throws SQLException {
        int        id     = 0,
                   idt    = 0;
        DAO        newDao = monDAO;
        DataBase   db     = newDao.getDb();
        Connection con    = db.getConnection();
        Statement  stmt   = con.createStatement();
        ResultSet  result = stmt.executeQuery("SELECT * FROM transaction");

        while (result.next()) {
            idt = result.getInt(7);

            if (id < idt) {
                id = idt;
            }
        }

        if (id == 0) {
            id = 100;
        }

        id = id + 2;

        return id;
    }
    public void addUser(User u) throws SQLException
    {u.id=getMaxIdUser();
        monDAO.addUser(u);
    }
    public void addTransaction(Transaction t) throws SQLException
    {t.id=getMaxTransaction();
        monDAO.addTransaction(t);
    }
    public void addProduct(Product p) throws SQLException
    {p.id=getMaxIdProduct();
        monDAO.addProduct(p);
    }
    public void addShoppingCart(ShoppingCart s) throws SQLException
    {s.id=getMaxShoppingCart();
        monDAO.addShopingCart(s);
    }
    public Transaction searchT(int id)
    {
      ArrayList<Transaction> t=monDAO.getTransaction();
      Transaction t1=new Transaction();
      for(int i=0;i<t.size();i++)
      {
          if(id==t.get(i).id) 
          t1=t.get(i);
      }
      return t1;
    }
     
    public Product searchP(String name)
    {ArrayList<Product> p=monDAO.getProduct();
    Product p1=new Product();
    for(int i=0;i<p.size();i++)
    {
        if(name.equals(p.get(i).name)) p1=p.get(i);
    }
    return p1;
        
    }
    public User searchU(String name)
    {ArrayList<User> u=monDAO.getUser();
    User u1=new User();
    for(int i=0;i<u.size();i++)
    {
        if(name.equals(u.get(i).name)) u1=u.get(i);
    }
        return u1;
    }
    public ShoppingCart searchS(String name)
    {ArrayList<ShoppingCart> s=monDAO.getShoppingCart();
    ShoppingCart s1=new ShoppingCart();
    for(int i=0;i<s.size();i++)
    {
        if(name.equals(s.get(i).nameProd)) s1=s.get(i);
    }
    return s1;
        
    }
    public void deleteT(Transaction t)
    {
        monDAO.deleteTransaction(t);
    }
    public void deleteU(User u)
    {
        monDAO.deleteUser(u);
    }
    public void deleteP(Product p)
    {
        monDAO.deleteProduct(p);
    }
}


//~ Formatted by Jindent --- http://www.jindent.com
