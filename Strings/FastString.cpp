//
// Created by zerophase on 5/30/21.
//

#include "FastString.h"
#include <cstring>
#include "BitTwiddling/BitHacks.h"
#if !USE_PRECOMPILED
	#include <iostream>
#include <cassert>
	#include "MemoryManagement/MemoryManager.h"
#endif

namespace StringManipulation
{
	using namespace BitTwiddle;
	
	#define MALLOC_STRING(s) (char*)malloc(tablePowersof2[log2_64(s)]);
	#define DEFAULT_MALLOC_STRING MALLOC_STRING(DEFAULT_MALLOC_VALUE)
	
	FastString::FastString()
	{
		cstring = DEFAULT_MALLOC_STRING
		endOfString = cstring;
		setEndOfString(0);
	}
	
	FastString::FastString(char *str)
	{
		cstring = DEFAULT_MALLOC_STRING
		endOfString = cstring;
		advanceString(str);
	}
	
	FastString::FastString(const char *str) //TODO check if this causes issues with null termination
	{
		cstring = DEFAULT_MALLOC_STRING
		endOfString = cstring;
		advanceString(str);
	}
	
	FastString::FastString(const char *str, size_t malloc_size)
	{
		cstring = MALLOC_STRING(malloc_size)
		endOfString = cstring;
		malloc_string_size = malloc_size;
		advanceString(str);
	}
	
	FastString::FastString(const FastString &other, size_t malloc_size)
	{
		cstring = MALLOC_STRING(malloc_size)
		endOfString = cstring;
		malloc_string_size = malloc_size;
		advanceString(other.cstring);
	}
	
	FastString::FastString(const FastString &other)
	{
		cstring = DEFAULT_MALLOC_STRING
		memset(cstring, 0, DEFAULT_MALLOC_VALUE);
		endOfString = cstring;
		advanceString(other.cstring);
	}
	
	FastString::~FastString()
	{
		free((void*)cstring);
	}
	
	void FastString::advanceString(const char *str)
	{
		size_t size = 0;
		while (*str != '\0')
		{
			*cstring = *str;
			++cstring;
			++str;
			++size;
		}
		cstring = cstring - size;
		setEndOfString(size);
		if (size > malloc_string_size)
			reallocate();
	}
	
	void FastString::setEndOfString(size_t len)
	{
		endOfString += len;
		*endOfString = '\0';
	}
	
	void FastString::setEndOfString()
	{
		*endOfString = '\0';
	}
	
	size_t FastString::Size() const
	{
		return (endOfString - cstring);
	}
	
	void FastString::erase(size_t pos, size_t length)
	{
		if (length > Size())
			throw "length is too large";
		memmove(cstring + pos, cstring + pos + 1, (Size() - pos - 1));
		endOfString -= length;
		*endOfString = '\0';
	}
	
	void FastString::eraseFromStart(size_t length)
	{
		if (length > Size())
			throw "length is too large";
		memmove(cstring, cstring + length, (Size() - length));
		endOfString -= length;
		*endOfString = '\0';
	}
	
	void FastString::insert(size_t position, const char *str)
	{
		size_t insertLen = strlen(str);
		memmove(cstring + position + insertLen, cstring + position, (Size() + insertLen));
		size_t countLeft = 0;
		while(countLeft < insertLen)
		{
			*(cstring + countLeft + position) = *(str + countLeft);
			++countLeft;
		}
		
		if (Size() + insertLen > GetMallocStringSize())
			reallocate();
		setEndOfString(insertLen);
	}
	
	FastString FastString::SubString(char * sub) const
	{
		char * match = strstr(this->cstring, sub);
		if (match)
			return FastString("Banter");
		else
			return FastString("Choice");
	}
	
	void FastString::replace(size_t startPos, size_t len, const char *str)
	{
		assert(len == strlen(str) && "str and len length must match");
		
		size_t curPos = 0;
		while(curPos < len)
		{
			*(cstring + curPos + startPos) = *(str + curPos);
			++curPos;
		}
		
		size_t totalSize = startPos + len;
		if (Size() < totalSize)
			setEndOfString(totalSize - Size());
	}
	
	void FastString::reallocate()
	{
		size_t  length = Size();
		malloc_string_size = 2 * malloc_string_size;
		cstring = (char*)realloc(this->cstring, malloc_string_size);
		endOfString = cstring;
		endOfString += length;
	}
	
	FastString &FastString::operator+=(const char *str)
	{
		while(*str != '\0')
		{
			*endOfString = *str;
			++endOfString;
			++str;
		}
		setEndOfString();
		if (Size() > malloc_string_size)
			reallocate();
		return *this;
	}
	
	FastString &FastString::operator+=(char *str)
	{
		while(*str != '\0')
		{
			*endOfString = *str;
			++endOfString;
			++str;
		}
		setEndOfString();
		if (Size() > malloc_string_size)
			reallocate();
		return *this;
	}
	
	FastString &FastString::operator+=(FastString &str)
	{
		size_t size = (str.Size());
		while(*str.cstring != '\0')
		{
			*endOfString = *str.cstring;
			++endOfString;
			++str.cstring;
		}
		setEndOfString();
		str.cstring = str.cstring - size;
		if (Size() > malloc_string_size)
			reallocate();
		return *this;
	}
	
	// TODO fix this going past the end of string.
	FastString &FastString::operator+=(const FastString &str)
	{
		size_t size = str.Size();
		if (malloc_string_size <= (endOfString - cstring) + size)
			reallocate();
		for(int i = 0; i < size; ++i)
		{
			*endOfString = *(str.cstring + i);
			++endOfString;
		}
		setEndOfString();
		return *this;
	}
	
	FastString &FastString::operator+=(size_t size)
	{
		endOfString += size; // move into grow method
		*endOfString = '\0';
		if (Size() > malloc_string_size)
			reallocate();
		return *this;
	}
	
	FastString &FastString::operator -=(int decrement)
	{
		for(int i = 0; i < decrement && endOfString != cstring; ++i)
		{
			--endOfString;
			*endOfString = '\0';
		}
		return *this;
	}
	
	FastString &FastString::operator=(const FastString& str)
	{
		size_t size = str.Size();
		malloc_string_size = str.malloc_string_size;
		int i = 0;
		for(; i < size; ++i)
			*(cstring + i) = *(str.cstring + i);
		endOfString = (cstring + i);
		*endOfString = '\0';
		return *this;
	}
	
	FastString &FastString::operator=(const char *str)
	{
		size_t size = 0;
		while(*(str + size) != '\0')
		{
			*(cstring + size) = *(str + size);
			++size;
		}
		endOfString = (cstring + size);
		*endOfString = '\0';
		if (size > malloc_string_size)
			reallocate();
		return *this;
	}
	
	FastString &FastString::operator=(const char &str)
	{
		throw("Fastring &operator=(const char &str) not implemented");
		return *this;
	}
	
	char &FastString::operator[](size_t index) const
	{
		assert(index <= Size());
		assert(index >= 0);
		return *(cstring + index);
	}
	
	void *FastString::operator new(size_t size)
	{
		return ::gMemoryManager.allocate(size);
	}
	
	void FastString::operator delete(void *ptr)
	{
		//gMemoryManager.free(ptr);
	}
	
	bool FastString::operator<(const FastString &a) const
	{
		return std::strcmp(a.cstring, cstring) < 0;
	}
	
	bool FastString::operator==(const FastString &a) const
	{
		return std::strcmp(a.cstring, cstring) == 0;
	}
	
	FastString operator+(FastString lhs, const FastString &rhs)
	{
		size_t size = rhs.Size();
		for(int i = 0; i < size; ++i)
		{
			*lhs.endOfString = *(rhs.cstring + i);
			++lhs.endOfString;
		}
		lhs.setEndOfString();
		return lhs;
	}
	
	FastString operator+(FastString lhs, const char *rhs)
	{
		while(*rhs != '\0')
		{
			*lhs.endOfString = *rhs;
			++lhs.endOfString;
			++rhs;
		}
		lhs.setEndOfString();
		return lhs;
	}
	
	FastString operator+(FastString lhs, char rhs)
	{
		*lhs.endOfString = rhs;
		++lhs.endOfString;
		lhs.endOfString = nullptr;
		return lhs;
	}
	
	FastString operator-(FastString lhs, size_t size)
	{
		assert(size <= lhs.Size());
		for(size_t i = size; i > 0; --i)
			--lhs.endOfString;
		*lhs.endOfString = '\0';
		return lhs;
	}
}

namespace std
{
	ostream &operator<<(ostream &os, StringManipulation::FastString &str)
	{
		os << str.cstring; // FIXME this is where the \" is getting lost
		return os;
	}
	
	ostream &operator<<(ostream &os, const FastString &str)
	{
		os << str.cstring;
		return os;
	}
}
