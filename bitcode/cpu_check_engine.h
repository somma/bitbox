/**
* @file    driver_engine.h
* @brief
* @author  Yu-hyeon, Cha (xargo707@hotmail.com)
* @date    2016.03.14 14:10 created.
* @copyright All rights reserved by team bixbox
**/
#pragma once
#include "conf.h"
#include "stdafx.h"
#include <intrin.h>

typedef class BCcpu : public IBCEngine
{
private:
	HANDLE _driver_hendle;

public:
	BCcpu()
	{

	}
	virtual ~BCcpu()
	{

	}

	bool initialize() { return true; }
	void finalize() { return; }
	BC_ENGINE_TYPE get_engine_type() { return CPU_ENGINE; }

	/// @brief
	bool is_exists(const char* values, ...)
	{
		char cpu_vendor[13] = { 0, };

		_ASSERTE(NULL != values);
		if (NULL == values) return false;
		
		cpu_write_vendor(cpu_vendor);

		if (!memcmp(cpu_vendor, values, 12)) return TRUE;

		return FALSE;
	}

	void dump(const char* values)
	{
		log_info "[Detected string] = %s", values log_end;
	}
	
	void cpu_write_vendor(char * vendor) 
	{	
#if _M_x64
		cpuid_vendor_00_x64(vendor);
#else
		cpuid_vendor_00_x86(vendor);
#endif
	}

	static inline void cpuid_vendor_00_x64(char *vendor)
	{
		// 구현중
	}

	static inline void cpuid_vendor_00_x86(char * vendor) 
	{
		int cpuInfo[4] = { 0, }; // [0] = ebx, [1] = edx, [2] = ecx, [3] = eax
		uint32_t function_id = 0; // A code that specifies the information to retrieve, passed in EAX.
								/*
									EAX = 0 : 제조업체 ID
									EAX=1: 프로세서 정보 및 기능 비트
									EAX=2: 캐시 및 TLB 서술자 정보
									EAX=3: 프로세서 일련 번호
									EAX=80000000h: 가장 높은 확장 함수 가져오기
									EAX=80000001h: 확장 프로세서 정보 및 기능 비트
									EAX=80000002h,80000003h,80000004h: 프로세서 브랜드 문자열
									// 상세는 Intel 64 및 IA-32 아키텍처 소프트웨어 개발자 설명서 2권: 명령 집합 참조
								*/

		__cpuid(cpuInfo, function_id); // function_id : EAX 레지스터로 복사되는 값이다.
										// 값에 따라 질의하는 CPU 정보가 달라짐.
		for (int i = 0; i < 4; i++)
			vendor[i] = cpuInfo[1] >> (i * 8);

		for (int i = 0; i < 4; i++)
			vendor[i + 4] = cpuInfo[3] >> (i * 8);

		for (int i = 0; i < 4; i++)
			vendor[i + 8] = cpuInfo[2] >> (i * 8);

		vendor[12] = 0x00;
	}	
} *PBCcpu;