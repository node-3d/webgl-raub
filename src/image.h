#ifndef IMAGE_H_
#define IMAGE_H_

#include "common.h"

#include <FreeImage.h>

using namespace v8;
using namespace node;

class Image : public ObjectWrap {
public:
  static void Initialize (Handle<Object> target);
  int GetWidth ();
  int GetHeight ();
  void *GetData ();
  void Load (const char *filename);

protected:
  static Handle<Value> New (const Arguments& args);
  static Handle<Value> WidthGetter (Local<String> property, const AccessorInfo& info);
  static Handle<Value> HeightGetter (Local<String> property, const AccessorInfo& info);
  static Handle<Value> SrcGetter (Local<String> property, const AccessorInfo& info);
  static void SrcSetter (Local<String> property, Local<Value> value, const AccessorInfo& info);
  static void OnloadSetter (Local<String> property, Local<Value> value, const AccessorInfo& info);

  ~Image ();

private:
  FIBITMAP *image_bmp;
  char *filename;
  void *data;
};

#endif  // IMAGE_H_
