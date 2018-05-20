using System;
using System.IO;
using System.Text;

namespace Test.Message { 

public enum Hello
{
	V1,
	V2,
	V3 = 100,
}


public partial class Test
{
	public int V1 = 33;
#if DEBUG
	public double Ff;
#else
	public Hello Hv;
#endif
	public na.h Can = new na.h();
	public na.h[] Arr = new na.h[Hello.v3];
}


public partial class Level2
{
	public Test Field1 = new Test();
	public Self.Hello.Test[] Field2 = new Self.Hello.Test[2];
}


public partial class ReqMove
{
	public string Who;
	public Vector3 Pos = new Vector3();
	public float Dir;
	public int Hp;
}

} // Test.Message
