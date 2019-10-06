import java.util.ArrayList;
import java.util.Collection;

public class Main {

    public static void main(String[] args) {
        System.out.println("Customer-Account excercise");
        Customer a = new Customer("ToTr",1134526);
        Account a1 = new Account(001);
        Account a2 = new Account(002,10.2);
        //adding Accounts
        a.addAccount(a1);
        a.addAccount(a2);
        ArrayList<Account> ac = a.getAccounts();
        //account 1 testing
        System.out.println(ac.get(1).getAccountNumber());
        System.out.println(ac.get(1).getBalance());
        //account 0 testing
        System.out.println(ac.get(0).getAccountNumber());
        System.out.println(ac.get(0).getBalance());
        ac.get(0).posting(-10);
        System.out.println(ac.get(0).getBalance());

    }
}
