using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ChessBoard
{

    class Chess
    {
        private int[, ] chess;

    public Chess(String s)
        {
            chess = new int[8, 8];
            String[] row = s.Split('/');
            for (int i = 0; i < row.Length; i++)
            {
                int j, k;
                for (k = j = 0; k < row[i].Length; k++)
                {
                    if (Char.IsDigit(row[i][k]))
                        j += row[i][k] - '0';
                    else
                        chess[i, j++] = row[i][k];
                }
            }
        }

        public void Move(int x, int y, int mx, int my, bool self)
        {
            if (!valid(x, y)) return;
            if (self || getFieldValue(x, y) < 2)
            {
                if (!self) setAttack(x, y);
                Move(x + mx, y + my, mx, my, false);
            }
        }

        public bool valid(int x, int y)
        {
            return x >= 0 && y >= 0 && x < 8 && y < 8;
        }

        public void setAttack(int x, int y)
        {
            if (valid(x, y) && chess[x,y] == 0)
                chess[x, y] = 1;
        }

        public int getFieldValue(int x, int y)
        {
            return chess[x, y];
        }

        public int getResult()
        {
            int db = 0;
            for (int i = 0; i < 8; i++)
                for (int j = 0; j < 8; j++)
                    if (chess[i, j] == 0) db++;
            return db;
        }

    }

    class ChessSolver
    {
        Chess game;

        private static readonly int[,,] MOVES = new int[2, 8, 2]{
                    { {-1, -1}, {-1,  0}, {-1,  1}, {0,  1},  {1,  1}, {1,  0}, { 1, -1}, { 0, -1} },
                    { {-1, -2}, {-2, -1}, { 1, -2}, {2, -1},  {1,  2}, {2,  1}, {-2,  1}, {-1,  2} }
    };

        public ChessSolver(String s)
        {
            this.game = new Chess(s);
        }

        void KingKnight(int x, int y, int type)
        {
            for (int i = 0; i < 8; i++)
                game.setAttack(x + MOVES[type, i, 0], y + MOVES[type, i, 1]);
        }

        void Rook(int x, int y)
        {
            for (int i = 1; i < 8; i += 2)
                game.Move(x, y, MOVES[0, i, 0], MOVES[0, i, 1], true);
        }

        void Bishop(int x, int y)
        {
            for (int i = 0; i < 8; i += 2)
                game.Move(x, y, MOVES[0, i, 0], MOVES[0, i, 1], true);
        }

        void Queen(int x, int y)
        {
            Rook(x, y);
            Bishop(x, y);
        }

        void Pawn(int x, int y, bool type)
        {
            if (type)
            {
                game.setAttack(x - 1, y - 1);
                game.setAttack(x - 1, y + 1);
            }
            else
            {
                game.setAttack(x + 1, y - 1);
                game.setAttack(x + 1, y + 1);
            }
        }

        public int SolveChess()
        {
            for (int i = 0; i < 8; i++)
            {
                for (int j = 0; j < 8; j++)
                {
                    int ch = game.getFieldValue(i, j);
                    switch (ch)
                    {
                        case 'q': case 'Q': Queen(i, j); break;
                        case 'r': case 'R': Rook(i, j); break;
                        case 'b': case 'B': Bishop(i, j); break;
                        case 'k': case 'K': KingKnight(i, j, 0); break;
                        case 'n': case 'N': KingKnight(i, j, 1); break;
                        case 'p': Pawn(i, j, false); break;
                        case 'P': Pawn(i, j, true); break;
                        default: break;
                    }
                }
            }
            return game.getResult();
        }
    }

    public class ChessMain
    {
        public static void Main(String[] args)
        {
            String s;
            while ((s = Console.ReadLine()) != null)
            {
                ChessSolver cs = new ChessSolver(s);
                Console.WriteLine(cs.SolveChess());
            }
        }
    }
}
