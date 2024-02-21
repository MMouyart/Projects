package poo.java;

import java.sql.ResultSet;
import java.sql.*;


public class SearchDataBase 
{
    private DataBase myBase;
    
    
    
    public SearchDataBase(DataBase myBase)
    {
        this.myBase = myBase;
        
    }
    
    public ResultSet search(String criteria, String table)
    {
          return myBase.query("Select * From " + table + " " + criteria  + " ;");
    }
    
}
