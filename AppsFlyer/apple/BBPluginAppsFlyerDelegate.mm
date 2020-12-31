#import "BBPluginAppsFlyerDelegate.h"
#import "Bridge/BBUtilsIOS.h"

@implementation BBPluginAppsFlyerDelegate

- (instancetype)init {
    self = [super init];
    return self;
}

- (void)onConversionDataSuccess:(NSDictionary *)conversionInfo {
    if (nil == self.plugin) {
        return;
    }

    BBMsg* msg = [self.plugin createDefaultMsg];
    [msg.values addObject: @"onConversionDataSuccess"];
    [msg.values addObject: [BBUtilsIOS dic2json: conversionInfo]];
    [self.plugin send:msg];
}

- (void)onConversionDataFail:(NSError *)error{
    if (nil == self.plugin) {
        return;
    }
    
    NSDictionary* dic = @{ @"error": error.description };
    BBMsg* msg = [self.plugin createDefaultMsg];
    [msg.values addObject: @"onConversionDataFail"];
    [msg.values addObject: [BBUtilsIOS dic2json: dic]];
    [self.plugin send:msg];
}

- (void)onAppOpenAttribution:(NSDictionary *)attributionData{
    if (nil == self.plugin) {
        return;
    }
    
    BBMsg* msg = [self.plugin createDefaultMsg];
    [msg.values addObject: @"onAppOpenAttribution"];
    [msg.values addObject: [BBUtilsIOS dic2json: attributionData]];
    [self.plugin send:msg];
}

- (void)onAppOpenAttributionFailure:(NSError *)error{
    if (nil == self.plugin) {
        return;
    }

    NSDictionary* dic = @{ @"error": error.description };
    BBMsg* msg = [self.plugin createDefaultMsg];
    [msg.values addObject: @"onAppOpenAttributionFailure"];
    [msg.values addObject: [BBUtilsIOS dic2json: dic]];
    [self.plugin send:msg];
}

- (NSDictionary <NSString *, NSString *> * _Nullable)allHTTPHeaderFieldsForResolveDeepLinkURL:(NSURL *)URL{
    return nil;
}

@end
