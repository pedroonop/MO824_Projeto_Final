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

int iterations, tenure;
list<Item> TL1;

int H, W;
int n, size;
vector<Item> items;
vector<vector<Alocation> > bins;

const double alpha = 1.0;
const Item fake = Item(-1, -1);

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

void organize(){
	int i = 0, j = size - 1;
	while (i < j){
		while (i < size && bins[i].size() != 0) i++;
		while (j >= 0 && bins[j].size() == 0) j--;
		if (i < size && j >= 0 && i < j) swap(bins[i], bins[j]);
	}
	for (int i = 0; i < size; i++){
		for (int j = 0; j < bins[i].size(); j++){
			bins[i][j].ss.ff = i;
		}
	}
}

void unpack(Solution sol){
	for (int i = 0; i < size; i++) bins[i].clear();
	for (Alocation aloc : sol){
		bins[aloc.ss.ff].pb(aloc);
	}
}

Solution pack(){
	Solution sol;
	for (int i = 0; i < size; i++){
		for (Alocation aloc : bins[i]){
			sol.pb(aloc);
		}
	}
	return sol;
}

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

void show_solution(Solution sol){
	for (Alocation aloc : sol){
		printf("(h: %d w: %d) bin: %d h_: %d w_: %d\n", aloc.ff.ff, aloc.ff.ss, aloc.ss.ff, aloc.ss.ss.ff, aloc.ss.ss.ss);
	}	
}

Solution initial_solution(vector<Item> items){
	Solution sol;
	for (int i = 0; i < items.size(); i++){
		sol.pb(Alocation(items[i], Position(i, ii(0, 0))));
	}
	return sol;
}

double compute_phi(int i){
	double phi = 0;
	for (Alocation aloc : bins[i]){
		phi += (aloc.ff.ff * aloc.ff.ss);
	}
	phi *= (alpha/(H * W));
	phi -= (bins[i].size() * 1.0)/size;
	return phi;		
}

double compute_phi(vector<Item> v){
	double phi = 0;
	for (Item item : v){
		phi += (item.ff * item.ss);
	}
	phi *= (alpha/(H * W));
	phi -= (v.size() * 1.0)/size;
	return phi;	
}

int weakest_bin(){
	double minimum = INT_MAX;
	int b = 0;

	for (int i = 0; i < size; i++){
		if (bins[i].size() == 0) continue;
		double phi = compute_phi(i);
		if (phi < minimum){
			minimum = phi;
			b = i;
		}
	}

	return b;
}

bool is_tabu(Item item){
	for (Item item_ : TL1){
		if (item == item_) return true;
	}
	return false;
}

bool contains(Item i, vector<Item> v){
	for (Item i_ : v){
		if (i == i_) return true;
	}
	return false;
}

bool first_neighborhood(){
	int b = weakest_bin();
	bool removed[bins[b].size()];
	for (int i = 0; i < bins[b].size(); i++) removed[i] = false;
	bool flag = false;
	for (int j = 0; j < bins[b].size(); j++){
		if (bins[b].size() > 1 && is_tabu(bins[b][j].ff)) continue;
		for (int i = 0; i < size; i++){
			if (i == b || bins[i].size() == 0) continue;
			vector<Item> Si;
			for (Alocation aloc : bins[i]) Si.pb(aloc.ff);
			Si.pb(bins[b][j].ff);
			Solution sol = FBS(Si);
			int cost = compute_cost(sol);
			if (cost == 1){
				bins[i].clear();
				for (Alocation aloc : sol){
					bins[i].pb(Alocation(aloc.ff, Position(i, aloc.ss.ss)));
				}
				TL1.pb(bins[b][j].ff);
				TL1.pop_front();
				removed[j] = true;
				flag = true;
				break;
			}
		}
	}
	vector<Alocation> aux;
	for (int j = 0; j < bins[b].size(); j++){
		if (!removed[j]) aux.pb(bins[b][j]);
	}
	bins[b] = aux;
	if (!flag){
		TL1.pop_front();
		TL1.pb(fake);
	}
	return flag;
}

int second_neighborhood(){
	int b = weakest_bin();
	for (int j = 0; j < bins[b].size(); j++){
		for (int h = 0; h < size; h++){
			if (h == b || bins[h].size() == 0) continue;
			for (int k = 0; k < size; k++){
				if (k == b || k == h || bins[k].size() == 0) continue;
				vector<Item> S;
				S.pb(bins[b][j].ff);
				for (Alocation aloc : bins[h]) S.pb(aloc.ff);
				for (Alocation aloc : bins[k]) S.pb(aloc.ff);
				Solution sol = FBS(S);
				int cost = compute_cost(sol);
				if (cost == 1){
					bins[h].clear();
					bins[k].clear();
					for (Alocation aloc : sol){
						if (aloc.ss.ff == 0) bins[h].pb(Alocation(aloc.ff, Position(h, aloc.ss.ss)));
						else bins[k].pb(Alocation(aloc.ff, Position(k, aloc.ss.ss)));
					}
					bins[b].erase(bins[b].begin() + j);
					return 1;
				}
				else if (cost == 2){
					bins[h].clear();
					bins[k].clear();
					for (Alocation aloc : sol){
						if (aloc.ss.ff == 0) bins[h].pb(Alocation(aloc.ff, Position(h, aloc.ss.ss)));
						else bins[k].pb(Alocation(aloc.ff, Position(k, aloc.ss.ss)));
					}
					bins[b].erase(bins[b].begin() + j);
					if (bins[b].empty()) return 21;
					else{
						double phib = compute_phi(b), phih = compute_phi(h), phik = compute_phi(k);
						if (phib < phih && phib < phik) return 221;
					}
				}
			}
		}
	}
	return 4;
}

void neighborhood_move(){
	while (iterations--){
		while (first_neighborhood()) organize();
		int code = second_neighborhood();
		while (code != 1 && code != 21 && code != 221 && code != 4){
			code = second_neighborhood();
			organize();
		}
	}
	organize();
}

int main(){

	iterations = 100;
	tenure = 3;

	for (int i = 0; i < tenure; i++){
		TL1.pb(fake);
	}

	H = W = 10;

	items.pb(Item(6,6));
	items.pb(Item(6,4));
	items.pb(Item(5,5));
	items.pb(Item(4,10));
	items.pb(Item(1,1));
	items.pb(Item(2,2));
	items.pb(Item(9,10));
	items.pb(Item(1,10));
	items.pb(Item(1,9));
	items.pb(Item(2,10));
	n = size = items.size();

	bins.resize(size);


//	Solution sol = FBS(items);
	Solution sol = initial_solution(items);
	unpack(sol);

	neighborhood_move();

	show_solution(pack());

	printf("\n");

	show_solution(FBS(items));

	return 0;
}