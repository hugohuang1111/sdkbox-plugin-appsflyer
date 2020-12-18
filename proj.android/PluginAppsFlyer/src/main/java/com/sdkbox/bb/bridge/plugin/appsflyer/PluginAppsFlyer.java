package com.sdkbox.bb.bridge.plugin.appsflyer;

import android.app.Activity;
import android.app.Application;
import android.content.Context;

import androidx.annotation.NonNull;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;

import com.appsflyer.AppsFlyerConversionListener;
import com.appsflyer.AppsFlyerInAppPurchaseValidatorListener;
import com.appsflyer.AppsFlyerLib;
import com.appsflyer.attribution.AppsFlyerRequestListener;
import com.sdkbox.bb.bridge.core.Bridge;
import com.sdkbox.bb.bridge.core.Msg;
import com.sdkbox.bb.bridge.core.PluginBase;

public class PluginAppsFlyer extends PluginBase {
    private static final String TAG = "PluginAppsFlyer";
    private String devKey = ""; // gQHXnL6H3dccTbdNcLywNj
    private Application application = null;

    public PluginAppsFlyer(Context ctx) {
        super(ctx);
    }

    @Override
    public void onApplicationCreate(Application app) {
        application = app;
    }

    @Override
    public void onActivityCreate(Activity activity) {
        AppsFlyerLib.getInstance().logSession(activity);
        AppsFlyerLib.getInstance().sendPushNotificationData(activity);
    }

    public void setAppID(Msg msg) {
        String s = msg.getValueString(0);
        AppsFlyerLib.getInstance().setAppId(s);
    }

    public void setDevKey(Msg msg) {
        devKey = msg.getValueString(0);
    }

    public void setDebug(Msg msg) {
        boolean b = msg.getValueBoolean(0);
        AppsFlyerLib.getInstance().setDebugLog(b);
    }

    public void setAdditionalData(Msg msg) {
        JSONObject jsonParams = msg.getValueJson(0);
        AppsFlyerLib.getInstance().setAdditionalData(json2Map(jsonParams));
    }

    public void setCustomerUserID(Msg msg) {
        String s = msg.getValueString(0);
        AppsFlyerLib.getInstance().setCustomerUserId(s);
    }

    public void waitForCustomerUserId(Msg msg) {
        boolean b = msg.getValueBoolean(0);
        AppsFlyerLib.getInstance().waitForCustomerUserId(b);
    }

    public void setImeiData(Msg msg) {
        String s = msg.getValueString(0);
        AppsFlyerLib.getInstance().setImeiData(s);
    }

    public void setAndroidIdData(Msg msg) {
        String s = msg.getValueString(0);
        AppsFlyerLib.getInstance().setAndroidIdData(s);
    }

    public void setCollectIMEI(Msg msg) {
        boolean b = msg.getValueBoolean(0);
        AppsFlyerLib.getInstance().setCollectIMEI(b);
    }

    public void setCollectAndroidID(Msg msg) {
        boolean b = msg.getValueBoolean(0);
        AppsFlyerLib.getInstance().setCollectAndroidID(b);
    }

    public void setCollectOaid(Msg msg) {
        boolean b = msg.getValueBoolean(0);
        AppsFlyerLib.getInstance().setCollectOaid(b);
    }

    public void start(Msg msg) {
        if (null == application) {
            android.util.Log.e(TAG, "application is null");
            return;
        }
        if (0 == devKey.length()) {
            android.util.Log.e(TAG, "DevKey is null");
            return;
        }

        AppsFlyerConversionListener conversionListener = new AppsFlyerConversionListener() {
            @Override
            public void onConversionDataSuccess(Map<String, Object> conversionData) {
                Msg msg = createDefaultMsg();
                msg.pushValue("onConversionDataSuccess");
                JSONObject jsonObject = new JSONObject(conversionData);
                msg.pushValue(jsonObject.toString());
                sendToNative(msg);
            }

            @Override
            public void onConversionDataFail(String errorMessage) {
                Msg msg = createDefaultMsg();
                msg.pushValue("onConversionDataFail");
                msg.pushValue(errorMessage);
                sendToNative(msg);
            }

            @Override
            public void onAppOpenAttribution(Map<String, String> conversionData) {
                Msg msg = createDefaultMsg();
                msg.pushValue("onAppOpenAttribution");
                JSONObject jsonObject = new JSONObject(conversionData);
                msg.pushValue(jsonObject.toString());
                sendToNative(msg);
            }

            @Override
            public void onAttributionFailure(String errorMessage) {
                Msg msg = createDefaultMsg();
                msg.pushValue("onAttributionFailure");
                msg.pushValue(errorMessage);
                sendToNative(msg);
            }
        };

        AppsFlyerLib.getInstance().registerValidatorListener(application.getApplicationContext(),
                new AppsFlyerInAppPurchaseValidatorListener() {
                    public void onValidateInApp() {
                        Msg msg = createDefaultMsg();
                        msg.pushValue("onValidateInApp");
                        sendToNative(msg);
                    }
                    public void onValidateInAppFailure(String error) {
                        Msg msg = createDefaultMsg();
                        msg.pushValue("onValidateInAppFailure");
                        msg.pushValue(error);
                        sendToNative(msg);
                    }
                });

        AppsFlyerLib.getInstance().init(devKey, conversionListener, application.getApplicationContext());
        AppsFlyerLib.getInstance().start(application.getApplicationContext());
    }

    public void logEvent(Msg msg) {
        if (null == application) {
            return;
        }
        String evt = msg.getValueString(0);
        JSONObject jsonParams = msg.getValueJson(1);

        AppsFlyerLib.getInstance().logEvent(application.getApplicationContext(), evt, json2Map(jsonParams),
                new AppsFlyerRequestListener() {
                    @Override
                    public void onSuccess() {
                        msg.cleanValue();
                        sendToNative(msg);
                    }

                    @Override
                    public void onError(int i, @NonNull String s) {
                        Msg msg = createDefaultMsg();
                        msg.pushValue(i);
                        msg.pushValue(s);
                        sendToNative(msg);
                    }
                });
    }

    public void validateAndLogInAppPurchase(Msg msg) {
        if (null == application) {
            return;
        }
        JSONObject purchaseJson = msg.getValueJson(0);

        String publicKey = null;
        String signature = null;
        String purchaseData = null;
        String price = null;
        String currency = null;
        JSONObject parameters = null;

        try {
            publicKey = purchaseJson.getString("publicKey");
            signature = purchaseJson.getString("signature");
            purchaseData = purchaseJson.getString("purchaseData");
            price = purchaseJson.getString("price");
            currency = purchaseJson.getString("currency");
            parameters = purchaseJson.getJSONObject("parameters");
        } catch (JSONException e) {
            e.printStackTrace();
        }

        AppsFlyerLib.getInstance().validateAndLogInAppPurchase(application.getApplicationContext(),
                publicKey, signature, purchaseData, price, currency, json2HashMap(parameters));
    }

    public void setMinTimeBetweenSessions(Msg msg) {
        int i = msg.getValueInt(0);
        AppsFlyerLib.getInstance().setMinTimeBetweenSessions(i);
    }

    public void setResolveDeepLinkURLs(Msg msg) {
        String[] urls = null;
        int len = msg.getValuesLength();
        if (0 == len) {
            return;
        }
        urls = new String[len];
        for (int i = 0; i < len; i++) {
            urls[i] = msg.getValueString(i);
        }
        if (1 == len) {
            // try json
            try {
                JSONArray jsonArray = new JSONArray(urls[0]);
                if (jsonArray.length() > 0) {
                    urls = new String[jsonArray.length()];
                    for (int i = 0; i < jsonArray.length(); i++) {
                        urls[i] = jsonArray.optString(i, "");
                    }
                }
            } catch (JSONException e) {
            }
        }

        AppsFlyerLib.getInstance().setResolveDeepLinkURLs(urls);
    }

    public void getAppsFlyerUID(Msg msg) {
        Context ctx = null;
        if (null != application) {
            ctx = application.getApplicationContext();
        }
        if (null == ctx && null != Bridge.getGameActivity()) {
            ctx = Bridge.getGameActivity();
        }
        if (null == ctx) {
            return;
        }
        String afid = AppsFlyerLib.getInstance().getAppsFlyerUID(ctx);

        msg.cleanValue();
        msg.pushValue(afid);
        sendToNative(msg);
    }

    public void stop(Msg msg) {
        boolean b = msg.getValueBoolean(0);
        Context ctx = null;
        if (null != application) {
            ctx = application.getApplicationContext();
        }
        if (null == ctx && null != Bridge.getGameActivity()) {
            ctx = Bridge.getGameActivity();
        }
        if (null == ctx) {
            return;
        }
        AppsFlyerLib.getInstance().stop(b, ctx);
    }

    public void isStopped(Msg msg) {
        msg.cleanValue();
        msg.pushValue(AppsFlyerLib.getInstance().isStopped());
        sendToNative(msg);
    }

    public void anonymizeUser(Msg msg) {
        boolean b = msg.getValueBoolean(0);
        AppsFlyerLib.getInstance().anonymizeUser(b);
    }

    private HashMap<String, String> json2HashMap(JSONObject jsonObj) {
        if (null == jsonObj) {
            return null;
        }
        HashMap<String, String> map = new HashMap<String, String>();
        for (Iterator<String> it = jsonObj.keys(); it.hasNext(); ) {
            String key = it.next();
            try {
                Object valObj = jsonObj.get(key);
                if (valObj instanceof String) {
                    map.put(key, (String)valObj);
                }
            } catch (JSONException e) {
                e.printStackTrace();
            }
        }

        return map;
    }

}
