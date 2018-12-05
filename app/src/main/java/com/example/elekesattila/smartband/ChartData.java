package com.example.elekesattila.smartband;

import android.content.Context;
import android.graphics.Color;
import android.os.Environment;
import android.util.Log;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import lecho.lib.hellocharts.model.Axis;
import lecho.lib.hellocharts.model.AxisValue;
import lecho.lib.hellocharts.model.Line;
import lecho.lib.hellocharts.model.LineChartData;
import lecho.lib.hellocharts.model.PointValue;

public class ChartData {
    private static final String TAG = "SmartBand";
    private Context context;
    LineChartData data = new LineChartData();

    ChartData(Context ctx){
        this.context = ctx;
    }

    public void setChartData() throws IOException {

        Log.v(TAG, "Starting setChartData");
        String[] xAxisData, yAxisData;
        List xAxisValues = new ArrayList();
        List yAxisValues = new ArrayList();

        File path = Environment.getExternalStorageDirectory();
        File file = new File(path,"data.txt");
        Log.v(TAG, "FILE");
        if (file.exists()) {
            try {
                Log.v(TAG, "Trying to read data");
                BufferedReader bufferedReader = new BufferedReader(new FileReader(file));
                String xAxisLine = bufferedReader.readLine();
                String yAxisLine = bufferedReader.readLine();
                bufferedReader.close();
                xAxisData = xAxisLine.split(" ", -1);
                yAxisData = yAxisLine.split(" ", -1);
                //API problems
                Log.v(TAG, "Setting up axis values");
                for (int i = 0; i < xAxisData.length; ++i) { //() ?
                    xAxisValues.add(i, new AxisValue(i).setLabel(xAxisData[i]));
                }

                for (int i = 0; i < yAxisData.length; ++i) { //() ?
                    xAxisValues.add(i, new PointValue(i, Integer.parseInt(yAxisData[i])));
                }
            } catch (IOException e) {
                Log.v(TAG, "Cannot read data");
            }
        }
        else{
            file.createNewFile();
            Log.v(TAG, "Input file created.");
        }

        Log.v(TAG, "Setting up axises");

        Line line = new Line(yAxisValues).setColor(Color.parseColor("#094200"));

        Axis xAxis = new Axis();
        xAxis.setValues(xAxisValues);
        xAxis.setTextSize(16);
        xAxis.setTextColor(Color.parseColor("#000000"));
        data.setAxisXBottom(xAxis);

        Axis yAxis = new Axis();
        yAxis.setTextSize(16);
        xAxis.setTextColor(Color.parseColor("#000000"));
        xAxis.setName("Footsteps per day.");
        data.setAxisYLeft(yAxis);

        List lines = new ArrayList();
        lines.add(line);
        data.setLines(lines);
    }

    public LineChartData getLineChartData(){
        return data;
    }
}
