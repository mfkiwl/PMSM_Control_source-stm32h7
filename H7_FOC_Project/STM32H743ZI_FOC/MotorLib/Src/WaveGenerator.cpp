/*
 * WaveGenerator.cpp
 *
 *  Created on: Dec 13, 2019
 *      Author: watashi
 */

#include "WaveGenerator.hpp"

WaveGenerator::WaveGenerator() {
	// TODO Auto-generated constructor stub

}

WaveGenerator::~WaveGenerator() {
	// TODO Auto-generated destructor stub
}

void WaveGenerator::InitFrequency(int pTargetHz) {
	mTargetHz = pTargetHz;
}


void WaveGenerator::ResetPhase() {
	mCount = 0;

}


float WaveGenerator::OutputWaveform() {
	float theta = ( (2 * M_PI)/(CONTROL_FREQ_HZ * mTargetHz) ) * mCount ;
	mCount++;

	if(mCount > CONTROL_FREQ_HZ - 1) {//CONTROL_FREQに届いたら0にする
		mCount = 0;
	}

	return Trigonometric::sin(theta);
}
