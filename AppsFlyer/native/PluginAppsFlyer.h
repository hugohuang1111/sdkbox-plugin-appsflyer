#pragma once

#include <string>

namespace sdkbox {
namespace bb {
namespace plugin {

    class AppsFlyer {
    public:
        static void init();
        static void setListener(const std::function<void(const std::string& evt, const std::string& json)>& listener);
        static void setAppID(const std::string& appID);
        static void setDevKey(const std::string& appID);
        static void setDebug(bool b);
        static void start();
    };

}
}
}
