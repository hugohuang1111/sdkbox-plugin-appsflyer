#include <string>
#include <sstream>
#include <thread>
#include <jni.h>
#include <android/log.h>
#include "Bridge.hpp"
#include "PluginAppsFlyer.h"

#define LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, "Native", __VA_ARGS__)

static JavaVM *gJVM = nullptr;
static jobject mainActivity = nullptr;
static int counter = 0;
static pthread_key_t gThreadKey;
static bool bThreadRunning = true;

JNIEnv* cacheEnv() {
    if (nullptr == gJVM) {
        return nullptr;
    }
    JNIEnv* env = nullptr;
    jint ret = gJVM->GetEnv((void**)&env, JNI_VERSION_1_4);
    switch (ret) {
        case JNI_OK: {
            pthread_setspecific(gThreadKey, env);
            break;
        }
        case JNI_EDETACHED: {
            if (gJVM->AttachCurrentThread(&env, nullptr) >= 0) {
                pthread_setspecific(gThreadKey, env);
            }
            break;
        }
    }

    return env;
}

JNIEnv* getEnv() {
    JNIEnv* env = (JNIEnv*)pthread_getspecific(gThreadKey);
    if (nullptr != env) {
        return env;
    }
    return cacheEnv();
}

void notifyToJava(const std::string& evt) {
    JNIEnv* env = getEnv();
    if (nullptr == env) {
        LOGD("env is null");
        return;
    }
    if (nullptr == mainActivity) {
        return;
    }

    jclass clazz = env->GetObjectClass(mainActivity);
    jmethodID method = env->GetMethodID(clazz, "onNativeRecv", "(Ljava/lang/String;)V");
    if (nullptr == method) {
        return;
    }
    env->CallVoidMethod(mainActivity, method, env->NewStringUTF(evt.c_str()));
}

void testThread() {
    while (bThreadRunning) {
        std::this_thread::sleep_for(std::chrono::seconds(10));

        std::string s = "native callback:";
        s += std::to_string(++counter);
        notifyToJava(s);
    }
}

extern "C"
JNIEXPORT void JNICALL
Java_com_sdkbox_test_app_sample_MainActivity_nativeInit(JNIEnv *env, jobject thiz) {
    env->GetJavaVM(&gJVM);
    if (nullptr != mainActivity) {
        env->DeleteGlobalRef(mainActivity);
        mainActivity = nullptr;
    }
    mainActivity = env->NewGlobalRef(thiz);

    sdkbox::bb::plugin::AppsFlyer::init();
    sdkbox::bb::plugin::AppsFlyer::setListener([](const std::string& evt, const std::string& json) {
        std::stringstream ss;
        ss << "AppsFlyer evt:" << evt << " json:" << json;
        notifyToJava(ss.str());
    });
}

extern "C"
JNIEXPORT void JNICALL
Java_com_sdkbox_test_app_sample_MainActivity_nativeSend1(JNIEnv *env, jobject thiz, jstring jplugin, jstring jfunc, jstring jparams) {
    const char* c_str = nullptr;
    c_str = env->GetStringUTFChars(jplugin, nullptr);
    if(c_str == nullptr) { return; }
    std::string plugin(c_str);
    env->ReleaseStringUTFChars(jplugin, c_str);

    c_str = nullptr;
    c_str = env->GetStringUTFChars(jfunc, nullptr);
    if(c_str == nullptr) { return; }
    std::string func(c_str);
    env->ReleaseStringUTFChars(jfunc, c_str);

    c_str = nullptr;
    c_str = env->GetStringUTFChars(jparams, nullptr);
    if(c_str == nullptr) { return; }
    std::string params(c_str);
    env->ReleaseStringUTFChars(jparams, c_str);

   sdkbox::bb::plugin::AppsFlyer::setAppID("com.sdkbox.test.app.sample");
   sdkbox::bb::plugin::AppsFlyer::setDevKey("gQHXnL6H3dccTbdNcLywNj");
   sdkbox::bb::plugin::AppsFlyer::setDebug(true);

    sdkbox::bb::plugin::AppsFlyer::setImeiData("imei string");
    sdkbox::bb::plugin::AppsFlyer::setAndroidIdData("android id");
    sdkbox::bb::plugin::AppsFlyer::setCollectIMEI(true);
    sdkbox::bb::plugin::AppsFlyer::setCollectAndroidID(true);
    sdkbox::bb::plugin::AppsFlyer::setCollectOaid(true);
    sdkbox::bb::plugin::AppsFlyer::anonymizeUser(true);
    sdkbox::bb::plugin::AppsFlyer::collectASA(true);

    sdkbox::bb::plugin::AppsFlyer::setAdditionalData(
R"({
"k1": "v1"
})");
    sdkbox::bb::plugin::AppsFlyer::getAppsFlyerUID([](const std::string& appsflyerID) {
        std::stringstream ss;
        // LOGD("AppsFlyer UID: %s", appsflyerID.c_str());
        ss << "AppsFlyer UID:" << appsflyerID;
        notifyToJava(ss.str());
    });
    sdkbox::bb::plugin::AppsFlyer::setCustomerUserID("user_123456");
    sdkbox::bb::plugin::AppsFlyer::waitForATTUserAuthorizationWithTimeoutInterval(13);
    sdkbox::bb::plugin::AppsFlyer::logEvent(sdkbox::bb::plugin::AppsFlyer::AFEventPurchase,
R"({
"name": "test_name",
"price": "123"
})"
                                            );
    sdkbox::bb::plugin::AppsFlyer::useReceiptValidationSandbox(true);
    sdkbox::bb::plugin::AppsFlyer::validateAndLogInAppPurchase(
R"({
    "publicKey": "pubKey",
    "signature": "sigxxxx",
    "purchaseData": "purhchasexxx",
    "price": "123",
    "currency": "CNY",
    "parameters": {
        "k1": "v1",
        "k2": "v2"
    }
})"
);
    sdkbox::bb::plugin::AppsFlyer::setMinTimeBetweenSessions(21);
    sdkbox::bb::plugin::AppsFlyer::setResolveDeepLinkURLs({"test.com", "click.test.com"});

    sdkbox::bb::plugin::AppsFlyer::start();
}

extern "C"
JNIEXPORT void JNICALL
Java_com_sdkbox_test_app_sample_MainActivity_nativeSend2(JNIEnv *env, jobject thiz, jstring jplugin, jstring jfunc, jint jparami) {
    const char* c_str = nullptr;
    c_str = env->GetStringUTFChars(jplugin, nullptr);
    if(c_str == nullptr) { return; }
    std::string plugin(c_str);
    env->ReleaseStringUTFChars(jplugin, c_str);

    c_str = nullptr;
    c_str = env->GetStringUTFChars(jfunc, nullptr);
    if(c_str == nullptr) { return; }
    std::string func(c_str);
    env->ReleaseStringUTFChars(jfunc, c_str);

    sdkbox::bb::Msg msg = sdkbox::bb::Msg(plugin, func);

    msg.pushValue(jparami);

    sdkbox::bb::plugin::AppsFlyer::stop();
}