package problems.binPacking2D;

public class Position {
	
	private Integer h;
	private Integer w;
	private Integer bin;
	
	public Position(Integer h, Integer w, Integer bin) {
		this.h = h;
		this.w = w;
		this.bin = bin;
	}

	public Integer getH() {
		return h;
	}

	public void setH(Integer h) {
		this.h = h;
	}

	public Integer getW() {
		return w;
	}

	public void setW(Integer w) {
		this.w = w;
	}

	public Integer getBin() {
		return bin;
	}

	public void setBin(Integer bin) {
		this.bin = bin;
	}

}
