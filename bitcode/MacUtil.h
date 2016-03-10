/**
* @file    MacUtil.h
* @brief
* @author  Hojei, Yu (hojei1452@gmail.com)
* @date    2016.03.10 23:11 created.
* @copyright All rights reserved by Hojei, Yu
**/
#pragma once

typedef class Mac
{
public:
	Mac() {}
	virtual ~Mac() { }

	bool getMacList(_Out_ std::list<std::string>& list)
	{
		PIP_ADAPTER_ADDRESSES pAdpAddrs;
		unsigned long ulBufLen = sizeof(IP_ADAPTER_ADDRESSES);

		pAdpAddrs = (PIP_ADAPTER_ADDRESSES)malloc(ulBufLen);
		if (!pAdpAddrs) return false;

		DWORD dwRet;
		dwRet = GetAdaptersAddresses(AF_INET, GAA_FLAG_INCLUDE_GATEWAYS, NULL, pAdpAddrs, &ulBufLen);
		if (dwRet == ERROR_BUFFER_OVERFLOW)
		{
			free(pAdpAddrs);
			pAdpAddrs = (PIP_ADAPTER_ADDRESSES)malloc(ulBufLen);

			if (!pAdpAddrs)
				return false;
		}

		dwRet = GetAdaptersAddresses(AF_INET, GAA_FLAG_INCLUDE_GATEWAYS, NULL, pAdpAddrs, &ulBufLen);
		if (dwRet != NO_ERROR)
		{
			free(pAdpAddrs);
			return false;
		}

		PIP_ADAPTER_ADDRESSES tmp;
		for (tmp = pAdpAddrs; tmp != NULL; tmp = tmp->Next)
		{
			if (tmp->PhysicalAddressLength != 6)
				continue;

			if (tmp->OperStatus != IfOperStatusUp)
				continue;

			char taddr[3] = { 0 };
			for (int i = 0; i < 3; i++)
			{
				UInt8ToChar(tmp->PhysicalAddress[i], &taddr[i]);
			}

			char addr[9] = { 0 };
			conversion(taddr, addr);
			std::string str = std::string(addr, 9);
			list.push_back(str);
		}

		free(pAdpAddrs);
		return true;
	}

private:
	void conversion(_In_ char* _src, _Out_ char* _dst)
	{
		int index = 0;
		for (int i = 0; i < 3; i++)
		{
			char ch1, ch2;
			ch1 = _src[i] & 0xF0;
			ch1 = ch1 >> 4;
			if (ch1 > 9)
				ch1 = ch1 + 'A' - 10;
			else
				ch1 = ch1 + '0';
			ch2 = _src[i] & 0x0F;
			if (ch2 > 9)
				ch2 = ch2 + 'A' - 10;
			else
				ch2 = ch2 + '0';
			_dst[index++] = ch1;
			_dst[index++] = ch2;
			_dst[index++] = ':';
		}
		_dst[--index] = '\0';
	}

} *PMac;