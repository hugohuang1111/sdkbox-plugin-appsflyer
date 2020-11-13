//
//  ViewController.m
//  test
//
//  Created by hugo on 2020/11/3.
//  Copyright © 2020 SDKBox. All rights reserved.
//

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
}

- (IBAction)onBtnStop:(id)sender {
}

@end
