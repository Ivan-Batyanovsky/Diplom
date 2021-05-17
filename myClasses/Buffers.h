//
// Created by ivanb on 3/6/2021.
//

// TO DO: unit tests.

#ifndef DIPLOM_BUFFERS_H
#define DIPLOM_BUFFERS_H

#include <iostream>
#include <vector>

namespace Buffers
{
    typedef struct {
        unsigned char x_, y_, z_, w_;
    } uchar4;

    // Uchar4 element buffer
    class ColourBuffer {
    private:
        std::vector<std::vector<uchar4> > data_;
        uint32_t rows_, columns_;
    public:
        // Constructors
        ColourBuffer();
        ColourBuffer(const uint32_t rows, const uint32_t columns);

        // Copy operator
        ColourBuffer(const ColourBuffer & buffer);

        // Assignment operator
        ColourBuffer & operator=(const ColourBuffer & buffer);

        // Class methods
        void resize(const uint32_t rows, const uint32_t columns);
        void clear(const uchar4 colour = {1,255,1,1});
        uint32_t getColumns() {return columns_;}
        uint32_t getRows() {return rows_;}
        void set(const int row, const int column, const uchar4 & pixel) { data_[row][column] = pixel; };
        uchar4 get(const int row, const int column) const { return data_[row][column]; };

        // Overloaded operators

        // Friends
        friend std::ostream & operator<<(std::ostream & os, const ColourBuffer & buffer);

        // Destructor
        ~ColourBuffer();
    };

    // Float element buffer
    class fDepthBuffer
    {
    private:
        std::vector<std::vector<float> >  data_;
        uint32_t rows_, columns_;
    public:
        // Constructors
        fDepthBuffer();
        fDepthBuffer(const uint32_t rows, const uint32_t columns);

        // Copy operator
        fDepthBuffer(const fDepthBuffer & buffer);

        // Assignment operator
        fDepthBuffer & operator=(const fDepthBuffer & buffer);

        // Class methods
        void resize(const uint32_t rows, const uint32_t columns, const float depth = -1.0f);
        void clear(const float depth = -1.0f);
        void set(const uint32_t row, const uint32_t column, const float & depth) { data_[row][column] = depth; };
        float get(const uint32_t row, const uint32_t column) const { return data_[row][column]; };

        // Overloaded operators

        // Friends
        friend std::ostream & operator<<(std::ostream & os, const fDepthBuffer & buffer);

        // Destructor
        ~fDepthBuffer();
    };
}

#endif //DIPLOM_BUFFERS_H
