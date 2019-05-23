package problems.binPacking2D;

public class Item {
	
	public final Integer h;
	
	public final Integer w;
	
	public Item(Integer h, Integer w) {
		this.h = h;
		this.w = w;
	}
	
	public boolean equals(Item i) {
		return h == i.h && w == i.w;
	}

}
