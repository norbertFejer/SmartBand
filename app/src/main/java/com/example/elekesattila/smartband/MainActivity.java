package com.example.elekesattila.smartband;

import android.bluetooth.BluetoothSocket;
import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.RadioButton;

import java.io.IOException;

public class MainActivity extends AppCompatActivity {
    private Button sendButton, chartButton;
    private EditText message;
    private BluetoothSocket btSocket = null;
    private static final String TAG = "SmartBand";
    private SenderClass senderClass = new SenderClass();

    protected void onCreate(Bundle savedInstanceState){
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        sendButton = (Button) findViewById(R.id.SendButton);
        chartButton = (Button) findViewById(R.id.ChartButton);

        new ConnectBT(senderClass).execute();

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
                    senderClass.sendIncomingPhoneCallNotification("Norbert", "0744139507");
                }
            }
        });

        chartButton.setOnClickListener(new View.OnClickListener(){
            public void onClick(View V){
                Intent intent = new Intent(MainActivity.this, LineChartActivity.class);
                startActivity(intent);
            }
        });
    }

    public void onPause() {
        super.onPause();
        disconnect();
    }

    private void disconnect(){
        if (btSocket!=null){
            try{
                btSocket.close();
                Log.v (TAG, "Disconnecting.");
            }
            catch (IOException e){
                Log.v(TAG, "Cannot disconnect.");
            }
        }
    }
}
