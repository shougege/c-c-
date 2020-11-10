package com.developerworks;
public class HelloJNI {
	// native 关键字告诉 JVM调用的是该方法在外部定义
	public native void sayHello();
	
	public native String getName(String name); 

	public native int getLengArray(int [] arr);
}
