#pragma once

// Singleton Design Pattern (to use if needed)

class Singleton {
public:

    static Singleton& GetInstance();

    // Delete the copy constructor and assignment operator to prevent duplication
    Singleton(Singleton const&) = delete;
    void operator=(Singleton const&) = delete;

    // Member functions and data
    void SomeFunction();

private:

    // Private constructor and destructor to prevent direct instantiation or deletion
    Singleton(); 
    ~Singleton();

};