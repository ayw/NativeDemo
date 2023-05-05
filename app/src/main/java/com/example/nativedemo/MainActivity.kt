package com.example.nativedemo

import android.os.Bundle
import androidx.appcompat.app.AppCompatActivity
import com.example.nativedemo.databinding.ActivityMainBinding

class MainActivity : AppCompatActivity() {

    private lateinit var binding: ActivityMainBinding

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

        // Example of a call to a native method
        binding.sampleText.text = stringFromJNI() + dynamicRegisterFunction()
    }

    /**
     * A native method that is implemented by the 'nativedemo' native library,
     * which is packaged with this application.
     */
    // 静态注册的函数
    external fun stringFromJNI(): String

    // 动态注册的函数
    external fun dynamicRegisterFunction(): String?

    companion object {
        // Used to load the 'nativedemo' library on application startup.
        init {
            System.loadLibrary("hello-sdk")
        }
    }
}