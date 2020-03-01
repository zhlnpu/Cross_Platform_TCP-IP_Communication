#pragma once

void _check_gl_error(const char *file, int line);

///
/// Usage
/// [... some opengl calls]
/// glCheckError();
///
#define CHECK_GL_ERROR() _check_gl_error(__FILE__,__LINE__)
