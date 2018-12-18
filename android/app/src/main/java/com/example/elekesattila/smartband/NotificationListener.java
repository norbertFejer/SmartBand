package com.example.elekesattila.smartband;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.database.Cursor;
import android.net.Uri;
import android.os.Bundle;
import android.provider.ContactsContract;
import android.telephony.SmsMessage;
import android.telephony.TelephonyManager;
import android.util.Log;

public class NotificationListener extends BroadcastReceiver {
    private static final String TAG = "SmartBandNotification";
    private static NotificationBinder notificationBinder;
    private static int lastState = TelephonyManager.CALL_STATE_IDLE;
    private String number;
    private Context context;
    private Boolean notificationSent = false;

    @Override
    public void onReceive(Context ctx, Intent intent) {
        context = ctx;
        if (intent.getAction().equals("android.provider.Telephony.SMS_RECEIVED")) {
            Bundle bundle = intent.getExtras();
            SmsMessage[] messages = null;
            if (bundle != null) {
                try {
                    Object[] pdus = (Object[]) bundle.get("pdus");
                    messages = new SmsMessage[pdus.length];
                    for (int i = 0; i < messages.length; i++) {
                        messages[i] = SmsMessage.createFromPdu((byte[]) pdus[i]);
                        String messageSender = getContactName(messages[i].getDisplayOriginatingAddress());
                        Log.d(TAG, "From: " + messageSender);
                        if (notificationBinder != null){
                            notificationBinder.messageReceived(messageSender);
                        }
                        else{
                            Log.d(TAG, "NotificationBinder is null.");
                        }
                        //keep only the sender
                    }
                } catch (Exception e) {
                    Log.d(TAG, "Error at message receiving:" + e.getMessage());
                }
            }
        }
        else if (intent.getAction().equals("android.intent.action.NEW_OUTGOING_CALL")) {
            number = intent.getExtras().getString("android.intent.extra.PHONE_NUMBER");
        }
        else{
            String stateString = intent.getExtras().getString(TelephonyManager.EXTRA_STATE);
            number = getContactName(intent.getExtras().getString(TelephonyManager.EXTRA_INCOMING_NUMBER));
            int state = 0;
            if(stateString.equals(TelephonyManager.EXTRA_STATE_IDLE)){
                state = TelephonyManager.CALL_STATE_IDLE;
            }
            else if(stateString.equals(TelephonyManager.EXTRA_STATE_RINGING)){
                state = TelephonyManager.CALL_STATE_RINGING;
            }

            onCallStateChanged(state);
        }
    }

    public void onCallStateChanged (int state){
        switch (state) {
            case TelephonyManager.CALL_STATE_RINGING:
                Log.d(TAG, "Incoming call, ringing: " + number);
                if (notificationBinder != null && !notificationSent){
                    notificationBinder.callReceived(number);
                    notificationSent = true;
                }
                else{
                    Log.d(TAG, "NotificationBinder is null.");
                }
                break;
            case TelephonyManager.CALL_STATE_IDLE:
                Log.d(TAG, "End of notifiation: " + number);
                if (notificationBinder != null){
                    notificationBinder.endOfCall();
                    notificationSent = false;
                }
                else{
                    Log.d(TAG, "NotificationBinder is null.");
                }
                break;
        }
    }

    public static void setBindListener(NotificationBinder binder) {
        notificationBinder = binder;
    }

    private String getContactName(final String phoneNumber)
    {
        Uri uri=Uri.withAppendedPath(ContactsContract.PhoneLookup.CONTENT_FILTER_URI,Uri.encode(phoneNumber));

        String[] projection = new String[]{ContactsContract.PhoneLookup.DISPLAY_NAME};

        String contactName=phoneNumber;
        Cursor cursor=context.getContentResolver().query(uri,projection,null,null,null);

        if (cursor != null) {
            if(cursor.moveToFirst()) {
                contactName=cursor.getString(0);
            }
            cursor.close();
        }

        return contactName;
    }
}

