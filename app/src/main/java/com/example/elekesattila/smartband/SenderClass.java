package com.example.elekesattila.smartband;

import android.bluetooth.BluetoothSocket;
import android.util.Log;

import java.io.IOException;
import java.io.OutputStream;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Calendar;

public class SenderClass {
    private static final String TAG = "SmartBandSenderClass";
    private BluetoothSocket bluetoothSocket = null;

    private void sendData(String messageString){
        messageString += "\n";
        Log.d(TAG, "Message to send: " + messageString);
        if (bluetoothSocket != null){
            try{
                OutputStream outputStream = bluetoothSocket.getOutputStream();
                byte[] messageBytes = messageString.getBytes();
                int messageLength = messageBytes.length;
                outputStream.write(messageBytes, 0, messageLength);
                outputStream.flush();
                Log.d (TAG, "Message sent. Bytes: " + messageLength);
            }
            catch (IOException e){
                Log.d(TAG, "Error sending message.");
            }
        }
        else{
            Log.d(TAG, "Device is not connected.");
        }
    }

    public void sendStepCount(Integer stepCount){
        String messageString;
        messageString = "s" + stepCount.toString();
        sendData(messageString);
    }

    public void sendTime(){
        // API problems
        String messageString;
        Log.d(TAG, "Sending time.");
        DateFormat timeFormat = new SimpleDateFormat("Hmm");
        messageString = "t" + timeFormat.format(Calendar.getInstance().getTime());
        sendData(messageString);
    }

    public void sendDate(){
        String messageString;
        Log.d(TAG, "Sending date.");
        DateFormat timeFormat = new SimpleDateFormat("MMdd");
        Calendar calendar = Calendar.getInstance();
        int day = calendar.get(Calendar.DAY_OF_WEEK) - 2;
        messageString = "d" + timeFormat.format(Calendar.getInstance().getTime()) + day;
        sendData(messageString);
    }

    public void sendMessageNotification(String senderName){
        String messageString;
        Log.d(TAG, "Sending incoming sms notification.");
        messageString = "m" + senderName;
        sendData(messageString);
    }

    public void sendIncomingPhoneCallNotification(String name){
        String messageString;
        Log.d(TAG, "Sending incoming phone call notification.");
        messageString = "p" + name;
        sendData(messageString);
    }

    public void sendEndOfNotification(){
        String messageString;
        Log.d(TAG, "Sending end of notification.");
        messageString = "nend";
        sendData(messageString);
    }

    public BluetoothSocket getBluetoothSocket() {
        return bluetoothSocket;
    }

    public void setBluetoothSocket(BluetoothSocket bluetoothSocket) {
        this.bluetoothSocket = bluetoothSocket;
    }
}
