package org.example;

import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class User {
    private Map<String, Integer> NameAge = new HashMap<>();
    private int size = 0;

    public void inputSize() {
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

    public void inputNameAge() {
        Scanner sc1 = new Scanner(System.in);
        Scanner sc2 = new Scanner(System.in);
        int count = 0;

        while (count<size) {
            String name;
            if (sc1.hasNextLine()) {
                name = sc1.nextLine();
            } else {
                System.err.println("Could not parse a line. Please, try again");
                sc1.next();
                continue;
            }

            int age;
            if (sc2.hasNextInt()) {
                age = sc2.nextInt();
            } else {
                System.err.println("Could not parse a number. Please, try again");
                sc2.next();
                continue;
            }

            if (age<=0) {
                System.err.println("Incorrect input. Age <= 0");
                continue;
            }

            NameAge.put(name, age);

            ++count;
        }
    }

    public void outTeen() {
        NameAge.entrySet()
                .removeIf(entery -> entery.getValue() < 18);
    }

    public void printRes() {
        NameAge.entrySet()
                .stream()
                .forEach(entry -> System.out.println(entry.getKey()));
    }
}
