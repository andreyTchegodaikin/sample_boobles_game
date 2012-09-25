/*
  color in A8R8G8B8 format

SUMMARY:
  цвет в 32-разрядном целом
*/
#ifndef RGBA32_H
#define RGBA32_H
//-------------------------------------------------------------------------------

#include <stdint.h>

//#define ARGB(a, r, g, b) ((uint32_t(a)<<24) + (uint32_t(r)<<16) + (uint32_t(g)<<8) + uint32_t(b))
//#define GETA(col)		((col)>>24)
//#define GETR(col)		(((col)>>16) & 0xFF)
//#define GETG(col)		(((col)>>8) & 0xFF)
//#define GETB(col)		((col) & 0xFF)
//#define SETA(col,a)		(((col) & 0x00FFFFFF) + (uint32_t(a)<<24))
//#define SETR(col,r)		(((col) & 0xFF00FFFF) + (uint32_t(r)<<16))
//#define SETG(col,g)		(((col) & 0xFFFF00FF) + (uint32_t(g)<<8))
//#define SETB(col,b)		(((col) & 0xFFFFFF00) + uint32_t(b))

// цвет в формате R8G8B8A8
struct rgba32_t
{
public:
  uint32_t      code;       //цвет одним 32-разрядным беззнаковым целым числом
public:
	rgba32_t(uint32_t vol = 0xffffffff):code(vol) {};
	rgba32_t(uint32_t r, uint32_t g, uint32_t b, uint32_t a): code((uint32_t(r)<<24) + (uint32_t(g)<<16) + (uint32_t(b)<<8) + uint32_t(a)) {};
	uint32_t red() const
	{
		return ((code)>>24);
	};
	uint32_t red(uint32_t r)
	{
		return code = (((code) & 0x00FFFFFF) + (uint32_t(r)<<24));
	};
	uint32_t green() const
	{
		return (((code)>>16) & 0xFF);
	};
	uint32_t green(uint32_t g)
	{
		return code = (((code) & 0xFF00FFFF) + (uint32_t(g)<<16));
	};
	uint32_t blue()
	{
		return (((code)>>8) & 0xFF);
	};
	uint32_t blue(uint32_t b)
	{
		return code = (((code) & 0xFFFF00FF) + (uint32_t(b)<<8));
	};
	uint32_t alpha()
	{
		return ((code) & 0xFF);
	};
	uint32_t alpha(uint32_t a)
	{
		return code = (((code) & 0xFFFFFF00) + uint32_t(a));
	};
};

//-------------------------------------------------------------------------------
#endif //RGBA32_H
