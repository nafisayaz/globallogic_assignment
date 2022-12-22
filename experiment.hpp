
#pragma once
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <random>
#include <functional>
#include <type_traits>

template<typename __T,
    typename std::enable_if<!std::is_same<
        typename std::vector<typename __T::value_type>::iterator,
         __T>::value, void>::type>
struct typeInfo{
    typedef typename std::vector<__T*>::iterator type;
};

template<typename Numeric, typename Generator = std::mt19937>
Numeric random(Numeric from, Numeric to)
{
    thread_local static Generator gen(std::random_device{}());
    using dist_type = typename std::conditional
    <
        std::is_integral<Numeric>::value
        ,std::uniform_int_distribution<Numeric>
        ,std::uniform_real_distribution<Numeric>
    >::type;

    thread_local static dist_type dist;
    return dist(gen, typename dist_type::param_type{from, to});

}

template<class __T> 
void initialize(std::vector<__T*>& v_data, int&& n){
    for(int i=0; i<n; ++i){
        __T* d = new __T();
        d->x = static_cast<decltype(d->y)>(1 + std::rand()/((RAND_MAX)/UINT8_MAX));
        d->y = random<decltype(d->y)>(0.0, 100);
        v_data.push_back(d);
    }

}

#if 0
template<typename __T, typename __Pre>
void sort_range( __T container, __Pre predicate ){
        std::partial_sort(container.rbegin(), container.rend(), predicate);
}
#endif


template<typename __T, typename __Pre>
__T operator | (__T container, __Pre&& predicate){

#if 0
    auto begin = const_cast<<decltype(__T)>::iterator&>(container.begin());
    decltype(container.begin()) begin = container.begin();
    decltype(container.begin()) end = container.end();
#endif

    auto begin = container.begin();
    auto end = container.end();
    std::sort(begin, end, predicate);

#if 0
    predicate(std::remove_reference<__T&>(container.begin()), std::remove_reference<__T&>(container.end()));
    predicate(container.begin(), container.end());
#endif
       
    return container;
}

template<class __T>
void reorder(__T begin, __T end, int&& comp){
        std::advance(end, -1);
        while( begin != end){
            if(comp >= *begin and comp >= (*end) ){
                --end;
            }else if(comp <= *begin and comp <= *end ){
                ++begin;
            }else if(comp > *begin and comp < *end){
                std::swap(*begin , *end);
                ++begin;
                --end;
            }else{
                ++begin;
                --end;
            }
            
            if(std::distance(begin, end) == 1 or std::distance(begin, end) == 0){
                break;
            }
        }
} 

template<class __T, class __Pred>
void reorder(__T begin, __T end, __Pred predicate ){
    std::advance(end, -1);
        while( begin != end){
            if(predicate(begin, end)){ }
            if(std::distance(begin, end) == 1 or std::distance(begin, end) == 0){
                break;
            }
        }
}

template<class __T, class __Pred>
__T reorder(__T container, __Pred predicate ){
    reorder(container.begin(), container.end(), predicate);
    return container;
}



#if 0
template<typename It, typename U, typename Predicate>
void operator |(void(*f)( It& begin, It& end, U& Comparitor ), std::function<void( It&, It&,  Predicate)>sort ){
        f(begin, end,Comparitor);
        sort(begin, end, Predicate );

}
#endif

