#pragma once
#include <stdint.h>

#pragma pack(push, 1)

#include "test_02.h"

namespace Test {
namespace Message {

enum Hello
{
	V1,
	V2,
	V3 = 100,
};


struct Position
{
	float	x = 0;
	float	y = 0;
	float	z = 0;
};


struct Test
{
	int32_t	V1 = 33;
#if DEBUG
	double	Ff;
#else
	Hello	Hv;
#endif
	na::h	Can;
	na::h	Arr[Hello::v3];
};


struct Level2
{
	Test	Field1;
	Self::Hello::Test	Field2[2];
};


class ReqMove
{
public:
// field functions
	const (unknown) GetWho() const;
	const Vector3& GetPos() const;
	const float GetDir() const;
	const int32_t GetHp() const;

private:
// field variables 
	(unknown)	__mWho;
	Vector3	__mPos;
	float	__mDir;
	int32_t	__mHp;
};

} // Test
} // Message

#pragma pack(pop)

