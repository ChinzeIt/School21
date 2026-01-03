package org.example;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.Scanner;

public class Main {
    private static String path;
    private static int size = 0;
    private static double[] nums;
    private static double min, max;
    public static void main(String[] args) {
        boolean flag;
        inputPath();
        flag = readFileTXT();
        if (flag) {
            MinMaxNums();
            outputNums();
            if (writeFileTXT()) System.out.println("Saving min and max values in file");
        } else {
            try {
                new PrintWriter("result.txt");
            } catch (FileNotFoundException e) {
                System.err.println("Error clear in result.txt");
            }
        }
    }

    public static void inputPath () {
        Scanner sc = new Scanner(System.in);
        while (true) {
            if (sc.hasNextLine()) {
                path = sc.nextLine();
                break;
            } else {
                System.err.println("Input error. No valid name");
                sc.next();
            }
        }
    }

    public static boolean readFileTXT() {
        try {
            File file = new File(path);
            if (!file.exists()) {
                System.err.println("Input error. File doesn't exist");
                return false;
            }
            if (file.length()==0) {
                System.err.println("File empty");
                return false;
            }
            Scanner sc = new Scanner(file);
            if (sc.hasNextInt()) size = sc.nextInt();
            else {
                System.err.println("Size not integer type");
                return false;
            }

            if (size<=0) {
                System.err.println("Input error. Size <= 0");
                return false;
            }

            nums = new double[size];
            int count = 0;

             while (sc.hasNextDouble()) {
                    nums[count]=sc.nextDouble();
                    ++count;
            }

             if (size!=count) {
                 System.err.println("Input error. Insufficient number of elements");
                 return false;
             }
        } catch (FileNotFoundException e) {
            System.err.println("File not found");
            return false;
        }
        return true;
    }

    public static void MinMaxNums () {
        min = nums[0];
        max = nums[0];

        for (int i=0; i<size; ++i) {
            if (min>nums[i]) min=nums[i];
            if (max<nums[i]) max=nums[i];
        }
    }

    public static void outputNums () {
        System.out.println(size);
        for (int i=0; i<size; ++i) {
            int temp = i;
            if (++temp!=size) System.out.print(nums[i]+" ");
            else System.out.println(nums[i]);
        }
    }

    public static boolean writeFileTXT() {
        try (PrintWriter pw = new PrintWriter("result.txt")) {
            pw.print(min + " ");
            pw.print(max);
        } catch (FileNotFoundException e) {
            System.err.println("Error in saving in file");
            return false;
        }
        return true;
    }
}