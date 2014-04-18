#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <cmath>

class PolarPoint;

class Point {
  public:
    Point(const float& x, const float& y);
    Point(const Point& other);
    Point(const PolarPoint& other);
    const Point& operator=(const Point& other);
    Point operator+(const Point& other);
    const Point& operator+=(const Point& other);
    float x() const;
    float y() const;
    friend std::ostream&
      operator<<(std::ostream& os, const Point& p);
  private:
    float x_;
    float y_;
};

class PolarPoint {
  public:
    PolarPoint(const Point& p);
    Point ConvertToPoint() const;
    PolarPoint AddAngle(const float& phi);
    float r() const;
    float theta() const;
  private:
    float r_;
    float theta_;
};

inline Point::Point(const float& x, const float& y) :
  x_(x), y_(y) { };

inline Point::Point(const Point& other) {
  x_ = other.x();
  y_ = other.y();
}

inline Point::Point(const PolarPoint& other) {
  x_ = other.r()*cos(other.theta());
  y_ = other.r()*sin(other.theta());
}

inline const Point& Point::operator=(const Point& other) {
  x_ = other.x();
  y_ = other.y();
  return *this;
}

inline Point Point::operator+(const Point& other) {
  return Point(x_+other.x(), y_+other.y());
}

inline const Point& Point::operator+=(const Point& other) {
  x_ += other.x();
  y_ += other.y();
  return *this;
}

inline float Point::x() const {
  return x_;
}

inline float Point::y() const {
  return y_;
}

inline std::ostream& operator<<(std::ostream& os, const Point& p) {
  os << "(" << p.x_ << ", " << p.y_ << ")";
  return os;
}


inline PolarPoint::PolarPoint(const Point& p){
  r_ = sqrt(pow(p.x(), 2) + pow(p.y(), 2));
  theta_ = atan(p.y() / p.x());
}

inline Point PolarPoint::ConvertToPoint() const {
  return Point(*this);
}

inline PolarPoint PolarPoint::AddAngle(const float& phi) {
  theta_ += phi;
  return *this;
}

inline float PolarPoint::r() const {
  return r_;
}

inline float PolarPoint::theta() const {
  return theta_;
}

#endif  /* POINT_H */
