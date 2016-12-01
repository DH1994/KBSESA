#ifndef NunchukLibrary_h
#define NunchukLibrary_h

class NunchukLibrary {
public:
    NunchukLibrary();
    void AN_sendByte(uint8_t data, uint8_t location);
    void NunchukLoop();
    uint8_t getStatus();
    uint8_t ANupdate();
	
    int zButton;
    int cButton;
    	
private:
    int analogX;
    int analogY;
    int accelX;
    int accelY;
    int accelZ;
	int beginPossX;
	int beginPossY;
	uint8_t status=0;
};
#endif
