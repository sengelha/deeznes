#pragma once

namespace deeznes
{
namespace sdlpp
{

class non_copyable 
{
public: 
   non_copyable (const non_copyable &) = delete;
   non_copyable & operator = (const non_copyable &) = delete;

protected:
   non_copyable () = default;
   ~non_copyable () = default; /// Protected non-virtual destructor
};

}
}