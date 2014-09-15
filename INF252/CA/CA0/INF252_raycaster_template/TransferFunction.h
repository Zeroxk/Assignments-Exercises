#ifndef TRANSFER_FUNCTION_H
#define TRANSFER_FUNCTION_H

#include <QObject>
#include "Vector3.h"


class TransferFunction : public QObject {
    Q_OBJECT

    // ************************************************************************
    // *** Basic methods ******************************************************
public:
    /// Constructor
    TransferFunction();

    /// Destructor
    ~TransferFunction();


    // ************************************************************************
    // *** Signals ************************************************************
signals:
    /// Emitted when the transfer function change
    void tfChanged();

    // ************************************************************************
    // *** Public methods *****************************************************
public:
    /// Reset the transfer function to the initial state
    void reset();

    /// Add a sample to the current transfer function
    bool addSample(double sample, double r, double g, double b, double alpha = 1.);

    /// Add a sample to the current transfer function
    bool addSample(double sample, const Vector3d& color, double alpha = 1.);

    /// Remove a sample from the list
    bool removeSample(double sample);

    /// Compute the color corresponding the the specified sample
    void getColor(double sample, Vector3d& outColor);

    /// Compute the alpha value corresponding the the specified sample
    double getAlpha(double sample);


    // TODO (Optional)
    // to display the transfer function in the glWidget, it can be
    // useful to have a method/s to get the full list of samples


    /// Store a transfer function on the specified file
    bool save(std::string filename);

    /// Load a trasnfer function from the specified file
    bool load(std::string filename);


    // ************************************************************************
    // *** Class members ******************************************************
private:

    // TODO (CA2): to store the samples you can use arrays/pointers
    // Alternatively, you can find the std::list and std::vector classes useful
    // Check them at http://www.cplusplus.com/


}; /* TransferFunction */

#endif // TRANSFER_FUNCTION_H
