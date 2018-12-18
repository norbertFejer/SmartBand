package com.example.elekesattila.smartband;

public interface NotificationBinder {
    void messageReceived(String message);
    void callReceived(String message);
    void endOfCall();
}
