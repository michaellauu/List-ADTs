// Michael Lau
// mlau10
// CMPS 101 - PA3
// 10/27/17

public class Matrix {
	
	private class Entry {
		int col;
		double data;
		private Entry(int col, double data) {
			this.col = col;
			this.data = data;
		}
		
		public String toString() {
			return "("+col+", "+data+")";
		} 
	}
	
	private int nnz, size;
	private List[] row;
	
	// Constructor
	Matrix(int n) { // Makes a new n x n zero Matrix.  pre: n>=1
		if (n >= 1) {
			size = n;
			row = new List[n+1];
			for(int i = 1; i <= n; i++) {
				row[i] = new List();
			}
		}
	}
	
	// Access functions 
	int getSize() { // Returns n, the number of rows and columns of this Matrix
		return size;
	}
	
	int getNNZ() { // Returns the number of non-zero entries in this Matrix
		return nnz;
	}
	
	public boolean equals(Object x) { // overrides Object's equals()method
		Matrix M = (Matrix) x;
		boolean eq = true;
		if(M.nnz != nnz) eq = false;
		if(M.size != size) eq = false;
		for(int i = 1; i <= size; i++) {
			if(!(M.row[i].equals(row[i]))) eq = false;		
		}
		return eq; 
	}	
	
	// Manipulation procedures
	void makeZero() { // sets this Matrix to the zero state
		for(int i = 1; i <= size; i++) {
			row[i].clear();
		}
		nnz = 0;
	}
	
	Matrix copy() { // returns a new Matrix having the same entries as this Matrix
		Matrix M = new Matrix(size);
		M.nnz = nnz;
		for(int i = 1; i <= size; i++) {
			row[i].moveFront();
			while(row[i].index() >=0) {
				Entry entry = (Entry) row[i].get();
				entry = new Entry(entry.col, entry.data);
				M.row[i].append(entry);
				row[i].moveNext();
			}
		}
		return M;
	}
	
	void changeEntry(int i, int j, double x) {// changes ith row, jth col of this Matrix to x
		if(i < 1 || i > size || j < 1 || j > size) { // pre: 1<=i<=getSize(), 1<=j<=getSize()
			throw new RuntimeException("Matrix: changeEntry called bad position\n");
		}
		boolean eq = false;
		row[i].moveFront();
		while(row[i].index() >= 0) {
			Entry entry = (Entry) row[i].get();
			eq = (entry.col == j);
			if(eq == true) {
				if(x == 0.0) {
					row[i].delete();
					nnz--;
				}
				if(x != 0.0 && entry.data != 0) entry.data = x;
				else {
					entry.data = x;
					nnz++;
				}
			}
			row[i].moveNext();
		}
		if(x != 0.0 && eq == false) {
			row[i].moveFront();
			if(row[i].index() == -1) {
				row[i].prepend(new Entry(j, x));
				nnz++;
			}
			else {
				while(row[i].index() >= 0 && ((Entry)row[i].get()).col < j) {
					row[i].moveNext();
				}
				if(row[i].index() >= 0) {
					row[i].insertBefore(new Entry(j, x));
					nnz++;
				}
				else {
					row[i].append(new Entry(j, x));
					nnz++;
				}
			}
		}
	}
	
	Matrix scalarMult(double x) { // returns a new Matrix that is the scalar product of this Matrix with x
		Matrix M = new Matrix(size);
		M.nnz = nnz;
		for(int i = 1; i <= size; i++) {
			row[i].moveFront();
			while(row[i].index() >= 0) {
				Entry entry = (Entry) row[i].get();
				entry = new Entry(entry.col, entry.data);
				entry.data = entry.data * x;
				M.row[i].append(entry);
				row[i].moveNext();
			}
		}
		return M;		
	}
	
	Matrix add(Matrix M) { // returns a new Matrix thatis the sum of this Matrix with M
		if(size != M.size) { // pre: getSize()==M.getSize()
			throw new RuntimeException("Matrix: add error, size difference\n");
		}
		if(this == M) return M.copy().scalarMult(2.0);
		Matrix A = new Matrix(size);
		A.nnz = nnz;
		for (int i = 1; i <= size; i++) {
			row[i].moveFront();
			M.row[i].moveFront();
			while (row[i].index() >= 0 || M.row[i].index() >= 0) {
				if(row[i].index() >= 0 && M.row[i].index() >= 0) {
					Entry a = (Entry) row[i].get();
					Entry b = (Entry) M.row[i].get();
					if(a.col > b.col) {
						A.row[i].append(new Entry(b.col, b.data));
						M.row[i].moveNext();
					}
					if(a.col < b.col) {
						A.row[i].append(new Entry(a.col, a.data));
						row[i].moveNext();
					} 
					else {
						A.row[i].append(new Entry(a.col, a.data+b.data));
						row[i].moveNext();
						M.row[i].moveNext();
					}
				} 
				if(row[i].index() >= 0 && M.row[i].index() == -1) {
					Entry a = (Entry) row[i].get();
					A.row[i].append(new Entry(a.col,a.data));
					row[i].moveNext();
				} 
				if(M.row[i].index() >= 0 && row[i].index() == -1) {
					Entry b = (Entry) M.row[i].get();
					A.row[i].append(new Entry((b.col), b.data));
					M.row[i].moveNext();
				}
			}
		} 
		return A;
	}

	Matrix sub(Matrix M) { // returns a new Matrix that is the difference of this Matrix with M
		if(size != M.size) { // pre: getSize()==M.getSize()
			throw new RuntimeException("Matrix: add error, size difference\n");
		}
		if(this == M) return new Matrix(size);
		Matrix A = new Matrix(size);
		A.nnz = nnz;
		Matrix MNeg = M.scalarMult(-1.0);
		A = add(MNeg);
		return A;
		// add nnz check
	}
	
	Matrix transpose() { // returns a new Matrix that is the transpose of this Matrix
		Matrix M = new Matrix(size);
		for(int i = 1; i <= size; i++) {
			row[i].moveFront();
			while(row[i].index() >= 0) {
				M.changeEntry((((Entry)row[i].get()).col),i,(((Entry)row[i].get()).data));
				row[i].moveNext();
			}
		}
		return M;
	}
	
	Matrix mult(Matrix M) { // returns a new Matrix that is the product of this Matrix with M
		if(size != M.size) { // pre: getSize()==M.getSize()
			throw new RuntimeException("Matrix: mult error, size difference\n");
		}
		Matrix A = new Matrix(size);
		Matrix B = M.transpose();
		A.nnz = nnz;
		for(int i = 1; i <= size; i++) {	
			A.changeEntry(i, i, dot(row[i], B.row[i]));
		}
		return A;
	}
	
	// Other functions 
	public String toString() { // overrides Object's toString() method
		String string = "";
		for(int i = 1; i <= size; i++) {
			if(row[i].length() > 0)
			string += (i+": "+row[i]+"\n"); 
		}
		return string;
	}
	
	public static double dot(List A, List B) {
		double total = 0.0;
		A.moveFront();
		B.moveFront();
		while(A.index() >= 0) {
			Entry a = (Entry) A.get();
			A.moveNext();
			while(B.index() >= 0) {
				Entry b = (Entry) B.get();
				B.moveNext();
				if (a.col == b.col) {
					total += a.data * b.data;
				}
			}
		}
		return total;
	}
}