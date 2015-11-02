#ifndef IMAGE_H_
#define IMAGE_H_

#include "common.h"

#include <FreeImage.h>

using namespace v8;
using namespace node;

class Image : public ObjectWrap {
public:
  static void Initialize (Handle<Object> target);
  static void AtExit();
  int GetWidth ();
  int GetHeight ();
  int GetPitch ();
  void *GetData ();
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

  virtual ~Image ();

private:
  static Persistent<Function> constructor_template;

  FIBITMAP *image_bmp;
  char *filename;
  void *data;
};

#endif  // IMAGE_H_
