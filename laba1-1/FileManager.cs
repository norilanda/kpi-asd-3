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
        public static void generateFile(string fileName, long sizeInMB, char mode = 'n', int minValue = 0, int maxValue = 20000)
        {
            BinaryWriter binaryWriter = null;
            if (mode == 'n')
                binaryWriter = new BinaryWriter(new FileStream(fileName, FileMode.Create));
            else if (mode == 'a')
            {
                if (File.Exists(fileName))
                    binaryWriter = new BinaryWriter(new FileStream(fileName, FileMode.Append));
                else
                    binaryWriter = new BinaryWriter(new FileStream(fileName, FileMode.Create));
            }
            const int bytesInOneMB = 1024 * 1024;
            long number = sizeInMB * bytesInOneMB / sizeof(int);
            int[] buff = new int[number];
            Random rnd = new Random();
            for (int i=0; i<number; i++)
            {
                buff[i] = rnd.Next(minValue, maxValue+1);
            }
            writeArrayOfInts(binaryWriter, ref buff);
            binaryWriter.Close();
        }
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
            while (binaryFile.BaseStream.Position != binaryFile.BaseStream.Length)
            {
                outputFile.Write(",");
                outputFile.Write(binaryFile.ReadInt32());
            }
            binaryFile.Close();
            outputFile.Close();
        }
        public static int[] readArrayOfInts(BinaryReader binaryReader, long numberInOneRun)
        {
            byte[] bytesArray = binaryReader.ReadBytes((int)(numberInOneRun * sizeof(int))); //reading the run as bytes
            int[] buff = new int[bytesArray.Length/sizeof(int)];
            for (int j = 0; j < bytesArray.Length / sizeof(int); j++)    //converting to int
            {
                buff[j] = BitConverter.ToInt32(bytesArray, (int)j * sizeof(int));
            }
            return buff;
        }
        public static int writeArrayOfInts(BinaryWriter binaryWriter, ref int[] buff)
        {
            byte[] bytesArray = new byte[buff.Length * sizeof(int)];
            Buffer.BlockCopy(buff, 0, bytesArray, 0, bytesArray.Length);
            binaryWriter.Write(bytesArray); //write merged array
            return bytesArray.Count();
        }
    }
}
