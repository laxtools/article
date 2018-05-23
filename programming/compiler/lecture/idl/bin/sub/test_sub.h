#pragma once
#include <stdint.h>

#pragma pack(push, 1)

namespace sub {
namespace test {

enum FieldSize
{
	embed_1 = 10,
};


struct Position
{
	float	x;
	float	y;
	float	z;
};


struct Embed
{
	int8_t	f1;
	Position	pos;
};


struct Test01
{
	int8_t	f1;
	int16_t	f2;
	int32_t	f3;
	int64_t	f4;
	float	f5;
	double	f6;
	int8_t	a1[3];
	float	a2[3];
	Embed	e[FieldSize::embed_1];
};

} // sub
} // test

#pragma pack(pop)

