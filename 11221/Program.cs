using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace palindrome
{
    class MagicSquarePalindrome
    {
        private String _alphas;
        private String _transpose;
        private int _n;
        private int _index;

        public MagicSquarePalindrome(String line, int index)
        {
            StringBuilder sb = new StringBuilder();
            for (int i = 0; i < line.Length; i++)
            {
                if (Char.IsLetter(line[i]))
                    sb.Append(line[i]);
            }
            _alphas = sb.ToString();
            this._index = index;
        }


        bool IsPalindrome(String line)
        {
            int i = 0, j = line.Length - 1;
            while (i <= j)
                if (line[i++] != line[j--])
                    return false;
            return true;
        }

        void Transpose()
        {
            StringBuilder sb = new StringBuilder();
            for (int i = 0; i < _alphas.Length; i++)
            {
                sb.Append(_alphas[(i / _n) + (i % _n) * _n]);
            }
            _transpose = sb.ToString();
        }

        int IsMagicSquare()
        {

            int len = _alphas.Length;

            if (len == 0) return 0;
            if ((_n = (int)Math.Sqrt(len)) != Math.Sqrt(len)) return -1;

            Transpose();

            return IsPalindrome(_alphas) && IsPalindrome(_transpose) ? _n : -1;
        }


        public void Print()
        {
            _n = IsMagicSquare();
            Console.WriteLine("Case #" + (_index + 1) + ":");

            if (_n == -1) Console.WriteLine("No magic :(");
            else Console.WriteLine(_n);
        }


    }

    public class Square
    {
        public static void Main(String[] args)
        {
            int N, i;
            N = Convert.ToInt32(Console.ReadLine());

            for (i = 0; i < N; i++)
            {
                MagicSquarePalindrome msp = new MagicSquarePalindrome(Console.ReadLine(), i);
                msp.Print();
            }
        }
    }

}
