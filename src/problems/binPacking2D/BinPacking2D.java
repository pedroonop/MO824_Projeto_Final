package problems.binPacking2D;

import problems.Evaluator;
import solutions.Solution;

public class BinPacking2D implements Evaluator<Alocation>{
	
	public final Integer H;

	public final Integer W;
	
	public final Integer size;
	
	public final Item[] items;
	
	public BinPacking2D(Integer H, Integer W, Integer size, Item[] items) {
		this.H = H;
		this.W = W;
		this.size = size;
		this.items = items;
	}

	@Override
	public Integer getDomainSize() {
		return size;
	}

	@Override
	public Double evaluate(Solution<Alocation> sol) {
		
		boolean[] usedBin = new boolean[size];
		Double cost = 0.0;
		
		for (int i = 0; i < size; i++) {
			usedBin[i] = false;
		}
		
		for (Alocation aloc : sol) {
			if (!usedBin[aloc.position.bin]) {
				usedBin[aloc.position.bin] = true;
				cost++;
			}
		}
		
		return sol.cost = cost;
	}

	@Override
	public Double evaluateInsertionCost(Alocation elem, Solution<Alocation> sol) {
		if (elem.bin >= sol.cost) return elem.bin - sol.cost + 1;
		return 0.0;
	}

	@Override
	public Double evaluateRemovalCost(Alocation elem, Solution<Alocation> sol) {
		
		Double maximum = Double.NEGATIVE_INFINITY;
		
		for (Alocation aloc : sol) {
			if (!elem.equals(aloc)) maximum = Math.max(maximum, aloc.bin);
		}
		
		return maximum - sol.cost;
	}

	@Override
	public Double evaluateExchangeCost(Alocation elemIn, Alocation elemOut, Solution<Alocation> sol) {
		
		Double maximum = Double.NEGATIVE_INFINITY;
		
		for (Alocation aloc : sol) {
			if (!elemOut.equals(aloc)) maximum = Math.max(maximum, aloc.bin);
		}
		
		if (elemIn.bin >= maximum) return maximum - sol.cost + 1;
		
		return maximum;
	}

}
