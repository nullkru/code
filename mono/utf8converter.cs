/* by mirko messer 2008
 * http://www.yoda.arachsys.com/csharp/unicode.html
 * unicode to latin-1 converter
 */

using System;
using System.IO;
using System.Text;

public class FileConverter
{
    const int BufferSize = 8096;
    
    public static void Main(string[] args)
    {
        if (args.Length != 2)
        {
            Console.WriteLine 
                ("utf-8 to latin-1 converter (mirko messer 2008)\nUsage: FileConverter <input file> <output file>");
            return;
        }
        
        // Open a TextReader for the appropriate file
        using (TextReader input = new StreamReader 
               (new FileStream (args[0], FileMode.Open),
                Encoding.UTF8))
        {
            // Open a TextWriter for the appropriate file
            using (TextWriter output = new StreamWriter 
                   (new FileStream (args[1], FileMode.Create),
                    Encoding.GetEncoding(28591)))
            {

                // Create the buffer
                char[] buffer = new char[BufferSize];
                int len;
                
                // Repeatedly copy data until we've finished
                while ( (len = input.Read (buffer, 0, BufferSize)) > 0)
                {
                    output.Write (buffer, 0, len);
                }
            }
        }
    }
}

