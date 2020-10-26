
class _LCD
{
	public:
		_LCD(unsigned char addr);
		void GoTo(int line, int pos);
		void Clear(void);
		void PrintLn(const char* s);
		void PrintChar(char val);
		void PrintInt(int i);
		void PrintFloat(float myFloat);
	private:
		void LcdSendByte(int bits, int mode);
		void lcd_toggle_enable(int bits);
		unsigned char Addr;
		const unsigned char Cmd, Data;
		int Fd;  // seen by all subroutines
};
