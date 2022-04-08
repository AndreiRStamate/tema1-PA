#include <cstdio>
#include <limits>
#include <vector>
#include <cstdlib>

using namespace std;

int main() {
	/* deschidere fisiere */
	freopen("ridge.in", "r", stdin);
	freopen("ridge.out", "w", stdout);

	size_t N; /* numar munti */
	scanf("%lu", &N);

	long long *H = new long long[N];
	long long *C = new long long[N];

	/* citire munti */
	for (size_t i = 0; i < N; i++) {
		scanf("%lld %lld", &H[i], &C[i]);
	}

	/* dp este o matrice de dimensiune N x 3 */
	vector<vector<long long>> dp(N, vector<long long>(3));

	/* caz de baza */
	for (size_t j = 0; j < 3u; j++) {
		/* se scade inaltimea muntelui cu j*/
		dp[0][j] = j * C[0];
	}

	/* caz general: dp[i][j] = j * cost[i] + minimum; */
	for (size_t i = 1; i < N; i++) {
		for (long long j = 0; j < 3; j++) {
			long long minim = std::numeric_limits<long long>::max();

			/* inaltime curenta diferita de inaltimea precedenta */
			if (H[i] - j != H[i-1]) {
				/* elementul precedent nemodificat */
				minim = dp[i-1][0];
			}

			/* inaltime curenta diferita de (inaltimea precedenta - 1) */
			if (H[i] - j != H[i-1] - 1 && H[i-1] - 1 >= 0) {
				/* minimul dintre minimul curent si 
					elementul precedent micsorat cu 1 */
				minim = (minim < dp[i-1][1]) ? minim : dp[i-1][1];
			}

			/* inaltime curenta diferita de (inaltimea precedenta - 2) */
			if (H[i] - j != H[i-1] - 2 && H[i-1] - 2 >= 0) {
				/* minimul dintre minimul curent si 
					elementul precedent micsorat cu 2 */
				minim = (minim < dp[i-1][2]) ? minim : dp[i-1][2];
			}

			dp[i][j] = j * C[i] + minim; /* minimul tuturor cazurilor */
		}
	}

	long long costMinim = std::numeric_limits<long long>::max();

	/* se ia costul minim de pe ultima linie a matricei dp*/
	costMinim = (costMinim < dp[N-1][0]) ? costMinim : dp[N-1][0];
	costMinim = (costMinim < dp[N-1][1]) ? costMinim : dp[N-1][1];
	costMinim = (costMinim < dp[N-1][2]) ? costMinim : dp[N-1][2];

	printf("%lld", costMinim);

	return 0;
}
