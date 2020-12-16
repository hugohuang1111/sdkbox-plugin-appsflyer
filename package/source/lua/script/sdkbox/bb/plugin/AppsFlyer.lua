local Msg = require("sdkbox.bb.Msg")

local AppsFlyer = {}

local app = cc.Application:getInstance()
local target = app:getTargetPlatform()


function AppsFlyer.init()
    sdkbox.bb.Bridge.init()

    if target == cc.PLATFORM_OS_ANDROID then
        sdkbox.bb.Bridge.addPlugin("AppsFlyer", "com.sdkbox.bb.bridge.plugin.appsflyer.PluginAppsFlyer");
    elseif target == cc.PLATFORM_OS_IPHONE or target == cc.PLATFORM_OS_IPAD then
        sdkbox.bb.Bridge.addPlugin("AppsFlyer", "BBPluginAppsFlyer");
    end

end

function AppsFlyer.setListener(lis)
    if not lis then
        return
    end
    sdkbox.bb.Bridge.onRecv(function(msg)
        if "AppsFlyer" ~= msg.plugin then
            return
        end
        lis(msg.values[1], msg.values[2])
    end)
end

function AppsFlyer.setAppID(appID)
    local m = Msg:create("AppsFlyer", "setAppID")
    m:pushValue(appID)

    sdkbox.bb.Bridge.send(m);
end

function AppsFlyer.setDevKey(devKey)
    local m = Msg:create("AppsFlyer", "setDevKey")
    m:pushValue(devKey)

    sdkbox.bb.Bridge.send(m);
end

function AppsFlyer.setDebug(b)
    local m = Msg:create("AppsFlyer", "setDebug");
    m:pushValue(b);
    sdkbox.bb.Bridge.send(m);
end

function AppsFlyer.setAdditionalData(json)
    local m = Msg:create("AppsFlyer", "setAdditionalData");
    m:pushValue(json);
    sdkbox.bb.Bridge.send(m);
end

function AppsFlyer.getAppsFlyerUID(cb)
    local m = Msg:create("AppsFlyer", "getAppsFlyerUID");
    sdkbox.bb.Bridge.send(m, function(msg)
        cb(msg.values[1])
    end);
end

function AppsFlyer.setCustomerUserID(userID)
    local m = Msg:create("AppsFlyer", "setCustomerUserID");
    m:pushValue(userID);
    sdkbox.bb.Bridge.send(m);
end

function AppsFlyer.anonymizeUser(b)
    local m = Msg:create("AppsFlyer", "anonymizeUser");
    m:pushValue(b);
    sdkbox.bb.Bridge.send(m);
end

function AppsFlyer.collectASA(b)
    if target == cc.PLATFORM_OS_IPHONE or target == cc.PLATFORM_OS_IPAD then
        local m = Msg:create("AppsFlyer", "collectASA");
        m:pushValue(b);
        sdkbox.bb.Bridge.send(m);
    end
end

function AppsFlyer.waitForATTUserAuthorizationWithTimeoutInterval(seconds)
    if target == cc.PLATFORM_OS_IPHONE or target == cc.PLATFORM_OS_IPAD then
        local m = Msg:create("AppsFlyer", "waitForATTUserAuthorizationWithTimeoutInterval");
        m:pushValue(seconds);
        sdkbox.bb.Bridge.send(m);
    end
end

function AppsFlyer.stop()
    local m = Msg:create("AppsFlyer", "stop");
    sdkbox.bb.Bridge.send(m);
end

function AppsFlyer.start()
    local m = Msg:create("AppsFlyer", "start");
    sdkbox.bb.Bridge.send(m);
end

function AppsFlyer.logEvent(evt, json)
    local m = Msg:create("AppsFlyer", "logEvent");
    m:pushValue(evt);
    m:pushValue(json);
    sdkbox.bb.Bridge.send(m);
end

function AppsFlyer.useReceiptValidationSandbox(b)
    if target == cc.PLATFORM_OS_IPHONE or target == cc.PLATFORM_OS_IPAD then
        local m = Msg:create("AppsFlyer", "useReceiptValidationSandbox");
        m:pushValue(b);
        sdkbox.bb.Bridge.send(m);
    end
end

function AppsFlyer.validateAndLogInAppPurchase(purchaseJson)
    local m = Msg:create("AppsFlyer", "validateAndLogInAppPurchase");
    m:pushValue(purchaseJson);
    sdkbox.bb.Bridge.send(m);
end

function AppsFlyer.setMinTimeBetweenSessions(seconds)
    local m = Msg:create("AppsFlyer", "setMinTimeBetweenSessions");
    m:pushValue(seconds);
    sdkbox.bb.Bridge.send(m);
end

function AppsFlyer.setResolveDeepLinkURLs(urls)
    local m = Msg:create("AppsFlyer", "setResolveDeepLinkURLs")
    for i = 1, #urls do
        m:pushValue(urls[i])
    end
    sdkbox.bb.Bridge.send(m)
end

function AppsFlyer.setImeiData(data)
    if target == cc.PLATFORM_OS_ANDROID then
        local m = Msg:create("AppsFlyer", "setImeiData");
        m:pushValue(data);
        sdkbox.bb.Bridge.send(m);
    end
end

function AppsFlyer.setAndroidIdData(data)
    if target == cc.PLATFORM_OS_ANDROID then
        local m = Msg:create("AppsFlyer", "setAndroidIdData");
        m:pushValue(data);
        sdkbox.bb.Bridge.send(m);
    end
end

function AppsFlyer.setCollectIMEI(b)
    if target == cc.PLATFORM_OS_ANDROID then
        local m = Msg:create("AppsFlyer", "setCollectIMEI");
        m:pushValue(b);
        sdkbox.bb.Bridge.send(m);
    end
end

function AppsFlyer.setCollectAndroidID(b)
    if target == cc.PLATFORM_OS_ANDROID then
        local m = Msg:create("AppsFlyer", "setCollectAndroidID");
        m:pushValue(b);
        sdkbox.bb.Bridge.send(m);
    end
end

function AppsFlyer.setCollectOaid(b)
    if target == cc.PLATFORM_OS_ANDROID then
        local m = Msg:create("AppsFlyer", "setCollectOaid");
        m:pushValue(b);
        sdkbox.bb.Bridge.send(m);
    end
end

sdkbox = sdkbox or {}
sdkbox.bb = sdkbox.bb or {}
sdkbox.bb.plugin = sdkbox.bb.plugin or {}
sdkbox.bb.plugin.AppsFlyer = AppsFlyer
