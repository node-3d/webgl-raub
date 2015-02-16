#include "image.h"
#include <cstdlib>
#include <vector>
#include <iostream>

using namespace v8;
using namespace node;
using namespace std;

static vector<Image*> images;

static void registerImage(Image *obj) {
  images.push_back(obj);
}


static void unregisterImage(Image* obj) {
  vector<Image*>::iterator it = images.begin();
  while(it != images.end()) {
    if(*it==obj) {
      images.erase(it);
      break;
    }
    it++;
  }
}


Persistent<FunctionTemplate> Image::constructor_template;

void Image::Initialize (Handle<Object> target) {
  NanScope();

  // constructor
  Local<FunctionTemplate> ctor = FunctionTemplate::New(New);
  NanAssignPersistent(FunctionTemplate, constructor_template, ctor);
  ctor->InstanceTemplate()->SetInternalFieldCount(1);
  ctor->SetClassName(JS_STR("Image"));

  // prototype
  NODE_SET_PROTOTYPE_METHOD(ctor, "save", save);
  Local<ObjectTemplate> proto = ctor->PrototypeTemplate();
  proto->SetAccessor(JS_STR("width"), WidthGetter);
  proto->SetAccessor(JS_STR("height"), HeightGetter);
  proto->SetAccessor(JS_STR("pitch"), PitchGetter);
  proto->SetAccessor(JS_STR("src"), SrcGetter, SrcSetter);
  //proto->SetAccessor(JS_STR("onload"), NULL, OnloadSetter);

  target->Set(NanNew<String>("Image"), ctor->GetFunction());

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
  FIBITMAP *tmp = FreeImage_Load(format, filename, 0);
  image_bmp = FreeImage_ConvertTo32Bits(tmp);
  FreeImage_Unload(tmp);
}

NAN_METHOD(Image::New) {
  NanScope();

  Image *image = new Image();
  image->Wrap(args.This());
  registerImage(image);

  NanReturnValue(args.This());
}

NAN_GETTER(Image::WidthGetter) {
  NanScope();

  Image *image = ObjectWrap::Unwrap<Image>(args.This());

  NanReturnValue(JS_INT(image->GetWidth()));
}

NAN_GETTER(Image::HeightGetter) {
  NanScope();

  Image *image = ObjectWrap::Unwrap<Image>(args.This());

  NanReturnValue(JS_INT(image->GetHeight()));
}

NAN_GETTER(Image::PitchGetter) {
  NanScope();

  Image *image = ObjectWrap::Unwrap<Image>(args.This());

  NanReturnValue(JS_INT(image->GetPitch()));
}

NAN_GETTER(Image::SrcGetter) {
  NanScope();

  Image *image = ObjectWrap::Unwrap<Image>(args.This());

  NanReturnValue(JS_STR(image->filename));
}

NAN_SETTER(Image::SrcSetter) {
  NanScope();

  Image *image = ObjectWrap::Unwrap<Image>(args.This());
  String::Utf8Value filename_s(value->ToString());
  image->Load(*filename_s);

  // adjust internal fields
  size_t num_pixels = FreeImage_GetWidth(image->image_bmp) * FreeImage_GetHeight(image->image_bmp);
  BYTE *pixels = FreeImage_GetBits(image->image_bmp);
  size_t num_bytes = num_pixels * 4;

  // FreeImage stores data in BGR
  // Convert from BGR to RGB
  for(size_t i = 0; i < num_pixels; i++)
  {
    size_t i4=i<<2;
    BYTE temp = pixels[i4 + 0];
    pixels[i4 + 0] = pixels[i4 + 2];
    pixels[i4 + 2] = temp;
  }

  args.This()->ToObject()->SetIndexedPropertiesToExternalArrayData(pixels,
                                                       kExternalUnsignedByteArray,
                                                       (int) num_bytes);

  // emit event
  Local<Value> emit_v = args.This()->Get(NanNew<String>("emit"));
  assert(emit_v->IsFunction());
  Local<Function> emit_f = emit_v.As<Function>();

  Handle<Value> argv[2] = {
    JS_STR("load"), // event name
    value  // argument
  };

  TryCatch tc;

  emit_f->Call(args.This(), 2, argv);

  if (tc.HasCaught())
    FatalException(tc);
}

NAN_METHOD(Image::save) {
  NanScope();
  String::Utf8Value filename(args[0]->ToString());

  FREE_IMAGE_FORMAT format = FreeImage_GetFIFFromFilename(*filename);

  Local<Object> obj=args[1]->ToObject();
  void *buffer = obj->GetIndexedPropertiesExternalArrayData();

  uint32_t width=args[2]->ToUint32()->Value();
  uint32_t height=args[3]->ToUint32()->Value();

  uint32_t pitch=width*4, bpp=32;
  uint32_t redMask=0xFF000000, greenMask=0x00FF0000, blueMask=0x0000FF00;

  if(args.Length()>4) pitch=args[4]->ToUint32()->Value();
  if(args.Length()>5) bpp=args[5]->ToUint32()->Value();
  if(args.Length()>6) redMask=args[6]->ToUint32()->Value();
  if(args.Length()>7) greenMask=args[7]->ToUint32()->Value();
  if(args.Length()>8) blueMask=args[8]->ToUint32()->Value();

  FIBITMAP *image = FreeImage_ConvertFromRawBits(
      (BYTE*)buffer,
      width, height, pitch, bpp,
      redMask, greenMask, blueMask);

  if(format==FIF_JPEG && bpp!=24) {
    FIBITMAP *old=image;
    image=FreeImage_ConvertTo24Bits(image);
    FreeImage_Unload(old);
  }
  bool ret=FreeImage_Save(format, image, *filename)==1;
  FreeImage_Unload(image);
  NanReturnValue(Boolean::New(ret));
}

Image::~Image () {
  if (image_bmp) {
    #ifdef LOGGING
    cout<<"  Deleting image"<<endl;
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
  while(it != images.end()) {
    Image *img=*it;
    //v8::Persistent<v8::Value> value = img->handle_;
    //v8::Object* obj = v8::Object::Cast(*value);
    //BYTE* ptr = (BYTE*) obj->GetIndexedPropertiesExternalArrayData();
    //value.ClearWeak();
    //value.Dispose();
    if (img->image_bmp) {
      #ifdef LOGGING
      cout<<"  Deleting image"<<endl;
      #endif
      FreeImage_Unload(img->image_bmp);
      img->image_bmp=NULL;
    }

    it++;
  }
  FreeImage_DeInitialise();
}
