package org.example;

import java.util.concurrent.TimeUnit;

public class Dog extends Animal {
    Dog (String name, int age) {
        super(name, age);
    }

    @Override
    public double goToWalk() {
        double time = getAge()*0.5;
        try {
            TimeUnit.SECONDS.sleep((long) time);
        } catch (InterruptedException e) {
            System.err.println("Can not start sleep");
        }
        return time;
    }

    @Override
    public String toString () {
        return "Dog name = " +
                getName() + "," + " age = " + getAge();
    }
}