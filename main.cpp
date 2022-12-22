

#include <iostream>
#include <vector>
#include <list>

#include "experiment.hpp"
#include "beautify.hpp"


struct Data{
    std::uint8_t x;
    double y;
};

void stl_int_test(){
    std::vector<int> v_int = {2,8,1,9,3,4,0};
    print(v_int);
    
    reorder(v_int.begin(), v_int.end(), 5);
    print(v_int);

    std::list<int> v_list = {2,8,1,9,3,4,0};
    print(v_list.begin(), v_list.end());
    
    reorder(v_list.begin(), v_list.end(), 5);
    print(v_list.begin(), v_list.end());
}


template<typename T>struct Comparitor{
    
    bool operator()(T& begin, T& end){
        const decltype((*begin)->x) comp = 155;
        if(comp >= (*begin)->x and comp >= (*end)->x ){
            --end;
        }else if(comp <= (*begin)->x and comp <= (*end)->x ){
            ++begin;
        }else if(comp > (*begin)->x and comp < (*end)->x){
            std::swap(*begin , *end);
            ++begin;
            --end;
        }else{
            ++begin;
            --end;
        }
        return true;
    }
};

template<typename T>struct Greater{
    bool operator()(T& lhs, T& rhs){
        std::cout <<"helo world" <<"\n" << (*lhs)->x << "  <<===>>> " <<(*rhs)->x;
        double epsilon = 0.0000001f;
        return std::isgreater((*lhs)->x, (*rhs)->x) ? true : false;
    }
};

void t_test(){

}


int main(){

    std::vector<Data*> v_data;
    initialize(v_data, 4);

    print_beautify(v_data);
    std::cout << "\n\n";
    
    reorder(v_data.begin(), v_data.end(), Comparitor<decltype(v_data.begin())>());
    print_beautify(v_data);

    std::cout << "\n\n";
    for(auto& el: reorder(v_data, Comparitor<decltype(v_data.begin())>())){
        std::cout <<"{ x: " << el->x <<", y: " <<el->y <<" }\n";
    }

    // std::cout << "\n\n";
    // auto result = reorder(v_data, Comparitor<decltype(v_data.begin())>()) | Greater<decltype(v_data.begin())>();
    // print_beautify(v_data);


#if 0
    auto result = reorder(v_data, Comparitor<decltype(v_data.begin())>()) | [](auto& lhs, auto& rhs){ return (*lhs)->x > (*rhs)->x; };
    auto result = reorder(v_data, Comparitor<decltype(v_data.begin())>()) | Greater<std::remove_reference<decltype(v_data.begin())>>();
    print_beautify(v_data);
    std::partial_sort(v_data.rbegin(), v_data.rend(), v_data.rend(), Greater<decltype(v_data.begin())>());
    

    reorder(v_data, Comparitor<decltype(v_data.begin())>()) | sort_range( v_data, Greater<decltype(v_data.begin())>()); 
    sort_range( v_data, Greater<decltype(v_data.begin())>()); 
#endif
         

}
