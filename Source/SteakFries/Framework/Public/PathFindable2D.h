// All rights reserved

#pragma once

class IPathFindable2D
{
public:

  virtual UE::Math::TIntPoint<int32> GetPoint() const = 0;
  virtual bool IsBlocked() const = 0;

  virtual int32 GetX() const { return GetPoint().X; }
  virtual int32 GetY() const { return GetPoint().Y; }

};