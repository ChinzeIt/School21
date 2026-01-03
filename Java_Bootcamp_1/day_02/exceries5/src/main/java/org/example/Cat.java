package org.example;

import java.util.concurrent.TimeUnit;

public class Cat extends Animal {
    Cat (String name, int age) {
        super(name, age);
    }

    @Override
    public double goToWalk() {
        double time = getAge()*0.25;
        try {
            TimeUnit.SECONDS.sleep((long) time);
        } catch (InterruptedException e) {
            System.err.println("Can not start sleep");
        }
        return time;
    }

    @Override
    public String toString () {
        return "Cat name = " +
                getName() + "," + " age = " + getAge();
    }
}
