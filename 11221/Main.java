
import java.util.Scanner;


class MagicSquarePalindrome{
    private String alphas;
    private String transpose;
    private int n;
    private int index;
    
    public MagicSquarePalindrome(String line, int index) {
        StringBuilder sb = new StringBuilder();
        for(int i = 0; i < line.length(); i++){
            if(Character.isAlphabetic(line.charAt(i)))
                sb.append(line.charAt(i));
        }
        alphas = sb.toString();
        this.index = index;
    }
    
    
    private boolean isPalindrome(String line){
        int i = 0, j = line.length() - 1;
        while(i <= j)
            if(line.charAt(i++) != line.charAt(j--))
                return false;
        return true;
    }
    
    private void transpose(){
        StringBuilder sb = new StringBuilder();
        for(int i = 0; i < alphas.length(); i++){
            sb.append(alphas.charAt((i / n) + (i % n) * n));
        }
        transpose = sb.toString();
    }

    private int isMagicSquare(){

        int len = alphas.length();

        if(len == 0) return 0;
        if((n = (int) Math.sqrt(len)) != Math.sqrt(len)) return -1;
        
        transpose();
        
        return isPalindrome(alphas) && isPalindrome(transpose) ? n : -1;
    }


    void print(){
        n = isMagicSquare();
        System.out.println("Case #" + ( index + 1) + ":");

        if(n == -1) System.out.println("No magic :(");
        else System.out.println(n);
    }


}

public class Main {
    public static void main(String[] args) {
        int N, i;
        Scanner sc = new Scanner(System.in);
        N = Integer.parseInt(sc.nextLine());
        
        for(i = 0; i < N; i++){
            MagicSquarePalindrome msp = new MagicSquarePalindrome(sc.nextLine(), i);
            msp.print();
        }
    }
}
