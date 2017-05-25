/* Disciplina: Computacao Concorrente */
/* Prof.: Silvana Rossetto */
/* Trabalho 1 */
/* Nome: Jéssica Genta dos Santos e Sidney Ribeiro Ramos Júnior*/

#include <stdio.h>
#include <stdlib.h> 
#include <math.h>
#include "timer.h"

double erro;

//conjunto que calcula a função 1 + x
double quadraturaAdaptativa(double intervalo_a, double intervalo_b, int n) { 
	double parcial = 0;
	double a = intervalo_a, b = intervalo_b;
	double h = (b-a)/n;
	int i;
	
	for (i = 0; i < n; i++){ 
		parcial=parcial+(1 +((a+(a+h))/2)); 
		a=a+h; 
	}
	return (h*parcial); 
} 
	
double quadraturaAdaptativaAux(double intervalo_a, double intervalo_b){
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
		
		printf("Ponto Medio: %lf\n", medio);
		areaMenor = (medio - a) * altura;
		//printf("AreaMenor: %lf\n", areaMenor);
		areaMenor2 = (b - medio) * altura;
		//printf("AreaMenor2: %lf\n", areaMenor2);
		areaMaior = base * (b + a);
		//printf("AreaMaior: %lf\n", areaMaior);
		diferenca = areaMaior - (areaMenor + areaMenor2);
		printf("Diferenca: %lf\n", diferenca);	
		
		if (diferenca <= erro){
			return i;
		}
		a = intervalo_a;
		b = medio;
		
	}	                 
}

//conjunto que calcula a função sqrt(1 - x^2)
/*double quadraturaAdaptativa(double intervalo_a, double intervalo_b, int n) { 
	double parcial = 0;
	double a = intervalo_a, b = intervalo_b;
	double h = (b-a)/n;
	int i;
	
	for (i = 0; i < n; i++){ 
		parcial=parcial+(sqrt(1 - pow(((a+(a+h))/2),2))); 
		a=a+h; 
	}
	return (h*parcial); 
} 
	
double quadraturaAdaptativaAux(double intervalo_a, double intervalo_b){
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
		
		printf("Ponto Medio: %lf\n", medio);
		areaMenor = (medio - a) * altura;
		//printf("AreaMenor: %lf\n", areaMenor);
		areaMenor2 = (b - medio) * altura;
		//printf("AreaMenor2: %lf\n", areaMenor2);
		areaMaior = base * (b + a);
		//printf("AreaMaior: %lf\n", areaMaior);
		diferenca = areaMaior - (areaMenor + areaMenor2);
		printf("Diferenca: %lf\n", diferenca);	
		
		if (diferenca <= erro){
			return i;
		}
		a = intervalo_a;
		b = medio;
		
	}	                 
}*/

//conjunto que calcula a função sqrt(1 + x^4)
/*double quadraturaAdaptativa(double intervalo_a, double intervalo_b, int n) { 
	double parcial = 0;
	double a = intervalo_a, b = intervalo_b;
	double h = (b-a)/n;
	int i;
	
	for (i = 0; i < n; i++){ 
		parcial=parcial+(sqrt(1 + pow(((a+(a+h))/2),4))); 
		a=a+h; 
	}
	return (h*parcial); 
} 
	
double quadraturaAdaptativaAux(double intervalo_a, double intervalo_b){
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
		
		printf("Ponto Medio: %lf\n", medio);
		areaMenor = (medio - a) * altura;
		//printf("AreaMenor: %lf\n", areaMenor);
		areaMenor2 = (b - medio) * altura;
		//printf("AreaMenor2: %lf\n", areaMenor2);
		areaMaior = base * (b + a);
		//printf("AreaMaior: %lf\n", areaMaior);
		diferenca = areaMaior - (areaMenor + areaMenor2);
		diferenca = -1 * diferenca;
		printf("Diferenca: %lf\n", diferenca);	
		
		if (diferenca <= erro){
			return i;
		}
		a = intervalo_a;
		b = medio;
		
	}	                 
}*/

//conjunto que calcula a função sen(x^2)
/*double quadraturaAdaptativa(double intervalo_a, double intervalo_b, int n) { 
	double parcial = 0;
	double a = intervalo_a, b = intervalo_b;
	double h = (b-a)/n;
	int i;
	
	for (i = 0; i < n; i++){ 
		parcial=parcial+(sin(pow(((a+(a+h))/2),2))); 
		a=a+h; 
	}
	return (h*parcial); 
} 
	
double quadraturaAdaptativaAux(double intervalo_a, double intervalo_b){
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
		
		printf("Ponto Medio: %lf\n", medio);
		areaMenor = (medio - a) * altura;
		//printf("AreaMenor: %lf\n", areaMenor);
		areaMenor2 = (b - medio) * altura;
		//printf("AreaMenor2: %lf\n", areaMenor2);
		areaMaior = base * (b + a);
		//printf("AreaMaior: %lf\n", areaMaior);
		diferenca = areaMaior - (areaMenor + areaMenor2);
		printf("Diferenca: %lf\n", diferenca);	
		
		if (diferenca <= erro){
			return i;
		}
		a = intervalo_a;
		b = medio;
		
	}	                 
}*/

//conjunto que calcula a função cos(e^-x)*(0.005 * x^3 + 1)
/*double quadraturaAdaptativa(double intervalo_a, double intervalo_b, int n) { 
	double parcial = 0;
	double a = intervalo_a, b = intervalo_b;
	double h = (b-a)/n;
	int i;
	
	for (i = 0; i < n; i++){ 
		parcial=parcial+(cos(pow(M_E,-1*((a+(a+h))/2))) * ((0.005 * pow(((a+(a+h))/2),3)) + 1)); 
		a=a+h; 
	}
	return (h*parcial); 
} 
	
double quadraturaAdaptativaAux(double intervalo_a, double intervalo_b){
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
		
		printf("Ponto Medio: %lf\n", medio);
		areaMenor = (medio - a) * altura;
		//printf("AreaMenor: %lf\n", areaMenor);
		areaMenor2 = (b - medio) * altura;
		//printf("AreaMenor2: %lf\n", areaMenor2);
		areaMaior = base * (b + a);
		//printf("AreaMaior: %lf\n", areaMaior);
		diferenca = areaMaior - (areaMenor + areaMenor2);
		printf("Diferenca: %lf\n", diferenca);	
		
		if (diferenca <= erro){
			return i;
		}
		a = intervalo_a;
		b = medio;
		
	}	                 
}*/

int main(void) {
	
  	double intervalo_a, intervalo_b;
	int n;
	double integral = 0;
	double inicio, fim, delta1;
	
	printf("Entre com o intervalo e o erro:\n");
	scanf("%lf %lf %lf", &intervalo_a, &intervalo_b, &erro);
	
	GET_TIME(inicio);
	
	n = quadraturaAdaptativaAux(intervalo_a, intervalo_b);
	n = pow(2, n);
	integral = quadraturaAdaptativa(intervalo_a, intervalo_b, n);
	
	GET_TIME(fim);
	delta1 = fim - inicio;
	
	printf("Resultado da integral: %lf\n", integral);
	printf("Tempo de execucao da integracao: %.8lf\n", delta1);
	
	return 0;
}