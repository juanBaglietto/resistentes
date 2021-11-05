class Color
{
private:
    int _red;
    int _green;
    int _blue;

public:
    Color()
    {
       _red=0;
       _green=0; 
       _blue=0; 
    }
    void changeColor(int red, int green, int blue);
    int getRed();
    int getGreen();
    int getBlue();

};