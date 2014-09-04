/*
 * common.h
 *
 *  Created on: Dec 13, 2011
 *      Author: ngk437
 */

#ifndef COMMON_H_
#define COMMON_H_

#include <node.h>
#include "nan.h"
#include <v8.h>
#include "arch_wrapper.h"

namespace {
#define JS_STR(...) NanNew<v8::String>(__VA_ARGS__)
#define JS_INT(val) NanNew<v8::Integer>(val)
#define JS_FLOAT(val) NanNew<v8::Number>(val)
#define JS_BOOL(val) NanNew<v8::Boolean>(val)

}
#endif /* COMMON_H_ */
