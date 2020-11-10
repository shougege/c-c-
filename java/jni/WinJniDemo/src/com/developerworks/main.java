package com.developerworks;
public class main {

	public	static void main(String[] args) {
		// write your code here
		Environment.initEnvironment();
		        // invoke the native method
	//	new HelloJNI().sayHello();  
		//new HelloJNI().getName();
		HelloJNI myhello = new HelloJNI();
		System.out.println(myhello.getName("true")); 
		int [] arr =  new int[] {1,2,3,4,5};
		System.out.println(myhello.getLengArray(arr));
	}
}

