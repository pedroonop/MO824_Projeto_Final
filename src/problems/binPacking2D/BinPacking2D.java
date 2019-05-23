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
		
		Double maximum = Double.NEGATIVE_INFINITY;
		
		for (Alocation aloc : sol) {
			maximum = Math.max(maximum, aloc.bin);
		}
		
		return maximum + 1;
	}

	@Override
	public Double evaluateInsertionCost(Alocation elem, Solution<Alocation> sol) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public Double evaluateRemovalCost(Alocation elem, Solution<Alocation> sol) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public Double evaluateExchangeCost(Alocation elemIn, Alocation elemOut, Solution<Alocation> sol) {
		// TODO Auto-generated method stub
		return null;
	}

}
