package org.example;

import java.util.ArrayList;
import java.util.Comparator;
import java.util.Scanner;

public class Main {
    private static Scanner sc = new Scanner(System.in);
    private static int size=0;
    private static ArrayList<Animal> pets = new ArrayList<>();
    public static void main(String[] args) {
        inputSize();
        for (int i=0; i<size; ++i) {
            String temp = sc.nextLine();
            if (temp.equalsIgnoreCase("dog")) addAnimalPets(0);
            else if (temp.equalsIgnoreCase("cat")) addAnimalPets(1);
            else if (temp.equalsIgnoreCase("hamster")) addAnimalPets(2);
            else if (temp.equalsIgnoreCase("guinea")) addAnimalPets(3);
            else System.err.println("Incorrect input. Unsupported pet type");
        }
        pets.stream().sorted(Comparator.comparingInt(a->{
            if (a instanceof Herbivore) return 1;
            else if (a instanceof Omnivore) return 2;
            else return 3;
        })).forEach(System.out::println);
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

    public static void addAnimalPets(int flag) {
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

            if (flag==0) pets.add(new Dog(tempN, tempA));
            else if (flag==1) pets.add(new Cat(tempN, tempA));
            else if (flag==2) pets.add(new Hamster(tempN, tempA));
            else if (flag==3) pets.add(new GuineaPig(tempN, tempA));
            break;
        }
    }
}