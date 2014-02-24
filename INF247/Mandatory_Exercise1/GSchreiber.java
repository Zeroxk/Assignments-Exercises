import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;


public class GSchreiber {

	static int cipherText [] = new int [1274];
	static String plainText = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	static final int [][] codeTable = { 
		{1,1,0,0,0}, {1,0,0,1,1}, {0,1,1,1,0}, {1,0,0,1,0}, {1,0,0,0,0}, {1,0,1,1,0}, {0,1,0,1,1},{0,0,1,0,1}, {0,1,1,0,0}, {1,1,0,1,0 }, 
		{1,1,1,1,0}, {0,1,0,0,1}, {0,0,1,1,1}, {0,0,1,1,0}, {0,0,0,1,1}, {0,1,1,0,1}, {1,1,1,0,1}, {0,1,0,1,0}, {1,0,1,0,0}, {0,0,0,0,1}, 
		{1,1,1,0,0}, {0,1,1,1,1}, {1,1,0,0,1}, {1,0,1,1,1}, {1,0,1,0,1}, {1,0,0,0,1}, {0,0,0,1,0}, {0,1,0,0,0}, {1,1,1,1,1},{1,1,0,1,1}, 
		{0,0,1,0,0}, {0,0,0,0,0}
	};
	static Integer coincidences[][];
	private static ArrayList<Integer[]> rawBucketList;
	static final int wheelSizes[] = {47,53,59,61,64,65,67,69,71,73};

	public static void main(String[] args) throws Exception {

		//Read ciphertext from file
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
		
		br.close();
		
		index = 0;
		
		//Gather all instances where ciphertext is 11111 or 00000, xor it with the related plain-text, 
		coincidences = new Integer[cipherText.length][5];
		for (int i = 0; i < cipherText.length; i++) {
			int c = cipherText[i];

			if(c == 29 || c == 32) {
				int [] pt = codeTable[i%26];
				int [] ct = codeTable[c-1];
				
				for (int k = 0; k < pt.length; k++) {

					int l = pt[k] ^ ct[k];

					coincidences[i][k] = l;
				}

			}

		}

		ArrayList<Wheel> wheels = new ArrayList<Wheel>();
		
		for(Integer w: wheelSizes) {
			wheels.add(new Wheel(w));
		}
		
		System.out.println("Finding first 5 cablings");
		ArrayList<Integer> permSet = new ArrayList<>();
		for(Wheel w: wheels) {

			int permPos = findPermPos(bucketSortWheel(w.getSize()));
			if(permPos != -1) {
				w.setPermPos(permPos);
				permSet.add(w.getSize());
			}
		}
		
		Collections.sort(wheels);	
		
		System.out.println("Wheel\tCabling");
		for(Wheel w : wheels){
			if(w.getPermPos() == Integer.MAX_VALUE) continue;
			System.out.println(w.getSize() + ":\t" + (w.getPermPos()+1));
		}
		
		System.out.println("\nFinding 0-1 distribution on first 5 cablings");
		find01dist1(wheels);
		
		System.out.println("\nWheel\t 0-1 distribution First pass");
		printWheelDist(wheels);
		
		find01dist2(wheels);
		System.out.println("\nWheel\t 0-1 distribution Second pass");
		printWheelDist(wheels);
		
		//Create complete inputlist for plaintext
		ArrayList<Integer[]> inputList = new ArrayList<>();
		ArrayList<Integer[]> plugList = new ArrayList<>();
		for (int i = 0; i < cipherText.length; i++) {
			int[] pt = codeTable[i%26];
			Integer[] input = new Integer[5];
			Integer[] plugs = new Integer[5];
			
			index = 0;
			for(Wheel w : wheels) {
				if(w.getPermPos() == Integer.MAX_VALUE) break;
				input[index] = pt[index] ^ w.getDistribution().get(i%w.getSize());
				plugs[index] = w.getDistribution().get(i%w.getSize());
				index++;
			}
			
			plugList.add(plugs);
			inputList.add(input);
		}
		
//		System.out.println("\nPlaintext\tplugBits\tInput");
//		for (int i = 0; i < inputList.size(); i++) {
//			System.out.println(Arrays.toString(codeTable[i%26]) + "\t" + Arrays.toString(plugList.get(i)) + "\t" + Arrays.toString(inputList.get(i)));
//		}
		rawBucketList = new ArrayList<>();
		
		System.out.println("\nFinding last 5 cablings");
		ArrayList<ArrayList<ArrayList<Integer[]>>> bsorted = findControlCabling(wheels,plugList,inputList);
		
		index = 5;
		for(int a=0; a<bsorted.size(); a++) {
			
			ArrayList<ArrayList<Integer[]>> buckets = bsorted.get(a);
			ArrayList<Integer> permSet2 = new ArrayList<>();
			
			int permPos = findPermPos(buckets);
			if(permPos != -1) {
				wheels.get(a+5).setPermPos(permPos+5);
				permSet2.add(wheels.get(a+5).getSize());
			}
			
//			System.out.println("Wheel " + wheels.get(index++).getSize());
//			for (int i = 0; i < buckets.size(); i++) {
//				System.out.println("Position " + (i+1) + "\t");
//				for (int j = 0; j < buckets.get(i).size(); j++) {
//					Integer[] arr = buckets.get(i).get(j);
//					System.out.println(Arrays.toString(arr)+ "");
//				}
//				System.out.println();
//			}
		}
		
		Collections.sort(wheels);
		System.out.println("Wheels\tCabling");
		for (int i = 5; i < wheels.size(); i++) {
			System.out.println(wheels.get(i).getSize() + ":\t" + (wheels.get(i).getPermPos()+1));
		}
		
//		System.out.println("Finding 0-1 distribution for last 5 cablings");
		find01dist3(wheels, plugList, inputList, bsorted);

		
	}
	
	private static ArrayList<ArrayList<ArrayList<Integer[]>>> findControlCabling(ArrayList<Wheel> wheels, ArrayList<Integer[]> plugList, ArrayList<Integer[]> inputList) {
		
		ArrayList<ArrayList<ArrayList<Integer[]>>> ret = new ArrayList<>();
		
		for(Wheel w : wheels) {
			if(w.getPermPos() != Integer.MAX_VALUE) continue;
			
			ArrayList<ArrayList<Integer[]>> buckets = new ArrayList<>();
			
			for (int i = 0; i < w.getSize(); i++) {
				buckets.add(new ArrayList<Integer[]>());
			}
			
			for (int i = 0; i < cipherText.length; i++) {
				int[] ct = codeTable[cipherText[i]-1];
				int[] input = toPrimIntArr(inputList.get(i));
				int[] controlBits = {-1,-1,-1,-1,-1};
				boolean found = false;
				
				if(Arrays.equals(input, new int[]{0,0,0,0,1}) || Arrays.equals(input, new int[]{1,1,1,1,0})) {
					
					if(Arrays.equals(ct, new int[]{0,0,0,0,1}) || Arrays.equals(ct, new int[]{1,1,1,1,0})) {
						controlBits = new int[]{1,1,2,2,2};
						found = true;
						
					}else if(Arrays.equals(ct, new int[]{0,0,0,1,0}) || Arrays.equals(ct, new int[]{1,1,1,0,1})) {
						controlBits = new int[]{1,0,1,2,2};
						found = true;
						
					}else if(Arrays.equals(ct, new int[]{0,0,1,0,0}) || Arrays.equals(ct,  new int[]{1,1,0,1,1})) {
						controlBits = new int[]{1,0,0,1,2};
						found = true;
					}
					
					if(found) {
						ArrayList<Integer[]> tmp = buckets.get(i%w.getSize());
						tmp.add(toObjIntArr(controlBits));
						rawBucketList.add(toObjIntArr(controlBits));
					}
					
				}else if(Arrays.equals(input, new int[]{0,0,0,1,0}) || Arrays.equals(input, new int[]{1,1,1,0,1})) {
					
					if(Arrays.equals(ct, new int[]{0,0,0,0,1}) || Arrays.equals(ct, new int[]{1,1,1,1,0})) {
						controlBits = new int[]{2,0,2,2,2};
						found = true;
						
					}else if(Arrays.equals(ct, new int[]{0,0,0,1,0}) || Arrays.equals(ct, new int[]{1,1,1,0,1})) {
						controlBits = new int[]{2,1,1,2,2};
						found = true;
						
					}else if(Arrays.equals(ct, new int[]{0,0,1,0,0}) || Arrays.equals(ct,  new int[]{1,1,0,1,1})) {
						controlBits = new int[]{2,1,0,1,2};
						found = true;
						
					}else if(Arrays.equals(ct, new int[]{0,1,0,0,0}) || Arrays.equals(ct,  new int[]{1,0,1,1,1})) {
						controlBits = new int[]{2,1,0,0,1};
						found = true;
						
					}else if(Arrays.equals(ct, new int[]{1,0,0,0,0}) || Arrays.equals(ct,  new int[]{0,1,1,1,1})) {
						controlBits = new int[]{2,1,0,0,0};
						found = true;
					}
					
					if(found) {
						ArrayList<Integer[]> tmp = buckets.get(i%w.getSize());
						tmp.add(toObjIntArr(controlBits));
					}
					
					
					
				}else if(Arrays.equals(input, new int[]{0,0,1,0,0}) || Arrays.equals(input, new int[]{1,1,0,1,1})) {
					
					if(Arrays.equals(ct, new int[]{0,0,0,1,0}) || Arrays.equals(ct, new int[]{1,1,1,0,1})) {
						controlBits = new int[]{2,2,0,2,2};
						found = true;
						
					}else if(Arrays.equals(ct, new int[]{0,0,1,0,0}) || Arrays.equals(ct,  new int[]{1,1,0,1,1})) {
						controlBits = new int[]{2,2,1,1,2};
						found = true;
						
					}else if(Arrays.equals(ct, new int[]{0,1,0,0,0}) || Arrays.equals(ct,  new int[]{1,0,1,1,1})) {
						controlBits = new int[]{2,2,1,0,1};
						found = true;
						
					}
					
					if(found) {
						ArrayList<Integer[]> tmp = buckets.get(i%w.getSize());
						tmp.add(toObjIntArr(controlBits));
					}
					
				}else if(Arrays.equals(input, new int[]{0,1,0,0,0}) || Arrays.equals(input, new int[]{1,0,1,1,1})) {
					
					if(Arrays.equals(ct, new int[]{0,0,1,0,0}) || Arrays.equals(ct,  new int[]{1,1,0,1,1})) {
						controlBits = new int[]{2,2,2,0,2};
						found = true;
						
					}else if(Arrays.equals(ct, new int[]{0,1,0,0,0}) || Arrays.equals(ct,  new int[]{1,0,1,1,1})) {
						controlBits = new int[]{2,2,2,1,1};
						found = true;
						
					}else if(Arrays.equals(ct, new int[]{1,0,0,0,0}) || Arrays.equals(ct,  new int[]{0,1,1,1,1})) {
						controlBits = new int[]{2,2,2,1,0};
						found = true;
					}
					
					if(found) {
						ArrayList<Integer[]> tmp = buckets.get(i%w.getSize());
						tmp.add(toObjIntArr(controlBits));
					}
					
				}else if(Arrays.equals(input, new int[]{1,0,0,0,0}) || Arrays.equals(input, new int[]{0,1,1,1,1})) {
					
					if(Arrays.equals(ct, new int[]{0,0,0,0,1}) || Arrays.equals(ct,  new int[]{1,1,1,1,0})) {
						controlBits = new int[]{0,1,2,2,2};
						found = true;
						
					}else if(Arrays.equals(ct, new int[]{0,0,0,1,0}) || Arrays.equals(ct,  new int[]{1,1,1,0,1})) {
						controlBits = new int[]{0,0,1,2,2};
						found = true;
						
					}else if(Arrays.equals(ct, new int[]{0,0,1,0,0}) || Arrays.equals(ct,  new int[]{1,1,0,1,1})) {
						controlBits = new int[]{0,0,0,1,2};
						found = true;
						
					}
					
					if(found) {
						ArrayList<Integer[]> tmp = buckets.get(i%w.getSize());
						tmp.add(toObjIntArr(controlBits));
					}
					
				}
				
				
				
			}
			
//			System.out.println("Wheel " + w.getSize());
//			for (int i = 0; i < buckets.size(); i++) {
//				System.out.println("Position " + (i+1) + "\t");
//				for (int j = 0; j < buckets.get(i).size(); j++) {
//					Integer[] arr = buckets.get(i).get(j);
//					System.out.println(Arrays.toString(arr)+ "");
//				}
//				System.out.println();
//			}
			
			ret.add(buckets);
		}
		return ret;
		
		
	}
	
	private static Integer[] toObjIntArr(int[] integers) {
		Integer[] ret = new Integer[integers.length];
		for (int i = 0; i < integers.length; i++) {
			ret[i] = integers[i];
		}
		return ret;
	}

	private static int[] toPrimIntArr(Integer[] integers) {
		int[] ret = new int[integers.length];
		for (int i = 0; i < integers.length; i++) {
			ret[i] = integers[i];
		}
		return ret;
	}


	private static void printWheelDist(ArrayList<Wheel> wheels) {
		for(Wheel w : wheels) {
			if(w.getPermPos() == Integer.MAX_VALUE) continue;
			
			System.out.println(w.getSize() + ":\t" + w.getDistribution().toString());
		}
	}
	
	/**
	 * First pass on finding 01 distribution for first 5 plug positions
	 * 
	 * @param wheels The G-Schreiber rotor wheels
	 */
	private static void find01dist1(ArrayList<Wheel> wheels) {

		for (int i = 0; i < cipherText.length; i++) {
			int c = cipherText[i];
			
			if(c == 29 || c == 32) {
				int[] pt = codeTable[i%26];
				int[] ct = codeTable[c-1];
				
				int index = 0;
				
				for(Wheel w : wheels) {
					if(w.getPermPos() == Integer.MAX_VALUE) continue;
					
					ArrayList<Integer> dist = w.getDistribution();
					int xor = ct[index] ^ pt[index];
					if(dist.get(i%w.getSize()) == 2) {
						dist.set(i%w.getSize(), xor);
					}
					index++;
				}
			
			}
		}
		
	}
	
	/**
	 * Second pass on finding 01 distribution for first 5 plug positions
	 * 
	 * @param wheels The G-Schreiber rotor wheels
	 */
	private static void find01dist2(ArrayList<Wheel> wheels) {
		
		for (int i = 0; i < cipherText.length; i++) {
			int c = cipherText[i];
			
			int[] plugBits = new int[5];
			Pair<Integer,Integer> missing = new Pair<Integer, Integer>(0, -1);
			for (int j = 0; j < 5; j++) {
				Wheel w = wheels.get(j);
				int bit = w.getDistribution().get(i%w.getSize());
				if(bit == 2) {
					missing.setFirst(missing.getFirst()+1); 
					missing.setSecond(j);
				}
				plugBits[j] = bit;
				
			}
//			System.out.println("Plugbits" + plugBits.toString());
			
			if(missing.getFirst() == 1) {
				int[] ct = codeTable[c-1];
				int[] pt = codeTable[i%26];
				
				int[] input = XOR(plugBits,pt);
				
				int newBit = countWeight(ct) == countWeight(input) ? 0 : 1;
				
				input[missing.getSecond()] = newBit;
				int[] newInput = XOR(input,pt);
				for(int j = 0; j < newInput.length; j++) {
					Wheel w = wheels.get(j);
					w.getDistribution().set(i%w.getSize(), newInput[j]);
				}
				
//				System.out.println("Corrected plug:\t" + Arrays.toString(plugBits));
			}
			
		}
	}
	
	private static void find01dist3(ArrayList<Wheel> wheels, ArrayList<Integer[]> plugList, ArrayList<Integer[]> inputList, ArrayList<ArrayList<ArrayList<Integer[]>>> bsorted) {
		
		for (int i = 0; i < cipherText.length; i++) {
			
		}
		
	}

	private static int[] XOR(int[] a, int[] b) {
		assert a.length == b.length;
		int[] res = new int[a.length];
		for (int i = 0; i < res.length; i++) {
			if(a[i] == 2 || b[i] == 2) {
				res[i] = 2;
			}else {
				res[i] = a[i] ^ b[i];
			}
		}
		return res;
	}

	private static int countWeight(int[] ct) {
		int cnt = 0;
		for (int i = 0; i < ct.length; i++) {
			if(ct[i] == 1) cnt++;
		}
		return cnt;
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
			for (int j = 0; j < position.size(); j++) {
				if(i == j) continue;
				Integer [] cmp = position.get(j);
				for (int k = 0; k < cmp.length; k++) {
					if(start[k] != cmp[k] && !(start[k] == 2 || cmp[k] == 2)) {
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
//		System.sout.println("Bucketsorting on wheel: " + wheelSize);
		ArrayList<ArrayList<Integer[]>> wheel = new ArrayList<>();
		for (int i = 0; i < wheelSize; i++) {
			wheel.add(new ArrayList<Integer[]>());
		}

		for (int i = 0; i < coincidences.length; i ++) {
			Integer[] bits = coincidences[i];
			if(bits[0] == null) continue;
			ArrayList<Integer []> arr = wheel.get(i%wheelSize);
			arr.add(bits);

		}

		return wheel;
	}
}

class Wheel implements Comparable<Wheel> {
	private int size;
	private int permPos;
	private ArrayList<Integer> distribution;
	
	Wheel(int size) {
		this.size = size;
		permPos = Integer.MAX_VALUE;
		distribution = new ArrayList<>();
		for (int i = 0; i < size; i++) {
			distribution.add(2);
		}
	}

	public int getSize() {
		return size;
	}

	public int getPermPos() {
		return permPos;
	}

	public void setPermPos(int permPos) {
		this.permPos = permPos;
	}

	public ArrayList<Integer> getDistribution() {
		return distribution;
	}

	public void setDistribution(ArrayList<Integer> distribution) {
		this.distribution = distribution;
	}

	@Override
	public int compareTo(Wheel o) {
		if(this.permPos < o.permPos) return -1;
		if(this.permPos > o.permPos) return 1;
		return 0;
	}

	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (obj == null)
			return false;
		if (getClass() != obj.getClass())
			return false;
		Wheel other = (Wheel) obj;
		if (permPos != other.permPos)
			return false;
		if (size != other.size)
			return false;
		return true;
	}
}

class Pair<F,S> {
	
	private F first;
	private S second;
	
	public Pair(F f, S s) {
		first = f;
		second = s;
	}

	public F getFirst() {
		return first;
	}

	public void setFirst(F first) {
		this.first = first;
	}

	public S getSecond() {
		return second;
	}

	public void setSecond(S second) {
		this.second = second;
	}
	
}
