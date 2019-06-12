#include <bits/stdc++.h>

using namespace std;

#define ii pair<int, int>
#define ff first
#define ss second

int H, W;
int h_min, w_min;
int h_max, w_max;

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

ii next_item(int nt){
	if (nt == 1) return ii(next_int(1, H / 2), next_int(2 * W / 3, W));
	if (nt == 2) return ii(next_int(2 * H / 3, H), next_int(1, W / 2));
	if (nt == 3) return ii(next_int(H / 2, H), next_int(W / 2, W));
	if (nt == 4) return ii(next_int(1, H / 2), next_int(1, W / 2));
	return ii(-1,-1);
}

int main(){

	int classe, n;
	scanf("%d %d", &classe, &n);

	int seed;
	scanf("%d", &seed);
	srand(seed);


	if (classe == 1 || classe == 2){
		printf("%d\n", n);
		if (classe == 1) H = W = 10;
		else H = W = 30;
		h_min = w_min = 1;
		h_max = w_max = 10;
		printf("%d %d\n", H, W);
		for (int i = 0; i < n; i++){
			printf("%d %d\n", next_int(h_min, h_max), next_int(w_min, w_max));
		}
	}
	else if (classe <= 6){
		printf("%d\n", n);
		H = W = 100;
		printf("%d %d\n", H, W);
		double p1, p2, p3;
		if (classe == 3){
			p1 = 0.7;
			p2 = 0.1;
			p3 = 0.1;
		}
		if (classe == 4){
			p1 = 0.1;
			p2 = 0.7;
			p3 = 0.1;
		}
		else if (classe == 5){
			p1 = 0.1;
			p2 = 0.1;
			p3 = 0.7;
		}
		else{
			p1 = p2 = p3 = 0.1;
		}
		for (int i = 0; i < n; i++){
			ii item = next_item(next_type(p1, p2, p3));
			printf("%d %d\n", item.ff, item.ss);
		}
	}
	else{
		printf("Classe invalida\n");
	}

	return 0;
}