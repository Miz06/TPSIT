using System;
using System.Collections.Generic;
using System.Data.SqlTypes;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Targa
{
    internal class Program
    {
        static void Main(string[] args)
        { //Alessandro Mizzon 4E
            string targa, caratteri, numeri; 
            double valoreF = 0; 
            char[] alfabeto = new char[26]; 

            for (int i = 0; i < 26; i++)
            {
                alfabeto[i] = Convert.ToChar(65 + i);
            }

            Console.WriteLine("Inserire una targa");
            targa = Console.ReadLine();

            caratteri = targa.Substring(0, 2) + targa.Substring(5);
            numeri = targa.Substring(2, 5);

            for (int i = 0; i<3; i++)
            {
                valoreF += (Convert.ToInt32(numeri[i])-'0') * Math.Pow(10, i); 
            }

            for (int i = 0; i < 4; i++)
            {
                valoreF += (Convert.ToInt32(caratteri[i])-'A') * Math.Pow(10, 3) * Math.Pow(26, i);
            }

            Console.WriteLine(valoreF); 
            Console.ReadLine();
        }
    }
}