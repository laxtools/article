using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace Test
{
    public class Packer
    {
        public void Write(Stream stream, bool b)
        {
            Write(stream, b ? (sbyte)1 : (sbyte)0);
        }

        private byte[] bout = new byte[1];
        public void Write(Stream stream, sbyte b)
        {
            bout[0] = (byte)b;
            WriteAll(stream, bout, 0, 1);
        }

        private byte[] i16out = new byte[2];
        public void WriteI(Stream stream, short s)
        {
            i16out[1] = (byte)(0xff & (s >> 8));
            i16out[0] = (byte)(0xff & s);
            WriteAll(stream, i16out, 0, 2);
        }

        private byte[] i32out = new byte[4];
        public void Write(Stream stream, int i32)
        {
            i32out[3] = (byte)(0xff & (i32 >> 24));
            i32out[2] = (byte)(0xff & (i32 >> 16));
            i32out[1] = (byte)(0xff & (i32 >> 8));
            i32out[0] = (byte)(0xff & i32);
            WriteAll(stream, i32out, 0, 4);
        }

        private byte[] i64out = new byte[8];
        public void Write(Stream stream, long i64)
        {
            i64out[7] = (byte)(0xff & (i64 >> 56));
            i64out[6] = (byte)(0xff & (i64 >> 48));
            i64out[5] = (byte)(0xff & (i64 >> 40));
            i64out[4] = (byte)(0xff & (i64 >> 32));
            i64out[3] = (byte)(0xff & (i64 >> 24));
            i64out[2] = (byte)(0xff & (i64 >> 16));
            i64out[1] = (byte)(0xff & (i64 >> 8));
            i64out[0] = (byte)(0xff & i64);
            WriteAll(stream, i64out, 0, 8);
        }

        public void Write(Stream stream, float d)
        {
            var bytes = BitConverter.GetBytes(d);

            // 여기는 엔디안이 반영될 것으로 보인다. 

            Write(stream, (sbyte)bytes[0]);
            Write(stream, (sbyte)bytes[1]);
            Write(stream, (sbyte)bytes[2]);
            Write(stream, (sbyte)bytes[3]);
        }

        public void Write(Stream stream, double d)
        {
            Write(stream, BitConverter.DoubleToInt64Bits(d));
        }

        public void WriteL8(Stream stream, string s)
        {
            byte[] sb = Encoding.GetEncoding(51949).GetBytes(s);

            // Endian 반영되는 지 모르겠다. 

            WriteAll(stream, sb, 0, 16);
        }

        public void Read(Stream stream, out bool v)
        {
            sbyte sv;
            Read(stream, out sv);

            v = (sv != 0);
        }

        private byte[] bin = new byte[1];
        public void Read(Stream stream, out sbyte v)
        {
            ReadAll(stream, bin, 0, 1);
            v = (sbyte)bin[0];
        }

        private byte[] i16in = new byte[2];
        public void Read(Stream stream, out short v)
        {
            ReadAll(stream, i16in, 0, 2);
            v = (short)(((i16in[1] & 0xff) << 8) | ((i16in[0] & 0xff)));
        }

        private byte[] i32in = new byte[4];
        public void Read(Stream stream, out int v)
        {
            ReadAll(stream, i32in, 0, 4);
            v = (int)(((i32in[3] & 0xff) << 24) | ((i32in[2] & 0xff) << 16) | ((i32in[1] & 0xff) << 8) | ((i32in[0] & 0xff)));
        }

#pragma warning disable 675

        private byte[] i64in = new byte[8];
        public void Read(Stream stream, out long v)
        {
            ReadAll(stream, i64in, 0, 8);
            unchecked
            {
                v = (long)(
                    ((long)(i64in[7] & 0xff) << 56) |
                    ((long)(i64in[6] & 0xff) << 48) |
                    ((long)(i64in[5] & 0xff) << 40) |
                    ((long)(i64in[4] & 0xff) << 32) |
                    ((long)(i64in[3] & 0xff) << 24) |
                    ((long)(i64in[2] & 0xff) << 16) |
                    ((long)(i64in[1] & 0xff) << 8) |
                    ((long)(i64in[0] & 0xff)));
            }
        }

#pragma warning restore 675

        public void Read(Stream stream, out float v)
        {
            ReadAll(stream, i32in, 0, 4);

            v = BitConverter.ToSingle(i32in, 0);
        }

        public void Read(Stream stream, out double v)
        {
            long tv = 0;
            Read(stream, out tv);
            v = BitConverter.Int64BitsToDouble(tv);
        }

        public void ReadL8(Stream stream, out string s)
        {
            byte[] sb = new byte[16];

            // 고정 길이로 일단 가정하고 진행

            ReadAll(stream, sb, 0, 16);

            s = Encoding.GetEncoding(51949).GetString(sb); 
        }

        private void WriteAll(Stream stream, byte[] buf, int off, int len)
        {
            stream.Write(buf, off, len);
        }

        private int ReadAll(Stream stream, byte[] buf, int off, int len)
        {
            return stream.Read(buf, 0, len);
        }
    }
}
