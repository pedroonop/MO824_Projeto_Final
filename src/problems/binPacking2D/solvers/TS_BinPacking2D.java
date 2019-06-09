package problems.binPacking2D.solvers;

import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;

import metaheuristics.tabusearch.AbstractTS;
import problems.binPacking2D.Alocation;
import problems.binPacking2D.BinPacking2D;
import problems.binPacking2D.Item;
import problems.binPacking2D.Position;
import solutions.Solution;

public class TS_BinPacking2D extends AbstractTS<Alocation>{
	
	private final Double EPS = 0.00001;
	
	private final Double alpha = 1.0;
	
	private final Integer size;
	
	private final Integer H;

	private final Integer W;
	
	private final Item[] items;
	
	private ArrayList<Alocation>[] bins;

	@SuppressWarnings("unchecked")
	public TS_BinPacking2D(Integer tenure, Integer iterations, Integer H, Integer W, Integer size, Item items[]) {
		super(new BinPacking2D(H, W, size, items), tenure, iterations);
		this.H = H;
		this.W = W;
		this.size = size;
		this.items = items;
		this.bins = new ArrayList[size];
		for (int i = 0; i < size; i++) {
			this.bins[i] = new ArrayList<Alocation>();
		}
	}
	
	@Override
	public Solution<Alocation> constructiveHeuristic(){
		ArrayList<Item> aux = new ArrayList<Item>();
		for (int i = 0; i < size; i++) {
			aux.add(items[i]);
		}
		Solution<Alocation> sol = FBS(aux);
		for (Alocation aloc : sol) {
			bins[aloc.position.bin].add(aloc);
		}
		return sol;
	}
	

	@Override
	public ArrayList<Alocation> makeCL() {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public ArrayList<Alocation> makeRCL() {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public ArrayDeque<Alocation> makeTL() {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public void updateCL() {
		// TODO Auto-generated method stub
		
	}

	@Override
	public Solution<Alocation> createEmptySol() {
		// TODO Auto-generated method stub
		return null;
	}
	
	private Solution<Alocation> FBS(ArrayList<Item> S){
		
		ArrayList<ArrayList<Item>> shelves = new Solution<ArrayList<Item>>();
		ArrayList<Integer> acW = new ArrayList<Integer>();
		ArrayList<Integer> biggestH = new ArrayList<Integer>();
		shelves.add(new ArrayList<Item>());
		acW.add(0);
		biggestH.add(0);
		
		Collections.sort(S, new Comparator<Item>() {
			public int compare(Item arg0, Item arg1) {
				return arg1.w.compareTo(arg0.w);
			}
		});
		
		for (Item item : S) {
			Integer res = Integer.MAX_VALUE;
			Integer b = 0;
			for (int i = 0; i < shelves.size(); i++) {
				if (acW.get(i) + item.w <= W && W - acW.get(i) - item.w < res) {
					res = W - acW.get(i) - item.w;
					b = i;
				}
			}
			if (res < Integer.MAX_VALUE) {
				acW.set(b, acW.get(b) + item.w);
				biggestH.set(b, Math.max(biggestH.get(b), item.h));
				shelves.get(b).add(item);				
			}
			else {
				acW.add(item.w);
				biggestH.add(item.h);
				shelves.add(new ArrayList<Item>());
				shelves.get(shelves.size() - 1).add(item);
			}
		}
		
		for (int i = 1; i < shelves.size(); i++) {
			for (int j = i - 1; j >= 0; j--) {
				if (biggestH.get(j) < biggestH.get(j + 1)) {
					Collections.swap(biggestH, j, j + 1);
					Collections.swap(shelves, j, j + 1);
				}
			}
		}
		
		Solution<Alocation> sol = new Solution<Alocation>();		
		ArrayList<Integer> binH = new ArrayList<Integer>();
		
		for (int i = 0; i < shelves.size(); i++) {
			Integer res = Integer.MAX_VALUE;
			Integer b = 0;
			for (int j = 0; j < binH.size(); j++) {
				if (binH.get(j) + biggestH.get(i) <= H && H - binH.get(j) - biggestH.get(i) < res) {
					res = H - binH.get(j) - biggestH.get(i);
					b = j;
				}
			}
			if (res < Integer.MAX_VALUE) {
				Integer H_ = binH.get(b), W_ = 0;
				binH.set(b, binH.get(b) + biggestH.get(i));
				for (Item item : shelves.get(i)) {
					sol.add(new Alocation(item, new Position(binH.size() - 1, H_, W_)));
					W_ += item.w;
				}				
			}
			else {
				Integer W_= 0;
				binH.add(biggestH.get(i));
				for (Item item : shelves.get(i)) {
					sol.add(new Alocation(item, new Position(binH.size() - 1, 0, W_)));
					W_ += item.w;
				}
			}
		}
		
		ObjFunction.evaluate(sol);
		
		return sol;
	}

	@Override
	public Solution<Alocation> neighborhoodMove() {
		
		Double z = incumbentSol.cost;
		
		Double minimum = Double.POSITIVE_INFINITY;
		Integer b = 0;
		
		Double phi[] = new Double[size];
		for (int i = 0; i < size; i++) {
			phi[i] = 0.0;
			for (Alocation aloc : bins[i]) {
				phi[i] += (aloc.item.h * aloc.item.w);
			}
			phi[i] = phi[i] * (alpha/(H * W));
			phi[i] -= (bins[i].size() * 1.0)/size;
			if (phi[i] < minimum) {
				minimum = phi[i];
				b = i;
			}
		}
		
		
		
		return null;
	}

}
