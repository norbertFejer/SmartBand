package com.example.elekesattila.smartband;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.RadioButton;
import android.widget.Toast;

import java.io.IOException;

public class MainActivity extends AppCompatActivity {
    private static final String TAG = "SmartBandMainActivity";
    private Button sendButton, chartButton, connectButton;
    private SenderClass senderClass = new SenderClass();
    private static MessageHandler handler = new MessageHandler();
    private BluetoothReceiverThread btrThread;

    protected void onCreate(Bundle savedInstanceState){
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        sendButton = (Button) findViewById(R.id.SendButton);
        chartButton = (Button) findViewById(R.id.ChartButton);
        connectButton = (Button) findViewById(R.id.ConnectButton);

        NotificationListener.setBindListener(new NotificationBinder() {
            @Override
            public void messageReceived(String messageSender) {
                Log.d(TAG, "Message received from: " + messageSender);
                senderClass.sendMessageNotification(messageSender);
            }
            @Override
            public void callReceived(String phoneNumber){
                Log.d(TAG, "Incoming call from: " + phoneNumber);
                senderClass.sendIncomingPhoneCallNotification(phoneNumber);
            }
        });

        connectButton.setOnClickListener(new View.OnClickListener(){
            public void onClick(View V){
                Log.d(TAG, "Connecting.");
                Toast.makeText(MainActivity.this, "Connecting...", Toast.LENGTH_SHORT).show();
                new ConnectBT(senderClass, new ConnectBTAnswer() {
                    @Override
                    public void isFinished(Boolean connected) {
                        Log.d(TAG, connected.toString());
                        if (connected){
                            Log.d(TAG, "Connected.");
                            Toast.makeText(MainActivity.this, "Connected.", Toast.LENGTH_SHORT).show();
                            btrThread = new BluetoothReceiverThread(senderClass.getBluetoothSocket(), handler);
                            btrThread.start();
                            //senderClass.sendTime();
                            //senderClass.sendDate();
                        }
                        else{
                            Log.d(TAG, "Connection failed.");
                            Toast.makeText(MainActivity.this, "Connection failed.", Toast.LENGTH_SHORT).show();
                        }
                    }
                }).execute();
            }
        });

        sendButton.setOnClickListener(new View.OnClickListener(){
            public void onClick(View V){
                RadioButton stepCountRB = (RadioButton) findViewById(R.id.stepCount);
                RadioButton timeRB = (RadioButton) findViewById(R.id.time);
                RadioButton dateRB = (RadioButton) findViewById(R.id.date);
                RadioButton smsRB = (RadioButton) findViewById(R.id.sms);
                RadioButton callRB = (RadioButton) findViewById(R.id.call);

                if (stepCountRB.isChecked()){
                    senderClass.sendStepCount(150);
                }
                if (timeRB.isChecked()){
                    senderClass.sendTime();
                }
                if (dateRB.isChecked()){
                    senderClass.sendDate();
                }
                if (smsRB.isChecked()){
                    senderClass.sendMessageNotification("Norbert");
                }
                if (callRB.isChecked()){
                    senderClass.sendIncomingPhoneCallNotification("Norbert");
                }
            }
        });

        chartButton.setOnClickListener(new View.OnClickListener(){
            public void onClick(View V){
                Log.d (TAG, "ChartButton pressed.");
                Intent intent = new Intent(MainActivity.this, LineChartActivity.class);
                Log.d (TAG, "Starting LineChartActivity.");
                startActivity(intent);
            }
        });

    }

    public void onPause() {
        super.onPause();
        NotificationListener.setBindListener(new NotificationBinder() {
            @Override
            public void messageReceived(String messageSender) {
                Log.d(TAG, "Message received from: " + messageSender);
                senderClass.sendMessageNotification(messageSender);
            }
            @Override
            public void callReceived(String phoneNumber){
                if (phoneNumber.equals("end")){
                    Log.d(TAG, "Call ended.");
                    senderClass.sendEndOfNotification();
                }
                else{
                    Log.d(TAG, "Incoming call from: " + phoneNumber);
                    senderClass.sendIncomingPhoneCallNotification(phoneNumber);
                }
            }
        });
    }

    /*private void disconnect(){
        if (senderClass.getBluetoothSocket()!=null){
            try{
                senderClass.getBluetoothSocket().close();
                Log.d (TAG, "Disconnecting.");
            }
            catch (IOException e){
                Log.d(TAG, "Cannot disconnect.");
            }
        }
        else{
            Log.d(TAG, "Cannot disconnect, device is not connected.");
        }
    }*/
}
