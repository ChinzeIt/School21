package org.example;

import java.util.Scanner;

public class Main {
    private static int size = 0;
    private static double[] nums;
    public static void main(String[] args) {
        inputSize();
        inputNums();
        if (size!=1) sortUpNums();
        outputRes();
    }

    public static void inputSize() {
        Scanner sc = new Scanner(System.in);
        while (true) {
            if(sc.hasNextInt()) {
                size = sc.nextInt();
                if (size<=0) System.err.println("Input error. Size <= 0");
                else break;
            } else {
                System.err.println("Could not parse a number. Please, try again");
                sc.next();
            }
        }
    }

    public static void inputNums() {
        nums = new double[size];
        Scanner sc = new Scanner(System.in);
        while (true) {
            if(sc.hasNextDouble()) {
                for (int i=0; i<size; ++i) {
                    nums[i]=sc.nextDouble();
                }
                break;
            } else {
                System.err.println("Could not parse a number. Please, try again");
                sc.next();
            }
        }
    }

    public static void sortUpNums() {
        for (int i=0; i<size; ++i) {
            for (int j=i+1; j<size; ++j) {
                double temp = nums[i];
                if (nums[j]<nums[i]) {
                    nums[i] = nums[j];
                    nums[j] = temp;
                }
            }
        }
    }

    public static void outputRes() {
        for(int i=0; i<size; ++i)
            System.out.println(nums[i]);
    }
}