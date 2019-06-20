
import java.util.Scanner;

class Chess{
    private int chess[][];

    public Chess(String s) {
        chess = new int[8][8];
        String[] row = s.split("/");
        for(int i = 0; i < row.length; i++){
            int j, k;
            for(k = j = 0; k < row[i].length(); k++){
                if(Character.isDigit(row[i].charAt(k))) 
                    j += row[i].charAt(k) - '0';
                else 
                    chess[i][j++] = row[i].charAt(k);
            }
        }
    }
    
    public void move(int x, int y, int mx, int my, boolean self){
        if(!valid(x, y)) return;
        if(self || getFieldValue(x, y) < 2){
            if(!self) setAttack(x, y);
                move(x+mx, y+my, mx, my, false);
        }
    }
    
    public boolean valid(int x, int y){
        return x >= 0 && y >= 0 && x < 8 && y < 8;
    }
    
    public void setAttack(int x, int y){
        if(valid(x, y) && chess[x][y] == 0)
            chess[x][y] = 1;
    }
    
    public int getFieldValue(int x, int y){
        return chess[x][y];
    }
    
    public int getResult(){
        int db = 0;
        for(int i = 0; i < 8; i++)
            for(int j = 0; j < 8; j++)
                if(chess[i][j] == 0) db++;
        return db;
    }
        
}

class ChessSolver{
    Chess game;
    
    private static final int[][][] MOVES = new int[][][]{
                    { {-1, -1}, {-1,  0}, {-1,  1}, {0,  1},  {1,  1}, {1,  0}, { 1, -1}, { 0, -1} },
                    { {-1, -2}, {-2, -1}, { 1, -2}, {2, -1},  {1,  2}, {2,  1}, {-2,  1}, {-1,  2} }
    };

    public ChessSolver(String s) {
        this.game = new Chess(s);
    }
    
    void kingKnight(int x, int y, int type){
        for(int i = 0; i < 8; i++)
            game.setAttack(x + MOVES[type][i][0], y + MOVES[type][i][1]);
    }

    void rook(int x, int y){
        for(int i = 1; i < 8; i += 2)
            game.move(x, y, MOVES[0][i][0], MOVES[0][i][1], true);
    }

    void bishop(int x, int y){
        for(int i = 0; i < 8; i += 2)
            game.move(x, y, MOVES[0][i][0], MOVES[0][i][1], true);
    }

    void queen(int x, int y){
        rook(x, y);
        bishop(x, y);
    }

    void pawn(int x, int y, boolean type){
        if(type){
            game.setAttack(x-1, y-1);
            game.setAttack(x-1, y+1);
        }
        else{
            game.setAttack(x+1, y-1);
            game.setAttack(x+1, y+1);
        }
    }
    
    public int solveChess(){
        for(int i = 0; i < 8; i++){
            for(int j = 0; j < 8; j++){
                int ch = game.getFieldValue(i, j);
                switch (ch) { 
                    case 'q': case 'Q': queen (i, j);   break;
                    case 'r': case 'R': rook  (i, j);   break;
                    case 'b': case 'B': bishop(i, j);   break;
                    case 'k': case 'K': kingKnight(i, j, 0);  break;
                    case 'n': case 'N': kingKnight(i, j, 1);  break;
                    case 'p': pawn(i, j, false);    break;
                    case 'P': pawn(i, j, true);     break;
                    default: break;
                }
            }
        }
        return game.getResult();
    }
}

public class Main {
    public static void main(String[] args) {
        String s;
        Scanner sc = new Scanner(System.in);
        while(sc.hasNextLine()){
            ChessSolver cs = new ChessSolver(sc.nextLine());
            System.out.println(cs.solveChess());
        }
    }
}
