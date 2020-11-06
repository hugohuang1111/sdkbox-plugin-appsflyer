#include "PluginAppsFlyer.h"
#include "Bridge.hpp"
#include "Msg.hpp"

namespace sdkbox {
namespace bb {
namespace plugin {

void AppsFlyer::init() {
    sdkbox::bb::Bridge::init();
    
#ifdef ANDROID
#elif __APPLE__
    sdkbox::bb::Bridge::addPlugin("AppsFlyer", "BBPluginAppsFlyer");
#else
    #error "Unknown support platform"
#endif
}

void AppsFlyer::setListener(const std::function<void(const std::string& evt, const std::string& json)>& listener) {
    sdkbox::bb::Bridge::onRecv([=](const Msg& msg) {
        auto pluginName = msg.getPlugin();
        auto valEvt = msg.getValue(0);
        if (0 != pluginName.compare("AppsFlyer")) {
            return ;
        }
        listener(valEvt.stringValue(), msg.getValue(1).stringValue());
    });
}

void AppsFlyer::setAppID(const std::string& appID) {
    sdkbox::bb::Msg msg = sdkbox::bb::Msg("AppsFlyer", "setAppID");
    msg.pushValue(appID);
    sdkbox::bb::Bridge::send(msg);
}

void AppsFlyer::setDevKey(const std::string& devKey) {
    sdkbox::bb::Msg msg = sdkbox::bb::Msg("AppsFlyer", "setDevKey");
    msg.pushValue(devKey);
    sdkbox::bb::Bridge::send(msg);
}

void AppsFlyer::setDebug(bool b) {
    sdkbox::bb::Msg msg = sdkbox::bb::Msg("AppsFlyer", "setDebug");
    msg.pushValue(b);
    sdkbox::bb::Bridge::send(msg);
}

void AppsFlyer::start(void) {
    sdkbox::bb::Msg msg = sdkbox::bb::Msg("AppsFlyer", "start");
    sdkbox::bb::Bridge::send(msg);
}

}
}
}
