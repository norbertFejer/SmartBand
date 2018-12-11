package com.example.elekesattila.smartband;

import android.os.Handler;
import android.os.Message;
import android.util.Log;

public class MessageHandler extends Handler {
    private StringBuilder stringBuilder;
    private static final String TAG = "SmartBandMessageHandler";

    public void handleMessage(Message msg) {
        switch (msg.what) {
            case 1:
                byte[] readBuf = (byte[]) msg.obj;
                String strIncom = new String(readBuf, 0, msg.arg1);
                stringBuilder.append(strIncom);
                int endOfLineIndex = stringBuilder.indexOf("\r\n");
                if (endOfLineIndex > 0) {
                    stringBuilder.delete(0, stringBuilder.length());
                }
                Log.d(TAG, "...String:"+ stringBuilder.toString() +  "Byte:" + msg.arg1 + "...");
                break;
        }
    }
}
