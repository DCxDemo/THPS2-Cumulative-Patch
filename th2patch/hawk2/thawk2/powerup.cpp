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

/*


// make enum
#define	POWERUP_LETTER_S	0x05
#define	POWERUP_LETTER_K	0x04
#define	POWERUP_LETTER_A	0x06
#define	POWERUP_LETTER_T	0x0F
#define	POWERUP_LETTER_E	0x0A
#define	POWERUP_HIDDEN_TAPE	0x10
#define	POWERUP_BUCKS_250	0x18
#define	POWERUP_BUCKS_50	0x19
#define	POWERUP_BUCKS_100	0x1a
#define	POWERUP_LEVELSPEC	0x21

void __thiscall CPowerUp::TakeEffect(CBruce *pSkater)
{
	// check taken flag?
	if (_GNumberOfPlayers == 1) {
		flags = (byte)(this->mFlags & 1);
	}
	else {
		flags = (byte)(this->.mFlags;

		if (pSkater == _MechList) {
			flags = flags & 0x40;
		}
		else {
			flags = flags & 1;
		}
	}

	//leave if anything is set
	if (flags > 0) return;

	// main switch with all supported powerup types
	switch (this->mPowerupType) {

		case POWERUP_LETTER_S:
		case POWERUP_LETTER_K:
		case POWERUP_LETTER_A:
		case POWERUP_LETTER_T:
		case POWERUP_LETTER_E:
		case POWERUP_HIDDEN_TAPE:
		// case 0xe: // Apocalypse SmallHealth leftover

			Mess_DeleteAll();

			switch (this->mPowerupType) {

				case POWERUP_LETTER_S:
					if (Panel_Letter(0)) {
						Mess_Message("S", &letterProg, 1, 0, 0);
						SFX_PlayX(0x14, 0x2000,0);
					}
					break;

				case POWERUP_LETTER_K:
					if (Panel_Letter(1)) {
						Mess_Message("K", &letterProg, 1, 0, 0);
						SFX_PlayX(0x14, 0x2000,0);
					}
					break;

				case POWERUP_LETTER_A:
					if (Panel_Letter(2)) {
						Mess_Message("A", &letterProg, 1, 0, 0);
						SFX_PlayX(0x14, 0x2000,0);
					}
					break;

				case POWERUP_LETTER_T:
					if (Panel_Letter(3)) {
						Mess_Message("T", &letterProg, 1, 0, 0);
						SFX_PlayX(0x14, 0x2000,0);
					}
					break;

				case POWERUP_LETTER_E:
					if (Panel_Letter(4)) {
						Mess_Message("E", &letterProg, 1, 0, 0);
						SFX_PlayX(0x14, 0x2000,0);
					}
					break;

				case POWERUP_HIDDEN_TAPE:
					Career_GiveGoalType(EGoalType::Hidden);
					break;

			}

			break;

		// if allowed thps2 powerup, process
		case POWERUP_BUCKS_250: // 250 bucks
		case POWERUP_BUCKS_50: // 50 bucks
		case POWERUP_BUCKS_100: // 100 bucks
		case POWERUP_LEVELSPEC: // level pickup

			if (pSkater->mInBail != 0) break;

			killPowerup = true;
			if (pSkater->mPhysicsState == PHYSICS_ON_GROUND) {
				CBruce__Trick_TakeOff(pSkater);
			}

			switch (this->mPowerupType) {
				case POWERUP_BUCKS_250: // bucks
					Mess_Message("250 bucks", Messprog_Goal, 1, 0, 0);
					SFX_SetVoicePitch(18, 900);
					SFX_PlayX(18, 0x2000, 0);
					Career_GiveMoney(this->mNode, 250);
					break;

				case POWERUP_BUCKS_50: // bucks
					Mess_Message("50 bucks", Messprog_Goal, 1, 0, 0);
					SFX_SetVoicePitch(18,0x45a);
					SFX_PlayX(18, 0x2000, 0);
					Career_GiveMoney(this->_mNode, 50);
					break;

				case POWERUP_BUCKS_100: // bucks
					Mess_Message("100 bucks!", Messprog_Goal, 1, 0, 0);
					SFX_SetVoicePitch(18,0x5dc);
					SFX_PlayX(18, 0x2000, 0);
					Career_GiveMoney(this->mNode, 100);
					break;

				case POWERUP_LEVELSPEC: // level specific
					Career_GetLevelPickup();
					SFX_SetVoicePitch(316,0x45a);
					SFX_PlayX(316, 0x2000, 0);
					break;
			}

			if (pSkater->mPhysicsState == PHYSICS_ON_GROUND) {
				*(undefined4 *)&pSkater->field_0x306c = 0;
				*(undefined4 *)&pSkater->field_0x3068 = 0;
				CBruce::Trick_Land(pSkater);
			}

			break;

		default:
			printf_s("Unknown powerup type %i", this->mPowerupType);
			break;
	}

	// send pulse to linked node, if got one
	if (this->mHasNode) Trig_SendPulse(Trig_GetLinksPointer(this->mNodeIndex);

	 // original game checks for a "kill" bool, but why would we leave an unknown powerup anyways? it leaves th1 bonuses hanging there
	this->Die();
}

*/