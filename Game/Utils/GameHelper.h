#ifndef GAMEHELPER_H
#define GAMEHELPER_H

class GameHelper {
    public:
        // Static method to get the single instance of the class
        static GameHelper& Get() {
            static GameHelper instance;
            return instance;
        }

        // Deleted copy constructor and assignment operator to prevent copying
        GameHelper(const GameHelper&) = delete;
        GameHelper& operator=(const GameHelper&) = delete;

        

        float PixelToMeter(const float Value)
        {
            return (Value * (1.0f / MetersPerPixelFactor));
        }

       /* b2Vec2 PixelToMeter(const b2Vec2& rVector)
        {
            return b2Vec2(PixelToMeter(rVector.x), PixelToMeter(rVector.y));
        }

        float MeterToPixel(const float Value)
        {
            return (Value * MetersPerPixelFactor);
        }

        b2Vec2 MeterToPixel(const b2Vec2& rVector)
        {
            return b2Vec2(MeterToPixel(rVector.x), MeterToPixel(rVector.y));
        }*/

    private:
        float MetersPerPixelFactor = 32.0f;

        GameHelper() {}

        ~GameHelper() { }
};

#endif // GAMEHELPER_H