package problems.binPacking2D;

public class Alocation {
		
	public Item item;
	
	public Integer bin;
	
	public Integer h;
	
	public Integer w;
	
	public Alocation(Integer bin, Integer h, Integer w) {
		this.bin = bin;
		this.h = h;
		this.w = w;
	}
	
	public boolean equals(Alocation a) {
		return this.item.equals(a.item) && bin == a.bin && h == a.h && w == a.w;
	}
	
}
