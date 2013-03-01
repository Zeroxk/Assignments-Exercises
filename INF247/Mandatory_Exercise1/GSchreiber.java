import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.util.ArrayList;
import java.util.Arrays;


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

//		wheelPos[0] = findPermPos(47);
//		wheelPos[1] = findPermPos(53);
//		wheelPos[2] = findPermPos(59);
//		wheelPos[3] = findPermPos(61);
//		wheelPos[4] = findPermPos(64);
//		wheelPos[5] = findPermPos(65);
//		wheelPos[6] = findPermPos(67);
//		wheelPos[7] = findPermPos(69);
//		wheelPos[8] = findPermPos(71);
//		wheelPos[9] = findPermPos(73);
		
		ArrayList<Integer[]> controlBitPermutations = genAllPermutes(5);
//		for (int i = 0; i < controlBitPermutations.size(); i++) {
//			System.out.print("{ ");
//			Integer [] tmp = controlBitPermutations.get(i);
//			for (int j = 0; j < tmp.length; j++) {
//				System.out.print(tmp[j] + " ");
//			}
//			System.out.print("}\n");
//		}

		Integer [] tmp = {1,1,1,1,0};
		Integer [] tmp2 = {0,0,0,0,1};
		ArrayList<Integer[]> shifts = genAllShifts(tmp2, 1);

		for(Integer[] a : shifts)  {
			printArray(a);
		}
		
//		for (int i = 0; i < controlBitPermutations.size(); i++) {
//			boolean found = findControlbits(tmp, tmp2, controlBitPermutations.get(i));
//			if(found) printArray(controlBitPermutations.get(i));
//		}
		
		

	}
	
	private static ArrayList<Integer[]>	genAllShifts (Integer[] bits, int weight) {
		ArrayList<Integer[]> allShifts = new ArrayList<Integer[]>();
		allShifts.add(bits);
		int elem = weight == 1 ? 1 : 0;
		
		for (int i = 0; i < bits.length; i++) {
			Integer[] tmp = Arrays.copyOf(bits, bits.length);
			int indexOfSing = -1;
			for (int k = 0; k < tmp.length; k++) {
				if(tmp[k] == elem) {
					indexOfSing = k;
					break;
				}
			}
			swap(tmp, indexOfSing, i);
			allShifts.add(tmp);
		}
		allShifts.remove(allShifts.size()-1);
		
		return allShifts;
	}
	
	private static boolean findControlbits(Integer[] input, Integer[] output, Integer[] controlBitPerms) {
		
		Integer [] tmp = Arrays.copyOf(input, input.length);
		controlBitSwap(tmp, controlBitPerms);
		for (int i = 0; i < output.length; i++) {
			if(tmp[i] != output[i]) {
				return false;
			}
		}
		return true;
		
	}
	
	private static void printArray(Integer[] arr) {
		System.out.print("{ ");
		for (int i = 0; i < arr.length; i++) {
			System.out.print(arr[i] + " ");
		}
		System.out.print("}\n");
	}

	private static ArrayList<Integer[]> genAllPermutes(int bitlength) {
		ArrayList<Integer[]> allPerms = new ArrayList<Integer[]>();

		Integer start [] = new Integer[bitlength];
		for (int i = 0; i < start.length; i++) {
			start[i] = 0;
		}
		allPerms.add(start);
		
		int size = (int) Math.pow(2, bitlength);
		for (int i = 0; i < size; i++) {
			Integer [] perm = Arrays.copyOf(allPerms.get(i), bitlength); 
			for (int j = perm.length-1; j >= 0; j--) {
				if(perm[j] == 0) {
					perm[j] = 1;
					for (int j2 = j+1; j2 < perm.length; j2++) {
						perm[j2] = 0;
					}
					break;
				}
			}
			allPerms.add(perm);
		}
		allPerms.remove(size-1);


		return allPerms;


	}

	private static void controlBitSwap (Integer[] group, Integer [] permutator) {

		if (permutator[0]== 0) swap(group, 0, 4);
		if (permutator[1] == 0) swap(group, 3,4);
		if (permutator[2] == 0) swap(group, 2, 3);
		if (permutator[3] == 0) swap(group, 1, 2);
		if (permutator[4] == 0) swap(group, 0, 1);


	}

	private static void swap(Integer[] arr, int i, int j) {
		int tmp = arr[i];
		arr[i] = arr[j];
		arr[j] = tmp;

	}

	private static int findPermPos(int wheelSize ) {
		System.out.println("Finding permutation position for wheel: " + wheelSize);
		ArrayList<ArrayList<Integer[]>> wheel = new ArrayList<ArrayList<Integer[]>>();
		for (int i = 0; i < wheelSize; i++) {
			wheel.add(new ArrayList<Integer[]>());
		}

		for (int i = 0; i < coincidences.length; i ++) {
			Integer[] bits = coincidences[i];
			if(bits[0] == null) continue;
			ArrayList<Integer []> arr = wheel.get(i%wheelSize);
			arr.add(bits);

		}

		for (int i = 0; i < wheel.size(); i++) {
			System.out.print("Position " + (i+1) + ":\t");
			ArrayList<Integer[]> arr = wheel.get(i);

			if(arr.size() == 0) {System.out.println(); continue; }
			for (int j = 0; j < arr.size(); j++) {
				Integer[] bits = arr.get(j);

				System.out.print("{");
				for (int k = 0; k < bits.length; k++) {
					System.out.print( bits[k] + " ");
				}
				System.out.print("}\n\t\t");
			}
			System.out.println();
		}
		System.out.println();

		return 0;
	}
}
