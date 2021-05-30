//
// Created by zerophase on 5/30/21.
//

#ifndef MOCKSTRING_MEMORYMANAGER_H
#define MOCKSTRING_MEMORYMANAGER_H
#pragma once

#include <cstddef>
#include <stdexcept>
#if !USE_PRECOMPILED
	#include "Exceptions/ExceptionHandling.h"
#endif

using std::runtime_error;
//TODO finalized design
// TODO make Stack Allocator
// have Stack Allocator capable of growing for inserts
// inserting has to shift all values after insert point up by x

// Also make linear allocator.


// Use linear allocator for for loops,
// use stack allocator for regular FastStrings
// start by using linear allocator for allocation of FastStrings
// later split into two separate string classes.
// do not use virtual methods
// implement new and delete just on
class MemoryManager
{
public:
	MemoryManager();
	~MemoryManager();
	
	inline void *allocate(size_t size)
	{
		// figure out alignment needed
		//current = AlignTop(current);
		void *usedPtr = current;
		current += size;
		if(current >= end)
			throw runtime_error("Out of Memory");
		
		return usedPtr;
	}
	
	void reallocate(size_t size)
	{
		current += size;
		if (current >= end)
		{
			size_t newSize = current - start;
			expandPoolSize(newSize);
		}
	}
	
	inline void free(void *ptr)
	{
		for(; ptr != current; --current);
		poolSize = (current - start);
	}
	
	void clear();
	
	void expandPoolSize(size_t expansionSize);
	[[nodiscard]] char * GetStart() const { return start; }
	[[nodiscard]] char * GetEnd() const { return end; }
	[[nodiscard]] char * GetCurrent() const { return current; }
	[[nodiscard]] size_t GetPoolSize() const { return poolSize; }

private:
	size_t poolSize;
	char *start;
	char *end;
	char *current;
};

extern MemoryManager gMemoryManager;

#endif //MOCKSTRING_MEMORYMANAGER_H
