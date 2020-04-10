#define LOG_INFO(message)        \
    {                            \
        Serial.print("<INFO> "); \
        Serial.print(__FILE__);  \
        Serial.print(":");       \
        Serial.print(__LINE__);  \
        Serial.print(" - ");     \
        Serial.println(message); \
    }
#define LOG_INFO_VALUE(message, value) \
    {                                  \
        Serial.print("<INFO> ");       \
        Serial.print(__FILE__);        \
        Serial.print(":");             \
        Serial.print(__LINE__);        \
        Serial.print(" - ");           \
        Serial.print(message);         \
        Serial.println(value);         \
    }

#define LOG_ERROR(message)        \
    {                             \
        Serial.print("<ERROR> "); \
        Serial.print(__FILE__);   \
        Serial.print(":");        \
        Serial.print(__LINE__);   \
        Serial.print(" - ");      \
        Serial.println(message);  \
    }

#define LOG_ERROR_VALUE(message, value) \
    {                                   \
        Serial.print("<ERROR> ");       \
        Serial.print(__FILE__);         \
        Serial.print(":");              \
        Serial.print(__LINE__);         \
        Serial.print(" - ");            \
        Serial.print(message);          \
        Serial.println(value);          \
    }