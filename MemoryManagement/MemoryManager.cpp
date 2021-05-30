//
// Created by zerophase on 5/30/21.
//

#include "BitTwiddling/BitHacks.h"
#if !USE_PRECOMPILED
	#include "MemoryManager.h"
#endif

using namespace BitTwiddle;

MemoryManager::MemoryManager()
{
	size_t size = 1024; // TODO make minimum size 4096
	start = current = (char*)malloc(size);
	end = start + size;
	poolSize = size;
	// create all allocators here.
	// initially just using one allocator in here.
}

MemoryManager::~MemoryManager()
{
	free(start);
}

void MemoryManager::clear()
{
	current = start;
}

void MemoryManager::expandPoolSize(size_t expansionSize)
{
	// since this is used for char pointers expand by
	// multiples of 8 bits.
	// calculate multiple of 8 bits needed.
	size_t powerOf2 = UpperPowerofTwo(expansionSize);
	char *temp = (char*)realloc((void *)start, powerOf2);
	free((void*)start);
	start = current = temp;
	current += expansionSize;
	end = start + powerOf2;
	poolSize = powerOf2;
}

MemoryManager gMemoryManager;
