#import <UserNotifications/UserNotifications.h>
#import <AppsFlyerLib/AppsFlyerLib.h>
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
    if (1 != [msg getValueListLength]) {
        return;
    }
    id appid = [msg getValue:0];
    NSString* sid = (NSString*)appid;
    [AppsFlyerLib shared].appleAppID = sid;
}

- (void) setDevKey:(BBMsg*)msg {
    if (1 != [msg getValueListLength]) {
        return;
    }
    NSString* nss = [msg getValue:0];
    [AppsFlyerLib shared].appsFlyerDevKey = nss;
}

- (void) setDebug:(BBMsg*)msg {
    if (1 != [msg getValueListLength]) {
        return;
    }
    id idObj = [msg getValue:0];
    NSNumber* num = (NSNumber*)idObj;
    [AppsFlyerLib shared].isDebug = (0 != [num intValue]);
}

- (void) start:(BBMsg*)msg {
    if (0 != [msg getValueListLength]) {
        return;
    }
    [AppsFlyerLib shared].delegate = delegate;
    [[AppsFlyerLib shared] start];
    
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

