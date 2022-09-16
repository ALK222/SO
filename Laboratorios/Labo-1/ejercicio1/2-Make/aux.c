#include <math.h>

double pi = M_PI;

double senGrados(double x) {
	double rad = (x*M_PI/180);
	return sin(rad);
}

double cosGrados(double x) {
	double rad = (x*M_PI/180);
	return cos(rad);
}
