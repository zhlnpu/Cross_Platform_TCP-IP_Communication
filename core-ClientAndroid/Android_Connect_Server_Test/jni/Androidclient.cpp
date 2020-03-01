/**********************************
 Java Native Interface library
**********************************/
#include <stdio.h>
#include <jni.h>
#include <string.h>
//#include "Listening_androidclient.h"


/** This is the C++ implementation of the Java native method.
@param env Pointer to JVM environment
@param thiz Reference to Java this object
*/

extern "C" JNIEXPORT jstring JNICALL Java_com_cpilab_cs_androidclient_Androidclient_testNative(JNIEnv* env, jobject thiz)
{
	// Enter code here
// 	ModelingData_androidclient m_androidclient;
// 	m_androidclient.Init("Localhost");

	return env->NewStringUTF("native method called");


}
