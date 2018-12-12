package com.example.elekesattila.smartband;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;

import java.io.IOException;
import java.text.SimpleDateFormat;

import lecho.lib.hellocharts.model.LineChartData;
import lecho.lib.hellocharts.model.Viewport;
import lecho.lib.hellocharts.view.LineChartView;

public class LineChartActivity extends AppCompatActivity{
    private static final String TAG = "SmartBandLineChartActiv";
    private LineChartView lineChartView;
    private LineChartData lineChartData;
    private StepChartData stepChartData;


    protected void onCreate(Bundle savedInstanceState){
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_line_chart);
        Log.d (TAG, "LineChartActivity started.");
        lineChartView = findViewById(R.id.LineChartView);
        stepChartData = new StepChartData();

        try{
            Log.d(TAG, "Trying to load chart data.");
            stepChartData.setChartData();
            updateChartData(new SimpleDateFormat("MMmdd").toString(), MainActivity.getStepCount());
            lineChartData = stepChartData.getLineChartData();
        }
        catch (IOException e){
            Log.d(TAG, "Error loading chart data.");
        }

        if (lineChartData != null && !stepChartData.isNewFile()){
            try{
                Log.d(TAG, "Trying to set chart data.");
                lineChartView.setLineChartData(lineChartData);

                Viewport viewport = new Viewport(lineChartView.getMaximumViewport());
                viewport.top=stepChartData.getMaxStep() + 1;
                lineChartView.setMaximumViewport(viewport);
                lineChartView.setCurrentViewport(viewport);
            }catch (Exception e){
                Log.d(TAG, "Error: " + e.getMessage());
            }
        }
        else{
            Log.d(TAG, "Null chart data or nothing to show.");
            finish();
        }
    }

    private void updateChartData(String newXData, Integer newYData){
        stepChartData.saveData(newXData, newYData);
    }
}

