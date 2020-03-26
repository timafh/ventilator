#ifndef BASELOOPABLE_H
#define BASELOOPABLE_H

/**
 * @brief BaseTickableComponent is a abstract base class to define components which have to called in the 1ms tick-function
 * @todo: Add linked list of all BaseTickableComponents and call from 1ms tick-function.
 */
class BaseTickableComponent
{
public:
    virtual void tick();
};

#endif