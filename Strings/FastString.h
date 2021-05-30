//
// Created by zerophase on 5/30/21.
//

#ifndef MOCKSTRING_FASTSTRING_H
#define MOCKSTRING_FASTSTRING_H


#include <iosfwd>

#define DEFAULT_MALLOC_VALUE 256

namespace StringManipulation
{
	struct FastString;
	FastString operator+(FastString lhs, const FastString &rhs);
	FastString operator+(FastString lhs, char rhs);
	FastString operator+(FastString lhs, const char*rhs);
	FastString operator-(FastString lhs, size_t size);
	
	
	struct FastString
	{
		FastString();
		explicit FastString(char *str);
		explicit FastString(const char *str);
		FastString(const char *str, size_t malloc_size);
		FastString(const FastString &other, size_t malloc_size);
		FastString(const FastString &other);
		~FastString();
		
		FastString &operator+=(const char *str);
		FastString &operator+=(char *str);
		FastString &operator+=(FastString &str);
		FastString &operator+=(const FastString &str);
		FastString &operator-=(int decrement);
		FastString &operator=(const FastString& str);
		FastString &operator=(const char *str);
		FastString &operator=(const char &str);
		FastString &operator+=(size_t size);
		
		friend FastString operator+(FastString lhs, const FastString &rhs);
		friend FastString operator+(FastString lhs, char rhs);
		friend FastString operator+(FastString lhs, const char*rhs);
		friend FastString operator-(FastString lhs, size_t size);
		
		char &operator[] (size_t index) const;
		void *operator new(size_t size);
		void operator delete(void *ptr);
		bool operator<(const FastString &a) const;
		bool operator==(const FastString &a) const;
		
		char *cstring;
		
		[[nodiscard("returns pointer")]] char * GetEndofString() const { return endOfString; }
		[[nodiscard("pointer math")]] size_t Size() const;
		[[nodiscard]] size_t GetMallocStringSize() const { return malloc_string_size; }
		void erase(size_t pos, size_t length);
		void eraseFromStart(size_t length);
		void insert(size_t position, const char *str);
		void replace(size_t startPos, size_t len, const char *str);
		FastString SubString(char * sub) const;
		
		void Reallocate() { reallocate(); }
	
	private:
		void advanceString(const char *str);
		inline void setEndOfString(size_t len);
		inline void setEndOfString();
		void reallocate();
	
	private:
		char *endOfString;
		size_t malloc_string_size = DEFAULT_MALLOC_VALUE;
	};
}


#endif //MOCKSTRING_FASTSTRING_H
