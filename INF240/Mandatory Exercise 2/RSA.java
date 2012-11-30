import java.math.BigInteger;
import java.util.ArrayList;


public class RSA {

	public static void main(String[] args) {

		ArrayList<BigInteger> crtA = new ArrayList<BigInteger>();
		ArrayList<BigInteger> crtN = new ArrayList<BigInteger>();

		crtA.add(new BigInteger("359335245251"));
		crtA.add(new BigInteger("10436363975495"));
		crtA.add(new BigInteger("5135984059593"));

		crtN.add(new BigInteger("2469247531693"));
		crtN.add(new BigInteger("11111502225583"));
		crtN.add(new BigInteger("44444222221411"));

		BigInteger mCube = CRT(crtA,crtN);
		System.out.println("M^3 = " + mCube.toString());
		
		//Computed cube root of M^3 manually on calculator
		BigInteger m = new BigInteger("805121215");
		System.out.println("M = " + m.toString());
		
		//Translate the message to text
		System.out.println("Decrypted message: " + convertToText(m));

	}

	/**
	 * Using algorithm for solving x on general form of CRT
	 * Page 108 problem 24 in our textbook
	 * Small modification, let zi = (n1*n2...*nk)/ni
	 * 
	 * @param crtA An array containing a1,a2...ak
	 * @param crtN An array containing n1,n2...nk
	 * @return an integer x which is the unique solution
	 */

	public static BigInteger CRT(ArrayList<BigInteger> crtA, ArrayList<BigInteger> crtN) {
		
		ArrayList<BigInteger> yList = new ArrayList<BigInteger>();

		BigInteger prodN = BigInteger.ONE;
		for(BigInteger n : crtN) {
			prodN = prodN.multiply(n);
		}
		System.out.println("The product of n1n2..nk is: " + prodN.toString());
		
		//Compute multiplicative inverse of ni
		for (int i = 0; i < crtN.size(); i++) {
			BigInteger z = prodN.divide(crtN.get(i));
			BigInteger y = z.modInverse(crtN.get(i));
			System.out.println("z" + (i+1) + " for n" + (i+1) + " : " + z.toString());
			System.out.println("y" + (i+1) + " for n" + (i+1) + " : " + y.toString());
			System.out.println();
			yList.add(y);
		}
		
		BigInteger x = BigInteger.ZERO;
		//Multiply a,y,z and add to x
		for(int i=0; i<crtA.size(); i++) {

			BigInteger a = crtA.get(i);
			BigInteger y = yList.get(i);
			BigInteger z = prodN.divide(crtN.get(i));

			x = x.add(a.multiply(y).multiply(z));

		}

		//X is a unique solution because every other solution is congruent to x mod (prodM)
		return x.mod(prodN);
	}

	public static String convertToText(BigInteger m) {
		String alphabet = "abcdefghijklmnopqrstuvwxyz";
		String message = "0".concat(m.toString());
		String decrypted = "";
		
		for (int i = 0; i < message.length()-1; i=i+2) {
			
			int position = Integer.parseInt(message.substring(i, i+2));
			decrypted += alphabet.charAt(position-1);
			
		}
		
		return decrypted;
	}

}