package com.example.elekesattila.smartband;

import android.util.Log;

import java.io.IOException;
import java.text.SimpleDateFormat;
import java.util.Calendar;

import lecho.lib.hellocharts.model.LineChartData;
import lecho.lib.hellocharts.model.Viewport;
import lecho.lib.hellocharts.view.LineChartView;

public class LineChart {
    private static final String TAG = "SmartBandLineChart";
    private LineChartView lineChartView;
    private LineChartData lineChartData;
    private StepChartData stepChartData;


    protected void setLineChart(LineChartView lineChartView){
        this.lineChartView = lineChartView;
        stepChartData = new StepChartData();

        try{
            Log.d(TAG, "Trying to load chart data.");
            stepChartData.setChartData();
            updateChartData(new SimpleDateFormat("MMMdd").format(Calendar.getInstance().getTime()), MainActivity.getStepCount());
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
        }
    }

    private void updateChartData(String newXData, Integer newYData){
        stepChartData.saveData(newXData, newYData);
    }
}
