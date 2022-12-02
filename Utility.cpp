#include "Utility.h"
#include "Vector.h"
#include "Box.h"
#include "GameManager.h"

#include <time.h>
#include <iostream>

bool battleCity::positionsIntersect(Vector p1, Vector p2)
{
    if (abs(p1.X - p2.X) <= 1 &&
        abs(p1.Y - p2.Y) <= 1)
    {
        return true;
    }
    else
        return false;
}

bool battleCity::boxesIntersect(Box A, Box B)
{
    bool xOverlap;
    bool yOverlap;
    Vector vecA = A.getCorner();
    Vector vecB = B.getCorner();
    float Ax1 = vecA.X, Ax2 = vecA.X + A.getHorizontal();
    float Ay1 = vecA.Y, Ay2 = vecA.Y + A.getVertical();

    float Bx1 = vecB.X, Bx2 = vecB.X + B.getHorizontal();
    float By1 = vecB.Y, By2 = vecB.Y + B.getVertical();

    //if (GM.stepCount % 1000 == 0)
    //{
    //    std::cout << "xOverlap: " << std::endl;
    //    std::cout << Bx1 << " <= " << Ax1 << " && " << Ax1 << " <= " << Bx2 << std::endl;
    //    std::cout << Ax1 << " <= " << Bx1 << " && " << Bx1 << " <= " << Ax2 << std::endl << std:: endl;

    //    std::cout << "yOverlap: " << std::endl;
    //    std::cout << By1 << " <= " << Ay1 << " && " << Ay1 << " <= " << By2 << std::endl;
    //    std::cout << Ay1 << " <= " << By1 << " && " << By1 << " <= " << Ay2 << std::endl;
    //    std::cout << "Ay1: " << Ay1 << " Ay2: " << Ay2 << std::endl << std::endl;

    //    std::cout << "Bx1: " << Bx1 << " Bx2: " << Bx2 << std::endl;
    //    std::cout << "By1: " << By1 << " By2: " << By2 << std::endl;
    //    std::cout << "--------------------------------" << std::endl;
    //}

    xOverlap = (Bx1 <= Ax1 && Ax1 <= Bx2) ||
               (Ax1 <= Bx1 && Bx1 <= Ax2);

    yOverlap = (By1 <= Ay1 && Ay1 <= By2) ||
               (Ay1 <= By1 && By1 <= Ay2);

    if (xOverlap && yOverlap)
        return true;
    else
        return false;
}

battleCity::Box battleCity::getWorldBox(const Object& ptrObject)
{
    Box tempBox = getWorldBox(ptrObject, ptrObject.getPosition());
    return tempBox;
}

battleCity::Box battleCity::getWorldBox(const Object& ptrObject, Vector where)
{
    Box tempBox = ptrObject.getBox();
    Vector corner = tempBox.getCorner();
    corner.X = corner.X + where.X;
    corner.Y = corner.Y + where.Y;
    tempBox.setCorner(corner);
    return tempBox;
}

int battleCity::randomNumber(int start, int end)
{
    return rand() % (end - start + 1) + start;
}