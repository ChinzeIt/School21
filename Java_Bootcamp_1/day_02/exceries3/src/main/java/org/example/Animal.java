package org.example;

public abstract class Animal {
    private String name;
    private int age;

    Animal (String name, int age) {
        this.name=name;
        this.age=age;
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
}