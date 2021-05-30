//
// Created by zerophase on 5/30/21.
//

#ifndef MOCKSTRING_BITHACKS_H
#define MOCKSTRING_BITHACKS_H

#include "GeneralMacros/ALIGN.h"
#include <cstdint>

namespace BitTwiddle
{
	#if !defined(_MSC_VER)
	using std::size_t;
	#endif
	
	ALIGNED(64) const int8_t logtable64[64] =
			{
					63,  0, 58,  1, 59, 47, 53,  2,
					60, 39, 48, 27, 54, 33, 42,  3,
					61, 51, 37, 40, 49, 18, 28, 20,
					55, 30, 34, 11, 43, 14, 22,  4,
					62, 57, 46, 52, 38, 26, 32, 41,
					50, 36, 17, 19, 29, 10, 13, 21,
					56, 45, 25, 31, 35, 16,  9, 12,
					44, 24, 15,  8, 23,  7,  6,  5
			};
	
	const unsigned int tablePowersof2[21] =
			{
					0,      2,      4,      8,      16,     32,     64,
					128,    256,    512,    1024,   2048,   4096,   8192,
					16384,  32768,  65536,  131072, 262144, 524288, 1048576
			};
	
	inline size_t log2_64(uint64_t value)
	{
		value |= value >> 1;
		value |= value >> 2;
		value |= value >> 4;
		value |= value >> 8;
		value |= value >> 16;
		value |= value >> 32;
		return logtable64[((uint64_t)((value + 1) * 0x07EDD5E59A4E28C2)) >> 58];
		//rounds down	//return logtable64[((uint64_t)((value - (value >> 1)) * 0x07EDD5E59A4E28C2)) >> 58];
	}
	
	const size_t logtable32[32] = {
			0,  9,  1, 10, 13, 21,  2, 29,
			11, 14, 16, 18, 22, 25,  3, 30,
			8, 12, 20, 28, 15, 17, 24,  7,
			19, 27, 23,  6, 26,  5,  4, 31};
	
	inline size_t log2_32(uint32_t value)
	{
		value |= value >> 1;
		value |= value >> 2;
		value |= value >> 4;
		value |= value >> 8;
		value |= value >> 16;
		return logtable32[(uint32_t)(value*0x07C4ACDD) >> 27]; // this rounds down
	}
	
	inline size_t UpperPowerofTwo(size_t v)
	{
		switch(sizeof(size_t) * 8)
		{
			case 32:
				return tablePowersof2[log2_32(v)];
			case 64:
				return tablePowersof2[log2_64(v)];
		}
	}
}
#endif //MOCKSTRING_BITHACKS_H
