#include <math.h>
#include <time.h>

#define N 10
void		datos_matriz(float *c);
float       **nueva(int opc);
int		    esCero     (float x);
void		genera_int(int opc, float *c);
void		multiplicacion(float *matriz_a, float *matriz_b, float *matriz_c);
void		suma      (float *matriz_a, float *matriz_b, float *matriz_c);
void		inversa   (float *A);
void		escribe   (float *A, char *nombre);
float        **convierte(int **a);
void		muestra   (float *c);
void		muestra_inversa(float *c);

void 
genera_int(int opc, float *c)
{
	if (opc == 1)
		datos_matriz(c);
}
float         **
nueva(int opc)
{
	int		i;
	float         **matriz;
	matriz = malloc(sizeof(float *) * 10);
	for (i = 0; i < 10; i++)
		matriz[i] = malloc(sizeof(float *) * 10);
	return matriz;

}
void 
datos_matriz(float *c)
{
	int		i         , j;
	srand(time(NULL));
	for (i = 0; i < 10; i++) {
		for (j = 0; j < 10; j++) {
			*c++ = (float)(rand() % 9);
		}
	}
}
void 
muestra(float *c)
{
	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < 10; ++j) {
			printf("[%.0f]", *c++);
		}
		printf("\n");
	}
	printf("\n");
}
void 
muestra_inversa(float *c)
{
	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < 10; ++j) {

			printf("[%.03f]", *c++);
		}
		printf("\n");
	}
	printf("\n");
}
void 
multiplicacion(float *matriz_a, float *matriz_b, float *matriz_c)
{
	int		temp;
	for (int i = 0; i < 10; ++i) {
		temp = 0;
		for (int j = 0; j < 10; ++j) {
			for (int k = 0; k < 10; ++k) {
				temp += matriz_a[(k * 10) + i] * matriz_b[(j * 10) + k];
				*matriz_c = temp;
			}
			*matriz_c++;
		}
	}
}
void 
suma(float *matriz_a, float *matriz_b, float *matriz_c)
{
	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < 10; ++j) {
			*matriz_c++ = (*matriz_a++) + (*matriz_b++);
		}
	}
}
void 
inversa(float *a)
{
	float         **A = nueva(0);
	float         **inv = nueva(0);
	float         *c = a;

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			A[i][j] = *c++;
		}
	}

	for (int i = 0; i < N; ++i)
		inv[i][i] = 1;
	int		i = 0,	j = 0;
	while (i < N && j < N) {
		if (esCero(A[i][j])) {
			for (int k = i + 1; k < N; ++k) {
				if (!esCero(A[k][j])) {
					float          *tmp = A[i];
					A[i] = A[k];
					A[k] = tmp;
					tmp = inv[i];
					inv[i] = inv[k];
					inv[k] = tmp;
					break;
				}
			}
		}
		if (!esCero(A[i][j])) {
			for (int l = 0; l < N; ++l)
				inv[i][l] /= A[i][j];
			for (int l = N - 1; l >= j; --l)
				A[i][l] /= A[i][j];
			for (int k = 0; k < N; ++k) {
				if (i == k)
					continue;
				for (int l = 0; l < N; ++l)
					inv[k][l] -= inv[i][l] * A[k][j];
				for (int l = N; l >= j; --l)
					A[k][l] -= A[i][l] * A[k][j];
			}
			++i;
		}
		++j;
	}
	c = a;

	for (i = 0; i < 10; i++) {
		for (j = 0; j < 10; j++) {
			*c++ = inv[i][j];
		}
	}
}


int 
esCero(float x)
{
	return fabs(x) < 1e-8;
}

void 
escribe(float *A, char *nombre)
{
	FILE           *fp = fopen(nombre, "w");
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j)
			fprintf(fp, "%0.3lf ", A[j * 10 + i]);
		fprintf(fp, "\n");
	}
	fclose(fp);
}
