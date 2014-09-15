#ifndef RAY_TRAVERSAL_H
#define RAY_TRAVERSAL_H

#include "Volume.h"

/// Handle traversal of a 3D Volume according to a certain strategy
class RayTraversal
{
public:
    /// Destructor
    virtual ~RayTraversal() {}

    /// Init the ray traversal
    virtual void init(const Volume& volume,
              float inX, float inY, float inZ,
              float rayX, float rayY, float rayZ,
              int stepsNum, float stepSize,
              float bgR, float bgG, float bgB) {
        mpVolume = &volume;
        mInX = inX; mInY = inY; mInZ = inZ;
        mRayX = rayX; mRayY = rayY; mRayZ = rayZ;
        mStepsNum = stepsNum; mStepSize = stepSize;
        mBgR = bgR; mBgG = bgG; mBgB = bgB;
    }

    /// Compute and returns the next position along the ray
    virtual void step(float &outX, float& outY, float& outZ) = 0;

    /// Return true if all the steps have been performed
    virtual bool end() const = 0;

    /** Accumulate the computed value
      * Intensity, Color and Transparency are specified in order to support different
      * compositing approaches. */
    virtual void accumulate(float intensity, float red, float green, float blue, float alpha) = 0;

    /// Return the computed color
    virtual void getColor(float &outR, float& outG, float& outB) = 0;

protected:
    const Volume* mpVolume;     ///< the volume which is being traversed
    float mInX, mInY, mInZ;     ///< entry point of the ray in the volume
    float mRayX, mRayY, mRayZ;  ///< the ray to trace
    int mStepsNum;              ///< the number of samples to extract
    float mStepSize;            ///< the distance between samples
    float mBgR, mBgG, mBgB;     ///< RGB color of the background
};


/// Specialization of RayTraversal for back-to-front dvr
class B2FDVR : public RayTraversal
{
    typedef RayTraversal super;
public:
    /// Init the ray traversal
    void init(const Volume& volume, float inX, float inY, float inZ,
              float rayX, float rayY, float rayZ,
              int stepsNum, float stepSize,
              float bgR, float bgG, float bgB) {
        super::init(volume, inX, inY, inZ, rayX, rayY, rayZ, stepsNum, stepSize, bgR, bgG, bgB);

        mStep = stepsNum - 1;           // Start from the farthest point in the volume
        mR = bgR; mG = bgG, mB = bgB;   // Accumulate starting from the background
    }

    /// Back-to-front traversal
    void step(float &outX, float& outY, float& outZ) {
        outX = super::mInX + super::mRayX * super::mStepSize * mStep;
        outY = super::mInY + super::mRayY * super::mStepSize * mStep;
        outZ = super::mInZ + super::mRayZ * super::mStepSize * mStep;
        --mStep;
    }

    /// Return true if all the steps have been performed
    bool end() const {
        return mStep < 0;
    }

    /// Accumulate the computed value (intensity is unused in DVR)
    void accumulate(float, float red, float green, float blue, float alpha) {
        mR = mR * (1.f - alpha) + red * alpha;
        mG = mG * (1.f - alpha) + green * alpha;
        mB = mB * (1.f - alpha) + blue * alpha;
    }

    /// Return the computed value
    virtual void getColor(float &outR, float& outG, float& outB) {
        outR = mR;
        outG = mG;
        outB = mB;
    }

private:
    int mStep;
    float mR, mG, mB;
}; /* B2FDVR */

/** Specialization of RayTraversal for MPI.
 * For MPI it does not really matter if it is B2F or F2B) */
class MPI : public RayTraversal
{
    typedef RayTraversal super;
public:
    /// Init the ray traversal
    void init(const Volume& volume, float inX, float inY, float inZ,
              float rayX, float rayY, float rayZ,
              int stepsNum, float stepSize,
              float bgR, float bgG, float bgB) {
        super::init(volume, inX, inY, inZ, rayX, rayY, rayZ, stepsNum, stepSize, bgR, bgG, bgB);

        mStep = stepsNum - 1;           // Start from the farthest point in the volume (use B2F)
        mR = bgR; mG = bgG, mB = bgB;   // Worst case, the color is from the background
        mMaxIntensity = -1.f;            // Maximum intensity encountered up to now
    }

    /// Back-to-front traversal
    void step(float &outX, float& outY, float& outZ) {
        outX = super::mInX + super::mRayX * super::mStepSize * mStep;
        outY = super::mInY + super::mRayY * super::mStepSize * mStep;
        outZ = super::mInZ + super::mRayZ * super::mStepSize * mStep;
        --mStep;
    }

    /// Return true if all the steps have been performed
    bool end() const {
        return mStep < 0;
    }

    /// If the specified intensity is higher than the current max, store its color value (alpha unused)
    void accumulate(float intensity, float red, float green, float blue, float) {
        if(intensity > mMaxIntensity) {
            mMaxIntensity = intensity;
            mR = red;
            mG = green;
            mB = blue;
        }
    }

    /// Return the computed value
    virtual void getColor(float &outR, float& outG, float& outB) {
        outR = mR;
        outG = mG;
        outB = mB;
    }

private:
    int mStep;
    float mR, mG, mB;
    float mMaxIntensity;
}; /* MIP */


/// Specialization of RayTraversal for Bounding Box Entry Point.
class BBEntry : public RayTraversal
{
    typedef RayTraversal super;
public:
    // parent init is sufficient

    /// No step to take, just return a valid position
    void step(float &outX, float& outY, float& outZ) {
        outX = super::mInX;
        outY = super::mInY;
        outZ = super::mInZ;
    }

    /// No step to take
    bool end() const {
        return true;
    }

    /// Nothing to do here
    void accumulate(float, float, float, float, float) {
    }

    /// Return the computed value
    virtual void getColor(float &outR, float& outG, float& outB) {
        outR = super::mInX / super::mpVolume->getWidth();
        outG = super::mInY / super::mpVolume->getHeight();
        outB = super::mInZ / super::mpVolume->getDepth();
    }
}; /* BBEntry */



#endif // RAY_TRAVERSAL_H
