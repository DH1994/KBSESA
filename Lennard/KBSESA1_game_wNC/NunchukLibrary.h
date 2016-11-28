#ifndef NunchukLibrary_h
#define NunchukLibrary_h

class NunchukLibrary {
public:
    void AN_sendByte(uint8_t data, uint8_t location);
    void NunchukLoop();
    void ANinit();
    uint8_t ANupdate();
	void UpdateLocation();
	
    int zButton;
    int cButton;
	//uint8_t status;
	
private:
    int analogX;
    int analogY;
    int accelX;
    int accelY;
    int accelZ;
	int beginPossX;
	int beginPossY;
	uint8_t status;
};
#endif