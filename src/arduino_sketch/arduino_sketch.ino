#include "AudioTools.h" // pschatzmann AudioTools library is required; see: https://github.com/pschatzmann/arduino-audio-tools/tree/main

AudioInfo info(44100, 1, 32); // SET AUDIO info
I2SStream i2sStream;
CsvOutput<int32_t> csvStream(Serial);
StreamCopy copier(csvStream, i2sStream); // copy i2sStream to csvStream

// Arduino Setup
void setup(void) {

    // SETUP SERIAL and AUDIOLOGGER
    Serial.begin(115200);
    AudioLogger::instance().begin(Serial, AudioLogger::Error);
    
    // SETUP I2S CONFIGURATION FOR MICROPHONE
    auto cfg = i2sStream.defaultConfig(RX_MODE);
    cfg.copyFrom(info);
    cfg.i2s_format = I2S_STD_FORMAT; // or try with I2S_LSB_FORMAT
    cfg.is_master = true;
    cfg.pin_bck = 14;
    cfg.pin_ws = 15;
    cfg.pin_data = 32;
    cfg.pin_data_rx = 32;
    i2sStream.begin(cfg);

    csvStream.begin(info);

}

void loop() {
    // COPY I2C DATA FOR MICROPHONE
    copier.copy();
}