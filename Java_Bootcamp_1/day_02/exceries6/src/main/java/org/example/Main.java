package org.example;

import java.util.ArrayList;
import java.util.Scanner;

public class Main {
    private static Scanner sc = new Scanner(System.in);
    private static int size=0;
    private static ArrayList<Animal> pets = new ArrayList<>();
    public static void main(String[] args) {
        inputSize();
        for (int i=0; i<size; ++i) {
            String temp = sc.nextLine();
            if (temp.equalsIgnoreCase("dog")) addAnimalPets(false);
            else if (temp.equalsIgnoreCase("cat")) addAnimalPets(true);
            else System.err.println("Incorrect input. Unsupported pet type");
        }
        AnimalIterator idx = new AnimalIterator(pets);
        while (idx.hasNext()) {System.out.println(idx.next());}
        idx.reset();
    }

    public static void inputSize() {
        while (true) {
            if (sc.hasNextInt()) {
                size = sc.nextInt();
                sc.nextLine();
                if (size<=0) System.err.println("Input size <=0");
                else break;
            } else {
                System.err.println("Could not parse a number. Please, try again");
                sc.next();
            }
        }
    }

    public static void addAnimalPets(boolean flag) {
        while (true) {
            String tempN;
            int tempA = 0;
            if (sc.hasNextLine()) {
                tempN = sc.nextLine();
            } else {
                System.err.println("Could not parse a line. Please, try again");
                sc.next();
                continue;
            }

            if (sc.hasNextInt()) {
                tempA = sc.nextInt();
                sc.nextLine();
            } else {
                System.err.println("Could not parse a number. Please, try again");
                sc.next();
                continue;
            }

            if (tempA<=0) {
                System.err.println("Incorrect input. Age <= 0");
                return;
            }
            if (flag) pets.add(new Cat(tempN, tempA));
            else pets.add(new Dog(tempN, tempA));
            break;
        }
    }
}