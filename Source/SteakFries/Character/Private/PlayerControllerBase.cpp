// All rights reserved


#include "PlayerControllerBase.h"

bool APlayerControllerBase::SetState(EPlayerControllerState NewState)
{
    if (State == NewState)
    {
      return false;
    }

    State = NewState;

    if (OnStateChangeDelegate.IsBound())
    {
      OnStateChangeDelegate.Broadcast(State);
    }

    return true;
}
