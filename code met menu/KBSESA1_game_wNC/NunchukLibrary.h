#ifndef NunchukLibrary_h
#define NunchukLibrary_h

class NunchukLibrary {
public:
    NunchukLibrary();
    void AN_sendByte(uint8_t data, uint8_t location);
    void NunchukLoop();
    uint8_t getStatus();
	uint8_t getZButton();
	uint8_t getCButton();
    uint8_t ANupdate();
	
    uint8_t zButton;
    uint8_t cButton;
    	
private:
    uint8_t analogX;
    uint8_t analogY;
    uint8_t accelX;
    uint8_t accelY;
    uint8_t accelZ;
	uint8_t beginPossX;
	uint8_t beginPossY;
	uint8_t status=0;
};
#endif
