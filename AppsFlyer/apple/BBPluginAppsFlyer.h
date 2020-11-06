#pragma once

#import <UIKit/UIKit.h>
#import "BBPluginBase.h"

@interface BBPluginAppsFlyer : BBPluginBase

- (void) setAppID:(BBMsg* _Nullable)msg;
- (void) setDevKey:(BBMsg* _Nullable)msg;
- (void) setDebug:(BBMsg* _Nullable)msg;
- (void) start:(BBMsg* _Nullable)msg;

// application life cycle

// Open URI-scheme for iOS 9 and above
- (BOOL)application:(UIApplication *)application
            openURL:(NSURL *)url
            options:(NSDictionary *) options;

// Open URI-scheme for iOS 8 and below
- (BOOL)application: (UIApplication *)application
            openURL: (NSURL *)url
  sourceApplication: (NSString*)sourceApplication
         annotation: (id)annotation;

// Open Universal Links
- (BOOL)application     : (UIApplication *)application
    continueUserActivity: (NSUserActivity *)userActivity
      restorationHandler: (void(^)(NSArray<id<UIUserActivityRestoring>> * __nullable restorableObjects))restorationHandler;

// Report Push Notification attribution data for re-engagements
- (void)application            : (UIApplication *)application
   didReceiveRemoteNotification: (NSDictionary *)userInfo
         fetchCompletionHandler: (void (^)(UIBackgroundFetchResult result))completionHandler;


// scene degelate
- (void)scene    : (UIScene *)scene
  openURLContexts: (NSSet<UIOpenURLContext *> *)URLContexts API_AVAILABLE(ios(13.0));

- (void)scene        : (UIScene *)scene
 continueUserActivity: (NSUserActivity *)userActivity API_AVAILABLE(ios(13.0));


@end


