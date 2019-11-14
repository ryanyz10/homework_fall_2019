import java.util.Scanner;
import java.util.Arrays;
import java.util.Stack;
 
 
public class MysteriousPresent {
    public static void main(String[] args) {
        new MysteriousPresent();
    }
 
    MysteriousPresent() {
        Scanner reader = new Scanner(System.in);
        int n = reader.nextInt();
        int w = reader.nextInt();
        int h = reader.nextInt();
 
        Envelope[] envelopes = new Envelope[n];
 
        for (int i = 0; i < n; i++) {
            envelopes[i] = new Envelope(i + 1, reader.nextInt(), reader.nextInt());
        }
 
        Arrays.sort(envelopes);
 
        // max chain using ith envelope
        int[] dp = new int[n];
        for (int i = 0; i < n; i++) {
            int currWidth = envelopes[i].width;
            int currHeight = envelopes[i].height;
 
            if (currWidth <= w || currHeight <= h) {
                dp[i] = 0;
            } else {
                int max = 0;
                int maxNum = -1;
                // check the smaller envelopes
                for (int j = i - 1; j >= 0; j--) {
                    int prevWidth = envelopes[j].width;
                    int prevHeight = envelopes[j].height;
 
                    if (prevWidth < currWidth && prevHeight < currHeight) {
                        if (dp[j] > max) {
                            max = dp[j];
                            maxNum = j;
                        }
                    }
                }
 
                dp[i] = max + 1;
                envelopes[i].parent = maxNum;
            }
        }
 
        /*
        for (int i = 0; i < n; i++) {
            System.out.println(i + ", " + envelopes[i].num + ", " + envelopes[i].parent + ": " + dp[i]);
        }
        */
 
        int max = 0;
        int env = 0;
 
        Stack<Integer> stack = new Stack<>();
        for (int i = 0; i < n; i++) {
            if (dp[i] > max) {
                max = dp[i];
                env = i;
            }
        }
 
        if (max == 0) {
            System.out.println(0);
            reader.close();
            return;
        }
 
        while (env >= 0) {
            stack.push(envelopes[env].num);
            env = envelopes[env].parent;
        }
 
        System.out.println(max);
        while (!stack.isEmpty()) {
            System.out.print(stack.pop() + " ");
        }
        System.out.println();
 
        reader.close();
    }
 
    class Envelope implements Comparable<Envelope> {
        int num;
        int parent;
        int width;
        int height;
 
        Envelope(int num, int width, int height) {
            this.num = num;
            this.width = width;
            this.height = height;
        }
 
        @Override
        public int compareTo(Envelope other) {
            double thisArea = (double)this.width * (double)this.height;
            double otherArea = (double)other.width * (double)other.height;
            if (thisArea < otherArea) {
                return -1;
            } else if (thisArea == otherArea) {
                return 0;
            } else {
                return 1;
            }
        }
    }
}
