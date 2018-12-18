package com.example.elekesattila.smartband;

import android.content.res.ColorStateList;
import android.graphics.Color;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.CompoundButton;
import android.widget.ProgressBar;
import android.widget.Switch;
import android.widget.TextView;
import android.widget.Toast;

import java.io.IOException;

import lecho.lib.hellocharts.view.LineChartView;

public class MainActivity extends AppCompatActivity {
    private static final String TAG = "SmartBandMainActivity";
    private static int stepCount, maxStepCount;
    private static Boolean goalAchieved;
    private Button deleteButton, chartButton;
    private Switch connectSwitch;
    private static TextView stepCountView, caloriesView;
    private static ProgressBar stepProgressBar, caloriesProgressbar;
    private static LineChartView lineChartView;
    private static MessageHandler handler = new MessageHandler();
    private static SenderClass senderClass = new SenderClass();
    private static LineChart lineChart;
    private BluetoothReceiverThread btrThread;

    protected void onCreate(Bundle savedInstanceState){
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        deleteButton = (Button) findViewById(R.id.DeleteButton);
        chartButton = (Button) findViewById(R.id.ChartButton);
        stepCountView = (TextView) findViewById(R.id.StepCountView);
        caloriesView = (TextView) findViewById(R.id.CaloriesView);
        connectSwitch = (Switch)  findViewById(R.id.ConnectSwitch);
        stepProgressBar = (ProgressBar) findViewById(R.id.StepProgressBar);
        caloriesProgressbar = (ProgressBar) findViewById(R.id.CaloriesProgressBar);
        lineChartView = (LineChartView) findViewById(R.id.LineChartView);

        setStepCount(-1);
        maxStepCount = stepProgressBar.getMax();

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

            @Override
            public void endOfCall(){
                Log.d(TAG, "Call ended.");
                senderClass.sendEndOfNotification();
            }
        });

        deleteButton.setOnClickListener(new View.OnClickListener(){
            public void onClick(View V){
                lineChartView.setVisibility(View.INVISIBLE);
                new StepChartData().deleteFile();
            }
        });

        chartButton.setOnClickListener(new View.OnClickListener(){
            public void onClick(View V){
                Log.d (TAG, "ChartButton pressed.");
                lineChart = new LineChart();
                lineChart.setLineChart(lineChartView);
                lineChartView.setVisibility(View.VISIBLE);
            }
        });

        connectSwitch.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                if (isChecked){
                    Log.d(TAG, "Connecting.");
                    Toast.makeText(MainActivity.this, "Connecting...", Toast.LENGTH_SHORT).show();
                    new ConnectBluetooth(senderClass, new ConnectBluetoothAnswer() {
                        @Override
                        public void isFinished(Boolean connected) {
                            Log.d(TAG, connected.toString());
                            if (connected){
                                Log.d(TAG, "Connected.");
                                Toast.makeText(MainActivity.this, "Connected.", Toast.LENGTH_SHORT).show();
                                btrThread = new BluetoothReceiverThread(senderClass.getBluetoothSocket(), handler);
                                btrThread.start();
                            }
                            else{
                                Log.d(TAG, "Connection failed.");
                                Toast.makeText(MainActivity.this, "Connection failed.", Toast.LENGTH_SHORT).show();
                                connectSwitch.setChecked(false);
                            }
                        }
                    }).execute();
                }
                else{
                    disconnect();
                }
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
                    Log.d(TAG, "Incoming call from: " + phoneNumber);
                    senderClass.sendIncomingPhoneCallNotification(phoneNumber);
            }

            @Override
            public void endOfCall(){
                Log.d(TAG, "Call ended.");
                senderClass.sendEndOfNotification();
            }
        });
    }

    private void disconnect(){
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
    }

    public static int getStepCount() {
        return stepCount;
    }

    public static void setStepCount(int stepCount) {
        Log.d(TAG, "Actual stepcount: " + MainActivity.stepCount);
        Log.d(TAG, "Received stepcount: " + stepCount);
        if (stepCount == -1){
            MainActivity.stepCount = stepCount;
            return;
        }
        if (MainActivity.stepCount > stepCount){
            MainActivity.stepCount += stepCount;
            senderClass.sendStepCount(MainActivity.stepCount);
        }
        else{
            MainActivity.stepCount = stepCount;
        }
        int calories = 60*MainActivity.stepCount/130;
        if (MainActivity.stepCount >= MainActivity.maxStepCount){
            stepCountView.setText("Actual steps: " + MainActivity.stepCount + "You achieved your daily goal!");
            caloriesView.setText("Calories: " + calories);
            stepProgressBar.setProgress(stepProgressBar.getMax());
            caloriesProgressbar.setProgress(caloriesProgressbar.getMax());
            if (!goalAchieved){
                senderClass.sendAchievementNotification();
                goalAchieved = true;
            }
        }
        else {
            stepCountView.setText("Actual steps: " + MainActivity.stepCount);
            caloriesView.setText("Calories: " + calories);
            stepProgressBar.setProgress(MainActivity.stepCount);
            caloriesProgressbar.setProgress(calories);
        }
    }

    public static void setTime(){
        Log.d(TAG, "Setting time.");
        senderClass.sendTime();
        senderClass.sendDate();
    }
}
