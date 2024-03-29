#include <glm/gtc/constants.hpp>

#include "Engine/VecConsts.h"
#include "Engine/Collision/Collision2D.h"

#include "Assert.h"

using namespace Kyst::VecConsts;
using namespace Kyst::Collision2D;

void assertColllide()
{
    
    Rectangle aRect{{1, 1}, {4, 4}};
    Rectangle bRect{{2, 2}, {5, 5}};
    Rectangle cRect{{6, 4}, {4, 2}};
    assert(collide(aRect, bRect));
    assert(collide(bRect, cRect));
    assert(!collide(aRect, cRect));

    Circle aCircle{{4, 4}, 2};
    Circle bCircle{{7, 4}, 2};
    Circle cCircle{{10, 4}, 2};
    assert(collide(aCircle, bCircle));
    assert(collide(bCircle, cCircle));
    assert(!collide(aCircle, cCircle));

    vec2 aPt{3, 5};
    vec2 bPt{3, 2};
    vec2 cPt{8, 4};
    vec2 down{5, -1};
    vec2 up{5, 2};
    Line aLine{aPt, down};
    Line bLine{aPt, up};
    Line cLine{bPt, up};
    Line dLine{cPt, down};
    assert(collide(aLine, bLine));
    assert(collide(aLine, cLine));
    assert(!collide(bLine, cLine));
    assert(collide(aLine, dLine));

    vec2 dPt{3, 4};
    vec2 ePt{11, 1};
    vec2 fPt{8, 4};
    vec2 gPt{11, 7};
    Segment aSeg{dPt, ePt};
    Segment bSeg{fPt, gPt};
    Segment cSeg{dPt, fPt};
    Segment dSeg{ePt, gPt};
    Segment eSeg{aPt, ePt};
    assert(collide(aSeg, aSeg)); // congruent
    assert(collide(aSeg, cSeg)); // copunctual
    assert(!collide(aSeg, bSeg));
    assert(!collide(cSeg, dSeg));
    assert(collide(eSeg, cSeg));
    assert(collide(cSeg, eSeg)); // reverse order

    OrientedRectangle aORect = {{3, 5}, {1, 3}, pi<float>() / 12};
    OrientedRectangle bORect = {{10, 5}, {2, 2}, -pi<float>() / 12};
    assert(!collide(aORect, bORect));
    OrientedRectangle cORect = {{-6, 5}, {2, 1}, 0};
    OrientedRectangle dORect = {{-4, 2}, {3, 1}, 0}; // colinear
    assert(!collide(cORect, dORect));
    assert(!collide(aORect, cORect));
    dORect.SetRotation(-pi<float>()/4);
    assert(collide(cORect, dORect));
    assert(collide(dORect, cORect));
    OrientedRectangle eORect = {{5, 2}, {3, 1}, -pi<float>()/4};
    OrientedRectangle fORect = {{9, -1}, {3, 1}, -pi<float>()/4};
    assert(collide(eORect, fORect));
    assert(!collide(eORect, cORect));

    Circle dCircle{{6, 4}, 3};
    vec2 hPt{8, 3}; 
    vec2 iPt{11, 7};
    assert(dCircle.Contains(hPt));
    assert(!dCircle.Contains(iPt));

    Circle eCircle{{3, -2}, 2};
    Line eLine{ZERO_2D, ONE_2D};
    Line fLine{ZERO_2D, vec2(1,-1)};
    assert(!collide(eCircle, eLine));
    assert(collide(eCircle, fLine));

    Segment fSeg{{3,-2}, {-1,-1}};
    Segment gSeg{{3,1}, {3,5}};
    Segment hSeg{{4,4}, {2,2}};
    assert(!collide(dCircle, fSeg));
    assert(collide(dCircle, gSeg));
    assert(collide(dCircle, hSeg));

    Circle fCircle{{-3, 0}, 1};
    Circle gCircle{{-3, 0}, 2};
    Circle hCircle{{-3, 0}, 3};
    Circle iCircle{{0, 0}, 2};
    Rectangle dRect{{-5, 2}, {3, 2}};
    assert(!collide(fCircle, dRect));
    assert(collide(gCircle, dRect));
    assert(collide(hCircle, dRect));
    assert(!collide(iCircle, dRect));
}
