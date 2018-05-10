using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace test_cs
{
    class Program
    {
        static void Main(string[] args)
        {
            Test2();
        }

        static void Test2()
        {
            FileStream fs = File.OpenRead("test_out.bin");

            var packer = new Test.Packer();

            var t1 = new Test.Test();

            t1.Unpack(packer, fs);

            System.Console.WriteLine(
                String.Format(
                    "V1: {0}, V2: {1}, V3: {2}, SV: {3},{4}, Name: {5}",
                    t1.V1, t1.V2, t1.V3, t1.sv[0].fv, (char)t1.sv[0].bv, t1.Name)
                    );
        } 

        static void Test1()
        {
            var t1 = new Test.Test();

            var packer = new Test.Packer();
            var stream = new MemoryStream();

            t1.Pack(packer, stream);

            System.Console.WriteLine(
                String.Format(
                    "V1: {0}, V2: {1}, V3: {2}, SV: {3},{4}, Name: {5}",
                    t1.V1, t1.V2, t1.V3, t1.sv[0].fv, (char)t1.sv[0].bv, t1.Name)
                    );

            // rewind
            stream.Seek(0, SeekOrigin.Begin);

            var t2 = new Test.Test();
            t2.Unpack(packer, stream);

            System.Console.WriteLine(
                String.Format(
                    "V1: {0}, V2: {1}, V3: {2}, SV: {3},{4}, Name: {5}",
                    t1.V1, t1.V2, t1.V3, t1.sv[0].fv, (char)t1.sv[0].bv, t1.Name)
                    );

        }
    }
}
