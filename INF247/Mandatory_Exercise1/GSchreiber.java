import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.util.ArrayList;


public class GSchreiber {
	
	static int cipherText [] = new int [1273];
	static String plainText = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	static final int [][] codeTable = { 
		{1,1,0,0,0}, {1,0,0,1,1}, {0,1,1,1,0}, {1,0,0,1,0}, {1,0,0,0,0}, {1,0,1,1,0}, {0,1,0,1,1},{0,0,1,0,1}, {0,1,1,0,0}, {1,1,0,1,0 }, 
		{1,1,1,1,0}, {0,1,0,0,1}, {0,0,1,1,1}, {0,0,1,1,0}, {0,0,0,1,1}, {0,1,1,0,1}, {1,1,1,0,1}, {0,1,0,1,0}, {1,0,1,0,0}, {0,0,0,0,1}, 
		{1,1,1,0,0}, {0,1,1,1,1}, {1,1,0,0,1}, {1,0,1,1,1}, {1,0,1,0,1}, {1,0,0,0,1}, {0,0,0,1,0}, {0,1,0,0,0}, {1,1,1,1,1},{1,1,0,1,1}, 
		{0,0,1,0,0}, {0,0,0,0,0}
		};
	static Integer coincidences[][];
	
	public static void main(String[] args) throws Exception {
		
		File f = new File("Ciphertext.txt");
		BufferedReader br = new BufferedReader(new FileReader(f));
		
		int index = 0;
		String str = br.readLine();
		while(str != null) {
			
			for (int i = 0; i < str.length(); i++) {
				Character c = str.charAt(i);
				if(Character.isDigit(c)) {
					Character c2 = str.charAt(i+1);
					if(Character.isDigit(c2)) {
						
						String s = c.toString().concat(c2.toString());
						
						cipherText[index++] = Integer.parseInt(s);
						i++;
					}else {
						cipherText[index++] = Integer.parseInt(c.toString());
					}
					
					
				}
			}
			str = br.readLine();
		}
		
		index = 0;
		coincidences = new Integer[cipherText.length][5];
		for (int i = 0; i < cipherText.length; i++) {
			int c = cipherText[i];
			
			if(c == 29 || c == 32) {
				int [] group = codeTable[i%26];
				int [] group2 = codeTable[c-1];
				for (int k = 0; k < group.length; k++) {
					
					int l = group[k] ^ group2[k];
					
					coincidences[i][k] = l;
				}
				
			}

		}
		
		int wheelPos [] = new int[10];

		wheelPos[0]= findPermPos(47);
		wheelPos[1] = findPermPos(53);
		wheelPos[2] = findPermPos(59);
		wheelPos[3] = findPermPos(61);
		wheelPos[4] = findPermPos(64);
		int wheel65;
		int wheel67;
		int wheel69;
		int wheel71;
		int wheel73;
		
		
		
	}
	
	static int findPermPos(int wheelSize ) {
		System.out.println("Finding permutation position for wheel: " + wheelSize);
		ArrayList<ArrayList<Integer[]>> wheel = new ArrayList<ArrayList<Integer[]>>();
		for (int i = 0; i < wheelSize; i++) {
			wheel.add(new ArrayList<Integer[]>());
		}
		
		for (int i = 0; i < coincidences.length; i ++) {
			Integer[] bits = coincidences[i];
			if(bits[0] == null) continue;
			ArrayList<Integer []> arr = wheel.get(i%47);
			arr.add(bits);
			
		}
		
		for (int i = 0; i < wheel.size(); i++) {
			System.out.print("Position " + (i+1) + ":\t");
			ArrayList<Integer[]> arr = wheel.get(i);
			
			if(arr.size() == 0) {System.out.println(); continue; }
			for (int j = 0; j < arr.size(); j++) {
				Integer[] bits = arr.get(j);
				
				for (int k = 0; k < bits.length; k++) {
					if (k == 0) System.out.print("{");
					System.out.print( bits[k] + " ");
				}
				System.out.print("}\n\t\t");
			}
			System.out.println();
		}
		
		return 0;
	}
}
