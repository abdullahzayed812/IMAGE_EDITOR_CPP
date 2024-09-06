#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>

class Point {
 private:
  double x;
  double y;
  mutable std::string stringPoint;

  void updateStringPoint() const {
    std::ostringstream oss;
    oss << "( " << x << ", " << y << " )";
    this->stringPoint = oss.str();
  }

 public:
  Point(double x, double y) : x(x), y(y) {}

  const double& getX() const { return this->x; }

  void setX(const double& x) { this->x = x; }

  const double& getY() const { return this->y; }

  void setY(const double& y) { this->y = y; }

  const std::string& toString() const { return this->stringPoint; }
};

class Shape {
 protected:
  int color;

 public:
  Shape(int color) : color(color) {}

  virtual int computeArea() const {
    throw std::logic_error("Not implemented, do override.");
    return -1;
  }

  virtual void draw() const { std::cout << "Drawing shape of area " << computeArea() << "\n"; }

  virtual Shape* clone() const {
    throw std::logic_error("Not implemented, do override");
    return nullptr;
  }

  virtual ~Shape() {}

  int getColor() const { return this->color; }

  void setColor(int color) { this->color = color; }
};

class Rectangle : public Shape {
 private:
  Point topLeft;
  Point bottomRight;

 public:
  Rectangle(int color, const Point& topLeft, const Point& bottomRight)
      : Shape(color), topLeft(topLeft), bottomRight(bottomRight) {}

  virtual int computeArea() const override { return 100; }

  virtual void draw() const override {
    Shape::draw();

    std::cout << "Drawing rectangle tl " << topLeft.toString() << " br " << bottomRight.toString() << "\n";
  }

  virtual Shape* clone() const override { return new Rectangle(*this); }

  virtual ~Rectangle() {}
};

class Circle : public Shape {
 private:
  Point center;
  double radius;

 public:
  Circle(int color, const Point& center, double radius) : Shape(color), center(center), radius(radius) {}

  virtual int computeArea() const override { return 20; }

  virtual void draw() const override {
    Shape::draw();

    std::cout << "Drawing circle center " << this->center.toString() << " radius " << this->radius << "\n";
  }

  virtual Shape* clone() const override { return new Circle(*this); }

  virtual ~Circle() {}
};

class ImageEditor {
 protected:
  std::vector<Shape*> shapes;

 public:
  void addShape(const Shape* shape) { shapes.push_back(shape->clone()); }

  virtual void draw() const {
    std::cout << "Image Editor::draw\n";

    for (Shape* shape : shapes) {
      shape->draw();
    }
  }

  virtual ~ImageEditor() {
    for (Shape* shape : shapes) {
      delete shape;
    }

    shapes.clear();
  }
};

class AdobeEditor : public ImageEditor {};

void initialize(AdobeEditor* editor) {
  Rectangle* rectangle = new Rectangle(122, Point(3, 4), Point(8, 5));
  Circle* circle = new Circle(111, Point(8, 1), 6);

  editor->addShape(rectangle);
  editor->addShape(circle);

  delete rectangle;
  delete circle;
}

int main() {
  AdobeEditor* editor = new AdobeEditor();

  initialize(editor);
  editor->draw();

  delete editor;
}