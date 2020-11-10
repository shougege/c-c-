// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"
#include "com_developerworks_HelloJNI.h"
#include<stdio.h>
#include<iostream>
using namespace std;
JNIEXPORT void JNICALL Java_com_developerworks_HelloJNI_sayHello
(JNIEnv* env, jobject obj)
{
    printf("Hello,JNI! \n");
}
JNIEXPORT jstring JNICALL Java_com_developerworks_HelloJNI_getName
(JNIEnv* env, jobject obj, jstring prompt)
{

    const char* str;
    jboolean b = false;
    str = env->GetStringUTFChars(prompt,&b);
    if (str == NULL)
    {
        return NULL;// OutOfMemoryError already throw
        
    }
    std::cout << str << std::endl;
    env->ReleaseStringUTFChars(prompt, str);
    char* tmpstr = (char*)"return string succeeded";
    jstring rtstr = env->NewStringUTF(tmpstr);

    return rtstr;
}
JNIEXPORT jint JNICALL Java_com_developerworks_HelloJNI_getLengArray
(JNIEnv* env, jobject obj, jintArray arr)
{
    jint* carr = NULL;
    carr = env->GetIntArrayElements(arr, false);
    if (carr == NULL)
    {
        return 0;
    }
    int size = env->GetArrayLength(arr);
    jint sum = 0;
    for (int i = 0; i < size; i++)
    {
        printf("%d ", carr[i]);
        sum += carr[i];
    }
    env->ReleaseIntArrayElements(arr, carr, 0);
    return sum;

}
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

