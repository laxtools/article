#include "stdafx.h"
#include <stdint.h>
#include <fstream>

#pragma pack(push, 1)


class Struct
{
	char bv = 'c';
	float fv = 12.3f;
};

struct TestMessage
{
	int32_t V1 = 33;
	float V2 = 0.017f;
	double V3 = 3.10324;
	Struct SV[128];
	char Name[16];
};

#pragma pack(pop)

int main()
{
	std::ofstream os("test_out.bin", std::ios::out | std::ios::binary);

	TestMessage tm; 

	::memcpy((void*)tm.Name, "한글이름을출력하는것", 16);

	os.write((const char*)&tm, sizeof(tm));

	os.close();

    return 0;
}

