// Michael Lau
// mlau10
// CMPS 101 - PA3
// 11/03/17

import java.io.*;
import java.util.Scanner;

class Sparse {
	public static void main(String[] args) throws IOException {
		Scanner in = null;
		PrintWriter out = null;
		int n, a, b;
		if(args.length < 2) {
			System.err.println("Usage: Sparse infile outfile");
			System.exit(1);
		}
		
		in = new Scanner(new File(args[0]));
		out = new PrintWriter(new FileWriter(args[1]));
		n = in.nextInt();
		a = in.nextInt();
		b = in.nextInt();
		Matrix A = new Matrix(n);
		
		for(int i = 0; i < a; i++) {
			int row = in.nextInt();
			//System.out.println(row);
			int col = in.nextInt();
			//System.out.println(col);
			double value = in.nextDouble();
			//System.out.println(value);
			A.changeEntry(row, col, value);
		}
		
		Matrix B = new Matrix(n);
		for(int i = 0; i < b; i++) {
			int row = in.nextInt();
			int col = in.nextInt();
			double value = in.nextDouble();
			B.changeEntry(row, col, value);
		}
		
		out.println("A has "+a+" non-zero entries:");
		out.println(A);
		out.println("B has "+b+" non-zero entries:");
		out.println(B);
		out.println("(1.5)*A =");
		out.println(A.scalarMult(1.5));
		out.println("A+B =");
		out.println(A.add(B));
		out.println("A+A =");
		out.println(A.add(A));
		out.println("B-A =");
		out.println(B.sub(A));
		out.println("A-A =");
		out.println(A.sub(A));
		out.println("Transpose(A) =");
		out.println(A.transpose());
		out.println("A*B =");
		out.println(A.mult(B));
		out.println("B*B =");
		out.println(B.mult(B));
		
		in.close();
		out.close();
	}
}