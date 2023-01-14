#include <Time.h>
#include <TimeLib.h>

#include <RTClib.h>

RTC_DS3231 rtc;

uint32_t timestamp() {
    DateTime now = rtc.now();
    return now.unixtime();
}

char* getDateTime(unsigned long timeInUnix) {
    char buff[32];
    const String months[12] = {"January", "February", "March", "May", "June", "July", "August", "September", "October", "November", "December"};
    
    //const String h = (hour(timeInUnix) > 12) ? (String)(hour(timeInUnix) % 12) : (String)(hour(timeInUnix));
    
    int h = 0;
    String ref = "";
    if(hour(timeInUnix) > 12) {
        // PM
        h = hour(timeInUnix) % 12;
        ref = "PM";
    } else {
        h = hour(timeInUnix);
        ref = "AM";
    }
    
    sprintf(buff, "%s %02d, %02d %02d:%02d:%02d %s", months[month(timeInUnix) - 1], day(timeInUnix), year(timeInUnix), h, minute(timeInUnix), second(timeInUnix), ref);
    Serial.println(buff);
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
    
    if (rtc.lostPower()) {
        Serial.println("RTC lost power, let's set the time!");
        // When time needs to be set on a new device, or after a power loss, the
        // following line sets the RTC to the date & time this sketch was compiled
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }

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