package com.example.elekesattila.smartband;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.os.AsyncTask;
import android.util.Log;

import java.io.IOException;
import java.util.UUID;

class ConnectBT extends AsyncTask<Void, Void, Void> {
    private static final String TAG = "SmartBandConnectBT";
    private static final UUID myUUID = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB");
    private boolean isConnected = false;
    private BluetoothAdapter btAdapter = null;
    private BluetoothSocket btSocket = null;
    private String address = "98:D3:51:FD:74:D1";
    private SenderClass senderClass;
    public ConnectBTAnswer delegate = null;

    public ConnectBT(SenderClass senderClass, ConnectBTAnswer answer){
        this.delegate = answer;
        this.senderClass = senderClass;
    }

    protected void onPreExecute(){
        Log.d(TAG, "Trying to connect.");
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
                isConnected = true;
            }
        }
        catch(IOException e){
            isConnected = false;
        }
        return null;
    }

    protected void onPostExecute(Void result){
        if (btSocket!=null){
            Log.d(TAG, "Connected.");
            senderClass.setBluetoothSocket(btSocket);
        }
        else{
            Log.d(TAG, "Not connected.");
        }
        delegate.isFinished(isConnected);
    }
}