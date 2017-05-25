/* Disciplina: Computacao Concorrente */
/* Prof.: Silvana Rossetto */
/* Trabalho 1 */
/* Nome: Jéssica Genta dos Santos e Sidney Ribeiro Ramos Júnior*/

#include <stdio.h>
#include <stdlib.h> 
#include <math.h>
#include "timer.h"
#include <pthread.h>

double intervalo_a;
double intervalo_b;
int n;
double erro;
double parcial = 0;
int nthreads;
int i_global = 0;
pthread_mutex_t mutex;

//conjunto que calcula a função 1 + x
void *quadraturaAdaptativa(void *args){ 
	double a = intervalo_a;
	double b = intervalo_b;
	double parcialLocal = 0;
	int i_local; 
	double h = (b-a)/n;
	
	pthread_mutex_lock(&mutex);
	i_local = i_global; 
	i_global++;
	pthread_mutex_unlock(&mutex);

	while(i_local < n) { 
		parcialLocal=parcialLocal+(1 +((a+(a+h))/2));
		a=a+h;
		pthread_mutex_lock(&mutex);
		i_local = i_global; 
		i_global++;
		pthread_mutex_unlock(&mutex);
	}
	
	parcial += h*parcialLocal;
	
	pthread_exit(NULL); 
	return 0;
} 

double quadraturaAdaptativaAux(){
	double a = intervalo_a, b = intervalo_b;	
	double base;
	double medio;
	double altura;
	double diferenca, areaMaior, areaMenor, areaMenor2;
	int i;
	
	for(i = 1; ;i++){
		base = abs(b - a);
		medio = (b + a)/2;
		altura = 1 + medio;
		
		//printf("Medio: %lf\n", medio);
		areaMenor = (medio - a) * altura;
		//printf("AreaMenor: %lf\n", areaMenor);
		areaMenor2 = (b - medio) * altura;
		//printf("AreaMenor2: %lf\n", areaMenor2);
		areaMaior = base * (b + a);
		//printf("AreaMaior: %lf\n", areaMaior);
		diferenca = areaMaior - (areaMenor + areaMenor2);
		//printf("Diferenca: %lf\n", diferenca);	
		
		if (diferenca <= erro){
			return i;
		}
		a = intervalo_a;
		b = medio;
		
	}	                 
}

//conjunto que calcula a função sqrt(1 - x^2)
/*void *quadraturaAdaptativa(void *args){ 
	double a = intervalo_a;
	double b = intervalo_b;
	double parcialLocal = 0;
	int i_local; 
	double h = (b-a)/n;
	
	pthread_mutex_lock(&mutex);
	i_local = i_global; 
	i_global++;
	pthread_mutex_unlock(&mutex);

	while(i_local < n) { 
		parcialLocal=parcialLocal+(sqrt(1 - pow(((a+(a+h))/2),2)));
		a=a+h;
		pthread_mutex_lock(&mutex);
		i_local = i_global; 
		i_global++;
		pthread_mutex_unlock(&mutex);
	}
	
	parcial += h*parcialLocal;
	
	pthread_exit(NULL); 
	return 0;
} 

double quadraturaAdaptativaAux(){
	double a = intervalo_a, b = intervalo_b;	
	double base;
	double medio;
	double altura;
	double diferenca, areaMaior, areaMenor, areaMenor2;
	int i;
	
	for(i = 1; ;i++){
		base = abs(b - a);
		medio = (b + a)/2;
		altura = sqrt(1 - pow(medio,2));
		
		//printf("Medio: %lf\n", medio);
		areaMenor = (medio - a) * altura;
		//printf("AreaMenor: %lf\n", areaMenor);
		areaMenor2 = (b - medio) * altura;
		//printf("AreaMenor2: %lf\n", areaMenor2);
		areaMaior = base * (b + a);
		//printf("AreaMaior: %lf\n", areaMaior);
		diferenca = areaMaior - (areaMenor + areaMenor2);
		//printf("Diferenca: %lf\n", diferenca);	
		
		if (diferenca <= erro){
			return i;
		}
		a = intervalo_a;
		b = medio;
		
	}	                 
}*/

//conjunto que calcula a função sqrt(1 + x^4)
/*void *quadraturaAdaptativa(void *args){ 
	double a = intervalo_a;
	double b = intervalo_b;
	double parcialLocal = 0;
	int i_local; 
	double h = (b-a)/n;
	
	pthread_mutex_lock(&mutex);
	i_local = i_global; 
	i_global++;
	pthread_mutex_unlock(&mutex);

	while(i_local < n) { 
		parcialLocal=parcialLocal+(sqrt(1 + pow(((a+(a+h))/2),4))); 
		a=a+h;
		pthread_mutex_lock(&mutex);
		i_local = i_global; 
		i_global++;
		pthread_mutex_unlock(&mutex);
	}
	
	parcial += h*parcialLocal;
	
	pthread_exit(NULL); 
	return 0;
} 

double quadraturaAdaptativaAux(){
	double a = intervalo_a, b = intervalo_b;	
	double base;
	double medio;
	double altura;
	double diferenca, areaMaior, areaMenor, areaMenor2;
	int i;
	
	for(i = 1; ;i++){
		base = abs(b - a);
		medio = (b + a)/2;
		altura = sqrt(1 + pow(medio,4));
		
		//printf("Medio: %lf\n", medio);
		areaMenor = (medio - a) * altura;
		//printf("AreaMenor: %lf\n", areaMenor);
		areaMenor2 = (b - medio) * altura;
		//printf("AreaMenor2: %lf\n", areaMenor2);
		areaMaior = base * (b + a);
		//printf("AreaMaior: %lf\n", areaMaior);
		diferenca = areaMaior - (areaMenor + areaMenor2);
		diferenca = -1 * diferenca;
		//printf("Diferenca: %lf\n", diferenca);	
		
		if (diferenca <= erro){
			return i;
		}
		a = intervalo_a;
		b = medio;
		
	}	                 
}*/

//conjunto que calcula a função sen(x^2)
/*void *quadraturaAdaptativa(void *args){ 
	double a = intervalo_a;
	double b = intervalo_b;
	double parcialLocal = 0;
	int i_local; 
	double h = (b-a)/n;
	
	pthread_mutex_lock(&mutex);
	i_local = i_global; 
	i_global++;
	pthread_mutex_unlock(&mutex);

	while(i_local < n) { 
		parcialLocal=parcialLocal+(sin(pow(((a+(a+h))/2),2))); 
		a=a+h;
		pthread_mutex_lock(&mutex);
		i_local = i_global; 
		i_global++;
		pthread_mutex_unlock(&mutex);
	}
	
	parcial += h*parcialLocal;
	
	pthread_exit(NULL); 
	return 0;
} 

double quadraturaAdaptativaAux(){
	double a = intervalo_a, b = intervalo_b;	
	double base;
	double medio;
	double altura;
	double diferenca, areaMaior, areaMenor, areaMenor2;
	int i;
	
	for(i = 1; ;i++){
		base = (b - a);
		medio = (b + a)/2;
		altura = sin(pow(medio,2));
		
		//printf("Medio: %lf\n", medio);
		areaMenor = (medio - a) * altura;
		//printf("AreaMenor: %lf\n", areaMenor);
		areaMenor2 = (b - medio) * altura;
		//printf("AreaMenor2: %lf\n", areaMenor2);
		areaMaior = base * (b + a);
		//printf("AreaMaior: %lf\n", areaMaior);
		diferenca = areaMaior - (areaMenor + areaMenor2);
		//printf("Diferenca: %lf\n", diferenca);	
		
		if (diferenca <= erro){
			return i;
		}
		a = intervalo_a;
		b = medio;
		
	}	                 
}*/

//conjunto que calcula a função cos(e^-x)*(0.005 * x^3 + 1)
/*void *quadraturaAdaptativa(void *args){ 
	double a = intervalo_a;
	double b = intervalo_b;
	double parcialLocal = 0;
	int i_local; 
	double h = (b-a)/n;
	
	pthread_mutex_lock(&mutex);
	i_local = i_global; 
	i_global++;
	pthread_mutex_unlock(&mutex);

	while(i_local < n) { 
		parcialLocal=parcialLocal+(cos(pow(M_E,-1*((a+(a+h))/2))) * ((0.005 * pow(((a+(a+h))/2),3)) + 1)); 
		a=a+h;
		pthread_mutex_lock(&mutex);
		i_local = i_global; 
		i_global++;
		pthread_mutex_unlock(&mutex);
	}
	
	parcial += h*parcialLocal;
	
	pthread_exit(NULL); 
	return 0;
} 
	
double quadraturaAdaptativaAux(){
	double a = intervalo_a, b = intervalo_b;	
	double base;
	double medio;
	double altura;
	double diferenca, areaMaior, areaMenor, areaMenor2;
	int i;
	
	for(i = 1; ;i++){
		base = abs(b - a);
		medio = (b + a)/2;
		altura = cos(pow(M_E,-1*medio)) * ((0.005 * pow(medio,3)) + 1);		
		
		//printf("Medio: %lf\n", medio);
		areaMenor = (medio - a) * altura;
		//printf("AreaMenor: %lf\n", areaMenor);
		areaMenor2 = (b - medio) * altura;
		//printf("AreaMenor2: %lf\n", areaMenor2);
		areaMaior = base * (b + a);
		//printf("AreaMaior: %lf\n", areaMaior);
		diferenca = areaMaior - (areaMenor + areaMenor2);
		//printf("Diferenca: %lf\n", diferenca);	
		
		if (diferenca <= erro){
			return i;
		}
		a = intervalo_a;
		b = medio;
		
	}	                 
}*/

int main(int argc, char *argv[]) {
	
	pthread_t tid[nthreads];
  	int id[nthreads];
	int t;
	double parcial_total = 0;  
	double inicio, fim, delta1;
	
	printf("Entre com o numero de threads (1 a 8):\n");
	scanf("%d", &nthreads);
	printf("Entre com o intervalo e o erro:\n");
	scanf("%lf %lf %lf", &intervalo_a, &intervalo_b, &erro);
	
	//limita o numero de threads, caso não coloque no intervalo de 1 a 8
	if(nthreads > 8 || nthreads == 0){
		nthreads = 2;	
	}
	
	GET_TIME(inicio);
	
	n = quadraturaAdaptativaAux(intervalo_a, intervalo_b);
	
	n = pow(2, n);
	
	//inicializa o mutex (lock de exclusao mutua)
	pthread_mutex_init(&mutex, NULL);
	
	//cria as threads
	for(t=0; t<nthreads; t++) {
		id[t]=t;
		if (pthread_create(&tid[t], NULL, quadraturaAdaptativa, (void*) &id[t])) {
			printf("--ERRO: pthread_create()\n"); exit(-1);
		}
  	}

	//espera todas as threads terminarem e imprime o vetor de saída
	for(t=0; t<nthreads; t++) {
     	if (pthread_join(tid[t], NULL)) {
        	printf("--ERRO: pthread_join()\n"); exit(-1);
     	}
 	}
	
	pthread_mutex_destroy(&mutex);
	parcial_total = parcial;

	GET_TIME(fim);
	delta1 = fim - inicio;
	
	printf("Resultado da integral com %d threads: %lf\n",nthreads, parcial_total);
	printf("Tempo da aplicacao concorrente da integracao: %.8lf\n", delta1);

	//printf("--Thread principal terminou\n");
  	pthread_exit(NULL);
	
	return 0;
}