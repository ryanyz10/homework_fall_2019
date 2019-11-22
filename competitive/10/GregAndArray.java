import java.util.*;

public class GregAndArray {
    public static void main(String[] args) {
        Scanner reader = new Scanner(System.in);

        int n = reader.nextInt();
        int m = reader.nextInt();
        int k = reader.nextInt();

        long[] arr = new long[n];
        for (int i = 0; i < n; i++) {
            arr[i] = reader.nextLong();
        }

        int[][] operations = new int[m][3];

        for (int i = 0; i < m; i++) {
            int l = reader.nextInt();
            int r = reader.nextInt();
            int d = reader.nextInt();

            int[] operation = {l, r, d};
            operations[i] = operation;
        }


        long[] diffs = new long[n];
        int[] freqs = new int[m];

        for (int i = 0; i < k; i++) {
            int x = reader.nextInt();
            int y = reader.nextInt();

            freqs[x - 1] += 1;
            if (y < m) {
                freqs[y] -= 1;
            }
        }

        int times = 0;
        for (int i = 0; i < m; i++) {
            int[] op = operations[i];
            int l = op[0];
            int r = op[1];
            int d = op[2];

            times += freqs[i];
            diffs[l] += times * d;
            if (r < n) {
                diffs[r] -= times * d;
            }
        }

        /*
        for (int i = 0; i < n; i++) {
            System.out.print(diffs[i] + " ");
        }

        System.out.println();
        */

        int prefixSum = 0;
        for (int i = 0; i < n; i++) {
            prefixSum += diffs[i];
            System.out.print(arr[i] + prefixSum + " ");
        }

        System.out.println();
        reader.close();
    }

}