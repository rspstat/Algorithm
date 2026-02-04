import java.io.*;
import java.util.*;

public class Main {
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(br.readLine().trim());

        int[][] cls = new int[n][5];

        for (int i = 0; i < n; i++) {
            StringTokenizer st = new StringTokenizer(br.readLine());
            for (int y = 0; y < 5; y++) {
                cls[i][y] = Integer.parseInt(st.nextToken());
            }
        }

        int bestIdx = 0;
        int bestCount = -1;

        for (int i = 0; i < n; i++) {
            int cnt = 0;

            for (int j = 0; j < n; j++) {
                if (i == j) continue;

                boolean same = false;
                for (int y = 0; y < 5; y++) {
                    if (cls[i][y] == cls[j][y]) {
                        same = true;
                        break;
                    }
                }
                if (same) cnt++;
            }

            // 동점이면 더 작은 번호(=더 앞 인덱스)가 유지되도록 ">"만 사용
            if (cnt > bestCount) {
                bestCount = cnt;
                bestIdx = i;
            }
        }

        System.out.print(bestIdx + 1);
    }
}
