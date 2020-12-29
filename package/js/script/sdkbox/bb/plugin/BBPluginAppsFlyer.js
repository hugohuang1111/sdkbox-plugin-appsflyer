
var sdkbox = sdkbox || {};
sdkbox.bb = sdkbox.bb || {};
sdkbox.bb.plugin = sdkbox.bb.plugin || {};
if (!sdkbox.bb.plugin.AppsFlyer) {

let Msg = sdkbox.bb.Msg;
let BBPluginAppsFlyer = {}

// const sys = sys || cc.sys;

BBPluginAppsFlyer.init = function() {
    sdkbox.bb.Bridge.init();

    if (BBPluginAppsFlyer._isAndroid()) {
        sdkbox.bb.Bridge.addPlugin("AppsFlyer", "com.sdkbox.bb.bridge.plugin.appsflyer.PluginAppsFlyer");
    } else if (BBPluginAppsFlyer._isIOS()) {
        sdkbox.bb.Bridge.addPlugin("AppsFlyer", "BBPluginAppsFlyer");
    }
}

BBPluginAppsFlyer.setListener = function(lis) {
    if(!lis) {
        return
    }
    sdkbox.bb.Bridge.onRecv(function(msg) {
        if ("AppsFlyer" != msg.plugin) {
            return
        }
        lis(msg.values[0], msg.values[1])
    })
}

BBPluginAppsFlyer.setAppID = function(appID) {
    const m = new Msg("AppsFlyer", "setAppID")
    m.pushValue(appID)

    sdkbox.bb.Bridge.send(m);
}

BBPluginAppsFlyer.setDevKey = function(devKey) {
    const m = new Msg("AppsFlyer", "setDevKey")
    m.pushValue(devKey)

    sdkbox.bb.Bridge.send(m);
}

BBPluginAppsFlyer.setDebug = function(b) {
    const m = new Msg("AppsFlyer", "setDebug");
    m.pushValue(b);
    sdkbox.bb.Bridge.send(m);
}

BBPluginAppsFlyer.setAdditionalData = function(json) {
    const m = new Msg("AppsFlyer", "setAdditionalData");
    m.pushValue(json);
    sdkbox.bb.Bridge.send(m);
}

BBPluginAppsFlyer.getAppsFlyerUID = function(cb) {
    const m = new Msg("AppsFlyer", "getAppsFlyerUID");
    sdkbox.bb.Bridge.send(m, function(msg) {
        cb && cb(msg.values[0]);
    });
}

BBPluginAppsFlyer.setCustomerUserID = function(userID) {
    const m = new Msg("AppsFlyer", "setCustomerUserID");
    m.pushValue(userID);
    sdkbox.bb.Bridge.send(m);
}

BBPluginAppsFlyer.anonymizeUser = function(b) {
    const m = new Msg("AppsFlyer", "anonymizeUser");
    m.pushValue(b);
    sdkbox.bb.Bridge.send(m);
}

BBPluginAppsFlyer.collectASA = function(b) {
    if (BBPluginAppsFlyer._isIOS()) {
        const m = new Msg("AppsFlyer", "collectASA");
        m.pushValue(b);
        sdkbox.bb.Bridge.send(m);
    }
}

BBPluginAppsFlyer.waitForATTUserAuthorizationWithTimeoutInterval = function(seconds) {
    if (BBPluginAppsFlyer._isIOS()) {
        const m = new Msg("AppsFlyer", "waitForATTUserAuthorizationWithTimeoutInterval");
        m.pushValue(seconds);
        sdkbox.bb.Bridge.send(m);
    }
}

BBPluginAppsFlyer.stop = function() {
    const m = new Msg("AppsFlyer", "stop");
    sdkbox.bb.Bridge.send(m);
}

BBPluginAppsFlyer.start = function() {
    const m = new Msg("AppsFlyer", "start");
    sdkbox.bb.Bridge.send(m);
}

BBPluginAppsFlyer.logEvent = function(evt, json, cb) {
    const m = new Msg("AppsFlyer", "logEvent");
    m.pushValue(evt);
    m.pushValue(json);
    sdkbox.bb.Bridge.send(m, function(msg) {
        cb && cb(msg.values[0], msg.values[1])
    });
}

BBPluginAppsFlyer.useReceiptValidationSandbox = function(b) {
    if (BBPluginAppsFlyer._isIOS()) {
        const m = new Msg("AppsFlyer", "useReceiptValidationSandbox");
        m.pushValue(b);
        sdkbox.bb.Bridge.send(m);
    }
}

BBPluginAppsFlyer.validateAndLogInAppPurchase = function(purchaseJson) {
    const m = new Msg("AppsFlyer", "validateAndLogInAppPurchase");
    m.pushValue(purchaseJson);
    sdkbox.bb.Bridge.send(m);
}

BBPluginAppsFlyer.setMinTimeBetweenSessions = function(seconds) {
    const m = new Msg("AppsFlyer", "setMinTimeBetweenSessions");
    m.pushValue(seconds);
    sdkbox.bb.Bridge.send(m);
}

BBPluginAppsFlyer.setResolveDeepLinkURLs = function(urls) {
    const m = new Msg("AppsFlyer", "setResolveDeepLinkURLs")
    for(let i = 0; i < urls.length; i++) {
        m.pushValue(urls[i])
    }
    sdkbox.bb.Bridge.send(m)
}

BBPluginAppsFlyer.setImeiData = function(data) {
    if (BBPluginAppsFlyer._isAndroid()) {
        const m = new Msg("AppsFlyer", "setImeiData");
        m.pushValue(data);
        sdkbox.bb.Bridge.send(m);
    }
}

BBPluginAppsFlyer.setAndroidIdData = function(data) {
    if (BBPluginAppsFlyer._isAndroid()) {
        const m = new Msg("AppsFlyer", "setAndroidIdData");
        m.pushValue(data);
        sdkbox.bb.Bridge.send(m);
    }
}

BBPluginAppsFlyer.setCollectIMEI = function(b) {
    if (BBPluginAppsFlyer._isAndroid()) {
        const m = new Msg("AppsFlyer", "setCollectIMEI");
        m.pushValue(b);
        sdkbox.bb.Bridge.send(m);
    }
}

BBPluginAppsFlyer.setCollectAndroidID = function(b) {
    if (BBPluginAppsFlyer._isAndroid()) {
        const m = new Msg("AppsFlyer", "setCollectAndroidID");
        m.pushValue(b);
        sdkbox.bb.Bridge.send(m);
    }
}

BBPluginAppsFlyer.setCollectOaid = function(b) {
    if (BBPluginAppsFlyer._isAndroid()) {
        const m = new Msg("AppsFlyer", "setCollectOaid");
        m.pushValue(b);
        sdkbox.bb.Bridge.send(m);
    }
}

BBPluginAppsFlyer._isAndroid = function() {
    if (cc) {
        if (cc.sys.platform == cc.sys.ANDROID) {
            return true;
        }
    } else {
        if (sys.os === sys.OS_ANDROID) {
            return true;
        }
    }
    return false;
}

BBPluginAppsFlyer._isIOS = function() {
    if (cc) {
        if (cc.sys.platform == cc.sys.IPHONE || cc.sys.platform == cc.sys.IPAD) {
            return true;
        }
    } else {
        if (sys.os === sys.OS_IOS) {
            return true;
        }
    }
    return false;
}


sdkbox.bb.plugin.AppsFlyer = BBPluginAppsFlyer;

}
