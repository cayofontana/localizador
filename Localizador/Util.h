#ifndef UTIL_H
#define UTIL_H

class Util
{
public:
        static void
        limparBufferSerial(void)
        {
                while (Serial.available())
                        Serial.read();
        }

};

#endif
