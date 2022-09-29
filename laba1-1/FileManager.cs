using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace laba1_1
{
    internal class FileManager
    {
        public static void display_file_numbers_from_range(string fileName, int startNumber = 1, int lastNumber = 0) { }	//displays all the numbers between startNumber and lastNumber positions
        public static string CreateCsvFileName(string fileName)
        {
            int position = fileName.LastIndexOf('.');
            if (position != -1)
                return fileName.Substring(0, position) + ".csv";
            else
                return fileName + ".csv";
        }
        public static void ConvertToCsv(string fileName)
        {
            string outputFileName = CreateCsvFileName(fileName);
            BinaryReader binaryFile = new BinaryReader(new FileStream(fileName, FileMode.Open));
            StreamWriter outputFile = new StreamWriter(outputFileName);
            outputFile.Write(binaryFile.ReadInt32());
            while (binaryFile.PeekChar() != -1)
            {
                outputFile.Write(",");
                outputFile.Write(binaryFile.ReadInt32());
            }
            binaryFile.Close();
            outputFile.Close();
        }
    }
}
