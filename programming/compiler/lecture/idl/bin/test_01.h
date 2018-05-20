#pragma once
#include <stdint.h>
#include <string>
#include <vector>


#include "test_02.h"

namespace Test {
namespace Message {

enum Hello
{
	V1,
	V2,
	V3 = 100,
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
	const string GetWho() const;
	const Vector3& GetPos() const;
	const float GetDir() const;
	const int32_t GetHp() const;

private:
// field variables 
	string	Who;
	Vector3	Pos;
	float	Dir;
	int32_t	Hp;
};

} // Test
} // Message

