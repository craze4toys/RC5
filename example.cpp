// example.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <cstdlib>
#include <string>
#include <iomanip>
#include "RC5.h"
using namespace std;

int main()
{
	const unsigned char key[8] = { 1,2,3,4,5,6,7,8 };
	RC5<unsigned short> rc5(16, 8, key);
	string cmd;
	unsigned int in;
	while (true)
	{
		cin >>dec >> cmd;
		if (cmd == "enc")
		{
			cin >> in;
			unsigned short pt[2];
			unsigned short ct[2];
			pt[0] = (unsigned short)in;
			pt[1] = (unsigned short)(in >> 16);
			rc5.Encrypt(pt, ct);
			unsigned int out;
			out = ((unsigned int)ct[0]) | ((unsigned int)(ct[1]) << 16);
			cout << "Encrypt: 0x" << hex << setfill('0') << setw(8) <<  out << endl;
		}
		else if (cmd == "dec")
		{
			cin >> hex >> in;
			unsigned short pt[2];
			unsigned short ct[2];
			ct[0] = (unsigned short)in;
			ct[1] = (unsigned short)(in >> 16);
			rc5.Decrypt(ct, pt);
			unsigned int out;
			out = ((unsigned int)pt[0]) | ((unsigned int)(pt[1]) << 16);
			cout << "Decrypt: " << dec << out << endl;
		}
		else if (cmd == "exit")
		{
			break;
		}
		else
		{
			cout << dec << "Wrong CMD, valid is enc, dec, exit" << endl;
		}
	}
    return 0;
	
}

