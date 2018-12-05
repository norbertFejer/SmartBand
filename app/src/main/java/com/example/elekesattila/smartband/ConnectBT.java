package com.example.elekesattila.smartband;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.os.AsyncTask;
import android.util.Log;

import java.io.IOException;
import java.util.UUID;

class ConnectBT extends AsyncTask<Void, Void, Void> {
    private static final String TAG = "SmartBand";
    private static final UUID myUUID = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB");
    private boolean connectSuccess = false;
    private boolean isConnected = false;
    private BluetoothAdapter btAdapter = null;
    private BluetoothSocket btSocket = null;
    private String address = "98:D3:51:FD:74:D1";
    private SenderClass senderClass;

    public ConnectBT(SenderClass senderClass){
        this.senderClass = senderClass;
    }

    protected void onPreExecute(){
        Log.v(TAG, "Trying to connect.");
    }

    protected Void doInBackground(Void... devices){ //???
        try{
            if (btSocket == null || !isConnected){
                btAdapter = BluetoothAdapter.getDefaultAdapter();
                BluetoothDevice btDevice = btAdapter.getRemoteDevice(address);
                btSocket = btDevice.createInsecureRfcommSocketToServiceRecord(myUUID);
                BluetoothAdapter.getDefaultAdapter().cancelDiscovery();
                btSocket.connect();
                senderClass.setBluetoothSocket(btSocket);
                connectSuccess = true;
                isConnected = true;
            }
        }
        catch(IOException e){
            connectSuccess = false;
        }
        return null;
    }

    protected void onPostExecute(Void result){
        if (connectSuccess){
            Log.v(TAG, "Connected.");
            senderClass.setBluetoothSocket(btSocket);
        }
        else{
            Log.v(TAG, "Not connected.");
        }
    }
}