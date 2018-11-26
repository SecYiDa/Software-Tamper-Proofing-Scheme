#include <jni.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <android/log.h>
#include <unistd.h>
#include <fstream>
#include <math.h>
#include <iostream>

static double weights1;
static double weights2;
static double weights3;
static double watermark_valu;
static jclass contextClass;
static jclass signatureClass;
static jclass packageNameClass;
static jclass packageInfoClass;

const char *getSignString(JNIEnv *env, jobject contextObject) {
    int i;
    char sa[11];
    char sb[30];
    char ma[] = {"fdwgHIHfas"};
    char mb[] = {"FhfshGDHgsdhaeGASHhhggajdheoh"};
    char keya[] = {21,13,16,9,41,61,61,20,4,0};
    char keyb[] = {10,9,8,23,26,40,45,44,72,16,11,6,21,0,41,53,124,56,5,71,52,14,6,4,5,28,16,29,13};
    for(i = 0;i < strlen(ma);i++)
    {
        sa[i] = keya[i] ^ ma[i];
    }
    for(i = 0;i < strlen(mb);i++)
    {
        sb[i] = keyb[i] ^ mb[i];
    }
    jmethodID getPackageManagerId = (env)->GetMethodID(contextClass, "getPackageManager",
                                                       "()Landroid/content/pm/PackageManager;");
    jmethodID getPackageNameId = (env)->GetMethodID(contextClass, "getPackageName",
                                                    "()Ljava/lang/String;");
    jmethodID signToStringId = (env)->GetMethodID(signatureClass, "toCharsString",
                                                  "()Ljava/lang/String;");
    jmethodID getPackageInfoId = (env)->GetMethodID(packageNameClass, "getPackageInfo",
                                                    "(Ljava/lang/String;I)Landroid/content/pm/PackageInfo;");
    jobject packageManagerObject = (env)->CallObjectMethod(contextObject, getPackageManagerId);
    jstring packNameString = (jstring) (env)->CallObjectMethod(contextObject, getPackageNameId);
    jobject packageInfoObject = (env)->CallObjectMethod(packageManagerObject, getPackageInfoId,
                                                        packNameString, 64);
    jfieldID signaturefieldID = (env)->GetFieldID(packageInfoClass,sa,
                                                  sb);
    jobjectArray signatureArray = (jobjectArray) (env)->GetObjectField(packageInfoObject,
                                                                       signaturefieldID);
    jobject signatureObject = (env)->GetObjectArrayElement(signatureArray, 0);
    return (env)->GetStringUTFChars(
                                    (jstring) (env)->CallObjectMethod(signatureObject, signToStringId), 0);
}


double sigmoid(double val){
    return 2.0 /(1.0 + exp(-2*val))-1;
}  // Sigmoid_function


void read_data_one(long int x,double Input[])   //NN1——读代码模块
{
    long int *p =(long int *) read_data_one;
    long int *& q = p;
    
    unsigned char c;
    long int b = *(q+x);                //代码1处
    int d =56;
    unsigned char &c_1=c;
    for(int i=0;i<=7;i++)
    {
        c_1 = b >> d;
        d = d-8;
        Input[i] = c_1;
    }
    long int *&l = p;
    b = *(l+x+1);                       //代码2处
    d =56;
    unsigned char &c_2=c;
    for(int i=0;i<=7;i++)
    {
        c_2 = b >> d;
        d = d-8;
        Input[i+8] = c_2;
    }
    long int *&h = p;
    b = *(h+x+2);                         //代码3处
    d =56;
    for(int i=0;i<=7;i++)
    {
        c = b >> d;
        d = d-8;
        Input[i+16] = c;
    }
    b = *(h+x+3);                         //代码4处
    d =56;
    for(int i=0;i<=7;i++)
    {
        c = b >> d;
        d = d-8;
        Input[i+24] = c;
    }
}   // check_read_text_for_NN2 ----> 第二层神经网络读代码段返回值,第二层神经网络读代码段 ，路径水印修改返回地址处, strcmp处跳转代码



void read_data_two(long int x,double Input[])   //NN2--读代码模块
{
    long int *p =(long int *) read_data_two;
    long int *& q = p;
    
    unsigned char c;
    long int b = *(q+x);                //读代码1处   watermark_valu;
    
    int d =56;
    unsigned char &c_1=c;
    for(int i=0;i<=7;i++)
    {
        c_1 = b >> d;
        d = d-8;
        Input[i] = c_1;
    }
    long int *&l = p;
    b = *(l+x+1);                        //读代码2处
    d =56;
    unsigned char &c_2=c;
    for(int i=0;i<=7;i++)
    {
        c_2 = b >> d;
        d = d-8;
        Input[i+8] = c_2;
    }
    long int *&h = p;
    b = *(h+x+2);                         //读代码3处
    d =56;
    for(int i=0;i<=7;i++)
    {
        c = b >> d;
        d = d-8;
        Input[i+16] = c;
    }
    b = *(h+x+3);                          //读代码4处
    d =56;
    for(int i=0;i<=7;i++)
    {
        c = b >> d;
        d = d-8;
        Input[i+24] = c;
    }
}   //check_read_text_for_NN1 -------> 神经网络1的读代码段返回值,错误响应模块,edit_ret模块



void read_text_for_RELEASE_SIGN(double a,double b,double c){
    size_t x = 1;
    long int p = (long int) watermark;
    long int *j = (long int *) p;
    long int *j_1 = j;
    long int *j_2 = j;
    unsigned int h;
    size_t *local = &x;
    size_t &y = x;
    size_t *local_1 = local;
    h = *(local + 70 * y);
    long int *j = (long int *) h;
    unsigned char q;
    int d =56;
    q = b >> d;
    d = d-8;
    a = q;
    q = b >> d;
    d = d-8;
    b = q;
    q = b >> d;
    d = d-8;
    c = q;
}              //读取代码给weights




double nn_calculate(double a,double b,double c)
{
    
    double result[4];
    
    a = 2*(a-32.65)/1.57-1;    //归一化
    b = 2*(b+2000)/4000-1;      //归一化
    
    
    result[0] = sigmoid((a*(-2.0468))+(b*1702.7)-2.6066);
    result[1] = sigmoid(a*1.4429+1+b*1646.1);
    result[2] = sigmoid(a*(773.08)+773.21+b*(-1549));
    result[3] = sigmoid(a*(786.21)+785.96+b*(1574));
    
    result[0] = result[0]*(-117.92);
    result[1] = result[1]*256.34;
    result[2] = result[2]*(-112.27);
    result[3] = result[3]*(-250.69);
    result[0] = sigmoid(result[0]+result[1]+result[2]+result[3]+0.79206);
    
    result[0] = (result[0]+1)*(94000010-10)/2+0;  //反归一化
    
    return result[0];
    
}


void watermark(int init)  //路径水印，返回值用于NN_2的读代码偏移

{
    size_t x = 1;
    long int p = (long int) watermark;
    long int *j = (long int *) p;
    long int *j_1 = j;
    long int *j_2 = j;
    
    size_t *local = &x;
    
    size_t *local_1 = local;     //watermark 栈定位
    
    unsigned char c;
    long int b = *(j_2 + x);     //读取一个数据进行操作
    
    double factor;              //factor--水印分支操作对象
    double &factor_1 = factor;
    double &factor_2 = factor;
    
    c = b >> 8;
    factor_1 = c;
    
    int counter = 3;            //迭代次数
    
    for (int i = 0; i < counter; i++, init >>= 1) {
        if ((init & 1) == 1) {
            factor_1 += 1;
            
        } else {
            factor_1 -= 133;
        }
        
    }
    watermark_valu = factor_2;
    
    size_t &y = x;  //指针引用
    
    init =94*init-752;           //此时条件变量 8 --A----0  和  9---B----60
    
    *(local + 89 * y)+=init;   // 94    /103 修改nn_predict_1 的返回地址
}


void edit_ret(int init)       //根据NN2计算结果修改发挥地址，决定分支方向
{
    size_t x = 1;
    size_t &y =x;
    
    size_t *local_1 = &x;
    size_t *&local =local_1;          //指针别名
    
    *(local + 94 * x)+=init;         //94     根据神经网络计算结果，选择跳转方向，
}



void nn_predict_1(int offset, double choice)     // neural_network_output
{
    double input[32];
    double (&b)[32] = input;
    
    read_data_one(offset,b);          // 根据offset。读取代码段上4处32个字节
    
    double (&c)[32] = input;          //指针别名混淆
    
    for(int i=0;i<32;i++)             //计算checksum
    {
        c[0] = c[0]+c[i];
    }
    
    
    c[0]=c[0]/100;                          //checksum 转 神经网络输入
    
    c[0] = nn_calculate(c[0],choice);            //输入checksum，条件变量choice --计算神经网络
    
    int j  = c[0] /1000000;                  //取最高两位做有效数值    70---A     78---B
    watermark(j);                           //路径水印 并修改返回地址
    
}

void nn_predict_2(int offset, double choice)
{
    double input[32];
    double (&b)[32] = input;
    
    read_data_two(offset,b);          // 根据offset。读取代码段上4处32个字节
    
    double (&c)[32] = input;          //指针别名混淆
    
    for(int i=0;i<32;i++)             //计算checksum
    {
        c[0] = c[0]+c[i];
    }
    
    
    c[0]=c[0]/100;                          //checksum 转 神经网络输入
    
    c[0] = nn_calculate(c[0],choice);            //输入checksum，条件变量choice --计算神经网络
    
    int j  = c[0] /1000000;                  //取最高两位做有效数值    0---A   94---B
    edit_ret(j);                            //NN2_修改返回地址以选择分支函数
    
}

void  crash_mo()                         //  本地crash_模块
{
    
    long int *p =(long int *) nn_calculate;
    size_t x =0;
    for(int i =0;i<15;i++)
    {
        *(p+i) =0;
    }
}



void jump()
{
    size_t x = 1;
    size_t *local = &x;
    *(local+5*x)+=81;
    
}

int asiccsum(const char *checksum)
{
    int total,i;
    
    for(total = 0,i = 0;checksum[i] != '\0' && i < strlen(checksum);i++)
        total += checksum[i];
    return total;
}

extern "C" JNIEXPORT jstring
JNICALL
Java_mobiliarbus_androidsecurity_MainActivity_stringFromJNI(JNIEnv *env,jobject jobj, jobject contextObject)
{
    double decision1=154;   //分支1的条件变量
    
    double decision2=0;   //分支2的条件变量
    
    int local_dynamic= 0 ;  //原程序之前动态生成的某个变量用作NN1的偏移参数
    
    
    char out[100]=" ";
    char A[]="local1——A\n";
    char B[]="local1——B\n";
    char C[]="local2——A\n";
    char D[]="local2——B\n";
    char E[]="Correct!\n";
    char F[]="Error!";
    
    
    
    nn_predict_1(local_dynamic,decision1);  // NN--1
    
    
    __android_log_print(ANDROID_LOG_INFO,"JNI","这是local_1,分支A！");
    
    strcat(out,A);
    
    jump();             //跳过分支local1——B
    
    
    __android_log_print(ANDROID_LOG_INFO,"JNI","这是local_1,分支B！");
    strcat(out,B);
    
    nn_predict_2(watermark_valu,decision2);    //NN-2
    
    
    __android_log_print(ANDROID_LOG_INFO,"JNI","这是local_2,分支A！");
    strcat(out,C);
    
    
    jump();                 //跳过分支local2——B
    
    __android_log_print(ANDROID_LOG_INFO,"JNI","这是local_2,分支B！");
    
    strcat(out,D);
    const char *signStrng = getSignString(env, contextObject);
    double c = (double) asiccsum(signStrng)/100;
    double decision3;
    c = nn_calculate(c,decision3);
    edit_ret(c);
    __android_log_print(ANDROID_LOG_INFO,"JNI","通过");
    strcat(out,E);
    jump();
    
    __android_log_print(ANDROID_LOG_INFO,"JNI","失败");
    //crash_mo();                                         //调用响应crash模块  成功！
    strcat(out,F);
    const char *signStrng = getSignString(env, contextObject);
    
    
    
    JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
        
        JNIEnv *env = NULL;
        jint result = -1;
        if (vm->GetEnv((void **) &env, JNI_VERSION_1_4) != JNI_OK)
            return result;
        
        contextClass = (jclass) env->NewGlobalRef((env)->FindClass("android/content/Context"));
        signatureClass = (jclass) env->NewGlobalRef((env)->FindClass("android/content/pm/Signature"));
        packageNameClass = (jclass) env->NewGlobalRef(
                                                      (env)->FindClass("android/content/pm/PackageManager"));
        packageInfoClass = (jclass) env->NewGlobalRef(
                                                      (env)->FindClass("android/content/pm/PackageInfo"));
        
        return JNI_VERSION_1_4;
    }
    //jni注册

