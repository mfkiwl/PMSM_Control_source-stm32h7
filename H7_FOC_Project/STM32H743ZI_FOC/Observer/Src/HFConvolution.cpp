/*
 * HFConvolution.cpp
 *
 *  Created on: 2020/01/05
 *      Author: watashi
 */

#include "HFConvolution.hpp"

HFConvolution::HFConvolution()
{
	// TODO Auto-generated constructor stub

}

HFConvolution::~HFConvolution() {
	// TODO Auto-generated destructor stub
}


void HFConvolution::LPFInit(float pGainB0, float pGainB1, float pGainA1) {
	mLPFIdc.Init(pGainB0, pGainB1, pGainA1);
	mLPFIqc.Init(pGainB0, pGainB1, pGainA1);
}

void HFConvolution::BPFInit(float pGainB0, float pGainB2, float pGainA1, float pGainA2) {
	mBPFIdc.Init(pGainB0, pGainB2, pGainA1, pGainA2);
	mBPFIqc.Init(pGainB0, pGainB2, pGainA1, pGainA2);
}

void HFConvolution::InitCycleTime(float pCycleTime) {
	mCycleTime = pCycleTime;
}

void HFConvolution::InitPII2(float pCycleTime, float pK1, float pK2, float pK3) {
	mEstThetaPII2.InitCycleTime(pCycleTime);
	mEstThetaPII2.InitGainK1(pK1);
	mEstThetaPII2.InitGainK2(pK2);
	mEstThetaPII2.InitGainK3(pK3);
}


void HFConvolution::SetIgdPair(const std::array<float, 2> &pIgd) {
	mIgd = pIgd;
}


void HFConvolution::SetSinCos(const std::array<float, 2> &pSinCos) {
	mSinCos = pSinCos;
}


void HFConvolution::Calculate() {
	float BPFIdc = mBPFIdc.Output(mCycleTime, mIgd.at(0));
	float BPFIqc = mBPFIqc.Output(mCycleTime, mIgd.at(1));
	float convIdc = BPFIdc * mSinCos.at(1);
	float convIqc = BPFIqc * mSinCos.at(0);
	float LPFIdc = mLPFIdc.Output(mCycleTime, convIdc);
	float LPFIqc = mLPFIqc.Output(mCycleTime, convIqc);

	//PII2を使うことも要検討。
	float estAxiErr = LPFIqc - LPFIdc;

	mEstThetaPII2.SetValue(estAxiErr);
	mEstThetaPII2.Calculate();
	mTheta_c = fmod( ( mEstThetaPII2.GetTheta() + 2 * M_PI ) , ( 2 * M_PI ) );//theta % 2pi

}


float HFConvolution::GetTheta_c(void) {
	return mTheta_c;
}