/*
 * Copyright (C) 2009 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
package com.cpilab.cs.androidclient;

import android.app.Activity;
import android.widget.TextView;
import android.os.Bundle;

/**
 * This class loads the Java Native Interface (JNI)
 * library, 'libAndroid_Connect_Server_Test.so', and provides access to the
 * exposed C functions.
 * The library is packaged and installed with the application.
 * See the C file, /jni/Android_Connect_Server_Test.c file for the
 * implementations of the native methods. 
 * 
 * For more information on JNI, see: http://java.sun.com/docs/books/jni/
 */

public class Androidclient extends Activity
{
	/** Called when the activity is first created. */
	@Override
	public void onCreate(Bundle savedInstanceState)
	{
		super.onCreate(savedInstanceState);

		// Enter code here

		//String testnative=android_connect_server_testNative();
		 
        TextView tv = new TextView(this);
        tv.setText(testNative());
        setContentView(tv);
	}

	/**
	 * An example native method.  See the library function,
	 * <code>Java_com_cpilab_cs_androidclient_Android_Connect_Server_Test_android_connect_server_testNative</code>
	 * for the implementation.
	 */
	public native String testNative();

	/* This is the static constructor used to load the
	 * 'Android_Connect_Server_Test' library when the class is
	 * loaded.
	 */
	static {
		System.loadLibrary("Androidclient");
	}
}
