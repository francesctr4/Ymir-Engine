#include "Singleton.h"

Singleton::Singleton()
{

}

Singleton::~Singleton()
{

}

// Static member function to access the instance
Singleton& Singleton::GetInstance() {

    static Singleton instance; // Static instance created only once

    return instance;
}

// Member functions and data
void Singleton::SomeFunction() {
    


}

