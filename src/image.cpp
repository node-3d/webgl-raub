#include <cstdlib>
#include <vector>
#include <iostream>

#include "image.hpp"

using namespace v8;
using namespace node;
using namespace std;


static vector<Image*> images;


static void registerImage(Image *obj) {
	images.push_back(obj);
}


static void unregisterImage(Image* obj) {
	vector<Image*>::iterator it = images.begin();
	while (it != images.end()) {
		if (*it == obj) {
			images.erase(it);
			break;
		}
		it++;
	}
}


Persistent<Function> Image::constructor_template;


void Image::Initialize(Handle<Object> target) { NAN_HS;
	
	// constructor
	Local<FunctionTemplate> ctor = Nan::New<FunctionTemplate>(New);
	ctor->InstanceTemplate()->SetInternalFieldCount(1);
	ctor->SetClassName(JS_STR("Image"));
	
	// prototype
	Nan::SetPrototypeMethod(ctor, "save",save);// NODE_SET_PROTOTYPE_METHOD(ctor, "save", save);
	Local<ObjectTemplate> proto = ctor->PrototypeTemplate();
	
	Nan::SetAccessor(proto,JS_STR("width"), WidthGetter);
	Nan::SetAccessor(proto,JS_STR("height"), HeightGetter);
	Nan::SetAccessor(proto,JS_STR("pitch"), PitchGetter);
	Nan::SetAccessor(proto,JS_STR("src"), SrcGetter, SrcSetter);
	Nan::Set(target, JS_STR("Image"), ctor->GetFunction());
	
	constructor_template.Reset(Isolate::GetCurrent(), ctor->GetFunction());
	
	FreeImage_Initialise(true);
	
}


int Image::GetWidth() {
	return FreeImage_GetWidth(image_bmp);
}


int Image::GetHeight () {
	return FreeImage_GetHeight(image_bmp);
}


int Image::GetPitch() {
	return FreeImage_GetPitch(image_bmp);
}


void *Image::GetData() {
	
	BYTE *pixels = FreeImage_GetBits(image_bmp);
	
	// FreeImage stores data in BGR
	// Convert from BGR to RGB
	int sz=FreeImage_GetWidth(image_bmp) * FreeImage_GetHeight(image_bmp);
	for(int i = 0; i < sz; i++)
	{
		int i4 = i << 2;
		BYTE temp = pixels[i4 + 0];
		pixels[i4 + 0] = pixels[i4 + 2];
		pixels[i4 + 2] = temp;
	}
	
	return pixels;
	
}


void Image::Load(const char *filename) {
	
	this->filename = (char *)filename;
	
	FREE_IMAGE_FORMAT format = FreeImage_GetFileType(filename, 0);
	FIBITMAP *tmp = FreeImage_Load(format, filename, 0);
	image_bmp = FreeImage_ConvertTo32Bits(tmp);
	FreeImage_Unload(tmp);
	
}


NAN_METHOD(Image::New) { NAN_HS;
	
	Image *image = new Image();
	image->Wrap(info.This());
	registerImage(image);
	
	RET_VALUE(info.This());
	
}


NAN_GETTER(Image::WidthGetter) { NAN_HS;
	
	Image *image = ObjectWrap::Unwrap<Image>(info.This());
	
	RET_VALUE(JS_INT(image->GetWidth()));
	
}


NAN_GETTER(Image::HeightGetter) { NAN_HS;
	
	Image *image = ObjectWrap::Unwrap<Image>(info.This());
	
	RET_VALUE(JS_INT(image->GetHeight()));
	
}


NAN_GETTER(Image::PitchGetter) { NAN_HS;
	
	Image *image = ObjectWrap::Unwrap<Image>(info.This());
	
	RET_VALUE(JS_INT(image->GetPitch()));
	
}


NAN_GETTER(Image::SrcGetter) { NAN_HS;
	
	Image *image = ObjectWrap::Unwrap<Image>(info.This());
	
	RET_VALUE(JS_STR(image->filename));
	
}


NAN_SETTER(Image::SrcSetter) { NAN_HS;
	
	Nan::MaybeLocal<v8::Object> buffer;
	
	Image *image = ObjectWrap::Unwrap<Image>(info.This());
	String::Utf8Value filename_s(value->ToString());
	image->Load(*filename_s);
	
	// adjust internal fields
	size_t num_pixels = FreeImage_GetWidth(image->image_bmp) * FreeImage_GetHeight(image->image_bmp);
	BYTE *pixels = FreeImage_GetBits(image->image_bmp);
	size_t num_bytes = num_pixels * 4;
	
	// FreeImage stores data in BGR
	// Convert from BGR to RGB
	for (size_t i = 0; i < num_pixels; i++) {
		size_t i4 = i << 2;
		BYTE temp = pixels[i4 + 0];
		pixels[i4 + 0] = pixels[i4 + 2];
		pixels[i4 + 2] = temp;
	}
	
	buffer= Nan::NewBuffer((int)num_bytes);
	
	std::memcpy(node::Buffer::Data(buffer.ToLocalChecked()), pixels, (int)num_bytes);
	
	Nan::Set(info.This(), JS_STR("data"), buffer.ToLocalChecked());
	
	// emit event
	Nan::MaybeLocal<Value> emit_v = Nan::Get(info.This(), JS_STR("emit"));//info.This()->Get(Nan::New<String>("emit"));
	assert(emit_v.ToLocalChecked()->IsFunction());
	Local<Function> emit_f = emit_v.ToLocalChecked().As<Function>();
	
	Handle<Value> argv[2] = {
		JS_STR("load"), // event name
		value	// argument
	};
	
	TryCatch tc;
	
	emit_f->Call(info.This(), 2, argv);
	
	if (tc.HasCaught()) {
		FatalException(info.GetIsolate(),tc);
	}
	
}


NAN_METHOD(Image::save) { NAN_HS;
	
	REQ_UTF8_ARG(0, filename)
	
	FREE_IMAGE_FORMAT format = FreeImage_GetFIFFromFilename(*filename);
	
	void *buffer = node::Buffer::Data(info[1]);
	
	REQ_UINT32_ARG(2, width);
	REQ_UINT32_ARG(3, height);
	
	USE_UINT32_ARG(4, pitch, width * 4);
	USE_UINT32_ARG(5, bpp, 32);
	USE_UINT32_ARG(6, redMask, 0xFF000000);
	USE_UINT32_ARG(7, greenMask, 0x00FF0000);
	USE_UINT32_ARG(8, blueMask, 0x0000FF00);
	
	FIBITMAP *image = FreeImage_ConvertFromRawBits(
		(BYTE*)buffer,
		width, height,
		pitch, bpp,
		redMask, greenMask, blueMask
	);
	
	if (format == FIF_JPEG && bpp != 24) {
		FIBITMAP *old = image;
		image = FreeImage_ConvertTo24Bits(image);
		FreeImage_Unload(old);
	}
	
	bool ret = FreeImage_Save(format, image, *filename) == 1;
	FreeImage_Unload(image);
	
	RET_VALUE(Nan::New<Boolean>(ret));
	
}


Image::~Image() {
	
	if (image_bmp) {
		#ifdef LOGGING
		cout<<"	Deleting image"<<endl;
		#endif
		FreeImage_Unload(image_bmp);
	}
	
	unregisterImage(this);
	
}


void Image::AtExit() {
	
	#ifdef LOGGING
	cout<<"Image AtExit()"<<endl;
	#endif
	
	vector<Image*>::iterator it = images.begin();
	while (it != images.end()) {
		Image *img = *it;
		
		if (img->image_bmp) {
			#ifdef LOGGING
			cout<<"	Deleting image"<<endl;
			#endif
			FreeImage_Unload(img->image_bmp);
			img->image_bmp = NULL;
		}
		
		it++;
	}
	
	FreeImage_DeInitialise();
	
}
