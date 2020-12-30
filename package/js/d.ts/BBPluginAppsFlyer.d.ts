
declare namespace sdkbox.bb.plugin.AppsFlyer {
    export function init();
    export function setListener(lis: (event: string, data: any) => void);
    export function setAppID(appID: string);
    export function setDevKey(devKey: string);
    export function setDebug(b: boolean);
    export function setAdditionalData(json: string);
    export function getAppsFlyerUID(cb: (uid: string) => void);
    export function setCustomerUserID(userID: string);
    export function anonymizeUser(b: boolean);
    export function collectASA(b: boolean);
    export function waitForATTUserAuthorizationWithTimeoutInterval(seconds: number);
    export function stop();
    export function start();
    export function logEvent(evt: string, json: string, cb: (val: any, val: any) => void);
    export function useReceiptValidationSandbox(b: boolean);
    export function validateAndLogInAppPurchase(purchaseJson: string);
    export function setMinTimeBetweenSessions(seconds: number);
    export function setResolveDeepLinkURLs(urls: Array<string>);
    export function setImeiData(data: string);
    export function setAndroidIdData(data: string);
    export function setCollectIMEI(b: boolean);
    export function setCollectAndroidID(b: boolean);
    export function setCollectOaid(b: boolean);
}


