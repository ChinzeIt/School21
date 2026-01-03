package org.example;

import java.util.ArrayList;
import java.util.Scanner;

public class Main {
    private static int size = 0;
    private static ArrayList<String> Lines = new ArrayList<>();
    private static String filter;
    public static void main(String[] args) {
        inputSize();
        inputLine();
        inputFilter();
        filtering();
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

    public static void inputLine() {
        Scanner sc = new Scanner(System.in);
        for (int i=0; i<size; ++i) {
            if (sc.hasNextLine()) Lines.add(sc.nextLine());
            else {
                System.err.println("Not valid line");
                sc.next();
                --i;
            }
        }
    }

    public static void inputFilter() {
        Scanner sc = new Scanner(System.in);
        while (true) {
            if(sc.hasNextLine()) {
                filter = sc.nextLine();
                break;
            } else {
                System.err.println("Could not parse a line. Please, try again");
                sc.next();
            }
        }
    }

    public static void filtering() {
        for (int i=0; i<size; ++i) {
            if (Lines.get(i).indexOf(filter)>=0) {
                System.out.println(Lines.get(i));
            }
        }
    }
}