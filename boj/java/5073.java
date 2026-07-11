import java.io.*;
import java.util.*;

public class Main {
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringBuilder sb = new StringBuilder();

        while (true) {
            String line = br.readLine();
            if (line == null) break;

            StringTokenizer st = new StringTokenizer(line);
            int a = Integer.parseInt(st.nextToken());
            int b = Integer.parseInt(st.nextToken());
            int c = Integer.parseInt(st.nextToken());

            if (a == 0 && b == 0 && c == 0) break;

            int[] v = {a, b, c};
            Arrays.sort(v); // v[2]가 가장 긴 변

            if (v[0] + v[1] <= v[2]) {
                sb.append("Invalid\n");
            } else if (v[0] == v[1] && v[1] == v[2]) {
                sb.append("Equilateral\n");
            } else if (v[0] == v[1] || v[1] == v[2] || v[0] == v[2]) {
                sb.append("Isosceles\n");
            } else {
                sb.append("Scalene\n");
            }
        }

        System.out.print(sb.toString());
    }
}
