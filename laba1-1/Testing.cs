using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace laba1_1
{
    internal class Testing
    {
        public static bool isSorted(string fileName, long chunkSize)
        {
            long fileSize = new System.IO.FileInfo(fileName).Length / sizeof(int);
            int previous = Int32.MinValue;
            BinaryReader binaryReader = new BinaryReader(new FileStream(fileName, FileMode.Open));
            while (fileSize > 0)
            {                
                int[] buff = FileManager.readArrayOfInts(binaryReader, chunkSize);
                if (buff[0] < previous)
                {
                    binaryReader.Close();
                    return false;                    
                }
                for(int i=1;i<buff.Length;i++)
                {
                    if (buff[i] < buff[i - 1])
                    {
                        binaryReader.Close();
                        return false;                        
                    }
                }
                previous = buff[buff.Length-1];
                fileSize -= buff.Length;
            }
            binaryReader.Close();
            return true;
        }
    }
}
