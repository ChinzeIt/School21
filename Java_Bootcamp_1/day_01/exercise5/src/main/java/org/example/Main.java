package org.example;

import java.util.Scanner;

public class Main {
    private static int size = 0, reSize=0;
    private static int[] nums, res;
    private static boolean flag = false;
    public static void main(String[] args) {
        inputSize();
        inputNums();
        succesNums();
        if (flag) {
            outputRes();
        } else {
            System.err.println("There are no such elements");
        }
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
                }
                break;
            } else {
                System.err.println("Could not parse a number. Please, try again");
                sc.next();
            }
        }
    }

    public static void succesNums() {
        int first, last, count;
        res = new int [size];
        for (int i=0; i<size; ++i) {
            res[reSize] = nums[i];
            first = 0;
            last = 0;
            count = 0;
            while (nums[i]!=0) {
                if (count==0) {
                    last = nums[i]%10;
                    first = nums[i]%10;
                } else {
                    first = nums[i]%10;
                }
                nums[i]/=10;
                ++count;
            }
            if (first==last) {
                flag = true;
                ++reSize;
            }
        }
    }

    public static void outputRes() {
        for(int i=0; i<reSize; ++i)
            System.out.println(res[i]);
    }
}