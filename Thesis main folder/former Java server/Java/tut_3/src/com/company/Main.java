package com.company;

public class Main {
    public static void main(String[] args){
        System.out.println("hi");
        DateTime dt = new DateTime();
        dt.updateTime();
        System.out.println(dt.getDay()+":"+dt.getMonth()+":"+dt.getYear());
        System.out.println(dt.getHour()+":"+dt.getMinute()+":"+dt.getSecond());
    }
}
