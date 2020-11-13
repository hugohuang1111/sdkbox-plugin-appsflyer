//
//  ViewController.m
//  test
//
//  Created by hugo on 2020/11/3.
//  Copyright © 2020 SDKBox. All rights reserved.
//

#import <vector>
#import "ViewController.h"
#import "../../AppsFlyer/native/PluginAppsFlyer.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
    sdkbox::bb::plugin::AppsFlyer::setListener([](const std::string& evt, const std::string& json) {
        NSString* nss = [NSString stringWithUTF8String: evt.c_str()];
        NSString* nsJson = [NSString stringWithUTF8String: json.c_str()];
        NSLog(@"AppsFlyer evt:%@ json:%@", nss, nsJson);
    });
}

- (IBAction)onBtnStart:(id)sender {
    sdkbox::bb::plugin::AppsFlyer::setAppID("1423010453");
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
        NSLog(@"AppsFlyer ID:%@", [NSString stringWithUTF8String: appsflyerID.c_str()]);
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
"productIdentifier": "pidxxx",
"transactionId": "txxx",
"price": "134",
"currency": "CNY",
"parameters": {
   "k1": "v1",
   "k2": "v2"
}})");
    sdkbox::bb::plugin::AppsFlyer::setMinTimeBetweenSessions(21);
    std::vector<std::string> urls {"test.com", "click.test.com"};
    sdkbox::bb::plugin::AppsFlyer::setResolveDeepLinkURLs(urls);

    sdkbox::bb::plugin::AppsFlyer::start();
}

- (IBAction)onBtnStop:(id)sender {
    sdkbox::bb::plugin::AppsFlyer::stop();
}

@end
