//
//  AppDelegate.m
//  test
//
//  Created by hugo on 2020/11/3.
//  Copyright © 2020 SDKBox. All rights reserved.
//

#import "AppDelegate.h"
#import "../../AppsFlyer/native/PluginAppsFlyer.h"

@interface AppDelegate ()

@end

@implementation AppDelegate


- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    // Override point for customization after application launch.

    sdkbox::bb::plugin::AppsFlyer::init();
    sdkbox::bb::plugin::AppsFlyer::setListener([](const std::string& evt, const std::string& json) {
        NSString* nss = [NSString stringWithUTF8String: evt.c_str()];
        NSString* nsJson = [NSString stringWithUTF8String: json.c_str()];
        NSLog(@"AppsFlyer evt:%@ json:%@", nss, nsJson);
    });
    sdkbox::bb::plugin::AppsFlyer::setAppID("1423010453");
    sdkbox::bb::plugin::AppsFlyer::setDevKey("gQHXnL6H3dccTbdNcLywNj");
    sdkbox::bb::plugin::AppsFlyer::setDebug(true);

    return YES;
}


#pragma mark - UISceneSession lifecycle


- (UISceneConfiguration *)application:(UIApplication *)application configurationForConnectingSceneSession:(UISceneSession *)connectingSceneSession options:(UISceneConnectionOptions *)options {
    // Called when a new scene session is being created.
    // Use this method to select a configuration to create the new scene with.
    return [[UISceneConfiguration alloc] initWithName:@"Default Configuration" sessionRole:connectingSceneSession.role];
}


- (void)application:(UIApplication *)application didDiscardSceneSessions:(NSSet<UISceneSession *> *)sceneSessions {
    // Called when the user discards a scene session.
    // If any sessions were discarded while the application was not running, this will be called shortly after application:didFinishLaunchingWithOptions.
    // Use this method to release any resources that were specific to the discarded scenes, as they will not return.
}


@end
