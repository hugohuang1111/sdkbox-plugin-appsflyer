#pragma once

#import <Foundation/Foundation.h>
#import <AppsFlyerLib/AppsFlyerLib.h>
#import "BBPluginAppsFlyer.h"

@interface BBPluginAppsFlyerDelegate : NSObject <AppsFlyerLibDelegate>

@property(nonatomic, weak) BBPluginAppsFlyer* plugin;

/**
 `conversionInfo` contains information about install.
 Organic/non-organic, etc.
 @param conversionInfo May contain <code>null</code> values for some keys. Please handle this case.
 */
- (void)onConversionDataSuccess:(NSDictionary *)conversionInfo;

/**
 Any errors that occurred during the conversion request.
 */
- (void)onConversionDataFail:(NSError *)error;

/**
 `attributionData` contains information about OneLink, deeplink.
 */
- (void)onAppOpenAttribution:(NSDictionary *)attributionData;

/**
 Any errors that occurred during the attribution request.
 */
- (void)onAppOpenAttributionFailure:(NSError *)error;

/**
 @abstract Sets the HTTP header fields of the ESP resolving to the given
 dictionary.
 @discussion This method replaces all header fields that may have
 existed before this method ESP resolving call.
 To keep default SDK dehavior - return nil;
 */
- (NSDictionary <NSString *, NSString *> * _Nullable)allHTTPHeaderFieldsForResolveDeepLinkURL:(NSURL *)URL;

@end

