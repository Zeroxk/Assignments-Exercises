#include "Volume.h"

#include <algorithm>
#include <math.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>


// ********************************************************************************************************
// *** Basic methods **************************************************************************************
// Default constructor.
Volume::Volume() :
    m_width(0), m_height(0), m_depth(0), m_sliceSize(0), m_voxelNum(0),
    m_voxelData(NULL),m_mean(0.0)
{
}



/// Create a Volume loading data from the specified file
Volume::Volume(const std::string &strFilename) :
    m_width(0), m_height(0), m_depth(0), m_sliceSize(0), m_voxelNum(0),
    m_voxelData(NULL)
{
    loadVolumeDat(strFilename);
}

/// Copy constructor
Volume::Volume(const Volume& other) :
    m_width(other.m_width), m_height(other.m_height), m_depth(other.m_depth),
    m_sliceSize(other.m_sliceSize), m_voxelNum(other.m_voxelNum),
    m_voxelData(new float[other.m_voxelNum])
{
    memcpy(m_voxelData, other.m_voxelData, m_voxelNum * sizeof(float));
}

/// Assignment operator
Volume& Volume::operator=(const Volume& other) {
    Volume tmp(other);
    this->swap(tmp);
    return *this;
}

/// Swap
void Volume::swap(Volume& other) {
    std::swap(m_width, other.m_width);
    std::swap(m_height, other.m_height);
    std::swap(m_depth, other.m_depth);
    std::swap(m_sliceSize, other.m_sliceSize);
    std::swap(m_voxelNum, other.m_voxelNum);
    std::swap(m_voxelData, other.m_voxelData); // Swap pointers only!

    //TODO (CA1): if you add class members to this class, swap them here
}

/// Destructor
Volume::~Volume(void) {
    delete [] m_voxelData;
}



// ********************************************************************************************************
// *** Public methods *************************************************************************************

/* Return a reference to the value of the voxel at the specified position
 *  NOTE: you are not supposed to modify the original data! */
float& Volume::getVoxel(int x, int y, int z) {
    return m_voxelData[m_sliceSize * z + m_width * y + x];
}


// Return the value of the voxel at the specified position (const)
const float& Volume::getVoxel(int x, int y, int z) const {
    return m_voxelData[m_sliceSize * z + m_width * y + x];
}

void Volume::setMean(float mean) {
    m_mean = mean;
}


/* Load a dataset from the specified file.
 * Return true if the dataset has been loaded successfully. */
bool Volume::loadVolumeDat(const std::string & strFilename) {

    std::cout << "- Loading file \"" << strFilename << "\" ... " << std::endl;

    // Try to open the file
    std::fstream fileIn(strFilename.c_str(),
                        std::ifstream::in | std::ifstream::binary);
    if(!fileIn.good()) {
        std::cerr << "+ Error opening the file." << std::endl;
        return false;
    }

    // Read the header
    std::cout << "- Reading file's header ..." << std::endl;

    // Union to read values from the file
    //  Variables in a union share the same memory locations, similarly to a
    //  reference. However, their type can be different
    union {
        char cVals[2];
        unsigned short int iVal;
    } buffer2;

    // read the volume's dimensions
    fileIn.read(buffer2.cVals, 2);  // read as a pair of bytes
    m_width = buffer2.iVal;         // interpret as a short integer
    fileIn.read(buffer2.cVals, 2);
    m_height = buffer2.iVal;
    fileIn.read(buffer2.cVals, 2);
    m_depth = buffer2.iVal;

    // compute the size of a slice and of the whole volume
    m_sliceSize = m_width * m_height;
    m_voxelNum = m_sliceSize * m_depth;

    std::cout << "- Dataset dimensions: " << m_width << "x"
              << m_height << "x" << m_depth << std::endl;
    std::cout << "- slice_size: " << m_sliceSize
              << " voxNum: " << m_voxelNum << std::endl;


    // Allocate memory to store the dataset values
    if (m_voxelData) // If previous data is present, get rid of it
        delete [] m_voxelData;
    m_voxelData = new float[m_voxelNum];

    // Read the rest of the file
    std::cout << "- Reading voxel values ..." << std::endl;


    /* TODO (CA1): COMPLETE THIS LOADER BY READING THE DATA INTO m_voxelData
     * You can also use a different voxel type, e.g., unsigned short or
     * unsigned char. If you do so, remember to change the type of the
     * m_voxelData class variable.
     * If you keep float voxel data, the data should be rescaled to [0,1]
     */

    int cnt = 0;
    while(!fileIn.eof()) {
        fileIn.read(buffer2.cVals, 2);
        //std::cout << buffer2.iVal << std::endl;
        float val = static_cast<float>(buffer2.iVal);
        //std::cout << val << std::endl;
        m_voxelData[cnt++] = val/4095.0;
        //std::cout << m_voxelData[cnt-1] << std::endl;
    }
    // for each voxel
    //   check if the file is finished or not
    //   read the value from the file to the buffer2
    //   convert it to the appropriate data type
    //   scale it to [0, 1] by dividing it by 4095.0
    // store it in the array of voxel


    std::cout << "+ Done." << std::endl;
    fileIn.close();
    return true;
} /* loadVolumeDat() */
