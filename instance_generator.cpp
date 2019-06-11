#include <bits/stdc++.h>

using namespace std;

double next_double(){
	return ((double)rand())/RAND_MAX;
}

int next_int(int min, int max){
	return (rand() % (max - min + 1)) + min;
}

int next_type(double p1, double p2, double p3){
	double r = next_double();
	if (r <= p1) return 1;
	r -= p1;
	if (r <= p2) return 2;
	r -= p2;
	if (r <= p3) return 3;
	return 4;
}

int main(){
	srand(0);

	int classe, n;
	scanf("%d %d", &classe, &n);
	printf("%d\n", n);

	int H, w;
	int h_min, w_min;
	int h_max, w_max;

	if (classe == 1){
		H = W = 10;
		h_min = w_min = 1;
		h_max = w_max = 10;
		printf("%d %d\n", H, W);
		for (int i = 0; i < n; i++){
			printf("%d %d\n", next_int(h_min, h_max), next_int(w_min, w_max));
		}
	}
	else if (classe == 2){
		H = W = 30;
		h_min = w_min = 1;
		h_max = w_max = 10;
		printf("%d %d\n", H, W);
		for (int i = 0; i < n; i++){
			printf("%d %d\n", next_int(h_min, h_max), next_int(w_min, w_max));
		}		
	}
	else if (classe == 3){
		H = W = 100;
		printf("%d %d\n", H, W);
		for (int i = 0; i < n; i++){
			int nt = next_type(0.7, 0.1, 0.1);
			if (nt == 1) printf("%d %d\n", next_int(1, H / 2), next_int(2 * W / 3, W));
			if (nt == 2) printf("%d %d\n", next_int(2 * H / 3, H), next_int(1, W / 2));
			if (nt == 3) printf("%d %d\n", next_int(H / 2, H), next_int(W / 2, W));
			if (nt == 4) printf("%d %d\n", next_int(1, H / 2), next_int(1, W / 2));
		}
	}

	return 0;
}