
#pragma once
#include <vector>

#if 0
template<typename Numeric, typename Generator = std::mt19937>
Numeric random(Numeric from, Numeric to)
{
    thread_local static Generator gen(std::random_device{}());

    using dist_type = typename std::conditional
    <
        std::is_integral<Numeric>::value
        , std::uniform_int_distribution<Numeric>
        , std::uniform_real_distribution<Numeric>
    >::type;

    thread_local static dist_type dist;

    return dist(gen, typename dist_type::param_type{from, to});
}

template<class __T> 
void initalize(std::vector<__T*>& v_data, int&& n){

    for(int i=0; i<n; ++i){
        __T* d = new __T();
        d->x = static_cast<std::uint8_t>(1 + std::rand()/((RAND_MAX)/UINT8_MAX));

        d->y = random<decltype(d->y)>(0.0, 100);

        v_data.push_back(d);

    }

}

#endif

template<class __T> 
void print_beautify(const std::vector<__T*>& v_data){
    for(auto& d: v_data){
        std::cout << "{ x: " << d->x << ", " << "y: " <<d->y <<" }\n";
    }
}

template<class __T>   
void print(const std::vector<__T>& v_data){
    std::cout << "{ ";
    for(auto& d: v_data){
        std::cout << d << ", ";
    }
    std::cout << "}\n";

}


template<class __T>   
void print(__T begin, __T end){
    std::cout << "{ ";
    while(begin != end){
        std::cout << *begin<< ", ";
        ++begin;
    }
    std::cout << "}\n";

}




