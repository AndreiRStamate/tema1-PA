#include <cstdio>
#include <limits>
#include <vector>

using namespace std;

int main() {
	/* deschidere fisiere */
	freopen("valley.in", "r", stdin);
	freopen("valley.out", "w", stdout);

	size_t N; /* numar inaltimi */
	scanf("%lu", &N);

	vector<long long> inaltimi; /* vector inaltimi */
	inaltimi.reserve(N);

	long long minim = std::numeric_limits<long long>::max();
	size_t pozitieMinim = -1;

	/* citire inaltimi si calculare punct comun */
	for (size_t i = 0; i < N; i++) {
		long long aux;
		scanf("%lld", &aux);
		inaltimi.push_back(aux);

		if (minim > aux) {
			minim = aux;
			pozitieMinim = i;
		}
	}
	/* punctul comun gasit este prima inaltime din vector =>
		mutam punctul la dreapta */
	if (pozitieMinim == 0) {
		pozitieMinim++;
	}

	/* construim un sir descrescator de inaltimi intre prima inaltime
		si punctul comun */
	long long ore = 0;
	for (size_t i = 1; i <= pozitieMinim; i++) {
		if (inaltimi[i] > inaltimi[i-1]) {
			long long diferenta = inaltimi[i] - inaltimi[i-1];
			ore += diferenta;
			inaltimi[i] -= diferenta;
		}
	}

	/* punctul comun gasit este ultima inaltime din vector =>
		mutam punctul la stanga */
	if (pozitieMinim == N-1) {
		pozitieMinim--;
	}

	/* construim un sir descrescator dinspre ultima inaltime din vector catre
		punctul comun (de fapt o rampa de la punctul comun la ultimul
		element din vector) */
	for (size_t i = N - 1; i > pozitieMinim; i--) {
		if (inaltimi[i] < inaltimi[i-1]) {
			long long diferenta = inaltimi[i-1] - inaltimi[i];
			ore += diferenta;
			inaltimi[i-1] -= diferenta;
		}
	}

	printf("%lld", ore);

	return 0;
}
