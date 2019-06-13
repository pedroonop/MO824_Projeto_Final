#include <bits/stdc++.h>

using namespace std;

#define ii pair<int, int>
#define Item ii
#define Position pair<int, ii>
#define ff first
#define ss second
#define Alocation pair<Item, Position>
#define Solution vector<Alocation>
#define pb(x) push_back(x)

int size;
int H, W;

bool compare_W(Item a, Item b){
	return a.ss > b.ss;
}

Solution FBS(vector<Item> S){
	vector<vector<Item> > shelves;
	vector<int> acW, bigH;

	sort(S.begin(), S.end(), compare_W);

	for (Item item : S){
		int res = INT_MAX;
		int b = 0;
		for (int i = 0; i < (int)shelves.size(); i++){
			if (acW[i] + item.ss <= W && W - acW[i] - item.ss < res){
				res = W - acW[i] - item.ss;
				b = i;
			}
		}
		if (res < INT_MAX){
			acW[b] += item.ss;
			bigH[b] = max(bigH[b], item.ff);
			shelves[b].pb(item);
		}
		else{
			acW.pb(item.ss);
			bigH.pb(item.ff);
			shelves.pb(vector<Item>());
			shelves.back().pb(item);
		}
	}


	for (int i = 1; i < shelves.size(); i++){
		for (int j = i - 1; j >= 0 && bigH[j] < bigH[j + 1]; j--){
			swap(bigH[j], bigH[j + 1]);
			swap(shelves[j], shelves[j + 1]);
		}
	}

	Solution sol;
	vector<int> bin_H;

	for (int i = 0; i < shelves.size(); i++){
		int res = INT_MAX;
		int b = 0;
		for (int j = 0; j < bin_H.size(); j++){
			if (bin_H[j] + bigH[i] <= H && H - bin_H[j] - bigH[i] < res){
				res = H - bin_H[j] - bigH[i];
				b = j;
			}
		}
		if (res < INT_MAX){
			int H_ = bin_H[b], W_ = 0;
			bin_H[b] += bigH[i];
			for (Item item : shelves[i]){
				sol.pb(Alocation(item, Position(b, ii(H_, W_))));
				W_ += item.ss;
			}
		}
		else{
			int W_ = 0;
			bin_H.pb(bigH[i]);
			for (Item item : shelves[i]){
				sol.pb(Alocation(item, Position(bin_H.size() - 1, ii(0, W_))));
				W_ += item.ss;
			}
		}
	}

	return sol;
}

int compute_cost(Solution sol){
	bool used_bin[size];
	for (int i = 0; i < size; i++){
		used_bin[i] = false;
	}
	int cost = 0;
	for (Alocation aloc : sol){
		if (!used_bin[aloc.ss.ff]){
			used_bin[aloc.ss.ff] = true;
			cost++;
		}
	}
	return cost;
}

int main(){



	vector<Item> items;

	scanf("%d", &size);
	scanf("%d %d", &H, &W);
	for (int i = 0; i < size; i++){
		int h, w;
		scanf("%d %d", &h, &w);
		items.pb(Item(h, w));
	}

	Solution sol = FBS(items);
	int cost = compute_cost(sol);

	printf("%d\n", cost);

	return 0;
}