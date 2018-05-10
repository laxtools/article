using System;
using System.IO;
using System.Text;

namespace Test
{

    public enum Hello
    {
        V1,
        V2,
        V3 = 100,
    }

    public class Struct
    {
        public sbyte bv = 3;
        public float fv = 3.141592f; 

        public void Pack(Packer packer, Stream s)
        {
            packer.Write(s, bv);                
            packer.Write(s, fv);                
        }

        public void Unpack(Packer packer, Stream s)
        {
            packer.Read(s, out bv);                
            packer.Read(s, out fv);                
        }
    }

    public partial class Test : Packable
    {
        public int V1 = 3;
        public float V2 = 1.017f;
        public double V3 = 2.10324f;
        public Struct[] sv = new Struct[128];
        public string Name = "한글이름을출력하는것";

        public override void Pack(Packer packer, Stream s) 
        {
            packer.Write(s, V1);
            packer.Write(s, V2);
            packer.Write(s, V3);

            for ( int i=0; i<128; ++i)
            {
                sv[i] = new Struct();
                sv[i].Pack(packer, s);
            }

            packer.WriteL8(s, Name);

            // structA.Pack(s);  

            // Exception: PackOverflow 
            // - 실제 발생할 가능성은 없다. 
        }

        public override void Unpack(Packer packer, Stream s)
        {
            packer.Read(s, out V1);
            packer.Read(s, out V2);
            packer.Read(s, out V3);

            // structA.Unpack(s);
            for ( int i=0; i<128; ++i)
            {
                sv[i] = new Struct();
                sv[i].Unpack(packer, s);
            }

            packer.ReadL8(s, out Name);

            // Exception: UnpackUnderflow 
        }
    }


} // Test
