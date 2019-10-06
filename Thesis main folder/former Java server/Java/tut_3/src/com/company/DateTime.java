package com.company;
import java.time.LocalDateTime;
public class DateTime implements IDate,ITime {
    int day,month,year,hour,minute,second;
    public DateTime(){
        LocalDateTime now = LocalDateTime.now();
        year=now.getYear();
        month=now.getMonthValue();
        day=now.getDayOfMonth();
        hour=now.getHour();
        minute=now.getMinute();
        second=now.getSecond();
    }
    public int getYear() {
        return year;
    }
    public int getMonth() {
        return month;
    }
    public int getDay() {
        return day;
    }
    public int getHour() {
        return hour;
    }
    public int getMinute() {
        return minute;
    }
    public int getSecond() {
        return second;
    }
    public void updateTime(){
        LocalDateTime now = LocalDateTime.now();
    }
}
