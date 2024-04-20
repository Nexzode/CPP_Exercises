#pragma once
#include <stddef.h>
#include <array>
#include <iostream>
#include <functional>

template<typename P, size_t W, size_t H>
class Image
{
    std::array<std::array<P, W>, H> _array;
public:
    Image(const P& pixel)
    {
        for(size_t i = 0; i < W; i++)
        {
            std::fill(_array[i].begin(), _array[i].end(), pixel);
        }
    }

    Image() = default;

    Image(const std::function<P(size_t i, size_t j)>& fcn){
        for(size_t i = 0; i < W; i++)
        {
            for(size_t j = 0; j < H; j++)
            {
                _array[i][j] = fcn(i, j);
            }
        }
    }

    const P& operator()(size_t i, size_t j) const{return _array[i][j];}
    P& operator()(size_t i, size_t j) {return _array[i][j];}

    Image operator +(const Image& other) const
    {
        Image img = Image<P, W, H>();
        for(size_t i = 0; i < W; i++)
        {
            for(size_t j = 0; i < H; i++)
            {
               img(i, j) = _array[i][j] + other(i, j);
            }
        }
        return img;
    }
};


// int main()
// {
//     auto img = Image<int, 2, 2>(1);
//     auto img2 = Image<int, 2, 2>(2);
//     auto img3 = img + img2;
//     std::cout << img3(0,0) << std::endl;
//     return 0;
// }