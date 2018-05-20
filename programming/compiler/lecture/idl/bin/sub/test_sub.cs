using System;
using System.IO;
using System.Text;

namespace sub.test { 

public enum FieldSize
{
	embed_1 = 10,
}


public partial class Position
{
	public float x;
	public float y;
	public float z;
}


public partial class Embed
{
	public byte f1;
	public Position pos = new Position();
}


public partial class Test01
{
	public byte f1;
	public short f2;
	public int f3;
	public long f4;
	public float f5;
	public double f6;
	public byte[] a1 = new byte[3];
	public float[] a2 = new float[3];
	public Embed[] e = new Embed[FieldSize.embed_1];
}

} // sub.test
