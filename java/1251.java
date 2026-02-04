import java.io.*;

public class Main {

    private static String rev(String s) {
        return new StringBuilder(s).reverse().toString();
    }

    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String word = br.readLine();
        int n = word.length();

        String best = null;

        // 0 < i < j < n
        for (int i = 1; i < n - 1; i++) {
            for (int j = i + 1; j < n; j++) {
                String a = word.substring(0, i);
                String b = word.substring(i, j);
                String c = word.substring(j, n);

                String candidate = rev(a) + rev(b) + rev(c);

                if (best == null || candidate.compareTo(best) < 0) {
                    best = candidate;
                }
            }
        }

        System.out.print(best);
    }
}
