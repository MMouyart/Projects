/// 4 attributs clients
/// Peut etre tirer les products pour pas avoir que 6 produits genre sucrée et sacré du coup rajouter un attribut
///Faire une rechers sur les products
///Faire par les + vendues
///Faire recherche général
///Le panier remplir
///Les ventes mettre les ventes pour les produits
///SI il veut faire des achats mettre 
/// Pour product rajouter productNum la quantité en stock, la quantité vendu, 
    ///la quantité pour laquelle on a la reduc et le montant de la reduc
/// ShopingCart



package poo.java;

import poo.java.view.View;
import java.sql.*;
import java.util.ArrayList;
import java.util.Scanner;
import javax.swing.*;
import poo.java.data.Product;


public class POOJAVA 
{

    public static void main(String[] args) throws ClassNotFoundException, SQLException, InterruptedException 
    {
        Controller controler = new Controller();
        View view=new View(controler);
        view.main(args);
        //View view=new View(controler);
        //view.viewLoginMenu();
        //view.viewMainMenu(controler.getProduct());
        //view.searchShopingCart();
        /*controler.start();
        controler.connect("matthieu", "myname");
       // controler.addCart();
        controler.confirmBuy();
        //controler.addTransaction();
        //controler.connect("myname", "matthieu");
        //controler.deleteUser();*/
   
    }
    
}
