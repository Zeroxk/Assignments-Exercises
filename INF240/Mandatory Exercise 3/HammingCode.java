
public class HammingCode {

	public final static int [][] parChkMatrix = { 
		{0,  0,  0,  0,  1,  1,  1,  1,  1,  1,  1, 1,  0,  0,  0},	  
		{1,  1,  1,  0,  0,  0,  0,  1,  1,  1,  1, 0,  1,  0,  0},
		{0,  1,  1,  1,  0,  1,  1,  0,  0,  1,  1, 0,  0,  1,  0},
		{1,  0,  1,  1,  1,  0,  1,  0,  1,  0,  1, 0,  0,  0,  1}};
	
	public final static int [][] exM = { 
		{0,0,0,0,1,1,1,1,1,1,1,1,0,0,0}, 
		{1,1,1,0,0,0,0,1,1,1,1,0,1,0,0},
		{0,1,1,1,0,1,1,0,0,1,1,0,0,1,0},
		{1,0,1,1,1,0,1,0,1,0,1,0,0,0,1}	
	};
	
	public final static int [] rcvVector = {0,1,1,0,0,0,1,1,0,0,0,1,0,1,0};
	public final static int [] exV = {0,0,0,0,1,0,0,0,0,0,1,1,0,0,1};

	public static void main(String[] args) {
		
		int[][] testM = {{1,2},{3,4},{5,6}};
		
		int [][] transMatrix = transpose(parChkMatrix);
		System.out.println("Transposed matrix: ");
		for (int i = 0; i < transMatrix.length; i++) {
			for (int j = 0; j < transMatrix[0].length; j++) {
				System.out.print(transMatrix[i][j] + " ");
			}
			System.out.println();
		}
		
		//syndrome is dot product of received vector and transposed parity check matrix
		int [] syndrome = findSyndrome(transMatrix,rcvVector);
		System.out.print("Syndrome vector: ");
		for (int i = 0; i < syndrome.length; i++) {
			System.out.print(syndrome[i] + " ");
		}
		System.out.println();
		
		//Find position of the error
		int errorPos = findError(parChkMatrix, syndrome);
		System.out.println("Error at pos " + (errorPos+1));
		//Flip the bit at the errorposition
		int [] decoded = correctError(rcvVector, errorPos);
		
		System.out.println("Flipped bit from " + ((decoded[errorPos]+1) % 2) + " to " + decoded[errorPos]);
		System.out.print("Decoded vector is: ");
		for (int i = 0; i < decoded.length; i++) {
			System.out.print(decoded[i] + " ");
		}
		
		//Discard the last 4 bits
		int [] origMes = new int[decoded.length-4];
		for (int i = 0; i < origMes.length; i++) {
			origMes[i] = decoded[i];
		}
		System.out.println();
		
		System.out.print("Original message was: ");
		for (int i = 0; i < origMes.length; i++) {
			System.out.print(origMes[i] + " ");
		}
		
		
		
	}

	private static int[] correctError(int[] vec, int errorPos) {
		vec[errorPos] = vec[errorPos] == 1 ? 0 : 1;
		
		return vec;
		
	}

	/**
	 * Finds position of the error in parity check matrix by comparing each column with the transposed syndrome, the error is where there is a match
	 * 
	 * @param vector the parity check matrix
	 * @param syndrome Syndrome vector
	 * @return The position of the error in a 0-based array, -1 if no errors
	 */
	private static int findError(int[][] vector, int[] syndrome) {
		
			for (int i = 0; i < vector[0].length; i++) {
				boolean foundError = true;
				for (int j = 0; j < vector.length; j++) {
					if(vector[j][i] != syndrome[j]) {
						foundError = false;
					}
				}
				if(foundError) {
					return i;
				}
			}

		
		return -1;
		
	}

	/**
	 * Finds syndrome by formula s = yH^T
	 * 
	 * @param transMatrix H^T, the transposed matrix
	 * @param rcvVec y, the received vector
	 * @return syndrome as a vector with the length of how many columns in H^T
	 */
	private static int[] findSyndrome(int[][] transMatrix, int[] rcvVec) {
		
		int[] syndrome = new int[transMatrix[0].length];
		
		for (int i = 0; i < transMatrix[0].length; i++) {
			int sum = 0;
			for (int j = 0; j < rcvVec.length; j++) {
				sum += transMatrix[j][i] * rcvVec[j];
			}
			syndrome[i] = sum % 2;
		}
		
		return syndrome;
	}

	/**
	 * Transpose a matrix by swapping the rows with the columns
	 * 
	 * @param matrix The matrix NxM to be transposed
	 * @return The transposed matrix with dimensions MxN
	 */
	private static int[][] transpose(int[][] matrix) {
		
		int [][] transposed = new int[matrix[0].length][matrix.length];
		
		for (int i = 0; i < matrix[0].length; i++) {
			for (int j = 0; j < matrix.length; j++) {
				transposed[i][j] = matrix[j][i];
			}
		}
		
		return transposed;
	}

}
