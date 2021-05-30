//
// Created by zerophase on 5/30/21.
//

#ifndef MOCKSTRING_ALIGN_H
#define MOCKSTRING_ALIGN_H
#pragma once

#if defined(_MSC_VER)
	#define ALIGNED(x) __declspec(align(x))
#else
	#define ALIGNED(x) __attribute__((aligned(x)))
#endif

#endif //MOCKSTRING_ALIGN_H
