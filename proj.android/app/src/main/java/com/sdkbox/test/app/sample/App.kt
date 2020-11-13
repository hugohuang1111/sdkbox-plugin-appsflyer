package com.sdkbox.test.app.sample

import android.app.Application
import com.sdkbox.bb.bridge.core.Bridge
import com.sdkbox.bb.bridge.plugin.appsflyer.PluginAppsFlyer

class App : com.sdkbox.bb.bridge.core.BApplication() {

    override fun onCreate() {
        Bridge.init(this)
        Bridge.newPlugin("com.sdkbox.bb.bridge.plugin.appsflyer.PluginAppsFlyer")
        super.onCreate()
    }

    companion object {
        init {
            System.loadLibrary("native-lib")
        }
    }
}
