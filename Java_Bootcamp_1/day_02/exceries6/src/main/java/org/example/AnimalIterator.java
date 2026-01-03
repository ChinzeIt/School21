package org.example;

import java.util.ArrayList;

public class AnimalIterator implements BaseIterator{
    private ArrayList<Animal> pets;
    private int index = 0;
    AnimalIterator (ArrayList<Animal> pets) {
        this.pets = pets;
    }

    public Animal next() {
        return pets.get(index++);
    }

    public boolean hasNext() {
        return index < pets.size();
    }

    public void reset() {
        index = 0;
    }
}
