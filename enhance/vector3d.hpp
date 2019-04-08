/*  
*   Copyright 2019 Simon Raschke
*
*   Licensed under the Apache License, Version 2.0 (the "License");
*   you may not use this file except in compliance with the License.
*   You may obtain a copy of the License at
*
*       http://www.apache.org/licenses/LICENSE-2.0
*
*   Unless required by applicable law or agreed to in writing, software
*   distributed under the License is distributed on an "AS IS" BASIS,
*   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*   See the License for the specific language governing permissions and
*   limitations under the License.
*/


#pragma once

#include "enabler.hpp"
#include <cmath>
#include <array>
#include <algorithm>
#include <numeric>



namespace enhance 
{ 
    template<typename T = float>
    struct Vector3d
        : public __internal::ArithmeticEnabler<T>
    {
        Vector3d();
        Vector3d(T value);
        Vector3d(T x, T y, T z);

        template<typename U>
        Vector3d(const Vector3d<U>& other);

        Vector3d(const Vector3d<T>& other) = default;
        Vector3d(Vector3d<T>&& other) = default;

        constexpr void swap( Vector3d<T>& other ) noexcept(std::is_nothrow_swappable_v<T>);

        Vector3d<T>& operator=(const Vector3d<T>& other) = default;;
        Vector3d<T>& operator=(Vector3d<T> &&) = default;

        inline auto begin()         { return std::begin(data); };
        inline auto end()           { return std::end(data); };
        constexpr inline auto begin() const   { return std::begin(data); };
        constexpr inline auto end()   const   { return std::end(data); };
        constexpr inline auto cbegin() const  { return std::cbegin(data); };
        constexpr inline auto cend()   const  { return std::cend(data); };
        inline auto rbegin()        { return std::rbegin(data); };
        inline auto rend()          { return std::rend(data); };
        constexpr inline auto rbegin() const  { return std::rbegin(data); };
        constexpr inline auto rend()   const  { return std::rend(data); };
        constexpr inline auto crbegin() const { return std::crbegin(data); };
        constexpr inline auto crend()   const { return std::crend(data); };

        // change data element wise directly
        template<typename UNARY_FUNCTOR>
        void unaryApply(UNARY_FUNCTOR&& unary);

        // make a copy of data, change copy and return copy
        template<typename UNARY_FUNCTOR>
        const Vector3d<T> unaryExpr(UNARY_FUNCTOR&& unary) const;

        template<typename U>
        Vector3d<U> cast() const;

        T& operator[](std::size_t i);
        constexpr T operator[](std::size_t i) const;

        T& operator()(std::size_t i);
        constexpr T operator()(std::size_t i) const;
        
        template<typename U>
        const Vector3d<T> operator+(const Vector3d<U>& other) const;
        
        template<typename U>
        const Vector3d<T> operator-(const Vector3d<U>& other) const;
        
        const Vector3d<T> operator-() const;
        
        template<typename U>
        Vector3d<T>& operator+=(const Vector3d<U>& other);
        
        template<typename U>
        Vector3d<T>& operator-=(const Vector3d<U>& other);

        float norm() const;
        void normalize();
        Vector3d<T> normalized() const;

        template<typename U>
        T dot(const Vector3d<U>& other) const;

        template<typename U>
        Vector3d<T> cross(const Vector3d<U>& other) const;


    protected:
        std::array<T,3> data;
    };



    template<typename T>
    Vector3d<T>::Vector3d()
        : data(
        {
            static_cast<T>(0), 
            static_cast<T>(0), 
            static_cast<T>(0)
        })
    {

    }



    template<typename T>
    Vector3d<T>::Vector3d(T value)
        : data({value, value, value})
    {

    }



    template<typename T>
    Vector3d<T>::Vector3d(T x, T y, T z)
        : data({x,y,z})
    {

    }

    
    template<typename T>
    template<typename U>
    Vector3d<T>::Vector3d(const Vector3d<U>& other)
    {
        data = other.template cast<T>().data;
    }



    template<typename T>
    template<typename U>
    Vector3d<U> Vector3d<T>::cast() const
    {
        return Vector3d<U>
        (
            static_cast<U>(data[0]),
            static_cast<U>(data[1]),
            static_cast<U>(data[2])
        );
    }



    template<typename T>
    constexpr void Vector3d<T>::swap( Vector3d<T>& other ) noexcept(std::is_nothrow_swappable_v<T>)
    {
        data.swap(other.data);
    }



    template<typename T>
    template<typename UNARY_FUNCTOR>
    const Vector3d<T> Vector3d<T>::unaryExpr(UNARY_FUNCTOR&& unary) const
    {
        Vector3d<T> copy(0);
        std::transform(std::begin(data), std::end(data), std::begin(copy), unary);
        return copy;
    }



    template<typename T>
    template<typename UNARY_FUNCTOR>
    void Vector3d<T>::unaryApply(UNARY_FUNCTOR&& unary)
    {
        std::transform(std::begin(data), std::end(data), std::begin(data), unary);
    }



    template<typename T>
    T& Vector3d<T>::operator[](std::size_t i)
    {
        return data[i];
    }
    


    template<typename T>
    constexpr T Vector3d<T>::operator[](std::size_t i) const
    {
        return data[i];
    }
    


    template<typename T>
    T& Vector3d<T>::operator()(std::size_t i) 
    {
        return data[i];
    }
    


    template<typename T>
    constexpr T Vector3d<T>::operator()(std::size_t i) const
    {
        return data[i];
    }
    


    template<typename T>
    template<typename U>
    const Vector3d<T> Vector3d<T>::operator+(const Vector3d<U>& other) const
    {
        Vector3d<T> copy(0);
        std::transform(std::begin(data), std::end(data), std::begin(other.data), std::begin(copy.data), std::plus<T>());
        return copy;
    }
    


    template<typename T>
    template<typename U>
    const Vector3d<T> Vector3d<T>::operator-(const Vector3d<U>& other) const
    {
        Vector3d<T> copy(0);
        std::transform(std::begin(data), std::end(data), std::begin(other.data), std::begin(copy.data), std::minus<T>());
        return copy;
    }
    


    template<typename T>
    const Vector3d<T> Vector3d<T>::operator-() const
    {
        Vector3d<T> copy = *this;
        std::transform(std::begin(data), std::end(data), std::begin(copy.data), std::negate<T>());
        return copy;
    }
    


    template<typename T>
    template<typename U>
    Vector3d<T>& Vector3d<T>::operator+=(const Vector3d<U>& other)
    {
        *this = *this + other;
        return *this;
    }
    


    template<typename T>
    template<typename U>
    Vector3d<T>& Vector3d<T>::operator-=(const Vector3d<U>& other)
    {
        *this = *this - other;
        return *this;
    }



    template<typename T>
    float Vector3d<T>::norm() const
    {
        return std::sqrt(std::inner_product(std::begin(data), std::end(data), std::begin(data), float(0)));
    }



    template<typename T>
    void Vector3d<T>::normalize()
    {
        const T norm_ = norm();
        std::transform(std::begin(data), std::end(data), std::begin(data), [&norm_](T element){ return element/norm_; } );
    }



    template<typename T>
    Vector3d<T> Vector3d<T>::normalized() const
    {
        auto copy = Vector3d<T>(*this);
        copy.normalize();
        return copy;
    }



    template<typename T>
    template<typename U>
    T Vector3d<T>::dot(const Vector3d<U>& other) const
    {
        return std::inner_product(std::begin(data), std::end(data), std::begin(other.data), static_cast<T>(0.0));
    }



    template<typename T>
    template<typename U>
    Vector3d<T> Vector3d<T>::cross(const Vector3d<U>& other) const
    {
        return Vector3d<T>(
            data[1]*other[2] - data[2]*other[1],
            data[2]*other[0] - data[0]*other[2],
            data[0]*other[1] - data[1]*other[0]
        );
    }
} // namespace enhance 



namespace std
{
    template<class T>
    constexpr void swap( enhance::Vector3d<T>& lhs, enhance::Vector3d<T>& rhs ) noexcept(noexcept(lhs.swap(rhs)))
    {
        lhs.swap(rhs);
    }
} // namespace std