public class Account {
    private int accountNumber;
    private double balance;
    //Constructor
    public Account(int accountNumber){
        this.accountNumber=accountNumber;
        this.balance=0;
    }
    public Account(int accountNumber,double balance){
        this.balance=balance;
        this.accountNumber=accountNumber;
    }

    public int getAccountNumber(){
        return accountNumber;

    }
    public void posting(double post){
        balance+=post;
    }
    public double getBalance() {
        return balance;
    }
}
