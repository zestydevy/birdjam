#include "animator.hpp"

TAnimator::TAnimator(int meshCount, Vtx* meshes[], int sizes[]){
    mMeshCount = meshCount;
    mMeshSizes = new int[mMeshCount];
    mMeshes = new Vtx*[mMeshCount];
    mAnim = new Vtx**[mMeshCount];
    for (int i = 0; i < mMeshCount; i++){
        mMeshes[i] = meshes[i];
        mMeshSizes[i] = sizes[i];
    }

    mLength = 0;
    mTimescale = 0.25f;
    mTime = 0.0f;
}
TAnimator::~TAnimator(){
    delete[] mMeshSizes;
    delete[] mMeshes;
    delete[] mAnim;
}

void TAnimator::update(){
    mTime += mTimescale;
    if (mTime >= mLength)
        mTime -= mLength;
    if (mTime < 0)
        mTime += mLength;

    for (int i = 0; i < mMeshCount; i++)
        lerpVertexPos(mMeshSizes[i], mMeshes[i], mAnim[i], mTime);
}

void TAnimator::setTimescale(float dt){
    mTimescale = dt;
}

void TAnimator::setAnimation(int length, Vtx** animation[]){
    mLength = length;
    for (int i = 0; i < mMeshCount; i++)
        mAnim[i] = animation[i];
}

void TAnimator::setVertexPos(int size, Vtx vtx[], Vtx* anim[], int frame){
    for (int i = 0; i < size; i++){
        vtx[i] = anim[frame % mLength][i];
    }
}

void TAnimator::lerpVertexPos(int size, Vtx vtx[], Vtx* anim[], float frame){
    int f = (int)frame;
    float irem = frame - f;
    float rem = 1.0f - irem;

    int nframe = (f + 1) % mLength;

    for (int i = 0; i < size; i++){
        vtx[i].n.ob[0] = (short)(((float)anim[nframe][i].n.ob[0] * irem) + ((float)anim[f][i].n.ob[0] * rem));
        vtx[i].n.ob[1] = (short)(((float)anim[nframe][i].n.ob[1] * irem)+ ((float)anim[f][i].n.ob[1] * rem));
        vtx[i].n.ob[2] = (short)(((float)anim[nframe][i].n.ob[2] * irem) + ((float)anim[f][i].n.ob[2] * rem));
        vtx[i].n.n[0] = (short)(((float)anim[nframe][i].n.n[0] * irem) + ((float)anim[f][i].n.n[0] * rem));
        vtx[i].n.n[1] = (short)(((float)anim[nframe][i].n.n[1] * irem) + ((float)anim[f][i].n.n[1] * rem));
        vtx[i].n.n[2] = (short)(((float)anim[nframe][i].n.n[2] * irem) + ((float)anim[f][i].n.n[2] * rem));
    }
}