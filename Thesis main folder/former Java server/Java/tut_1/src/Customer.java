import java.util.ArrayList;

public class Customer {
    private String name;
    private int customerID;
    private ArrayList<Account> accounts;
    public Customer(int customerID){
        this.customerID=customerID;
        this.name="";
        this.accounts = new ArrayList<Account>();
    }
    public Customer(String name,int customerID) {
        this.name = name;
        this.customerID = customerID;
        this.accounts = new ArrayList<Account>();
    }

    public String getName(){
        return name;
    }
    public void setName(String name){
        this.name=name;
    }

    public int getCustomerID() {
        return customerID;
    }
    public void addAccount(Account account){
        accounts.add(account);

    }
    public ArrayList<Account> getAccounts(){
        return accounts;
    }
}
