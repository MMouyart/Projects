package poo.java.view;

import java.awt.*;
import java.awt.event.*;
import java.sql.SQLException;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.*;
import poo.java.Controller;




public class Launcher extends JFrame implements ActionListener
{
    private JButton bouton;
    private JButton bouton2;

    private JPasswordField pwdSField;
    private JTextField nameField;
    
    private String pwd;
    private String name;
    private Controller c;
    private boolean done;
    

    
    //private User u = new User();
    //Controller c = new Controller();
    
    public Launcher(Controller c)
    {
            super();
            build();//On initialise notre fenêtre
            this.c=c;
            done=false;
    }

    
    private void build()
    {
        setTitle("Cyber Shop 2077");
        
        setSize(600,350); 
        setLocationRelativeTo(null); 
        
        setResizable(false); 
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setContentPane(buildContentPane());
    }

    public boolean getDone()
            {
                return done;
            }
    private JPanel buildContentPane()
    {
        JPanel panel = new JPanel();
        panel.setLayout(null);
        
        

        bouton = new JButton("Log in");
        bouton.addActionListener(this);
 
        bouton2 = new JButton("Sign up");
        bouton2.addActionListener(this);
        
        pwdSField = new JPasswordField();
        pwdSField.addActionListener(this);

        
        nameField = new JTextField();
        nameField.addActionListener(this);
        
        bouton.setBounds(170, 200, 100, 40);
        bouton2.setBounds(320, 200, 100, 40);
        nameField.setBounds(200,40, 190, 30);
        pwdSField.setBounds(200, 110, 190, 30);
        
        
        panel.add(nameField);
        panel.add(pwdSField);
        panel.add(bouton);
        panel.add(bouton2);
        

        return panel;
    }


    
    public void actionPerformed(ActionEvent e) 
    {
            try { Object source = e.getSource();

            if(source == bouton) ///Si on se connecte
            {
                name = nameField.getText();
                pwd = pwdSField.getText();
               
                    c.connect(name, pwd);
                JOptionPane.showInputDialog("Connection done");
                
            } 
            
            else if(source == bouton2) ///Si on s'enregistre
            {
                name = nameField.getText();
                pwd = pwdSField.getText();
                c.addUser(name, pwd);
                JOptionPane.showInputDialog("   Registration completed ");
                
                
            }
            
           
            setVisible(false);
            done=true;
            
          /*  
            if(u == null) ///Si pas de de correspondance
                afficher connexion impossible;
                        
                        
            else ///Si correspondance on femrme la fenetreet on charge le magasin si client ou controle si employer
            {
               dispose();
               
                if(u.access == 1)
                {
                    employeeView(u , c.getProduct(), c.getShoppingCart(), c.getTransactio());
                }   
                    
            
                else
                {
                    clientView(u , c.getProduct(), c.getShoppingCart());
                } 
                    
            }
            
            
          */
     } catch (SQLException ex) {
                    Logger.getLogger(Launcher.class.getName()).log(Level.SEVERE, null, ex);
                }      
            
    }

   

    
    
}