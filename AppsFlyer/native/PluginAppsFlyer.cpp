#include "PluginAppsFlyer.h"
#include "Bridge.hpp"
#include "Msg.hpp"

#ifdef ANDROID
#elif __APPLE__
    #define PLUGIN_APPSFLYER_NAME "BBPluginAppsFlyer"
#else
    #error "Unknown support platform"
#endif

namespace sdkbox {
namespace bb {
namespace plugin {

void AppsFlyer::setListener(const std::function<void(const std::string& evt, const std::string& json)>& listener) {
    sdkbox::bb::Bridge::onRecv([=](const Msg& msg) {
        auto pluginName = msg.getPlugin();
        auto valEvt = msg.getValue(0);
        if (0 != pluginName.compare(PLUGIN_APPSFLYER_NAME)) {
            return ;
        }
        listener(valEvt.stringValue(), msg.getValue(1).stringValue());
    });
}

void AppsFlyer::setAppID(const std::string& appID) {
    sdkbox::bb::Msg msg = sdkbox::bb::Msg(PLUGIN_APPSFLYER_NAME, "setAppID");
    msg.pushValue(appID);
    sdkbox::bb::Bridge::send(msg);
}

void AppsFlyer::setDevKey(const std::string& devKey) {
    sdkbox::bb::Msg msg = sdkbox::bb::Msg(PLUGIN_APPSFLYER_NAME, "setDevKey");
    msg.pushValue(devKey);
    sdkbox::bb::Bridge::send(msg);
}

void AppsFlyer::setDebug(bool b) {
    sdkbox::bb::Msg msg = sdkbox::bb::Msg(PLUGIN_APPSFLYER_NAME, "setDebug");
    msg.pushValue(b);
    sdkbox::bb::Bridge::send(msg);
}

void AppsFlyer::start(void) {
    sdkbox::bb::Msg msg = sdkbox::bb::Msg(PLUGIN_APPSFLYER_NAME, "start");
    sdkbox::bb::Bridge::send(msg);
}

}
}
}
