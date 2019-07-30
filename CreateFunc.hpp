#pragma once

#include <utility>

template<class Derived>
struct CreateFunc
{
    template<class... Args>
    static Derived* create(Args&&... args)
    {
        auto p = new Derived();
        if (p->init(std::forward<Args>(args)...))
        {
            p->autorelease();
            return p;
        }
        else
        {
            delete p;
            return nullptr;
        }
    }
};
