#pragma once
class Rectangle
{
    private:
        double _width;
        double _height;
    public:
        Rectangle() : _width{ 1.0 }, _height{ 1.0 } {}
        
        Rectangle(double width, double height) : _width{ width }, _height{ height } {}

        double get_width() const // const here indicates this funciton won't change values 
        { 
            return _width; 
        }
        
        double get_height() const // const here indicates this funciton won't change values
        { 
            return _height; 
        }

        double area() const; // const here indicates this funciton won't change values
};
