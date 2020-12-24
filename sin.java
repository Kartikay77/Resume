import java.net.InetAddress;
import java.net.UnknownHostException;

public class NewClass1 {
   public static void main(String[] args) {
      InetAddress ip;
      String hostname;
      try {
         ip = InetAddress.getLocalHost();
         hostname = ip.getHostName();
         System.out.println("Your current IP address : " + ip);
         System.out.println("Your current Hostname : " + hostname);
      } catch (UnknownHostException e) {
         e.printStackTrace();
      }
   }
}
