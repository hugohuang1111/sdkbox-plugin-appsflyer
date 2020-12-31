package com.sdkbox.test.app.sample

import android.os.Bundle
import android.util.Log
import android.view.TouchDelegate
import android.widget.Button
import android.widget.TextView
import androidx.appcompat.app.AppCompatActivity

class MainActivity : AppCompatActivity() {

    private var tvLog: TextView? = null

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        tvLog = findViewById<TextView>(R.id.log)
        var button: Button? = findViewById<Button>(R.id.btnInit)
        button?.setOnClickListener {
            nativeInit()
        }
        button = findViewById<Button>(R.id.btnStart)
        button?.setOnClickListener {
            nativeSend1("", "", "")
        }
        button = findViewById<Button>(R.id.btnStop)
        button?.setOnClickListener {
            nativeSend2("", "", "")
        }
    }

    private fun log(s: String) {
        Log.d(TAG, "onRecv:$s")
        val txt = tvLog?.text.toString()
        var lines = txt.split("\n").toMutableList()
        while (lines.size > 4) {
            lines.removeAt(0)
        }
        lines.add(s)
        val sb = StringBuilder()
        for (i in lines.indices) {
            if (i > 0) {
                sb.append("\n")
            }
            sb.append(lines[i])
        }
        tvLog?.text = sb.toString()
    }

    fun onNativeRecv(s: String) {
        log(s)
    }

    private external fun nativeInit()
    private external fun nativeSend1(plugin: String, f: String, params: String)
    private external fun nativeSend2(plugin: String, f: String, params: String)

    companion object {
        private val TAG: String = "MainActivity"
    }
}