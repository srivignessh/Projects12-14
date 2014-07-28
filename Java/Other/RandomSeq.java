public class RandomSeq { 
    public static void main(String[] args) {

        // command-line argument
        int N = Integer.parseInt(args[0]);

        // generate and print N numbers between 0 and 1
        for (int i = 0; i < N; i++) {
            System.out.println(Math.random());
        }
    }
}