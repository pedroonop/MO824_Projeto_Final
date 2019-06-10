package problems.binPacking2D;

public class Alocation {
		
	public Item item;
	
	public Position position;
	
	public Alocation(Item item, Position position) {
		this.item = item;
		this.position = position;
	}
	
	public boolean equals(Alocation a) {
		return this.item.equals(a.item) && bin == a.bin && h == a.h && w == a.w;
	}
	
}
