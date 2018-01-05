#ifndef _IMAGE_HPP_
#define _IMAGE_HPP_

// These two includes must be in such a specific order
#include <nan.h>
#include <FreeImage.h>

#include "common.hpp"


class Image : public node::ObjectWrap {
	
public:
	static void Initialize (v8::Handle<v8::Object> target);
	static void AtExit();
	int GetWidth();
	int GetHeight();
	int GetPitch();
	void *GetData();
	void Load (const char *filename);
	
	
protected:
	static NAN_METHOD(New);
	static NAN_GETTER(WidthGetter);
	static NAN_GETTER(HeightGetter);
	static NAN_GETTER(SrcGetter);
	static NAN_SETTER(SrcSetter);
	static NAN_SETTER(OnloadSetter);
	static NAN_GETTER(PitchGetter);
	static NAN_METHOD(save);
	
	virtual ~Image();
	
	
private:
	static v8::Persistent<v8::Function> constructor_template;
	
	FIBITMAP *image_bmp;
	char *filename;
	void *data;
	
};

#endif // _IMAGE_HPP_
