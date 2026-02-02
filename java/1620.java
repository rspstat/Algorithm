import java.util.*;
import java.io.*;

public class Main {
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());

        int N = Integer.parseInt(st.nextToken());
        int M = Integer.parseInt(st.nextToken());

        // 번호 -> 이름 (1부터 시작)
        String[] idxToName = new String[N + 1];
        // 이름 -> 번호 (넉넉히)
        HashMap<String, Integer> nameToIdx = new HashMap<>(N * 2);

        for (int i = 1; i <= N; i++) {
            String name = br.readLine();
            idxToName[i] = name;
            nameToIdx.put(name, i);
        }

        StringBuilder sb = new StringBuilder();

        for (int i = 0; i < M; i++) {
            String q = br.readLine();

            char c = q.charAt(0);
            if ( c >= '0' && c <= '9' ) {
                int idx = Integer.parseInt(q);
                sb.append(idxToName[idx]).append('\n');
            }

            else {
                sb.append(nameToIdx.get(q)).append('\n');
            }
        }

        System.out.print(sb.toString());
    }
}
