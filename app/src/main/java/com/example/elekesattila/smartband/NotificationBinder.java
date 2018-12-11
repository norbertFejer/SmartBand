package com.example.elekesattila.smartband;

public interface NotificationBinder {
    //void bindSmsListener();
    //void unbindSmsListener();
    void messageReceived(String message);
    void callReceived(String message);
}
