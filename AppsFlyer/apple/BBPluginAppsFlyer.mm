#import <UserNotifications/UserNotifications.h>
#import <AppsFlyerLib/AppsFlyerLib.h>
#import "BBUtilsIOS.h"
#import "BBPluginAppsFlyer.h"
#import "BBPluginAppsFlyerDelegate.h"
#import "BBUNUserNotificationCenterDelegate.h"

@implementation BBPluginAppsFlyer
{
    BBPluginAppsFlyerDelegate* delegate;
    BBUNUserNotificationCenterDelegate* unDelegate;
}

- (instancetype)init {
    self = [super init];
    
    delegate = [[BBPluginAppsFlyerDelegate alloc] init];
    delegate.plugin = self;

    return self;
}

- (void) dealloc {
    delegate = nil;
}

- (void) setAppID:(BBMsg*)msg {
    if (1 != [msg getValuesLength]) {
        return;
    }
    id appid = [msg getValue:0];
    NSString* sid = (NSString*)appid;
    [AppsFlyerLib shared].appleAppID = sid;
}

- (void) setDevKey:(BBMsg*)msg {
    if (1 != [msg getValuesLength]) {
        return;
    }
    NSString* nss = [msg getValue:0];
    [AppsFlyerLib shared].appsFlyerDevKey = nss;
}

- (void) setDebug:(BBMsg*)msg {
    if (1 != [msg getValuesLength]) {
        return;
    }
    BOOL b = [msg getValueBOOL:0];
    [AppsFlyerLib shared].isDebug = b;
}

- (void) setAdditionalData:(BBMsg*)msg {
    if (1 != [msg getValuesLength]) {
        return;
    }
    NSString* jsonStr = (NSString*)[msg getValue:0];
    NSDictionary* dic = [BBUtilsIOS json2dic:jsonStr];
    if (nil == dic) {
        NSLog(@"ERROR, AppsFlyer setAdditionalData data is nil");
        return;
    }
    [[AppsFlyerLib shared] setAdditionalData: dic];
}

- (void) getAppsFlyerUID: (BBMsg*)msg {
    NSString* s = [AppsFlyerLib shared].getAppsFlyerUID;
    [msg cleanValues];
    if (nil == s) {
        s = @"";
    }
    [msg pushValueString: s];
    [self send: msg];
}

- (void) setCustomerUserID: (BBMsg*)msg {
    if (1 != [msg getValuesLength]) {
        return;
    }
    NSString* uid = (NSString*)[msg getValue:0];
    [AppsFlyerLib shared].currencyCode = uid;
}

- (void) anonymizeUser: (BBMsg*) msg {
    [AppsFlyerLib shared].disableAdvertisingIdentifier = [msg getValueBOOL:0];
}

- (void) collectASA: (BBMsg*) msg {
    [AppsFlyerLib shared].disableCollectASA = [msg getValueBOOL:0];
}

- (void) waitForATTUserAuthorizationWithTimeoutInterval: (BBMsg*) msg {
    NSNumber* num = [msg getValueNumber:0];
    [[AppsFlyerLib shared] waitForATTUserAuthorizationWithTimeoutInterval: num.integerValue];
}

- (void) stop: (BBMsg*)msg {
    [AppsFlyerLib shared].isStopped = YES;
}

- (void) start:(BBMsg*)msg {
    if (0 != [msg getValuesLength]) {
        return;
    }
    [AppsFlyerLib shared].delegate = delegate;
    [AppsFlyerLib shared].isStopped = NO;
    // [[AppsFlyerLib shared] start];
    [[AppsFlyerLib shared] startWithCompletionHandler:^(NSDictionary<NSString *,id> *dictionary, NSError *error) {
        if (nil != error) {
            NSLog(@"ERROR, AppsFlyer start failed: %ld, %@", (long)error.code, error.description);
        }
    }];

    if (@available(iOS 10, *)) {
        unDelegate = [[BBUNUserNotificationCenterDelegate alloc] init];
        UNUserNotificationCenter *center = [UNUserNotificationCenter currentNotificationCenter];
        center.delegate = unDelegate;
        [center requestAuthorizationWithOptions:(UNAuthorizationOptionSound | UNAuthorizationOptionAlert | UNAuthorizationOptionBadge) completionHandler:^(BOOL granted, NSError * _Nullable error) {
        }];
    } else {
        UIUserNotificationSettings *settings = [UIUserNotificationSettings settingsForTypes: UIUserNotificationTypeAlert | UIUserNotificationTypeSound | UIUserNotificationTypeBadge categories:nil];
        [[UIApplication sharedApplication] registerUserNotificationSettings:settings];
    }
    [[UIApplication sharedApplication] registerForRemoteNotifications];
}

- (void) logEvent: (BBMsg*)msg {
    NSString* evt = (NSString*)[msg getValue:0];
    NSString* jsonStr = (NSString*)[msg getValue:1];
    NSDictionary* dic = [BBUtilsIOS json2dic:jsonStr];

    if (nil == dic) {
        NSLog(@"ERROR, logEvent params can't translate to dictionary");
        return;
    }

    // [[AppsFlyerLib shared] logEvent: evt withValues: dic];
    [[AppsFlyerLib shared] logEventWithEventName: evt
                                     eventValues: dic
                               completionHandler: ^(NSDictionary<NSString *,id> * _Nullable dictionary, NSError * _Nullable error) {
        [msg cleanValues];
        if (nil != error) {
            [msg pushValueNumber: [NSNumber numberWithInteger: error.code]];
            [msg pushValueString: error.description];
        }
        [self send:msg];
    }];
}

- (void) useReceiptValidationSandbox: (BBMsg*) msg {
    BOOL b = [msg getValueBOOL:0];
    [AppsFlyerLib shared].useReceiptValidationSandbox = b;
}

- (void) validateAndLogInAppPurchase: (BBMsg*) msg {
    NSString* purchaseInfo = (NSString*)[msg getValue:0];
    NSDictionary* purchaseDic = [BBUtilsIOS json2dic:purchaseInfo];
    
    NSString* productIdentifier = [purchaseDic valueForKey:@"productIdentifier"];
    NSString* transactionId = [purchaseDic valueForKey:@"transactionId"];
    NSString* price = [purchaseDic valueForKey:@"price"];
    NSString* currency = [purchaseDic valueForKey:@"currency"];
    NSDictionary* parameters = [purchaseDic valueForKey:@"parameters"];

    [[AppsFlyerLib shared] validateAndLogInAppPurchase: productIdentifier
                                                 price: price
                                              currency: currency
                                         transactionId: transactionId
                                  additionalParameters: parameters
                                               success:^(NSDictionary * _Nonnull response) {
        BBMsg* msg = [self createDefaultMsg];
        [msg.values addObject: @"onValidateInApp"];
        [self send:msg];
    }
                                               failure:^(NSError * _Nullable error, id  _Nullable reponse) {
        BBMsg* msg = [self createDefaultMsg];
        [msg pushValueString: @"onValidateInAppFailure"];
        if (nil != error) {
            [msg pushValueString: error.description];
        }
        [self send:msg];
    }];
}

-(void) setMinTimeBetweenSessions: (BBMsg*) msg {
    NSNumber* num = [msg getValueNumber:0];
    [AppsFlyerLib shared].minTimeBetweenSessions = num.integerValue;
}

-(void) setResolveDeepLinkURLs: (BBMsg*) msg {
    NSString* json = [msg getValueString:0];
    NSArray* urls = [BBUtilsIOS json2arr:json];
    [AppsFlyerLib shared].resolveDeepLinkURLs = urls;
}

- (BOOL)application: (UIApplication *)application
            openURL: (NSURL *)url
            options: (NSDictionary *) options {
    [[AppsFlyerLib shared] handleOpenUrl:url options:options];
    return YES;
}

- (BOOL)application: (UIApplication *)application
            openURL: (NSURL *)url
  sourceApplication: (NSString*)sourceApplication
         annotation: (id)annotation {
    [[AppsFlyerLib shared] handleOpenURL:url sourceApplication:sourceApplication withAnnotation:annotation];
    return YES;
}

// Open Universal Links
- (BOOL)application     : (UIApplication *)application
    continueUserActivity: (NSUserActivity *)userActivity
      restorationHandler: (void(^)(NSArray<id<UIUserActivityRestoring>> * __nullable restorableObjects))restorationHandler {
    if (@available(iOS 9, *)) {
        [[AppsFlyerLib shared] continueUserActivity:userActivity restorationHandler:restorationHandler];
    }

    return YES;
}

// Report Push Notification attribution data for re-engagements
- (void)application            : (UIApplication *)application
   didReceiveRemoteNotification: (NSDictionary *)userInfo
         fetchCompletionHandler: (void (^)(UIBackgroundFetchResult result))completionHandler {
    [[AppsFlyerLib shared] handlePushNotification:userInfo];
}

- (void)scene   : (UIScene *)scene
 openURLContexts: (NSSet<UIOpenURLContext *> *)URLContexts API_AVAILABLE(ios(13.0)) {
    NSURL* url = [[URLContexts allObjects] objectAtIndex:0].URL;
    if(url){
        [[AppsFlyerLib shared] handleOpenUrl:url options:nil];
    }
}

- (void)scene        : (UIScene *)scene
 continueUserActivity:(NSUserActivity *)userActivity API_AVAILABLE(ios(13.0)) {
    [[AppsFlyerLib shared]continueUserActivity:userActivity restorationHandler:nil];
}

@end

