//
// Created by m43 on 16. 03. 2020..
//

#ifndef FER_IRG_VECTOR_H
#define FER_IRG_VECTOR_H

#include <memory>
#include "vector.h"
#include "abstract_vector.h"

namespace linalg {

    class Vector : public AbstractVector {
    public:

        virtual ~Vector();

        /**
         * Create an instance of the class with given values
         *
         * @param values the values of the vector
         */
        explicit Vector(const vector<double> &values);


        /**
         * Create an instance of the class with given dimension and the values initialized to 0
         * @param dimensions the number of vector dimensions
         */
        explicit Vector(size_t dimensions);

        /**
         * Create an instance of the class with given values.
         *
         * @param readOnly is this vector read only
         * @param values the values of the vector
         */
        Vector(bool readOnly, const vector<double> &values);

        /**
         * Create an instance of the class with given values. Use the given pointer to share ownership of the values.
         * Don't change the vectors dimensions from outside.
         *
         * @param readOnly is this vector read only
         * @param values the values of the vector
         */
        Vector(bool readOnly, const shared_ptr<vector<double>> &values);

        double get(int index) override;

        Vector &set(int index, double value) override;

        int getDimension() override;

        // TODO is there any way I could rather return a unique_ptr to Vector rather than IVector?
        //      If I try doing so, i get the error:
        //          "error: invalid covariant return type for ‘virtual std::unique_ptr<linalg::Vector> linalg::Vector::clone()’"
        //      and:
        //          "note: overridden function is ‘virtual std::unique_ptr<linalg::IVector> linalg::IVector::clone()’"
        // TODO the reason I would like to return Vector is to be able to, for instance, call Vector implementation
        //      specific member functions (that could exist in an arbitrary class implementation, though there are none
        //      additional member functions in this implementation of Vector)
        std::unique_ptr<IVector> clone() override;

        unique_ptr<IVector> newInstance(int dimension) override;

        static unique_ptr<Vector> parseSimple(string str);


    private:

        /**
         * Smart pointer to std::vector that stores the elements of the vector.
         */
        shared_ptr<vector<double>> elements_;

        /**
         * The dimension of the vector
         */
        int dimension_;

        /**
         * Is the vector readonly
         */
        bool readOnly_ = false;
    };

}


#endif //FER_IRG_VECTOR_H
