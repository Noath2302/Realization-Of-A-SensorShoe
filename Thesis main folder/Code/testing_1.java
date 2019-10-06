import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Scanner;
import java.util.concurrent.Executors;
public class testing_1 {

    public static void main(String[] args) throws Exception {
        System.out.println("The Smartshoe server is running...");
        var pool = Executors.newFixedThreadPool(20);
        try (var listener = new ServerSocket(22222)) {
            while (true) {
                pool.execute(new Smartshoe(listener.accept()));
            }
        }
    }
    private static class Smartshoe implements Runnable {
        private Socket socket;
		public FileWriter fileWriter;
		public BufferedWriter bufferedWriter;
		private String path;
        public Smartshoe(Socket socket){
            this.socket = socket;			
            System.out.println("Connected: " + socket);
        }

        public void run() {
            try {
				//===== making the write-file app =====
				path = "tes.txt";
				
                var in = new Scanner(socket.getInputStream());
                //var out = new PrintWriter(socket.getOutputStream(), true);
                while (in.hasNextLine()) {
					try{
						fileWriter = new FileWriter(path,true);
					}
					catch (IOException e2){
						System.out.println("====== cannot open file ======");
					}
					bufferedWriter = new BufferedWriter(fileWriter);
					String a = in.nextLine();
                    System.out.println(a);
					bufferedWriter.write(a);
					bufferedWriter.write("\n");
					bufferedWriter.close();
                }
				
            } catch (Exception e) {
                System.out.println("Error:" + socket);
            } finally {
                try { socket.close(); } catch (IOException e) {}
                System.out.println("Closed: " + socket);
            }
        }
    }
}