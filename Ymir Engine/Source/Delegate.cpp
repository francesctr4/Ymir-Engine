#include "Delegate.h"

#include "Log.h"

void Delegate::SetCallback(FunctionPtr function) {

    callback = function;

}

void Delegate::Invoke() {

    if (callback != nullptr) {

        callback(); // Invoke the function

    }
    else {

        LOG("Delegate: Callback function not set!");

    }

}