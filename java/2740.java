import java.util.*;
import java.io.*;

public class Main {
    static BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

    static int[][] readMatrix(int r, int c) throws Exception {
        int[][] mat = new int[r][c];

        for (int i = 0; i < r; i++) {
            StringTokenizer st = new StringTokenizer(br.readLine());
            for (int j = 0; j < c; j++) {
                mat[i][j] = Integer.parseInt(st.nextToken());
            }
        }

        return mat;
    }

    public static void main(String[] args) throws Exception {
        StringTokenizer st = new StringTokenizer(br.readLine());

        int n = Integer.parseInt(st.nextToken());
        int m = Integer.parseInt(st.nextToken());
        int[][] A = readMatrix(n, m);

        st = new StringTokenizer(br.readLine());
        int m2 = Integer.parseInt(st.nextToken());
        int k = Integer.parseInt(st.nextToken());
        int[][] B = readMatrix(m2, k);

        int[][] C = new int[n][k];
        for (int i = 0; i < n; i++) {
            for (int t = 0; t < m; t++) {
                int a = A[i][t];
                for (int j = 0; j < k; j++) {
                    C[i][j] += a * B[t][j];
                }
            }
        }

        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < k; j++) {
                sb.append(C[i][j]).append(j + 1 == k ? '\n' : ' ');
            }
        }

        System.out.print(sb.toString());
    }
}
