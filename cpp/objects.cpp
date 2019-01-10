#include <cstring>
#include <vector>

#include <node_buffer.h>

#include "webgl.hpp"

using namespace node;
using namespace v8;
using namespace std;


#ifdef _WIN32
	#define	strcasestr(s, t) strstr(strupr(s), strupr(t))
#endif


namespace webgl {

struct GLObj {
	
	GLObjectType type;
	GLuint obj;
	
	GLObj(GLObjectType type, GLuint obj) {
		this->type = type;
		this->obj = obj;
	}
	
};


vector<GLObj*> globjs;
static bool atExit = false;

void registerGLObj(GLObjectType type, GLuint obj) {
	globjs.push_back(new GLObj(type, obj));
}


void unregisterGLObj(GLuint obj) {
	
	if (atExit) {
		return;
	}
	
	vector<GLObj*>::iterator it = globjs.begin();
	
	while (globjs.size() && it != globjs.end()) {
		
		GLObj *globj = *it;
		
		if (globj->obj == obj) {
			delete globj;
			globjs.erase(it);
			break;
		}
		
		++it;
		
	}
	
}

#define CASES_OBJECT_TYPE_PROGRAM case GLOBJECT_TYPE_PROGRAM:
#define CASES_OBJECT_TYPE_BUFFER case GLOBJECT_TYPE_BUFFER:
#define CASES_OBJECT_TYPE_FRAMEBUFFER case GLOBJECT_TYPE_FRAMEBUFFER:
#define CASES_OBJECT_TYPE_RENDERBUFFER case GLOBJECT_TYPE_RENDERBUFFER:
#define CASES_OBJECT_TYPE_SHADER case GLOBJECT_TYPE_SHADER:
#define CASES_OBJECT_TYPE_TEXTURE case GLOBJECT_TYPE_TEXTURE:

void deinit() {
	
	atExit = true;
	
	vector<GLObj*>::iterator it;
	
	it = globjs.begin();
	while(globjs.size() && it != globjs.end()) {
		
		GLObj *globj = *it;
		GLuint obj = globj->obj;
		
		switch(globj->type) {
		
		CASES_OBJECT_TYPE_PROGRAM
			glDeleteProgram(obj);
			break;
		
		CASES_OBJECT_TYPE_BUFFER
			glDeleteBuffers(1, &obj);
			break;
		
		CASES_OBJECT_TYPE_FRAMEBUFFER
			glDeleteFramebuffers(1, &obj);
			break;
		
		CASES_OBJECT_TYPE_RENDERBUFFER
			glDeleteRenderbuffers(1, &obj);
			break;
		
		CASES_OBJECT_TYPE_SHADER
			glDeleteShader(obj);
			break;
		
		CASES_OBJECT_TYPE_TEXTURE
			glDeleteTextures(1, &obj);
			break;
		
		default:
			break;
		
		}
		
		delete globj;
		++it;
		
	}
	
	globjs.clear();
	
}

} // namespace webgl
