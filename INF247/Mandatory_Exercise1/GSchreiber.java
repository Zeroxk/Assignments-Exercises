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

		//Read ciphertext from file
		File f = new File("Ciphertext.txt");
		BufferedReader br = new BufferedReader(new FileReader(f));

		int index = 0;
		String str = br.readLine();
		while(str != null) {

			//If char being read is a digit, check the next char if it is a digit too
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
		
		//Gather all instances where ciphertext is 11111 or 00000, xor it with the related plain-text, 
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

		Integer wheelPos [] = new Integer[10];


		wheelPos[0] = findPermPos(bucketSortWheel(47));
		wheelPos[1] = findPermPos(bucketSortWheel(53));
		wheelPos[2] = findPermPos(bucketSortWheel(59));
		wheelPos[3] = findPermPos(bucketSortWheel(61));
		wheelPos[4] = findPermPos(bucketSortWheel(64));
		wheelPos[5] = findPermPos(bucketSortWheel(65));
		wheelPos[6] = findPermPos(bucketSortWheel(67));
		wheelPos[7] = findPermPos(bucketSortWheel(69));
		wheelPos[8] = findPermPos(bucketSortWheel(71));
		wheelPos[9] = findPermPos(bucketSortWheel(73));
		
		System.out.println("Wheel cabling after key-stream attack, wheelPos[i] indicates what position in the permuted key-stream the wheel is.\nWheels are from left to right, wheel 47 is on the leftmost side");
		printArray(wheelPos);
		
		System.out.println("\nGenerating all controlbit-group permutations");
		ArrayList<Integer[]> controlBitPermutations = genAllPermutes(5);
		for (int i = 0; i < controlBitPermutations.size(); i++) {
			Integer [] tmp = controlBitPermutations.get(i);
			printArray(tmp);
		}

		Integer [] weight1 = {0,0,0,0,1};
		Integer [] weight4 = {1,1,1,1,0};
		System.out.println("\nGenerating all bitstrings of weight 1");
		ArrayList<Integer[]> shiftsW1 = genAllShifts(weight1, 1);
		System.out.println("Generating all bitstrings of weight 4");
		ArrayList<Integer[]> shiftsW4 = genAllShifts(weight4, 4);

		System.out.println("\nPrinting all bitstrings of weight 1");
		for(Integer[] a : shiftsW1)  {
			printArray(a);
		}
		
		System.out.println("\nPrinting all bitstrings of weight 4");
		for(Integer[] a : shiftsW4) {
			printArray(a);
		}
		
		//Finds all valid controlbit groups where input/output is known and of weight 1 or 43656
		
		for (int i = 0; i < controlBitPermutations.size(); i++) {
			boolean found = findControlbits(weight1, weight4, controlBitPermutations.get(i));
			if(found) printArray(controlBitPermutations.get(i));
			
		}
		
		

	}
	
	/**
	 * Finds the cabling index for the wheel, -1 otherwise
	 * 
	 * @param bucketSortWheel wheel sorted into buckets
	 * @return index of where wheel is permuted to, -1 if it does not exist
	 */
	private static int findPermPos(
			ArrayList<ArrayList<Integer[]>> bucketSortWheel) {
		Integer [] pos = {1,1,1,1,1};
		
		for (int i = 0; i < bucketSortWheel.size(); i++) {
			ArrayList<Integer[]> position = bucketSortWheel.get(i);
			if(position.size() == 0) continue;
			
			Integer[] start = position.get(0);
			for (int j = 1; j < position.size(); j++) {
				Integer [] cmp = position.get(j);
				for (int k = 0; k < cmp.length; k++) {
					if(start[k] != cmp[k]) {
						pos[k] = -1;
					}
				}
			}
		}

		for (int i = 0; i < pos.length; i++) {
			if(pos[i] == 1) return i;
		}
		return -1;
	}

	/**
	 * Generate all binary strings of weight 1 or 4
	 * 
	 * @param bits The binary string to be shifted
	 * @param weight weight of bits, 1 or 4
	 * @return A list of all shifts of bits
	 */
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
	
	/**
	 * Given known switch input/output find the valid controlbit groups that permutes the input into output
	 * 
	 * @param input Binary input
	 * @param output Expected Binary output
	 * @param controlBitPerms All permutations of the controlbit groups
	 * @return
	 */
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
	
	/**
	 * Prints an array to std in
	 * 
	 * @param arr Array to be printed
	 */
	private static void printArray(Integer[] arr) {
		System.out.print("{ ");
		for (int i = 0; i < arr.length; i++) {
			System.out.print(arr[i] + " ");
		}
		System.out.print("}\n");
	}

	/**
	 * Generate all binary string permutations of length n
	 * 
	 * @param bitlength Desired length of the strings
	 * @return All binary string permutations of length n
	 */
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

	/**
	 * Permutes a bitgroup by swapping bits at position i,j if permutator[i] == 0
	 * 
	 * @param group The bitgroup to be permuted
	 * @param permutator The permuting bitgroup
	 */
	private static void controlBitSwap (Integer[] group, Integer [] permutator) {

		if (permutator[0]== 0) swap(group, 0, 4);
		if (permutator[1] == 0) swap(group, 3,4);
		if (permutator[2] == 0) swap(group, 2, 3);
		if (permutator[3] == 0) swap(group, 1, 2);
		if (permutator[4] == 0) swap(group, 0, 1);


	}

	/**
	 * Swaps two values in an array
	 * 
	 * @param arr Array to be swapped
	 * @param i index of value to be swapped
	 * @param j index of value to be swapped
	 */
	private static void swap(Integer[] arr, int i, int j) {
		int tmp = arr[i];
		arr[i] = arr[j];
		arr[j] = tmp;

	}

	/**
	 * Does a sort of bucketsort on the ciphertext with # of buckets == wheelSize s.t bitgroups at ciphertext[i%wheelSize] is in the same list as ciphertext[i]
	 * 
	 * @param wheelSize Size of the wheel
	 * @return List of lists containing the ciphertext in bucketsorted order
	 */
	private static ArrayList<ArrayList<Integer[]>> bucketSortWheel(int wheelSize ) {
		System.out.println("Bucketsorting on wheel: " + wheelSize);
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

		return wheel;
	}
}
