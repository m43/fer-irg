//
// Created by m43 on 16. 03. 2020..
//

#ifndef FIRST_VECTOR_H
#define FIRST_VECTOR_H

#include <memory>

namespace linalg {

    class Vector : public AbstractVector {
    public:

        virtual ~Vector();

        /**
         * Create an instance of the class with given values
         *
         * @param values the values of the vector
         */
        explicit Vector(const vector<double>& values);


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
        Vector(bool readOnly, const vector<double>& values);

        /**
         * Create an instance of the class with given values. Use the given pointer to share ownership of the values.
         * Don't change the vectors dimensions from outside.
         *
         * @param readOnly is this vector read only
         * @param values the values of the vector
         */
        Vector(bool readOnly, const shared_ptr<vector<double>>& values);

        double get(int index) override;

        Vector &set(int index, double value) override;

        int getDimension() override;

        // TODO for Java, the professors have written in the diagram that clone, newinstance and set should return
        //      IVector, not Vector, hwy is that so?
        std::unique_ptr<IVector> clone() override;

        unique_ptr<IVector> newInstance(int) override;

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


#endif //FIRST_VECTOR_H