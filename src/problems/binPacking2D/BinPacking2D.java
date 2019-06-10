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
		return null;
	}

	@Override
	public Double evaluateRemovalCost(Alocation elem, Solution<Alocation> sol) {
		return null;
	}

	@Override
	public Double evaluateExchangeCost(Alocation elemIn, Alocation elemOut, Solution<Alocation> sol) {
		return null;
	}

}
