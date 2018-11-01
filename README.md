# How to Link Shared Library(.so) and Use It in Android Studio 
## Including C Code and Prebuilt Shared Library  
1. Build external library from source code with ndk-build tool
    * If you already have external library file(.so), skip this stage
    
2. Build my library from source code with ndk-build tool
    * when writing android.mk, use ***LOCAL_EXPORT_C_INCLUDES*** option to include <br>
    external library's header file

3. After build, compress libs folder to ***[AnyName].jar***
4. Copy folders in libs to [ProjectFolder]/app/src/main/jniLibs/
    * if jniLibs doesn't exist, make jniLibs
5. Copy [AnyName].jar to [ProjectFolder]/app/libs/
6. add below code in [ProjectFolder]/app/build.gradle
    <pre><code>
    implementation fileTree(include: ['*.jar'], dir: 'libs') 
    implementation files('libs/[AnyName].jar')
    </code></pre>

## Use the Libraries
1. add below code in app source code
    <pre><code>
    static{
        System.loadLibrary("[LibraryName]");
    }
    </code></pre>
2. declare function that you will use with ***native*** keyword
    <pre><code>example)
     public native string stringFromJNI();
    </code></pre>