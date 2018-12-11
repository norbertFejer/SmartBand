package com.example.elekesattila.smartband;

import android.bluetooth.BluetoothSocket;
import android.util.Log;

import java.io.IOException;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Calendar;

public class SenderClass {
    private static final String TAG = "SmartBandSenderClass";
    private BluetoothSocket bluetoothSocket = null;
    private String messageString;

    private void sendData(){
        Log.d(TAG, "Message to send: " + messageString);
        if (bluetoothSocket != null){
            try{
                bluetoothSocket.getOutputStream().write(messageString.getBytes());
                Log.d (TAG, "Message sent.");
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
        messageString = "s" + stepCount.toString();
    }

    public void sendTime(){
        Log.d(TAG, "Sending time.");
        DateFormat timeFormat = new SimpleDateFormat("Hmm");
        messageString = "t" + timeFormat.format(Calendar.getInstance().getTime());
        sendData();
    }

    public void sendDate(){
        Log.d(TAG, "Sending date.");
        DateFormat timeFormat = new SimpleDateFormat("MMddu");
        messageString = "d" + timeFormat.format(Calendar.getInstance().getTime());
        sendData();
    }

    public void sendMessageNotification(String senderName){
        Log.d(TAG, "Sending incoming sms notification.");
        messageString = "m" + senderName;
        sendData();
    }

    public void sendIncomingPhoneCallNotification(String name){
        Log.d(TAG, "Sending incoming phone call notification.");
        messageString = "p" + name;
        sendData();
    }

    public void sendEndOfNotification(){
        Log.d(TAG, "Sending end of notification.");
        messageString = "nend";
        sendData();
    }

    public BluetoothSocket getBluetoothSocket() {
        return bluetoothSocket;
    }

    public void setBluetoothSocket(BluetoothSocket bluetoothSocket) {
        this.bluetoothSocket = bluetoothSocket;
    }
}
