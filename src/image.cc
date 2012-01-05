#include "image.h"
#include <cstdlib>

using namespace v8;
using namespace node;

Persistent<FunctionTemplate> Image::constructor_template;

void Image::Initialize (Handle<Object> target) {
  HandleScope scope;

  Local<FunctionTemplate> t = FunctionTemplate::New(New);
  constructor_template = Persistent<FunctionTemplate>::New(t);

  constructor_template->InstanceTemplate()->SetInternalFieldCount(1);
  constructor_template->SetClassName(JS_STR("Image"));

  constructor_template->PrototypeTemplate()->SetAccessor(JS_STR("width"), WidthGetter);
  constructor_template->PrototypeTemplate()->SetAccessor(JS_STR("height"), HeightGetter);
  constructor_template->PrototypeTemplate()->SetAccessor(JS_STR("pitch"), PitchGetter);
  constructor_template->PrototypeTemplate()->SetAccessor(JS_STR("src"), SrcGetter, SrcSetter);
  //constructor_template->PrototypeTemplate()->SetAccessor(JS_STR("onload"), NULL, OnloadSetter);

  target->Set(String::NewSymbol("Image"), constructor_template->GetFunction());

  FreeImage_Initialise(true);
}

int Image::GetWidth () {
  return FreeImage_GetWidth(image_bmp);
}

int Image::GetHeight () {
  return FreeImage_GetHeight(image_bmp);
}

int Image::GetPitch () {
  return FreeImage_GetPitch(image_bmp);
}

void *Image::GetData () {
  BYTE *pixels = FreeImage_GetBits(image_bmp);

  // FreeImage stores data in BGR
  // Convert from BGR to RGB
  int sz=FreeImage_GetWidth(image_bmp) * FreeImage_GetHeight(image_bmp);
  for(int i = 0; i < sz; i++)
  {
    int i4=i<<2;
    BYTE temp = pixels[i4 + 0];
    pixels[i4 + 0] = pixels[i4 + 2];
    pixels[i4 + 2] = temp;
  }

  return pixels;
}

void Image::Load (const char *filename) {
  this->filename = (char *)filename;

  FREE_IMAGE_FORMAT format = FreeImage_GetFileType(filename, 0);
  image_bmp = FreeImage_Load(format, filename, 0);
  image_bmp = FreeImage_ConvertTo32Bits(image_bmp);
}

Handle<Value> Image::New (const Arguments& args) {
  HandleScope scope;

  Image *image = new Image();
  image->Wrap(args.This());

  return args.This();
}

Handle<Value> Image::WidthGetter (Local<String> property, const AccessorInfo& info) {
  HandleScope scope;

  Image *image = ObjectWrap::Unwrap<Image>(info.This());

  return scope.Close(JS_INT(image->GetWidth()));
}

Handle<Value> Image::HeightGetter (Local<String> property, const AccessorInfo& info) {
  HandleScope scope;

  Image *image = ObjectWrap::Unwrap<Image>(info.This());

  return scope.Close(JS_INT(image->GetHeight()));
}

Handle<Value> Image::PitchGetter (Local<String> property, const AccessorInfo& info) {
  HandleScope scope;

  Image *image = ObjectWrap::Unwrap<Image>(info.This());

  return scope.Close(JS_INT(image->GetPitch()));
}

Handle<Value> Image::SrcGetter (Local<String> property, const AccessorInfo& info) {
  HandleScope scope;

  Image *image = ObjectWrap::Unwrap<Image>(info.This());

  return scope.Close(JS_STR(image->filename));
}

void Image::SrcSetter (Local<String> property, Local<Value> value, const AccessorInfo& info) {
  HandleScope scope;

  Image *image = ObjectWrap::Unwrap<Image>(info.This());
  String::Utf8Value filename_s(value->ToString());
  image->Load(*filename_s);

  // adjust internal fields
  size_t num_bytes = FreeImage_GetWidth(image->image_bmp) * FreeImage_GetHeight(image->image_bmp);
  BYTE *pixels = FreeImage_GetBits(image->image_bmp);

  // FreeImage stores data in BGR
  // Convert from BGR to RGB
  for(int i = 0; i < num_bytes; i++)
  {
    int i4=i<<2;
    BYTE temp = pixels[i4 + 0];
    pixels[i4 + 0] = pixels[i4 + 2];
    pixels[i4 + 2] = temp;
  }

  info.This()->ToObject()->SetIndexedPropertiesToExternalArrayData(pixels,
                                                       kExternalUnsignedByteArray,
                                                       num_bytes);

  // emit event
  Local<Value> emit_v = info.This()->Get(String::NewSymbol("emit"));
  assert(emit_v->IsFunction());
  Local<Function> emit_f = emit_v.As<Function>();

  Handle<Value> argv[2] = {
    JS_STR("load"), // event name
    value  // argument
  };

  TryCatch tc;

  emit_f->Call(info.This(), 2, argv);

  if (tc.HasCaught())
    FatalException(tc);
}

/*void Image::OnloadSetter (Local<String> property, Local<Value> value, const AccessorInfo& info) {
  HandleScope scope;

  Image *image = ObjectWrap::Unwrap<Image>(info.This());

  // emit event
  Local<Value> cb = value;
  assert(cb->IsFunction());
  Local<Function>cb_f = cb.As<Function>();

  TryCatch tc;

  cb_f->Call(info.This(), 0, NULL);

  if (tc.HasCaught())
    FatalException(tc);
}*/

Image::~Image () {
  if (image_bmp) FreeImage_Unload(image_bmp);
  FreeImage_DeInitialise();
}

