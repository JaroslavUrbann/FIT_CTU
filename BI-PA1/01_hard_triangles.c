#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>
#include <string.h>

#define WRONG_INPUT {printf("Nespravny vstup.\n"); exit(1);}
#define WRONG_DATA {printf("Vstup netvori trojuhelnik.\n"); exit(1);}
#define ARE_IDENTICAL {printf("Trojuhelniky jsou shodne.\n"); exit(0);}
#define ARE_SIMILAR {printf("Trojuhelniky nejsou shodne, ale jsou podobne.\n"); exit(0);}
#define NOT_SAME_OR_SIMILAR printf("Trojuhelniky nejsou shodne ani podobne.\n"); exit(0);


void convert_sus(double* a, double* b, double* c){
	if (*b >= 180)
		WRONG_INPUT
	*b = sqrt(*a * *a + *c * *c - 2 * *a * *c *cos(*b * M_PI / 180));
}

void convert_usu(double* a, double* b, double* c){
	if (*a >= 180 || *c >= 180)
		WRONG_INPUT
	double tmp_a = *b * sin(*a * M_PI / 180) / sin((*a + *c) * M_PI / 180);
	*c = *b * sin(*c * M_PI / 180) / sin((*a + *c) * M_PI / 180);
	*a = tmp_a;
}


void get_triangle(double* a, double* b, double* c, int triangle_n){
	char type[3];

	printf("Trojuhelnik #%d:\n", triangle_n);
	
	if (scanf(" %c%c%c", &type[0], &type[1], type[2]) != 3)
		WRONG_INPUT

	if (scanf("%lf%lf%lf", a, b, c) != 3 || *a <= 0 || *b <= 0 || *c <= 0)
		WRONG_INPUT

	if (!strcmp(type, "SUS"))
		convert_sus(a, b, c);

	else if (!strcmp(type, "USU"))
		convert_usu(a, b, c);

	else if (strcmp(type, "SSS"))
		WRONG_INPUT
}


void check_triangularity(double* a, double* b, double* c){
	if (*b + *c - *a <= 100 * DBL_EPSILON * *a)
		WRONG_DATA
}

void sort_sides(double* a, double* b, double* c){
	if (*a < *b){
		double tmp = *a;
		*a = *b;
		*b = tmp;
	}
	if (*a < *c){
		double tmp = *a;
		*a = *c;
		*c = tmp;
	}
	if (*b < *c){
		double tmp = *b;
		*b = *c;
		*c = tmp;
	}
}


void get_data(double* a, double* b, double* c, double* d, double* e, double* f){
	get_triangle(a, b, c, 1);
	sort_sides(a, b, c);
	check_triangularity(a, b, c);

	get_triangle(d, e, f, 2);
	sort_sides(d, e, f);
	check_triangularity(d, e, f);
}


int are_sides_identical(double* a, double* b, double* c, double* d, double* e, double* f){
	return (fabs(*a - *d) <= 100 * DBL_EPSILON * *a
		 && fabs(*b - *e) <= 100 * DBL_EPSILON * *b
		 && fabs(*c - *f) <= 100 * DBL_EPSILON * *c);
}


int are_sides_same_ratio(double* a, double* b, double* c, double* d, double* e, double* f){
	return fabs((*a / *d) - (*b / *e)) <= 100 * DBL_EPSILON * (*a / *d)
		&& fabs((*a / *d) - (*c / *f)) <= 100 * DBL_EPSILON * (*a / *d);
}


void check_similarity(double* a, double* b, double* c, double* d, double* e, double* f){
	if (are_sides_same_ratio(a, b, c, d, e, f))
		ARE_SIMILAR
}


void check_identicality(double* a, double* b, double* c, double* d, double* e, double* f){
	if (are_sides_identical(a, b, c, d, e, f))
		ARE_IDENTICAL
}


int main(){
	double a, b, c, d, e, f;
	get_data(&a, &b, &c, &d, &e, &f);
	check_identicality(&a, &b, &c, &d, &e, &f);
	check_similarity(&a, &b, &c, &d, &e, &f);
	NOT_SAME_OR_SIMILAR
}
