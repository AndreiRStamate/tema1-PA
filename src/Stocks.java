import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;
import static java.lang.Math.max;
import java.util.Scanner;
import java.util.StringTokenizer;

public class Stocks {

	static class MyScanner {
		public final String inputFile = "stocks.in";

		BufferedReader br;
		StringTokenizer st;

		public MyScanner() throws FileNotFoundException {
			br = new BufferedReader(new FileReader(inputFile));
		}

		String next() {
			while (st == null || !st.hasMoreElements()) {
				try {
					st = new StringTokenizer(br.readLine());
				} catch (IOException e) {
					e.printStackTrace();
				}
			}
			return st.nextToken();
		}

		int nextInt() {
			return Integer.parseInt(next());
		}

		long nextLong() {
			return Long.parseLong(next());
		}

		double nextDouble() {
			return Double.parseDouble(next());
		}

		String nextLine() {
			String str = "";
			try {
				str = br.readLine();
			} catch (IOException e) {
				e.printStackTrace();
			}
			return str;
		}
	}

	static class Task {
		public final String outputFile = "stocks.out";
		public int N, B, L;
		public int[] preturi; /* preturi actiuni */
		public int[] minime; /* profit minim actiuni */
		public int[] maxime; /* profit maxim actiuni */

		public void solve() {
			readInput();
			writeOutput(getResult());
		}

		private void readInput() {
			/* citire actiuni */
			try {
				MyScanner sc = new MyScanner();
				N = sc.nextInt();
				B = sc.nextInt();
				L = sc.nextInt();
				preturi = new int[N + 1];
				minime = new int[N + 1];
				maxime = new int[N + 1];
				for (int i = 1; i <= N; i++) {
					preturi[i] = sc.nextInt();
					minime[i] = sc.nextInt();
					maxime[i] = sc.nextInt();
				}
			} catch (IOException e) {
				throw new RuntimeException(e);
			}
		}

		private void writeOutput(int result) {
			try {
				PrintWriter pw = new PrintWriter(new File(outputFile));
				pw.printf("%d\n", result);
				pw.close();
			} catch (IOException e) {
				throw new RuntimeException(e);
			}
		}

		private int getResult() {
			return maxProfit();
		}

		private int maxProfit() {
			/* dp este o matrice tridimensionala */
			int[][][] dp = new int[N + 1][B + 1][L + 1];

			/* cazul de baza */
			for (int b = 0; b <= B; b++) {
				for (int l = 0; l <= L; l++) {
					dp[0][b][l] = 0;
				}
			}

			/* cazul general */
			for (int n = 1; n <= N; n++) {
				for (int b = 1; b <= B; b++) {
					for (int l = 1; l <= L; l++) {
						/* nu se foloseste obiectul n => solutia de la pasul n-1 */
						dp[n][b][l] = dp[n - 1][b][l];

						/* se foloseste obiectul n => am folosit maxim b - preturi bani 
							si am pierdut maxim l - preturi + profit_minim */
						if (l - preturi[n] + minime[n] >= 0 && b - preturi[n] >= 0) {
							int sol_aux = dp[n - 1][b - preturi[n]][l - preturi[n] + minime[n]]
								+ maxime[n] - preturi[n];
							dp[n][b][l] = max(dp[n][b][l], sol_aux);
						}
					}
				}
			}
			return dp[N][B][L];
		}
	}

	public static void main(String[] args) throws FileNotFoundException {
		new Task().solve();
	}
}

