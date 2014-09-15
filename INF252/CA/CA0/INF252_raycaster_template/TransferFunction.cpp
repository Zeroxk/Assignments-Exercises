#include "TransferFunction.h"

#include <fstream>
#include <iostream>

// ****************************************************************************
// *** Basic methods **********************************************************
// Constructor
TransferFunction::TransferFunction() {
    reset();
} /* constructor */


// Destructor
TransferFunction::~TransferFunction() {
    // TODO (CA2): deallocate stuff here
} /* destructor */


// ****************************************************************************
// *** Public methods *********************************************************
// Reset the transfer function to the initial state
void TransferFunction::reset() {
    std::cout << "TransferFunction::reset()" << std::endl;

    // TODO (CA2): reset the transfer function to the initial state
    // (usually consisting of only 2 default samples for 0. and 1.)
}/* reset() */


// Add a sample to the current transfer function
bool TransferFunction::addSample(double sample,
                                 double r, double g, double b,
                                 double alpha)
{
    return addSample(sample, Vector3d(r,g,b), alpha);
} /* addSample() */


// Add a sample to the current transfer function
bool TransferFunction::addSample(double sample,
                                 const Vector3d& color,
                                 double alpha)
{
    assert(sample >= 0 && sample <= 1.);
    assert(color.x() >= 0. && color.x() <= 1.);
    assert(color.y() >= 0. && color.y() <= 1.);
    assert(color.z() >= 0. && color.z() <= 1.);
    assert(alpha >= 0. && alpha <= 1.);

    std::cout << "TransferFunction::addSample(" << sample
              << ", ...)" << std::endl;

    // TODO (CA2):
    // look through the saved samples
    // if there is a sample corresponding to the requested one (within a
    // reasonable threshold):
    //   return false;
    // otherwise:
    //   store the sample in the list
    //   emit tfChanged(); // Notify that the transfer function is changed
    //   return true;

    return false;
} /* addSample() */


// Remove a sample from the list
bool TransferFunction::removeSample(double sample) {
    assert(sample >= 0 && sample <= 1.);

    std::cout << "TransferFunction::removeSample("<< sample
              << ")" << std::endl;

    // TODO (CA2):
    // look through the saved samples
    // if there is a sample corresponding to the requested one (within a
    // reasonable threshold):
    //   remove it
    //   emit tfChanged(); // Notify that the transfer function is changed
    //   return true;
    // otherwise:
    //   return false;

    return false;
} /* removeSample() */


// Compute the color corresponding the the specified sample
void TransferFunction::getColor(double sample, Vector3d& outColor) {
    assert(sample >= 0 && sample <= 1.);

    std::cout << "TransferFunction::getColor("<< sample
              << ", ...)" << std::endl;

    // TODO (CA2):
    // look through the saved samples
    // if there is a sample corresponding to the requested one (within a
    // reasonable threshold):
    //   output the associated color
    // otherwise:
    //   find the 2 closest samples to the requested one
    //   output the bilinear interpolation between the 2 associated colors

    outColor.set(0., 0., 0.);
} /* getColor() */

// Compute the alpha value corresponding the the specified sample
double TransferFunction::getAlpha(double sample) {
    assert(sample >= 0 && sample <= 1.);

    std::cout << "TransferFunction::getAlpha("<< sample
              << ")" << std::endl;

    // TODO (CA2):
    // same as GetColor, but with the alpha values

    return 0;
}


// TODO (CA2) (Optional): implement the method/s to get the full list of samples


/// Store a transfer function on the specified file
bool TransferFunction::save(std::string filename) {
    std::cout << "TransferFunction::save("<< filename
              << ")" << std::endl;

    std::ofstream tfOut(filename.c_str());
    if(!tfOut.good()) {
        std::cerr << "Unable to save the transfer function to the"
                  << "specified file." << std::endl;
        tfOut.close();
        return false;
    }

    // TODO (CA2): (Optional)
    // save the transfer function to a file according to your own format

    tfOut.close();
    return true;
} /* save() */


// Load a transfer function from the specified file
bool TransferFunction::load(std::string filename) {
    std::cout << "TransferFunction::load("<< filename.c_str()
              << ")" << std::endl;

    std::ifstream tfIn(filename);
    if(!tfIn.good()) {
        std::cerr << "Unable to open the specified file." << std::endl;
        tfIn.close();
        return false;
    }

    // TODO (CA2) (Optional)
    // Read the content of the file accordng to the same format used
    // to save the transfer function

    // make sure that color and alpha for sample 0. and 1. are defined

    tfIn.close();
    emit tfChanged(); // Notify that the transfer function is changed
    return true;
} /* load() */
