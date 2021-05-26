//
// Created by ivanb on 3/6/2021.
//

#include "Buffers.h"
#include <cstring>

Buffers::ColourBuffer::ColourBuffer() {
    data_ = std::vector< std::vector<uchar4> > (0, std::vector<uchar4>(0)); // Bad practice?
    rows_ = 0;
    columns_ = 0;
}

Buffers::ColourBuffer::ColourBuffer(const size_t rows, const size_t columns) {
    rows_ = rows;
    columns_ = columns;
    data_ = std::vector< std::vector<uchar4> > (rows, std::vector<uchar4> (columns));
}

Buffers::ColourBuffer::ColourBuffer(const Buffers::ColourBuffer & buffer) {
    rows_ = buffer.rows_;
    columns_ = buffer.columns_;

    data_ = std::vector< std::vector<uchar4> > (buffer.rows_, std::vector<uchar4> (buffer.columns_));
    for (size_t i = 0; i < rows_; ++i) {
        for (size_t j = 0; j < columns_; ++j) {
            data_[i][j] = buffer.data_[i][j];
        }
    }
}

Buffers::ColourBuffer & Buffers::ColourBuffer::operator=(const Buffers::ColourBuffer & buffer) {
    if (this == &buffer)
        return *this;

    rows_ = buffer.rows_;
    columns_ = buffer.columns_;

    data_ = std::vector< std::vector<uchar4> > (buffer.rows_, std::vector<uchar4> (buffer.columns_));
    for (size_t i = 0; i < rows_; ++i) {
        for (size_t j = 0; j < columns_; ++j) {
            data_[i][j] = buffer.data_[i][j];
        }
    }

    return *this;
}

void Buffers::ColourBuffer::resize(const size_t width, const size_t height) {
    columns_ = width;
    rows_ = height;
    data_ = std::vector< std::vector<uchar4> > (height, std::vector<uchar4> (width));
}

void Buffers::ColourBuffer::clear(const uchar4 colour) { // Bad practice?
    for (size_t i = 0; i < rows_; ++i) {
        for (size_t j = 0; j < columns_; ++j) {
            data_[i][j] = colour;
        }
    }
}

Buffers::ColourBuffer::~ColourBuffer()
{
}

// Friends
std::ostream & Buffers::operator<<(std::ostream & os, const Buffers::ColourBuffer & buffer) {
    Buffers::uchar4 temp;
    int rows = buffer.rows_, columns = buffer.columns_;
    os << "----------------ColourBuffer----------------" << std::endl;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            temp = buffer.data_[i][j];
            os << "("<< temp.x_ << ", " << temp.y_ << ", " << temp.z_ << ", " << temp.w_ << "), ";
        }
        os << std::endl;
    }
    os << "----------------ColourBufferEnd----------------" << std::endl;
    return os;
}

// Constructors
Buffers::fDepthBuffer::fDepthBuffer() {
    data_ = std::vector<std::vector<float> > (0, std::vector<float> (0));
    rows_ = 0;
    columns_ = 0;
}

Buffers::fDepthBuffer::fDepthBuffer(const size_t width, const size_t height) {
    rows_ = height;
    columns_ = width;
    data_ = std::vector<std::vector<float> > (height, std::vector<float> (width));
}

// Copy operator
Buffers::fDepthBuffer::fDepthBuffer(const Buffers::fDepthBuffer & buffer) {
    columns_ = buffer.columns_;
    rows_ = buffer.columns_;

    data_ = std::vector< std::vector<float> > (buffer.rows_, std::vector<float> (buffer.columns_));
    for (size_t i = 0; i < rows_; ++i) {
        for (size_t j = 0; j < columns_; ++j) {
            data_[i][j] = buffer.data_[i][j];
        }
    }
}

// Assignment operator
Buffers::fDepthBuffer & Buffers::fDepthBuffer::operator=(const Buffers::fDepthBuffer & buffer) {
    if (this == &buffer)
        return *this;

    rows_ = buffer.rows_;
    columns_ = buffer.columns_;

    data_ = std::vector< std::vector<float> > (buffer.rows_, std::vector<float> (buffer.columns_));
    for (size_t i = 0; i < rows_; ++i) {
        for (size_t j = 0; j < columns_; ++j) {
            data_[i][j] = buffer.data_[i][j];
        }
    }

    return *this;
}

// Class methods
void Buffers::fDepthBuffer::resize(const size_t width, const size_t height) {
    rows_ = height;
    columns_ = width;

    data_ = std::vector< std::vector<float> > (height, std::vector<float> (width));
}

void Buffers::fDepthBuffer::clear(const float depth) {
    data_ = std::vector< std::vector<float> > (rows_, std::vector<float> (columns_ , depth)); // Bad practice?
}

Buffers::fDepthBuffer::~fDepthBuffer() {
}

// Friends
std::ostream & Buffers::operator<<(std::ostream & os, const Buffers::fDepthBuffer &buffer) {
    int rows = buffer.rows_, columns = buffer.columns_;
    float temp;
    os << "----------------fDepthBuffer----------------" << std::endl;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            temp = buffer.data_[i][j];
            os << temp << ", ";
        }
        os << std::endl;
    }
    os << "----------------fDepthBufferEnd----------------" << std::endl;
    return os;
}

