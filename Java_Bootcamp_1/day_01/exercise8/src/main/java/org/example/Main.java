package org.example;

import java.util.Scanner;

public class Main {
    private static int nums=0, temp=0;
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        boolean flag = false;
        while(true) {
            if (!sc.hasNextInt() && !flag) {
                System.err.println("Input error");
                sc.next();
                continue;
            }
            if (sc.hasNextInt()) {
                nums=sc.nextInt();
                if (nums<temp) {
                    System.err.println("The sequence is ordered in ascending order " + nums);
                    break;
                }
                temp = nums;
                flag = true;
            } else {
                System.err.println("The sequence is ordered in ascending order");
                break;
            }
        }
    }
}