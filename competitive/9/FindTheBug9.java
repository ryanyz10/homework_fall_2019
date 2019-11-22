import java.util.*;

/**
 * Problem statement: http://codeforces.com/problemset/problem/614/C
 */
public class FindTheBug9 {

    private static class Point {
        private int x;
        private int y;

        Point(int x, int y) {
            this.x = x;
            this.y = y;
        }

        double norm2() {
            return x * x + y * y;
        }
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int n = scanner.nextInt();
        int xOrigin = scanner.nextInt();
        int yOrigin = scanner.nextInt();
        List<Point> points = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            int xCurrent = scanner.nextInt() - xOrigin;
            int yCurrent = scanner.nextInt() - yOrigin;
            points.add(new Point(xCurrent, yCurrent));
        }
        System.out.println(getSnowCleared(points));
    }

    private static double getSnowCleared(List<Point> polygon) {
        // We're going to clear a circle of snow centered at the origin, but
        // with a smaller circle cut out of the middle. Let R be the radius
        // of the outer circle and r be the radius of the inner circle. Then
        // the amount of snow cleared is pi*R^2 - pi*r^2 = pi(R^2 - r^2). I
        // claim that the outer circle's radius is the same as the distance
        // from the origin to the point furthest from it on the polygon, and
        // that the inner circle's radius is the same as the distance from
        // the origin to the point closest to it on the polygon.
        double outer = Double.NEGATIVE_INFINITY;
        double inner = Double.POSITIVE_INFINITY;
        for (Point vertex : polygon) {
            double norm2 = vertex.norm2();
            outer = Math.max(outer, norm2);
            inner = Math.min(inner, norm2);
        }
        return Math.PI * (outer - inner);
    }

}
