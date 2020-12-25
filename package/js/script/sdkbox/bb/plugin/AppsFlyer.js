
var sdkbox = sdkbox || {};
sdkbox.bb = sdkbox.bb || {};
sdkbox.bb.plugin = sdkbox.bb.plugin || {};
if (!sdkbox.bb.plugin.AppsFlyer) {

let Msg = sdkbox.bb.Msg;
let AppsFlyer = {}

// const sys = sys || cc.sys;

AppsFlyer.init = function() {
    sdkbox.bb.Bridge.init();

    if (sys.os === sys.OS_ANDROID) {
        sdkbox.bb.Bridge.addPlugin("AppsFlyer", "com.sdkbox.bb.bridge.plugin.appsflyer.PluginAppsFlyer");
    } else if (sys.os === sys.OS_IOS) {
        sdkbox.bb.Bridge.addPlugin("AppsFlyer", "BBPluginAppsFlyer");
    }
}

AppsFlyer.setListener = function(lis) {
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

AppsFlyer.setAppID = function(appID) {
    const m = new Msg("AppsFlyer", "setAppID")
    m.pushValue(appID)

    sdkbox.bb.Bridge.send(m);
}

AppsFlyer.setDevKey = function(devKey) {
    const m = new Msg("AppsFlyer", "setDevKey")
    m.pushValue(devKey)

    sdkbox.bb.Bridge.send(m);
}

AppsFlyer.setDebug = function(b) {
    const m = new Msg("AppsFlyer", "setDebug");
    m.pushValue(b);
    sdkbox.bb.Bridge.send(m);
}

AppsFlyer.setAdditionalData = function(json) {
    const m = new Msg("AppsFlyer", "setAdditionalData");
    m.pushValue(json);
    sdkbox.bb.Bridge.send(m);
}

AppsFlyer.getAppsFlyerUID = function(cb) {
    const m = new Msg("AppsFlyer", "getAppsFlyerUID");
    sdkbox.bb.Bridge.send(m, function(msg) {
        cb && cb(msg.values[0]);
    });
}

AppsFlyer.setCustomerUserID = function(userID) {
    const m = new Msg("AppsFlyer", "setCustomerUserID");
    m.pushValue(userID);
    sdkbox.bb.Bridge.send(m);
}

AppsFlyer.anonymizeUser = function(b) {
    const m = new Msg("AppsFlyer", "anonymizeUser");
    m.pushValue(b);
    sdkbox.bb.Bridge.send(m);
}

AppsFlyer.collectASA = function(b) {
    if (sys.os === sys.OS_IOS) {
        const m = new Msg("AppsFlyer", "collectASA");
        m.pushValue(b);
        sdkbox.bb.Bridge.send(m);
    }
}

AppsFlyer.waitForATTUserAuthorizationWithTimeoutInterval = function(seconds) {
    if (sys.os === sys.OS_IOS) {
        const m = new Msg("AppsFlyer", "waitForATTUserAuthorizationWithTimeoutInterval");
        m.pushValue(seconds);
        sdkbox.bb.Bridge.send(m);
    }
}

AppsFlyer.stop = function() {
    const m = new Msg("AppsFlyer", "stop");
    sdkbox.bb.Bridge.send(m);
}

AppsFlyer.start = function() {
    const m = new Msg("AppsFlyer", "start");
    sdkbox.bb.Bridge.send(m);
}

AppsFlyer.logEvent = function(evt, json, cb) {
    const m = new Msg("AppsFlyer", "logEvent");
    m.pushValue(evt);
    m.pushValue(json);
    sdkbox.bb.Bridge.send(m, function(msg) {
        cb && cb(msg.values[0], msg.values[1])
    });
}

AppsFlyer.useReceiptValidationSandbox = function(b) {
    if (sys.os === sys.OS_IOS) {
        const m = new Msg("AppsFlyer", "useReceiptValidationSandbox");
        m.pushValue(b);
        sdkbox.bb.Bridge.send(m);
    }
}

AppsFlyer.validateAndLogInAppPurchase = function(purchaseJson) {
    const m = new Msg("AppsFlyer", "validateAndLogInAppPurchase");
    m.pushValue(purchaseJson);
    sdkbox.bb.Bridge.send(m);
}

AppsFlyer.setMinTimeBetweenSessions = function(seconds) {
    const m = new Msg("AppsFlyer", "setMinTimeBetweenSessions");
    m.pushValue(seconds);
    sdkbox.bb.Bridge.send(m);
}

AppsFlyer.setResolveDeepLinkURLs = function(urls) {
    const m = new Msg("AppsFlyer", "setResolveDeepLinkURLs")
    for(let i = 0; i < urls.length; i++) {
        m.pushValue(urls[i])
    }
    sdkbox.bb.Bridge.send(m)
}

AppsFlyer.setImeiData = function(data) {
    if (sys.os === sys.OS_ANDROID) {
        const m = new Msg("AppsFlyer", "setImeiData");
        m.pushValue(data);
        sdkbox.bb.Bridge.send(m);
    }
}

AppsFlyer.setAndroidIdData = function(data) {
    if (sys.os === sys.OS_ANDROID) {
        const m = new Msg("AppsFlyer", "setAndroidIdData");
        m.pushValue(data);
        sdkbox.bb.Bridge.send(m);
    }
}

AppsFlyer.setCollectIMEI = function(b) {
    if (sys.os === sys.OS_ANDROID) {
        const m = new Msg("AppsFlyer", "setCollectIMEI");
        m.pushValue(b);
        sdkbox.bb.Bridge.send(m);
    }
}

AppsFlyer.setCollectAndroidID = function(b) {
    if (sys.os === sys.OS_ANDROID) {
        const m = new Msg("AppsFlyer", "setCollectAndroidID");
        m.pushValue(b);
        sdkbox.bb.Bridge.send(m);
    }
}

AppsFlyer.setCollectOaid = function(b) {
    if (sys.os === sys.OS_ANDROID) {
        const m = new Msg("AppsFlyer", "setCollectOaid");
        m.pushValue(b);
        sdkbox.bb.Bridge.send(m);
    }
}

sdkbox.bb.plugin.AppsFlyer = AppsFlyer;

}
