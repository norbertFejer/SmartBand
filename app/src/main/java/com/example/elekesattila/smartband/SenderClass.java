package com.example.elekesattila.smartband;

import android.bluetooth.BluetoothSocket;
import android.util.Log;

import java.io.IOException;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Calendar;

public class SenderClass {
    private static final String TAG = "SmartBand";
    private BluetoothSocket bluetoothSocket = null;
    private String messageString;

    private void sendData(){
        if (bluetoothSocket != null){
            try{
                bluetoothSocket.getOutputStream().write(messageString.getBytes());
                Log.v (TAG, "Message sent.");
            }
            catch (IOException e){
                Log.v(TAG, "Error sending message.");
            }
        }
    }

    public void sendStepCount(Integer stepCount){
        messageString = "s" + stepCount.toString();
    }

    public void sendTime(){
        DateFormat timeFormat = new SimpleDateFormat("HHmm");
        messageString = "t" + timeFormat.format(Calendar.getInstance().getTime());
        sendData();
    }

    public void sendDate(){
        DateFormat timeFormat = new SimpleDateFormat("MMddEEE");
        messageString = "d" + timeFormat.format(Calendar.getInstance().getTime());
        sendData();
    }

    public void sendMessageNotification(String senderName){
        messageString = "m" + senderName;
        sendData();
    }

    public void sendIncomingPhoneCallNotification(String name, String phoneNumber){
        if (name == ""){
            messageString = "p" + phoneNumber;
        }
        else{
            messageString = "p" + name + ": " + phoneNumber;
        }
        sendData();
    }

    public void setBluetoothSocket(BluetoothSocket bluetoothSocket) {
        this.bluetoothSocket = bluetoothSocket;
    }
}
