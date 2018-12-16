package com.example.elekesattila.smartband;

import android.os.Handler;
import android.os.Message;
import android.util.Log;

public class MessageHandler extends Handler {
    private StringBuilder stringBuilder = new StringBuilder();
    private static final String TAG = "SmartBandMessageHandler";

    public void handleMessage(Message msg) {
        switch (msg.what) {
            case 1:
                byte[] readBuf = (byte[]) msg.obj;
                String strIncom = new String(readBuf, 0, msg.arg1);
                stringBuilder.append(strIncom);
                Log.d(TAG, "Received message: " + stringBuilder.toString());
                Log.d(TAG, "Received bytes: " + msg.arg1);
                try{
                    MainActivity.setStepCount(Integer.parseInt(stringBuilder.toString().substring(0, msg.arg1 - 1)));
                }
                catch (Exception e){
                    Log.d(TAG, "Exception at parseInt: " + e.getMessage());
                }
                stringBuilder.setLength(0);
                break;
        }
    }
}
