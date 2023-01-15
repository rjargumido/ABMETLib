#include <RTClib.h>
#include <Time.h>
#include <TimeLib.h>


RTC_DS3231 rtc;

uint32_t timestamp() {
    DateTime now = rtc.now();
    return now.unixtime();
}

char* getDateTime(unsigned long _t) {
    const String months[12] = {"January", "February", "March", "May",
     "June", "July", "August", "September", "October", "November", "December"};
    
    int h = 0;
    String ref = "";
    if(hour(_t) > 12) {
        // PM
        h = hour(_t) % 12;
        ref = "PM";
    } else {
        h = hour(_t);
        ref = "AM";
    }
    
    char buff[32];
    sprintf(buff, "%s %02d, %02d %02d:%02d:%02d %s", months[month(_t) - 1], day(_t), year(_t), h, minute(_t), second(_t), ref);
    return buff;
}

void setup() {
    Serial.begin(115200);

    // Enable RTC Module
    if (!rtc.begin()) {
        Serial.println("Couldn't find RTC");
        Serial.flush();
        while (1) delay(10);
    }
    
    // Sets RTC Date & Time 
    if (rtc.lostPower()) { rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); }

    Serial.println("Running");
}

void loop() {
    unsigned long dt = timestamp();

    Serial.print("Unix Time: ");
    Serial.println(dt);

    Serial.print("Readable Time: ");
    Serial.println(getDateTime(dt));
    delay(3000);
}