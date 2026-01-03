package org.example;

public interface BaseIterator<T> {
    public T next();

    public boolean hasNext();

    public void reset();
}
