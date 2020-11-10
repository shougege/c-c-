package com.developerworks;

public class Environment {
    public static boolean initEnvironment() {

        String OS = System.getProperty("os.name").toLowerCase();
        boolean isLinux = false;

        if (OS.indexOf("windows") > -1) {

            String strLibPath = "C:\\Users\\Administrator\\source\\repos\\hello\\x64\\Debug\\hello.dll";
            System.load(strLibPath);
            return true;

        } else if (OS.indexOf("linux") > -1) {

            String strLibPath = "/home/work/JavaCodeLib/JNI_Learn/hello/hello/hello.so"; 
            System.load(strLibPath);
            return true;
        }
        else if (OS.indexOf("linux") > -1) {

            String strLibPath = "/home/work/JavaCodeLib/JNI_Learn/hello/hello/hello.so";
            System.load(strLibPath);
            return true;
        }
        else if (OS.indexOf("unix") > -1) {

            String strLibPath = "/home/work/JavaCodeLib/JNI_Learn/hello/hello/hello.so";
            System.load(strLibPath);
            return true;
        }
        else if (OS.indexOf("solaris") > -1) {

            String strLibPath = "/home/work/JavaCodeLib/JNI_Learn/hello/hello/hello.so";
            System.load(strLibPath);
            return true;
        }
        else if (OS.indexOf("mac") > -1) {
            String strLibPath = "/Users/wang/javaPrj/hello.dylib";
            System.load(strLibPath);
            return true;
        }
       else
        {
             return false;
        }

   }
}
