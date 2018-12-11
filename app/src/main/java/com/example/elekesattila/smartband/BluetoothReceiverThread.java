package com.example.elekesattila.smartband;

import android.bluetooth.BluetoothSocket;
import android.os.Message;
import android.util.Log;

import java.io.IOException;
import java.io.InputStream;

public class BluetoothReceiverThread extends Thread {
    private static final String TAG = "SmartBandBluetoothRec";
    private final InputStream inputStream;
    private static MessageHandler handler;
    private BluetoothSocket bluetoothSocket;


    public BluetoothReceiverThread(BluetoothSocket socket, MessageHandler handler) {
        BluetoothReceiverThread.handler = handler;
        this.bluetoothSocket = socket;

        InputStream tmpIn = null;
        try {
            tmpIn = bluetoothSocket.getInputStream();
            Log.d(TAG, "Stream set.");
        }
        catch (IOException e) {
            Log.d(TAG, "Cannot get stream.");
        }
        inputStream = tmpIn;
    }

    public void run() {
        byte[] buffer = new byte[256];
        int bytes;

        while (true) {
            try {
                bytes = inputStream.read(buffer);
                handler.obtainMessage(1, bytes, -1, buffer).sendToTarget();
                handler.handleMessage(new Message());
            } catch (IOException e) {
                break;
            }
        }
    }
}
