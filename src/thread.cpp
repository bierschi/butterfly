#include "thread.h"

Thread::Thread() {

}

Thread::~Thread() {

}

void Thread::start() {
    pthread_create(&_self, NULL, executorFunc, this);
}

void Thread::join() {
    pthread_join(_self, NULL);
}

void Thread::detach() {
    pthread_detach(_self);
}

void* Thread::executorFunc(void *exec) {
    ((Thread*)exec)->execute();
    return NULL;
}