using System;
using System.Text;

namespace _10279
{

    class Moves
    {
        private static int[,] MOVES = new int[8, 2] { { 0, 1 }, { 1, 0 }, { 1, 1 }, { -1, 0 }, { 0, -1 }, { -1, -1 }, { -1, 1 }, { 1, -1 } };

        public static int X(int i)
        {
            return MOVES[i, 0];
        }
        public static int Y(int i)
        {
            return MOVES[i, 1];
        }
    }

    class MineSweeper
    {
        private int _nxn;
        private int _out;
        private int[,,] _grid;


        public MineSweeper(int nxn, String[] input1, String[] input2)
        {
            this._nxn = nxn;
            this._out = 1;
            _grid = new int[2, nxn, nxn];
            for (int i = 0; i < nxn; i++)
            {
                for (int j = 0; j < nxn; j++)
                {
                    _grid[0, i, j] = input1[i][j];
                    _grid[1, i, j] = input2[i][j];
                }
            }
        }


        private bool Valid(int x, int y)
        {
            return x >= 0 && y >= 0 && x < _nxn && y < _nxn;
        }

        private void SetZone(int x, int y, int m)
        {
            _grid[m, x, y] = '0';
            for (int i = 0; i < 8; i++)
            {
                int xplus = x + Moves.X(i),
                    yplus = y + Moves.Y(i);

                if (Valid(xplus, yplus) && _grid[0, xplus, yplus] == '*')
                    _grid[m, x, y]++;
            }
        }

        public void Solve()
        {
            int k = 1;
            for (int i = 0; i < _nxn; i++)
            {
                for (int j = 0; j < _nxn; j++)
                {
                    if (_grid[1, i, j] == 'x')
                    {
                        if (_grid[0, i, j] == '*') k = 0;
                        else SetZone(i, j, 0);
                        SetZone(i, j, 1);
                    }
                }
            }
            _out = k;
        }


        public override String ToString()
        {
            StringBuilder sb = new StringBuilder();
            for (int i = 0; i < _nxn; i++)
            {
                for (int j = 0; j < _nxn; j++)
                {
                    sb.Append((char)_grid[_out, i, j]);
                }
                sb.Append('\n');
            }
            return sb.ToString();
        }


        public class Mine
        {

            public static void Main(String[] args)
            {
                int N, i, n;
                N = Convert.ToInt32(Console.ReadLine());

                for (i = 0; i < N; i++)
                {
                    Console.ReadLine();
                    n = Convert.ToInt32(Console.ReadLine());

                    String[] input1 = new String[n];
                    String[] input2 = new String[n];
                    for (int j = 0; j < n; j++)
                        input1[j] = Console.ReadLine();
                    for (int j = 0; j < n; j++)
                        input2[j] = Console.ReadLine();

                    MineSweeper ms = new MineSweeper(n, input1, input2);
                    ms.Solve();
                    Console.WriteLine(ms);
                    if (i < N - 1) Console.WriteLine();
                }
            }

        }
    }
}



