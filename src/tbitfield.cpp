
// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

#define BITS_IN_ONE_MEM (sizeof(TELEM) * 8)

TBitField::TBitField(int len) 
{
	if (len < 0) 
	{
		std::cout << "Negative value";
		throw "Negative value";
	}
	else 
	{
		BitLen = len;
		MemLen = BitLen / (sizeof(TELEM) * 8) + 1;
		pMem = new TELEM[MemLen];
		for (int i = 0; i < MemLen; ++i)
			pMem[i] = 0;
	}

}

TBitField::TBitField(const TBitField& bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; ++i)
		pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
	delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if (n < 0 || n > BitLen)
		std::cout << "Invalid index";
	else return (n / (sizeof(TELEM) * 8));
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	if (n < 0 || n > BitLen)
		std::cout << "Invalid value";
	else return (1 << (n % (sizeof(TELEM) * 8)));
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if (n < 0 || n > BitLen) 
	{
		std::cout << "Invalid index";
		throw "Invalid index";
	}
	else pMem[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if (n < 0 || n > BitLen) 
	{
		std::cout << "Invalid index";
		throw "Invalid index";
	}
	else pMem[GetMemIndex(n)] &= ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if (n < 0 || n > BitLen) 
	{
		std::cout << "Invalid index";
		throw "Invalid index";
	}
	else if (pMem[GetMemIndex(n)] & GetMemMask(n))
		return 1;
	else return 0;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField & bf) // присваивание
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; ++i)
		pMem[i] = bf.pMem[i];
	return *this;
}

int TBitField::operator==(const TBitField & bf) const // сравнение
{
	if (BitLen != bf.BitLen)
		return 0;
	for (int i = 0; i < MemLen; ++i) 
	{
		if (pMem[i] != bf.pMem[i])
			return 0;
	}
	return 1;
}

int TBitField::operator!=(const TBitField & bf) const // сравнение
{
	if (*this == bf)
		return 0;
	else return 1;
}

TBitField TBitField::operator|(const TBitField & bf) // операция "или"
{
	int tmpSize;
	if (BitLen > bf.BitLen)
		tmpSize = BitLen;
	else tmpSize = bf.BitLen;

	TBitField tmp(tmpSize);

	for (int i = 0; i < MemLen; ++i)
		tmp.pMem[i] = pMem[i];
	for (int i = 0; i < MemLen; ++i)
		tmp.pMem[i] = (bf.pMem[i] | pMem[i]);
	return tmp;
}

TBitField TBitField::operator&(const TBitField & bf) // операция "и"
{
	int tmpSize;
	int tmpMem;
	if (BitLen > bf.BitLen) 
	{
		tmpSize = BitLen;
		tmpMem = bf.MemLen;
	}
	else 
	{
		tmpSize = bf.BitLen;
		tmpMem = MemLen;
	}

	TBitField tmp(tmpSize);

	for (int i = 0; i < tmpMem; ++i)
		tmp.pMem[i] = bf.pMem[i] & pMem[i];
	return tmp;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField tmp(BitLen);
	for (int i = 0; i < BitLen; ++i)
		if (GetBit(i) != 0)
			tmp.ClrBit(i);
		else
			tmp.SetBit(i);
	return tmp;
}

// ввод/вывод

istream& operator>>(istream & istr, TBitField & bf) // ввод
{
	int value;
	for (int i = 0; i < bf.GetLength(); ++i) 
	{
		istr >> value;
		if (value == 0)
			bf.ClrBit(i);
		else
			bf.SetBit(i);
	}
	return istr;
}

ostream& operator<<(ostream & ostr, const TBitField & bf) // вывод
{
	for (int i = 0; i < bf.GetLength(); ++i)
		ostr << bf.GetBit(i);
	ostr << '\n';
	return ostr;
}
