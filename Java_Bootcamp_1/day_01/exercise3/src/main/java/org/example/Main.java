package org.example;

import java.util.Scanner;

public class Main {
    private static final long MAX = 92;
    private static long num=0;

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        while (true) {
            if (sc.hasNextLong()) {
                num = sc.nextLong();
                break;
            } else {
                System.out.println("Could not parse a number. Please, try again");
                sc.next();
            }
        }

        if (num>MAX || num<-MAX) {
            System.err.println("To large n");
            return;
        }

        System.out.println(fibonacci(num));
    }

    public static long fibonacci (long num) {
        if (num==0) return 0;
        if (num==1) return 1;
        if (num==-1) return 1;

        if (num>0) {
            long a = fibonacci(num-1);
            long b = fibonacci(num-2);

            if (a>Long.MAX_VALUE-b) throw new ArithmeticException("To large n");

            return a+b;
        } else {
            long a = fibonacci(num+2);
            long b = fibonacci(num+1);

            if (a < Long.MIN_VALUE + b) throw new ArithmeticException("To large n");

            return a-b;
        }
    }
}