package org.example;

public abstract class Animal {
    private String name;
    private int age;
    private double weight;

    Animal (String name, int age, double weight) {
        this.name=name;
        this.age=age;
        this.weight=weight;
    }

    String getName () {
        return name;
    }

    int getAge () {
        return age;
    }

    void setName(String name) {
        this.name=name;
    }

    void setAge(int age) {
        this.age=age;
    }

    double getWeight() {
        return weight;
    }

    void setWeight(double weight) {
        this.weight=weight;
    }

    abstract double getFeedInfoKg();
}