#include <stdio.h>
#include <stdlib.h>

/* structura pentru reprezentarea unui calculator (nivel + pret upgrade) */
struct pair {
	long long first;
	long long second;
};

/* functie de calcul al pretului pentru upgrade al tuturor calculatoarelor
	pana la un anumit nivel */
long long suma(long long putere, struct pair perechi[], long long N);
/* functie de sortare in functie de nivelul calculatorului */
int cmpfunc(const void* a, const void* b);

int main() {
	/* deschidere fisiere */
	freopen("crypto.in", "r", stdin);
	freopen("crypto.out", "w", stdout);

	long long N; /* numar calculatoare */
	long long B; /* bani alocati upgrade-urilor */

	scanf("%lld%lld", &N, &B);

	struct pair* calculatoare = (struct pair*)malloc(sizeof(struct pair)*N);

	/* citire date calculatoare */
	for (long long i = 0; i < N; i++) {
		long long Pi, Ui;
		scanf("%lld%lld", &Pi, &Ui);
		calculatoare[i] = (struct pair){Pi, Ui};
	}

	/* sortare in functie de nivel, folosind qsort */
	qsort(calculatoare, N, sizeof(struct pair), cmpfunc);

	long long minim = calculatoare[0].first; /* nivel calculator minim */
	long long bestMax = minim;
	long long maxim = calculatoare[N-1].first; /* nivel calculator maxim */

	/* cautam valoarea maxima la care putem aduce toate calculatoarele
		cu banii alocati, folosind o cautare de tipul cautarii binare  */
	while (minim <= maxim) {
		long long mijloc = (minim + maxim) / 2;
		long long val = suma(mijloc, calculatoare, N);
		/* costul este egal cu suma de bani alocata => 
			afisam valoarea si terminam programul */
		if (val == B) {
			printf("%lld", mijloc);
			return 0;
		} else if (val < B) {
			/* putem upgrada mai mult => cautam in dreapta */
			bestMax = mijloc; /* retinem upgrade-ul maxim */
			minim = mijloc + 1;
		} else {
			/* nu ne permitem un asemenea upgrade de rig => cautam in stanga */
			maxim = mijloc - 1;
		}
	}

	/* dupa upgradarea tuturor calculatoarelor la nivelul maxim 
		raman bani si atunci se upgradeaza toate cu catul dintre 
		suma totala si costul upgrade-ului tuturor calculatoarelor
		de la nivelul initial pana la nivelul maxim + 1 */
	bestMax += B / suma(minim, calculatoare, N);
	printf("%lld", bestMax);
	return 0;
}

long long suma(long long putere, struct pair perechi[], long long N) {
	long long s = 0;
	for (long long i = 0; i < N; i++) {
		/* upgrade-ul se realizeaza doar de la nivelul initial
			pana la nivelul "putere" */
		long long dif = putere - perechi[i].first;
		if (dif > 0) {
			s += dif * perechi[i].second;
		} else {
			return s;
		}
	}
	return s;
}

int cmpfunc(const void* a, const void* b) {
	struct pair* p1 = (struct pair*)a;
	struct pair* p2 = (struct pair*)b;

	return (p1->first - p2->first);
}
