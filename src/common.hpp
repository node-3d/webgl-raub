#ifndef _COMMON_HPP_
#define _COMMON_HPP_


#include <node.h>
#include <nan.h>
#include <v8.h>


#include <GL/glew.h>

#define JS_STR(...) Nan::New<String>(__VA_ARGS__).ToLocalChecked()
#define JS_INT(val) Nan::New<v8::Integer>(val)
#define JS_NUM(val) Nan::New<v8::Number>(val)
#define JS_BOOL(val) (val) ? Nan::True() : Nan::False()
#define JS_RETHROW(tc) v8::Local<v8::Value>::New(tc.Exception());

#define REQ_ARGS(N)                                                     \
	if (info.Length() < (N))                                            \
		Nan::ThrowTypeError("Expected at least " #N " arguments");

#define REQ_STR_ARG(I, VAR)                                             \
	if (info.Length() <= (I) || ! info[I]->IsString())                  \
		Nan::ThrowTypeError("Argument " #I " must be a string");        \
	String::Utf8Value _v8_##VAR(info[I]->ToString());                   \
	std::string _std_##VAR = std::string(*_v8_##VAR);                   \
	const char *VAR = _std_##VAR.c_str();

#define REQ_UTF8_ARG(I, VAR)                                            \
	if (info.Length() <= (I) || ! info[I]->IsString())                  \
		Nan::ThrowTypeError("Argument " #I " must be a string");        \
	String::Utf8Value VAR(info[I]);

#define REQ_INT32_ARG(I, VAR)                                           \
	if (info.Length() <= (I) || ! info[I]->IsInt32())                   \
		Nan::ThrowTypeError("Argument " #I " must be an int32");        \
	int VAR = info[I]->Int32Value();

#define LET_INT32_ARG(I, VAR)                                           \
	if ( ! (info[I]->IsNull() || info[I]->IsInt32()) )                  \
		Nan::ThrowTypeError("Argument " #I " must be an int32 or null");\
	int VAR = info[I]->IsNull() ? 0 : info[I]->Int32Value();

#define REQ_BOOL_ARG(I, VAR)                                            \
	if (info.Length() <= (I) || ! info[I]->IsBoolean())                 \
		Nan::ThrowTypeError("Argument " #I " must be a bool");          \
	int VAR = info[I]->BooleanValue();

#define REQ_UINT32_ARG(I, VAR)                                          \
	if (info.Length() <= (I) || ! info[I]->IsUint32())                  \
		Nan::ThrowTypeError("Argument " #I " must be a uint32");        \
	unsigned int VAR = info[I]->Uint32Value();

#define USE_UINT32_ARG(I, VAR, DEF)                                     \
	if ( ! (info[I]->IsNull() || info[I]->IsUint32()) )                 \
		Nan::ThrowTypeError("Argument " #I " must be an uint32 or null");\
	unsigned int VAR = info[I]->IsNull() ? (DEF) : info[I]->Uint32Value();
	
#define LET_UINT32_ARG(I, VAR)                                          \
	USE_UINT32_ARG(I, VAR, 0)

#define REQ_INT_ARG(I, VAR)                                             \
	if (info.Length() <= (I) || ! info[I]->IsNumber())                  \
		Nan::ThrowTypeError("Argument " #I " must be a int");           \
	size_t VAR = static_cast<size_t>(info[I]->IntegerValue());

#define REQ_DOUBLE_ARG(I, VAR)                                          \
	if (info.Length() <= (I) || ! info[I]->IsNumber())                  \
		Nan::ThrowTypeError("Argument " #I " must be a int");           \
	double VAR = static_cast<size_t>(info[I]->NumberValue());

#define REQ_FLOAT_ARG(I, VAR)                                           \
	if (info.Length() <= (I) || ! info[I]->IsNumber())                  \
		Nan::ThrowTypeError("Argument " #I " must be a int");           \
	float VAR = static_cast<float>(info[I]->NumberValue());

#define REQ_EXT_ARG(I, VAR)                                             \
	if (info.Length() <= (I) || ! info[I]->IsExternal())                \
		Nan::ThrowTypeError("Argument " #I " invalid");                 \
	Local<External> VAR = Local<External>::Cast(info[I]);

#define REQ_FUN_ARG(I, VAR)                                             \
	if (info.Length() <= (I) || ! info[I]->IsFunction())                \
		Nan::ThrowTypeError("Argument " #I " must be a function");      \
	Local<Function> VAR = Local<Function>::Cast(info[I]);

#define REQ_OBJ_ARG(I, VAR)                                             \
	if (info.Length() <= (I) || ! info[I]->IsObject())                  \
		Nan::ThrowTypeError("Argument " #I " must be an object");       \
	Local<Object> VAR = Local<Object>::Cast(info[I]);

#define REQ_ARRV_ARG(I, VAR)                                            \
	REQ_OBJ_ARG(I, _obj_##VAR);                                         \
	if( ! _obj_##VAR->IsArrayBufferView() )                             \
		Nan::ThrowTypeError("Argument " #I " must be an array buffer"); \
	Local<ArrayBufferView> VAR = Local<ArrayBufferView>::Cast(_obj_##VAR);

#define REQ_ERROR_THROW(error)                                          \
	if (ret == error)                                                   \
		Nan::ThrowError(String::New(#error));

#define NAN_HS Nan::HandleScope scope;

#define RET_VALUE(VAL) info.GetReturnValue().Set(VAL);
#define RET_UNDEFINED info.GetReturnValue().Set(Nan::Undefined());

#endif // _COMMON_HPP_
