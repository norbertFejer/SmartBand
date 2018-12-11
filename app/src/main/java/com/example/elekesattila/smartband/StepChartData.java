package com.example.elekesattila.smartband;

import android.content.Context;
import android.graphics.Color;
import android.os.Environment;
import android.util.Log;
import android.widget.Toast;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.List;

import lecho.lib.hellocharts.model.Axis;
import lecho.lib.hellocharts.model.AxisValue;
import lecho.lib.hellocharts.model.Line;
import lecho.lib.hellocharts.model.LineChartData;
import lecho.lib.hellocharts.model.PointValue;

public class StepChartData {
    private static final String TAG = "SmartBandStepChartData";
    private Context context;
    private LineChartData data;
    private File file;
    private String xAxisLine, yAxisLine, path;

    StepChartData(Context ctx){
        this.context = ctx;
        this.data = new LineChartData();
        this.path = Environment.getExternalStorageDirectory().getAbsolutePath();
        this.file = new File(path, "smart_band_chart_data.txt");
        Log.d(TAG, "Input file: " + file.getPath());
        this.xAxisLine = null;
        this.yAxisLine = null;
    }

    public void setChartData() throws IOException {

        Log.d(TAG, "Starting setChartData");
        String[] xAxisData, yAxisData;
        List xAxisValues = new ArrayList();
        List yAxisValues = new ArrayList();

        if (file.exists()) {
            try {
                Log.d(TAG, "Trying to read data.");
                file.setReadable(true);
                FileInputStream fileInputStream = new FileInputStream(file);
                InputStreamReader inputStreamReader = new InputStreamReader(fileInputStream);
                BufferedReader bufferedReader = new BufferedReader(inputStreamReader);
                xAxisLine = bufferedReader.readLine();

                yAxisLine = bufferedReader.readLine();

                bufferedReader.close();
                fileInputStream.close();

                xAxisData = xAxisLine.split(" ", -1);
                yAxisData = yAxisLine.split(" ", -1);
                //API problems

                for (int i = 0; i < xAxisData.length; ++i) {
                    xAxisValues.add(new AxisValue(i).setLabel(xAxisData[i]));
                }
                for (int i = 0; i < yAxisData.length; ++i) {
                    yAxisValues.add(new PointValue(i, Integer.parseInt(yAxisData[i])));
                }

                Line line = new Line(yAxisValues).setColor(Color.parseColor("#094200"));

                List lines = new ArrayList();
                lines.add(line);
                data.setLines(lines);

                Axis xAxis = new Axis();
                xAxis.setValues(xAxisValues);
                xAxis.setTextSize(16);
                xAxis.setTextColor(Color.parseColor("#000000"));
                data.setAxisXBottom(xAxis);

                Axis yAxis = new Axis();
                xAxis.setName("Footsteps per day");
                yAxis.setTextSize(16);
                xAxis.setTextColor(Color.parseColor("#000000"));
                data.setAxisYLeft(yAxis);

            } catch (IOException e) {
                Log.d(TAG, "Cannot read data");
                data = null;
            }
        }
        else{
            file.createNewFile();
            //saveData("A B C D E F", "1 2 3 4 5 6");
            Log.d(TAG, "Input file created.");
        }
    }

    public LineChartData getLineChartData() {
        return this.data;
    }

    public void saveData(String newXData, Integer newYData) {
        Log.d(TAG, "Saving data.");
        file.setWritable(true);
        String newXAxisLine = xAxisLine + newXData;
        String newYAxisLine = yAxisLine + newYData.toString();
        PrintWriter writer = null;
        try {
            writer = new PrintWriter(file);
        } catch (FileNotFoundException e) {
            Log.d(TAG, "File not found.");
        }
        writer.println(newXAxisLine);
        writer.println(newYAxisLine);
        writer.close();
        Log.d(TAG, "Data saved.");
    }

    public void deleteFile(){
        file.delete();
        Log.d(TAG, "Data deleted.");
        //Toast.makeText(context, "Data deleted.", Toast.LENGTH_SHORT).show();
    }
}