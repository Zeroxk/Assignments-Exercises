#ifndef VOLUME_H
#define VOLUME_H

#include <string>

/**
 * Simple linear volume class which supports loading from DAT files.
 * Voxel values are rescaled in [0,1] range.
 * There is no need for double precision floating point since the values in the
 *  datasets (for these assignemnts) are in the range [0, 4096].
 */
class Volume {

    // ********************************************************************************************************
    // *** Basic methods **************************************************************************************
public:
    /// Default constructor.
    Volume();

    /// Create a Volume loading data from the specified file
    Volume(const std::string &strFilename);

    /// Copy constructor
    Volume(const Volume& other);

    /// Assignment operator
    Volume& operator=(const Volume& other);

    /// Swap
    void swap(Volume& other);

    /// Destructor
    ~Volume(void);

    // ********************************************************************************************************
    // *** Public methods *************************************************************************************
public:
    /// Return Volume's width.
    inline int getWidth() const { return m_width; }

    /// Return Volume's height.
    inline int getHeight() const { return m_height; }

    /// Return volume's depth.
    inline int getDepth() const { return m_depth; }

    /// Return the total number of voxels.
    inline int getVoxelNum() const { return m_voxelNum; }

    /** Return a pointer to the voxel values
     *  NOTE: you are not supposed to modify the original data! */
    inline float *getData() { return m_voxelData; }

    /// Return a (const) pointer to the voxel values
    inline const float *getData() const { return m_voxelData; }

    /** Return a reference to the value of the voxel at the specified position
     *  NOTE: you are not supposed to modify the original data! */
    float& getVoxel(int x, int y, int z);

    /// Return the value of the voxel at the specified position (const)
    const float& getVoxel(int x, int y, int z) const;

    /** Load a dataset from the specified file.
     *  Return true if the dataset has been loaded successfully. */
    bool loadVolumeDat(const std::string & strFilename);


    // ************************************************************************
    // *** Class members ******************************************************
private:
    int m_width;     ///< width of the volume, in voxels
    int m_height;    ///< width of the volume, in voxels
    int m_depth;     ///< width of the volume, in voxels

    int m_sliceSize;   ///< number of voxels in a width-height slice
    int m_voxelNum;    ///< number of voxels in the volume

    float *m_voxelData;  ///< linear array with the volume's intensity values
}; /* Volume */

#endif /* VOLUME_H */
