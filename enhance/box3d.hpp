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
#include "vector3d.hpp"
#include <cmath>
#include <array>
#include <algorithm>
#include <numeric>



namespace enhance 
{
    template<typename T = float>
    struct  Box3d
        : public __internal::ArithmeticEnabler<T>
    {
        enum class Corner
        {
            FrontBottomLeft,
            FrontBottomRight,
            FrontTopLeft,
            FrontTopRight,
            BackBottomLeft,
            BackBottomRight,
            BackTopLeft,
            BackTopRight,
            Center
        }

        enum class Face
        {
            Front,
            Back,
            Left,
            Right,
            Top,
            Bottom
        }

        Box3d();
        Box3d(const Vector3d<T>&, const Vector3d<T>&);

        Box3d(const Box3d<T>& other) = default;
        Box3d(Box3d<T>&& other) = default;

        template<Corner C>
        get(C c);
        
        constexpr void swap( Box3d<T>& other ) noexcept(std::is_nothrow_swappable_v<T>);

    protected:
        std::vector<Vector3d<T>> corners;
    };

    

    template<typename T>
    Box3d<T>::Box3d()
    {
        corners.emplace_back(Vector3d(0,0,0));
        corners.emplace_back(Vector3d(1,0,0));
        corners.emplace_back(Vector3d(0,1,0));
        corners.emplace_back(Vector3d(0,0,1));
        corners.emplace_back(Vector3d(1,1,0));
        corners.emplace_back(Vector3d(1,0,1));
        corners.emplace_back(Vector3d(0,1,1));
        corners.emplace_back(Vector3d(1,1,1));
    }



    template<typename T>
    Box3d<T>::Box3d(const Vector3d<T>& bottomLeft, const Vector3d<T>& upperRight)
    {
        corners.emplace_back(bottomLeft);
        corners.emplace_back(upperRight(0), bottomLeft(1), bottomLeft(2));
        corners.emplace_back(bottomLeft(0), upperRight(1), bottomLeft(2));
        corners.emplace_back(bottomLeft(0), bottomLeft(1), upperRight(2));
        corners.emplace_back(upperRight(0), upperRight(1), bottomLeft(2));
        corners.emplace_back(upperRight(0), upperRight(1), bottomLeft(2));
        corners.emplace_back(bottomLeft(0), upperRight(1), upperRight(2));
        corners.emplace_back(upperRight);
    }



    template<typename T>
    constexpr void Box3d<T>::swap( Box3d<T>& other ) noexcept(std::is_nothrow_swappable_v<T>)
    {
        corners.swap(other.corners);
    }
} // namespace enhance 



namespace std
{
    template<class T>
    constexpr void swap( enhance::Box3d<T>& lhs, enhance::Box3d<T>& rhs ) noexcept(noexcept(lhs.swap(rhs)))
    {
        lhs.swap(rhs);
    }
} // namespace std