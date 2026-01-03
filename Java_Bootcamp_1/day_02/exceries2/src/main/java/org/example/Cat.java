package org.example;

public class Cat extends Animal {
    Cat (String name, int age, double weight) {
        super(name, age, weight);
    }

    @Override
    public double getFeedInfoKg() {
        return getWeight()*0.1;
    }

    @Override
    public String toString () {
        return "Cat name = " +
                getName() + "," + " age = " + getAge() + ", mass = " + getWeight() + ", feed = " + getFeedInfoKg();
    }
}