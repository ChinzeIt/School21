package org.example;

import java.text.DecimalFormat;

public class Dog extends Animal {
    Dog (String name, int age, double weight) {
        super(name, age, weight);
    }

    @Override
    public double getFeedInfoKg() {
        return getWeight()*0.3;
    }

    @Override
    public String toString () {
        DecimalFormat df = new DecimalFormat("0.00");
        return "Dog name = " +
                getName() + "," + " age = " + getAge() + ", mass = " + getWeight() + ", feed = " + df.format(getFeedInfoKg());
    }
}