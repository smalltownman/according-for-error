#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define _USE_MATH_DEFINES
#include <cmath>


typedef float FP;

inline FP TY(FP x, FP y) {
	return - y * tan(x) - 1.0 / cos(x);
}
inline FP YT(FP x) {
	return cos(x) - sin(x);
}

const char gnuplot[] = "\"C:\\Program Files\\gnuplot\\bin\\gnuplot.exe\" -persist";


int main(int argc, char * argv[]) {
	

#pragma region colculated
	FP x1 = M_PI / 4.0, x2 = 1.292695729373;
	FP x = 0.0, y = 0.0, newy = 0.0, z = 0.0, term = 0.0, dx1 = 0.0;
	FP x_1 = 0.0, y_1 = 0.0, z_1 = 0.0, term_1 = 0.0, newy_1 = 0.0, dx2 = 0.0;
	FP y1 = YT(x1), y2 = YT(x2);

	int i;
	int N, j;
	FILE * f = fopen("two.txt", "w");
	for (i = 1; i <=27; i++) {

		N = (int)pow(2.0, i);
		dx1 = (FP)x1 / N;
		dx2 = (FP)x2 / N;
		y = 1.0;
		x = 0.0;
		y_1 = 1.0;
		x_1 = 0.0;
		for (j = 1; j <= N; j++) {

			
			term = dx1 * TY(x, y) +z;
			newy = y + term;
			z = term - (newy - y);
			y = newy;
			x = j * dx1;

			term_1 = dx2 * TY(x_1, y_1) + z_1;
			newy_1 = y_1 + term_1;
			z_1 = term_1 - (newy_1 - y_1);
			y_1 = newy_1;
			x_1 = j * dx2;
		}
		fprintf(f, "%12.9le\t%12.9le\t%12.9le\n",  double(1.0 / N), fabs(newy - y1), fabs(newy_1 - y2));
	}
	fclose(f);
#pragma endregion


#pragma region drawing a graph

	FILE * pipe = _popen(gnuplot, "w");
	fprintf(pipe,
		"set terminal postscript eps enhanced\n"
		"set terminal pngcairo size 40cm, 20cm font \'Times, 10\'\n"

		"set output \'curve1.png\'\n"

	
		"set grid lw 1\n"

		"set multiplot layout 1, 2 rowsfirst\n"

		"set format y \"10^{%%L}\"\n"
		"set format x \"10^{%%L}\"\n"
		"set log y\n"
		"set log x\n"
		"set autoscale y\n"
		"set autoscale x\n"

		
		"plot	\'two.txt\' using 1:2 notitle  w l lc rgb\'#008072\'\n"

		
		"plot	\'two.txt\'  using 1:3 notitle  w l lc rgb\'#008072\'\n"

		
	"unset multiplot\n");
	_pclose(pipe);

#pragma endregion


	return 0;
}