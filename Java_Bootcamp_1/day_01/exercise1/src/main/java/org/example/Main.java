package org.example;

import java.util.ArrayList;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        ArrayList<Double> PointXY = new ArrayList<Double>();
        byte size = 0;
        while (size<6) {
            if (sc.hasNextDouble()) {
                PointXY.add(sc.nextDouble());
                ++size;
            } else {
                System.out.println("Could not parse a number. Please, try again");
                sc.next();
            }
        }

        double A = Math.sqrt(Math.pow((PointXY.get(2)-PointXY.get(0)), 2)+ Math.pow((PointXY.get(3)- PointXY.get(1)), 2));
        double B = Math.sqrt(Math.pow((PointXY.get(4)-PointXY.get(2)), 2)+ Math.pow((PointXY.get(5)- PointXY.get(3)), 2));
        double C = Math.sqrt(Math.pow((PointXY.get(0)-PointXY.get(4)), 2)+ Math.pow((PointXY.get(1)- PointXY.get(5)), 2));

        if (A+B>C && A+C>B && B+C>A) {
            System.out.println(String.format("%.3f", A+B+C));
        } else {
            System.out.println("It's not a triangle");
        }
    }
}