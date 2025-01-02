#include "stdafx.h"
#include "powerup.h"

/*
CPowerUp::CPowerUp(unsigned short PowerUpType, int* pos, int* vel, char Flags, unsigned short Lifetime, unsigned short Node)
{
	throw;
}
*/

/*
CPowerUp::~CPowerUp()
{
	throw;
}
*/

void CPowerUp::SetGravity(int Gravity, int Friction)
{
	//cItem_gravity = Gravity;
	//cItem_friction = Friction;
}

void CPowerUp::DontDisplay()
{
	//cItem_flags |= 0x41;
	DeleteStuff();
}

/*
void CPowerUp::DeleteStuff()
{
	throw;
}
*/

void CPowerUp::Die()
{
	// why even check?
	if (!IsDead())
		mCBodyFlags |= CBODY_DEAD;
}

/*
void CPowerUp::AI()
{
	throw;
}
*/

void CPowerUp::SetNode(unsigned short nodeIndex)
{
	mHasNode = true;
	mNodeIndex = nodeIndex;
}

CPowerUp* PowerUp_Create(unsigned short PowerUpType, void* pos, char Flags, unsigned short Lifetime, unsigned short Node)
{
	return NULL;
	//return new CPowerUp(PowerUpType, pos, emptyvel, Flags, Lifetime, Node);
}