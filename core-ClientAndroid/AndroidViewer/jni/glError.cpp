#include "glError.h"

#if defined ANDROID
#  include <GLES/gl.h>
#  include <GLES/glext.h>
#else
#  include <OpenGLES/ES1/gl.h>
#  include <OpenGLES/ES1/glext.h>
#endif

#include <android/log.h>

#include <string>

using namespace std;

#define  LOG_TAG    "GL_ERROR"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

void _check_gl_error(const char *file, int line) {
	GLenum err(glGetError());

	while (err != GL_NO_ERROR) {
		string error;

		switch (err) {
		case GL_INVALID_OPERATION:      error = "GL_INVALID_OPERATION";		break;
		case GL_INVALID_ENUM:           error = "GL_INVALID_ENUM";			break;
		case GL_INVALID_VALUE:          error = "GL_INVALID_VALUE";			break;
		case GL_OUT_OF_MEMORY:          error = "GL_OUT_OF_MEMORY";			break;
		default:															break;
		}

		LOGE("%s - %s: %s\n", error.c_str(), file, line);
		err = glGetError();
	}
}
