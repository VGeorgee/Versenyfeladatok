
import java.util.Scanner;

class Moves{
    private static final int MOVES[][] = { {0, 1}, {1, 0}, {1, 1}, {-1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, -1} };
    
    public static int x(int i){
        return MOVES[i][0];
    }
    public static int y(int i){
        return MOVES[i][1];
    }
}

class MineSweeper{
    private final int nxn;
    private int out;
    private int[][][] grid;

    
    public MineSweeper(int nxn, String[] input1, String[] input2) {
        this.nxn = nxn;
        out = 1;
        grid = new int[2][nxn][nxn];
        for(int i = 0; i < nxn; i++){
            for(int j = 0; j < nxn; j++){
                grid[0][i][j] = input1[i].charAt(j);
                grid[1][i][j] = input2[i].charAt(j);
            }
        }
    }
    
    
    private boolean valid(int x, int y){
        return x >= 0 && y >= 0 && x < nxn && y < nxn;
    }
    
    private void set_zone(int x, int y, int m){
    grid[m][x][y] = '0';
    for(int i = 0; i < 8; i++){
        int xplus = x + Moves.x(i),
            yplus = y + Moves.y(i);

        if(valid(xplus, yplus) && grid[0][xplus][yplus] == '*')
            grid[m][x][y]++;
    }
}
    
    public void solve(){
       int k = 1;
       for(int i = 0; i < nxn; i++){
           for(int j = 0; j < nxn; j++){
               if(grid[1][i][j] == 'x'){
                   if(grid[0][i][j] == '*') k = 0;
                   else set_zone(i, j, 0);
                   set_zone(i, j, 1);
               }
           }
       }
       out = k;
   }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        for(int i = 0; i < nxn; i++){
            for(int j = 0; j < nxn; j++){
                sb.append((char)grid[out][i][j]);
            }
            sb.append("\n");
        }
        return sb.toString();
    }
    
    

    public void output() {
        for(int i = 0; i < nxn; i++){
            for(int j = 0; j < nxn; j++){
                System.out.print((char)grid[out][i][j]);
            }
            System.out.println("");
        }
    }
}


public class Main {

    public static void main(String[] args) {
        int N, i, n;
        Scanner sc = new Scanner(System.in);
        N = Integer.parseInt(sc.nextLine());
        
        for(i = 0; i < N; i++){
            sc.nextLine();
            n = Integer.parseInt(sc.nextLine());
            
            String[] input1 = new String[n];
            String[] input2 = new String[n];
            for(int j = 0; j < n; j++)
                input1[j] = sc.nextLine();
            for(int j = 0; j < n; j++)
                input2[j] = sc.nextLine();
            
            MineSweeper ms = new MineSweeper(n, input1, input2);
            ms.solve();
            ms.output();
            if(i < N-1) System.out.println("");
        }
    }
    
}
