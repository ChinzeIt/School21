package org.example;

import java.util.Scanner;

public class Main {
    private static int hours=0, minutes=0, seconds=0;

    public static void main(String[] args) {
        input();
        calculate();
        output();
    }

    public static void input () {
        Scanner sc = new Scanner(System.in);

        while (true) {
            if (sc.hasNextInt()) {
                seconds = sc.nextInt();
                if (seconds<0) {
                    System.out.println("Incorrect time");
                } else {
                    break;
                }
            } else {
                System.out.println("Could not parse a number. Please, try again");
                sc.next();
            }
        }
    }

    public static void calculate () {
        int tempSeconds = seconds;
        seconds = tempSeconds % 60;
        minutes = (tempSeconds / 60) % 60;
        hours = tempSeconds / 3600;
        if (hours == 24) {
            hours = 0;
        } else if (hours>24) {
            while (hours>24) {
                hours = hours - 24;
            }
        }
    }

    public static void output () {
        System.out.printf("%02d:%02d:%02d%n", hours, minutes, seconds);
    }
}