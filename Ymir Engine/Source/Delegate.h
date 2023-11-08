#pragma once

// Delegate Class using function pointers (to use if needed)

class Delegate {
public:

    using FunctionPtr = void(*)(); // Define a function pointer type

    void SetCallback(FunctionPtr function);

    void Invoke();

private:

    FunctionPtr callback = nullptr;

};