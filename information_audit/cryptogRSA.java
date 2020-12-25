package crypto; 
import java.io.File; 
import java.io.FileInputStream;
import java.io.FileOutputStream; 
import java.security.Key; 
import javax.crypto.Cipher;
import javax.crypto.spec.SecretKeySpec; 
public class cryptogRSA { 
	private static long
	startTime = System.currentTimeMillis(); 
	static void fileProcessor(int cipherMode ,String key,File inputFile,File outputFile)
	{ 
		try {
				Key secretKey = new SecretKeySpec(key.getBytes(),"RSA");
				Cipher cipher = Cipher.getInstance("RSA"); 
				cipher.init(cipherMode,secretKey);
				FileInputStream inputStream = new FileInputStream(inputFile);
				byte[]
				inputBytes = new byte[(int) inputFile.length()]; 
				inputStream.read(inputBytes);
				byte[] outputBytes = cipher.doFinal(inputBytes);
				FileOutputStream outputStream = new FileOutputStream(outputFile);
				outputStream.write(outputBytes);
				inputStream.close();
				outputStream.close();
		} catch (Exception e)
		{ 
			e.printStackTrace();
		}
	}
public static void main(String[] args) {
	String key = "This is a secret";
	File inputFile = new File("C:\\Users\\Dell\\Desktop\\slonline compiler code.txt");
	File encryptedFile = new File("text.encrypted");
	File decryptedFile = new File("decrypted-text.txt");
	try { 
			cryptog.fileProcessor(Cipher.ENCRYPT_MODE,key,inputFile,encryptedFile); 
			cryptog.fileProcessor(Cipher.DECRYPT_MODE,key,encryptedFile,decryptedFile);
			System.out.println("Success");
		} catch (Exception ex)
			{
				System.out.println(ex.getMessage());
				ex.printStackTrace();
			}
	long endTime = System.currentTimeMillis();
	System.out.println("It took " + (endTime - startTime) + " milliseconds");
}
}
