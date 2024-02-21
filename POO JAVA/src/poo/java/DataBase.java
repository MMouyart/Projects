package poo.java;

import java.awt.FlowLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

import java.util.logging.Level;
import java.util.logging.Logger;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JTextField;

public class DataBase {
    private Connection connexionDataBase;
    private Statement  stmt;
    private boolean    isDone;

    public DataBase() throws ClassNotFoundException {
        JFrame     frame;
        JLabel     user;
        JTextField userF;
        JLabel     password;
        JTextField passwordF;
        JLabel     pName;
        JTextField pNameField;
        JButton    Done;
        String     projetS   = "";
        String     userS     = "";
        String     passwordS = "";
        int        nbmaj     = 0;
        ResultSet  resultat  = null;

        try {
            frame = new JFrame("enter your databse private datas");
            frame.setSize(1000, 1000);
            frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
            isDone     = false;
            Done       = new JButton("click here to end the procedure");
            user       = new JLabel("enter the user name for your database access");
            userF      = new JTextField("root");
            password   = new JLabel("enter your password ");
            passwordF  = new JTextField("");
            pName      = new JLabel("enter your project name to create the database in");
            pNameField = new JTextField("");

            FlowLayout flow = new FlowLayout();

            frame.setLayout(flow);
            frame.add(Done);
            frame.add(user);
            frame.add(userF);
            frame.add(password);
            frame.add(passwordF);
            frame.add(pName);
            frame.add(pNameField);
            Done.addActionListener(new DoneListener());

            while (isDone == false) {
                frame.setVisible(true);
                userS     = userF.getText();
                passwordS = passwordF.getText();
                projetS   = pNameField.getText();
            }

            if (userS.equals("")) {
                userS = "root";
            }

            if (passwordS.equals("   ")) {
                passwordS = "";
            }

            if (passwordS.equals("   ")) {
                passwordS = "";
            }

            frame.setVisible(false);
            Class.forName("com.mysql.jdbc.Driver");
            connexionDataBase = DriverManager.getConnection("jdbc:mysql://localhost:3306/" + projetS, userS, passwordS);
            stmt              = connexionDataBase.createStatement();

            if (userS.equals("root")) {
                connexionDataBase = DriverManager.getConnection("jdbc:mysql://localhost:3306/" + projetS,
                                                                userS,
                                                                passwordS);
            }

            stmt  = connexionDataBase.createStatement();
            nbmaj = stmt.executeUpdate(
                "CREATE TABLE IF NOT EXISTS `product` (`id` int(11) NOT NULL,`sold` int(11) DEFAULT NULL,`stocks` int(11) DEFAULT NULL,`amountDiscount` int(11) DEFAULT NULL,`name` varchar(50) DEFAULT NULL,`type` varchar(50) DEFAULT NULL,`price` double DEFAULT NULL,`discount` double DEFAULT NULL,PRIMARY KEY (`id`)) ENGINE=InnoDB DEFAULT CHARSET=latin1;");
            nbmaj = stmt.executeUpdate(
                "CREATE TABLE IF NOT EXISTS `user` (`passWord` varchar(50) NOT NULL,`userName` varchar(50) NOT NULL,`access` tinyint(1) NOT NULL,`id` int(11) NOT NULL,PRIMARY KEY (`id`)) ENGINE=InnoDB DEFAULT CHARSET=latin1;");
            nbmaj = stmt.executeUpdate(
                "CREATE TABLE IF NOT EXISTS `shopingcart` (`nameProd` varchar(50) NOT NULL,`productId` int(11) NOT NULL, `nameUser` varchar(50) NOT NULL,`number` int(11) NOT NULL,`id` int(11) NOT NULL,PRIMARY KEY (`id`)) ENGINE=InnoDB DEFAULT CHARSET=latin1;");
            nbmaj = stmt.executeUpdate(
                "CREATE TABLE IF NOT EXISTS `transaction` (`userId` int(11) NOT NULL,`productId` int(11) NOT NULL,`quantity` int(11) NOT NULL,`month` int(11) NOT NULL,`year` int(11) NOT NULL,`price` double NOT NULL,`id` int(11) NOT NULL, PRIMARY KEY (`id`)) ENGINE=InnoDB DEFAULT CHARSET=latin1;");

            try {
                nbmaj = stmt.executeUpdate(
                    "INSERT INTO `user` (`passWord`, `userName`, `access`, `id`) VALUES ('myname', 'matthieu', 1, 100),('theo', 'theophile', 1, 101),('olive & tom', 'thomas', 1, 102);");
            } catch (Exception e) {
                System.out.println(e.getMessage());
            }

            try {
                nbmaj = stmt.executeUpdate(
                    "INSERT INTO `product` (`id`, `sold`, `stocks`, `amountDiscount`, `name`, `type`, `price`, `discount`) VALUES(100, 0, 500, 10, 'Joystick Switch', 'produit', 4.95, 45),(101, 0, 500, 10, 'USb controller Game pad', 'produit', 5.5, 50),(102, 0, 5000, 1, 'Bottle o_Bubbles', 'produit', 0.99, 0.99),(103, 0, 50, 1, 'Nintendo Wii System', 'produit', 399.99, 399.99),(104, 0, 500, 1, 'Mario Wii', 'produit', 65, 65),(105, 0, 50, 1, 'Small X-box', 'produit', 65, 65),(106, 0, 5000, 1, 'E-pen', 'produit', 4.5, 4.5),(107, 0, 5000, 1, 'Rubrik Cube', 'produit', 5, 5),(108, 0, 5000, 10, 'Java is amazing! Button', 'produit', 1.5, 11),(109, 0, 5000, 20, 'Java Java Java! Sticker', 'produit', 0.99, 8.99);");
            } catch (Exception e) {
                System.out.println(e.getMessage());
            }
        } catch (SQLException e) {
            System.out.println("Error no Database !");
        }
    }

    public ResultSet query(String query) {
        try {
            return stmt.executeQuery(query);
        } catch (SQLException ex) {
            Logger.getLogger(DataBase.class.getName()).log(Level.SEVERE, null, ex);

            return null;
        }
    }

    public void queryUpdate(String query) {
        try {
            stmt.executeUpdate(query);
        } catch (SQLException ex) {
            Logger.getLogger(DataBase.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    public Connection getConnection() {
        return connexionDataBase;
    }

    public class DoneListener implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent ae) {    // fonction permettant d'écouter le bouton de fin de procédure
            isDone = true;
        }
    }
    
}


//~ Formatted by Jindent --- http://www.jindent.com
