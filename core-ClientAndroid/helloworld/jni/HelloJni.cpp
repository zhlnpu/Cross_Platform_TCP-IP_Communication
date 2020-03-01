#include <stdio.h>
#include <string.h>
#include <jni.h>
#include "Listeningandroidclient.h"

/* This is a trivial JNI example where we use a native method
 * to return a new VM String. See the corresponding Java source
 */


ModelingData_androidclient androidclient;

extern "C" JNIEXPORT jstring JNICALL Java_com_example_hellojni_HelloJni_stringFromJNI(JNIEnv* env, jobject thiz)
{

	if (androidclient.Init())
		return env->NewStringUTF("connected to server");
	else
		return env->NewStringUTF("NO NO NO NO NO");



}
