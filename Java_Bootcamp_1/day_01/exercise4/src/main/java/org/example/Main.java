package org.example;

import java.util.Scanner;

public class Main {
    private static int size = 0, reSize = 0, res = 0;
    private static int[] nums;
    private static boolean flag = false;
    public static void main(String[] args) {
        inputSize();
        inputNums();
        if (flag) {
            avgNums();
        } else {
            System.err.println("There are no negative elements");
        }
        System.out.println(res);
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
        nums = new int[size];
        Scanner sc = new Scanner(System.in);
        while (true) {
            if(sc.hasNextInt()) {
                for (int i=0; i<size; ++i) {
                    nums[i]=sc.nextInt();
                    if (nums[i]<0) flag = true;
                }
                break;
            } else {
                System.err.println("Could not parse a number. Please, try again");
                sc.next();
            }
        }
    }

    public static void avgNums() {
        for (int i = 0; i<size; ++i) {
            if (nums[i]<0) {
                res+=nums[i];
                ++reSize;
            }
        }

        res/=reSize;
    }
}