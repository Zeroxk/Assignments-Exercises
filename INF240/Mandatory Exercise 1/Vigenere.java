public class Vigenere {


	public final static String alphabet = "abcdefghijklmnopqrstuvwxyz";

	/*public static String cipherText = "ocwyikoooniwugpmxwktzdwgtssayjzwyemdlbnqaaavsuwdvbrflauplo" +
			"oubfgqhgcscmgzlatoedcsdeidpbhtmuovpiekifpimfnoamvlpqfxejsm" +
			"xmpgkccaykwfzpyuavtelwhrhmwkbbvgtguvtefjlodfefkvpxsgrsorvg" +
			"tajbsauhzrzalkwuowhgedefnswmrciwcpaaavogpdnfpktdbalsisurln" +
			"psjyeatcuceesohhdarkhwotikbroqrdfmzghgucebvgwcdqxgpbgqwlpb" +
			"daylooqdmuhbdqgmyweuikmvswrvnqlszdmgaoqsakmlupsqforvtwvdfc" +
			"jzvgsoaoqsacjkbrsevbel";*/
            //public static String cipherText = "SSFZAFLDVWDTQDVFQETYLSEBSQFOFTZSFHKTOYPCJEKNSZUVWBSREALDVFQEGXSWSHLLCLQSXKHZQGLGSBFYGXSPAXWCRSXINOFSPIDVAWDFGEFPAXWCBOKDWKBSUGZDPCJEK";

	public static String cipherText = "SSF ZAFL DVWDTQDVFQE TYLSE BSQ FOF TZSFHK TOY PCJEK NSZUVWBSR EAL DVFQE GX SWSHL LCLQS XKH ZQG LGSBFY GXS PAXWC RSXINOFSP IDV AWD FGEF PAXWC BOK DWKB SUGZD PCJEK";
	//public static String cipherText = "vptnvffuntshtarptymjwzirappljmhhqvsubwlzzygvtyitarptyiougxiuydtgzhhvvmumshwkzgstfmekvmpkswdgbilvjljmglmjfqwioiivknulvvfemioiemojtywdsajtwmtcgluysdsumfbieugmvalvxkjduetukatymvkqzhvqvgvptytjwwldyeevquhlulwpkt";
	public final static double alphFreq [] = {0.082,0.015,0.028,0.043,0.127,0.022,0.020,0.061,0.070,0.002
		,0.008,0.040,0.024,0.067,0.075,0.019,0.001,0.060,0.063,0.091,0.028,0.010,0.023,0.001,0.020,0.001};

	public static void main(String[] args) {

		cipherText = cipherText.toLowerCase();
		//Start by finding keylength
		int keylength = findKeyLength(cipherText); 
		System.out.println("Keylength is: " + keylength);

		if(keylength > -1) {
			//DecryptVector is an array containing the indices of the keyword
			int decryptVector [] = new int[keylength];
			for(int i = 0; i<keylength; i++) {
				//Find the keyword
				decryptVector[i] = findKey(i,keylength);
			}
			
			System.out.print("Key is: ");
			for (int i = 0; i < decryptVector.length; i++) {
				//System.out.println( 25-decryptVector[i]);
				System.out.print(alphabet.charAt( (26-decryptVector[i]) % 25 ));
			}
			System.out.println();

			//After we've found the keyword we decipher the ciphertext, if the result is sensible we are correct.
			decipher(decryptVector, keylength);
		}



	}


	/**
	 * Deciphers the ciphertext to plaintext
	 * 
	 * @param decryptVector An array containing the alphabet indices of the keyword
	 * @param keylength The keylength
	 */
	private static void decipher(int[] decryptVector, int keylength) {
		char [] plainText = cipherText.toCharArray();

		for (int i = 0; i < decryptVector.length; i++) {
			for (int j = i; j < plainText.length; j += keylength) {
				//Shifts cipherchar back to plaintextchar according to key
				if(Character.isLetter(plainText[j])) {
					plainText[j] = alphabet.charAt( (alphabet.indexOf(plainText[j]) + decryptVector[i]) % 26);
				}
			}
		}

		//Print plaintext
		for (int i = 0; i < plainText.length; i++) {
			System.out.print(plainText[i]);
		}
	}


	/**
	 * Finds key by finding the frequency of characters in (start + keylength) positions in the ciphertext, we name this vector W
	 * We then compute the dot product of W*Aj where Aj is the alphFreq vector shifted by j, where 0<=j<=25
	 * The key is the j where W*Aj is the highest
	 * 
	 * @param start From where in the ciphertext we start
	 * @param keylength Length of the key 
	 * @return index The j where W*Aj is the highest
	 */
	private static int findKey(int start,int keylength) {

		int count = 0;
		//Array that counts how many times each letter occurs in the (start + keylength) positions in the ciphertext
		double [] occurences = new double[alphabet.length()];

		for (int i = start; i < cipherText.length(); i += keylength) {
			for (int j = 0; j < alphabet.length(); j++) {
				if(cipherText.charAt(i) == alphabet.charAt(j)) {
					occurences[j]++;
				}
			}
			count++;
		}
		System.out.println(count);
		//Divides each letter by the shifted text length to get frequency probability
		for (int i = 0; i < occurences.length; i++) {
			occurences[i] = occurences[i]/count;
		}

		//Keep track of the greatest dot product and its index
		double greatest = 0;
		int index = 0;
		for(int i = 0; i<alphabet.length(); i++ ) {
			double sum = 0;
			for (int j = 0; j < occurences.length; j++) {
				//Computing the dot product piece by piece, (j+i)%26 ensures we get the correctly shifted value
				sum += occurences[j]*alphFreq[(j+i)%26];
			}
			if(greatest < sum) {
				greatest = sum;
				index = i;
			}
			System.out.println("Dot product for " + i + ":\t" + sum);
		}

		return index;


	}


	/**
	 * Find key length of a given ciphertext, only tries up to a possible length of 10
	 * We count the number of coincidences. A coincidence is where the character in the 
	 * shifted and ciphertext at position i is the same.
	 * The key length with the highest number of coincidences is most likely the correct keylength
	 * 
	 * @param text The ciphertext
	 * @return keylength The keylength
	 */
	private static int findKeyLength(String text) {

		int tries = text.length();
		int greatest = 0;
		int keylength = -1;
		String shiftText = text;
		System.out.println("# of coincidences");
		for(int i = 0; i < tries; i++) {

			//Shifts text by one space to the right each iteration
			shiftText = " ".concat(shiftText);
			int occurence = 0;

			for (int j = 0; j < text.length(); j++) {
				//Check if we have a coincidence
				if(Character.isLetter(text.charAt(j)) && Character.isLetter(shiftText.charAt(j))) {
					if(text.charAt(j) == shiftText.charAt(j)) {
						occurence++;
					}
				}
				
			}

			if(occurence > greatest) {
				greatest = occurence;
				keylength = i;
			}

			//Print for easy overview
			System.out.println((i+1) + ": " + occurence);

		}

		return keylength+1;
	}

}
