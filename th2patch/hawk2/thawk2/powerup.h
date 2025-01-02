#pragma once

//CItem->CIcon3d only for arrow?
// 
//CItem->CBody->CCamera sizeof = 0x674
//CItem->CBody->CPowerUp sizeof = 0x100
//CItem->CBody->CSuper sizeof = 0x168
//CItem->CBody->CBackground sizeof = 0xcc

#define CBODY_SUSPENDED (1 << 0)
#define CBODY_HASSHADOW (1 << 3) // 0008
#define CBODY_DEAD (1 << 6)   // 0040

/*
CBODY_HITBYSMARTBOMB(1 << 8)
CBODY_TIMETODIE(1<<7)
CBODY_ZOMBIE(1<<6)
CBODY_PROTECTED(1 << 5))
CBODY_TARGETTABLE(1 << 4)
CBODY_HASSHADOW(1<<3))
CBODY_CANBESEEDED(1<<2)
CBODY_RADIALSUSPENSION(1<<1)
CBODY_SUSPENDED(1 << 0)
*/

/* inherited from Cbody:
 * CBackground
 * CCamera
 * CPowerup
 */

class CBody {
public:
    CBody** mppOriginalList;
    unsigned short mCBodyFlags;

    virtual void DeleteStuff() = 0;
    virtual void Die() = 0;
    virtual void AI() = 0;

    void ShadowOn()
    {
        mCBodyFlags |= CBODY_HASSHADOW;
    }

    bool IsDead()
    {
        return (mCBodyFlags & CBODY_DEAD) > 0;
    }


    void Suspend(CBody** list)
    {
        // check if maybe flag is set already
        if (mCBodyFlags & 0xffffff01)
            printf("Suspended flag illegally set.");

        // null check the list we're going to remove it from
        if (list == NULL)
            printf("woops (list is null in CBody::Suspend)");

        // delete stuff?
        //DeleteStuff();

        // remember the list
        mppOriginalList = list;

        // remove from list
        //DeleteFrom(this, list);
         
        // attach to global list of suspended items
        //AttachTo(this, SuspendedList);

        // set suspended flag
        mCBodyFlags |= CBODY_SUSPENDED;
    }


    void UnSuspend()
    {
        if ((mCBodyFlags & CBODY_SUSPENDED) > 0) {
            //DeleteFrom(&SuspendedList);
            //AttachTo(pBody->mppOriginalList);

            mCBodyFlags &= ~CBODY_SUSPENDED;
        }
    }
};

/*
interface CItem? CBody?
    delete
    DeleteStuff()
    Die()
    AI()
    EveryFrame()
    DoLightingSetup()
    Hit()
*/

/*
DEFAULT_ROTSPEED 100
PFLAG_DROPFOREVER 1<<4
PFLAG_HOPUP 1<<3
PFLAG_DROPONCREATION 1<<2
PFLAG_EFFECTONCREATION 1<<1
PFLAG_PLAYSOUNDONCREATION 1<<0
 */

class CPowerUp : CBody
{
public:
    void* mpGlow;
    unsigned short mGlowRadiusOrg;
    unsigned short mGlowRadiusAmp;
    bool mHasNode;
    bool mIs3d;
    bool mDropping;
    bool mDropForever;
    short mHoverHeight;
    unsigned short mNodeIndex;
    int mGroundY;
    // svector3
    int mOrgPosX;
    int mOrgPosY;
    int mOrgPosZ;
    unsigned short mT;
    short mMaxWobbleAmplitude;
    short mWobbleAmplitude;
    short mWobbleSpeed;
    short mLifetime;
        // unknown 6 bytes
        // unknown int
    int mTimer;

    void CheckAge();
    CPowerUp();
    //void CPowerUp()
    void WhoAmI();
    void SetNode(unsigned short nodeIndex);
    void TakeEffect();
    void SetGravity(int, int);
    void DontDisplay();
    void CreateBit();
    void DeleteStuff() override;
    void DoPhysics();
    void Die() override;
    void AI() override;
};

//0x00568490
extern CBody** PowerUpList;

//CPowerUp* PowerUp_Create(unsigned short PowerUpType, int* pos, char Flags, unsigned short Lifetime, unsigned short Node);