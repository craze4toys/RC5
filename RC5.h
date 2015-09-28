#ifndef _RC5_H_
#define _RC5_H_

#include <cstring>

template <class WORD> class RC5
{
public:
	RC5(int r, int keyLength, const unsigned char * keyData); //r for round, keyLength in Byte, and keyData
	~RC5();
	void Encrypt(const WORD * in, WORD * out); //must input WORD x[2] for in and out
	void Decrypt(const WORD * in, WORD * out); //must input WORD x[2] for in and out
private:
	int _wordLengthInBit; //w
	int _round; //r
	int _keyLengthInByte; //b
	int _keyLengthInWord; //c: key length in
	int _sTableSize; // t: S table size
	WORD *_S; //S table
	WORD _P; //magic constants
	WORD _Q; //magic constants
	void KeyIninitialize(const unsigned char *keyData); //initialize S table
	WORD CyclicRightShift(WORD x, WORD y); //cyclic right shift the number x by y bit
	WORD CyclicLeftShift(WORD x, WORD y); //cyclic left shift the number x by y bit
};


template<class WORD>
RC5<WORD>::RC5(int r, int keyLength, const unsigned char * keyData)
{
	_wordLengthInBit = sizeof(WORD) * 8;
	_round = r;
	_keyLengthInByte = keyLength;
	_keyLengthInWord = _keyLengthInByte * 8 / _wordLengthInBit;
	_sTableSize = 2 * (_round + 1);
	switch (sizeof(WORD))
	{
	case 2:
		_P = (WORD)0xb7e1;
		_Q = (WORD)0x9e37;
		break;
	case 4:
		_P = (WORD)0xb7e15163;
		_Q = (WORD)0x9e3779b9;
		break;
	case 8:
		_P = (WORD)0xb7e151628aed2a6b;
		_Q = (WORD)0x9e3779b97f4a7c15;
		break;
	default:
		break;
	}
	_S = new WORD[_sTableSize];
	KeyIninitialize(keyData);
}
template<class WORD>
RC5<WORD>::~RC5()
{
	delete[] _S;
}
template<class WORD>
void RC5<WORD>::Encrypt(const WORD * pt, WORD * ct)
{
	int i;
	WORD A = pt[0] + _S[0], B = pt[1] + _S[1];
	for (i = 1; i <= _round; i++)
	{
		A = CyclicLeftShift((WORD)(A^B), B) + _S[2 * i];
		B = CyclicLeftShift((WORD)(B^A), A) + _S[2 * i + 1];
	}
	ct[0] = A;
	ct[1] = B;
}
template<class WORD>
void RC5<WORD>::Decrypt(const WORD * ct, WORD * pt)
{
	int i;
	WORD B = ct[1], A = ct[0];
	for (i = _round; i > 0; i--)
	{
		B = CyclicRightShift(B - _S[2 * i + 1], A) ^ A;
		A = CyclicRightShift(A - _S[2 * i], B) ^ B;
	}
	pt[1] = B - _S[1];
	pt[0] = A - _S[0];
}
template<class WORD>
void RC5<WORD>::KeyIninitialize(const unsigned char * keyData)
{
	int i, j, k;
	WORD A, B;
	WORD u = _wordLengthInBit / 8;
	WORD *L = new WORD[_keyLengthInWord];
	memset(L, 0, sizeof(L));
	for (i = _keyLengthInByte - 1; i != -1; i--)
		L[i / u] = (L[i / u] << 8) + keyData[i];
	for (i = 1, _S[0] = _P; i < _sTableSize; i++)
		_S[i] = _S[i - 1] + _Q;
	for (A = B = i = j = k = 0; k < 3 * _sTableSize; k++)
	{
		A = _S[i] = CyclicLeftShift(_S[i] + (A + B), 3);
		B = L[j] = CyclicLeftShift(L[j] + (A + B), A + B);
		i = (i + 1) % _sTableSize;
		j = (j + 1) % _keyLengthInWord;
	}
	delete[] L;
}

template<class WORD>
WORD RC5<WORD>::CyclicRightShift(WORD x, WORD y)
{
	return (x >> (y&(_wordLengthInBit - 1))) | (x << (_wordLengthInBit - (y&(_wordLengthInBit - 1))));
}

template<class WORD>
WORD RC5<WORD>::CyclicLeftShift(WORD x, WORD y)
{
	return (x << (y&(_wordLengthInBit - 1))) | (x >> (_wordLengthInBit - (y&(_wordLengthInBit - 1))));
}

#endif