public class UF {
	
private int [] id;
	
		public UF(int N)
	{   
		id = new int[N];
		for(int i=0;i<N;i++)
			id[i]=i;
		// TODO Auto-generated constructor stub
	}
	public boolean connected(int p,int q)
	{ 
		return id[p]== id[q]; 
			
	}
	public void union(int p,int q)
	{
		int pid=id[p];
		int qid=id[q];
		for (int i=0;i<id.length;i++)
			if(id[i]==pid)id[i]=qid;
	}

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		int N = StdIn.readInt();
		UF uf=new UF(N+1);
		while (!StdIn.isEmpty())
		{
			int p= StdIn.readInt();
			int q= StdIn.readInt();
			if(!uf.connected(p,q))
			{
				uf.union(p, q);
			StdOut.println(p+" "+q);
			}
	    }
	}
}
