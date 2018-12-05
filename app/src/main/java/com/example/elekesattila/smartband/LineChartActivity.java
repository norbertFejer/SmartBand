package com.example.elekesattila.smartband;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;

import java.io.IOException;

import lecho.lib.hellocharts.model.Viewport;
import lecho.lib.hellocharts.view.LineChartView;

public class LineChartActivity extends AppCompatActivity{
    private static final String TAG = "SBLCA";

    protected void onCreate(Bundle savedInstanceState){
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        LineChartView lineChartView = findViewById(R.id.chart);

        ChartData chartData = new ChartData(this.getBaseContext());

        try{
            chartData.setChartData();
        }
        catch (IOException e){
            Log.v(TAG, "Error loading chart data");
        }

        Viewport viewport = new Viewport(lineChartView.getMaximumViewport());
        viewport.top=12;
        lineChartView.setMaximumViewport(viewport);
        lineChartView.setCurrentViewport(viewport);

        lineChartView.setLineChartData(chartData.getLineChartData());
    }
}

