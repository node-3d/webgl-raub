#ifndef _COMMON_HPP_
#define _COMMON_HPP_


#include <node.h>
#include <nan.h>
#include <v8.h>

#include <GL/glew.h>

#include <addon-tools.hpp>

#define USE_UINT32_ARG(I, VAR, DEF)                                          \
	CHECK_LET_ARG(I, IsUint32(), "uint32");                             \
	unsigned int VAR = IS_ARG_EMPTY(I) ? (DEF) : info[I]->Uint32Value();


#endif // _COMMON_HPP_
