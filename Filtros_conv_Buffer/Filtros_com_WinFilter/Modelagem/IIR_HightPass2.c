/**************************************************************
WinFilter version 0.8
http://www.winfilter.20m.com
akundert@hotmail.com

Filter type: High Pass
Filter model: Butterworth
Filter order: 5
Sampling Frequency: 100 Hz
Cut Frequency: 10.000000 Hz
Coefficents Quantization: float

Z domain Zeros
z = 1.000000 + j 0.000000
z = 1.000000 + j 0.000000
z = 1.000000 + j 0.000000
z = 1.000000 + j 0.000000
z = 1.000000 + j 0.000000

Z domain Poles
z = 0.548290 + j -0.234148
z = 0.548290 + j 0.234148
z = 0.509525 + j -0.000000
z = 0.684659 + j -0.473087
z = 0.684659 + j 0.473087
***************************************************************/
#define NCoef 5
float iir(float NewSample) {
    float ACoef[NCoef+1] = {
        0.35430488162785484000,
        -1.77152440813927430000,
        3.54304881627854850000,
        -3.54304881627854850000,
        1.77152440813927430000,
        -0.35430488162785484000
    };

    float BCoef[NCoef+1] = {
        1.00000000000000000000,
        -2.97542210978194090000,
        3.80601811938360690000,
        -2.54525286838600940000,
        0.88113007546329158000,
        -0.12543062215961828000
    };

    static float y[NCoef+1]; //output samples
    static float x[NCoef+1]; //input samples
    int n;

    //shift the old samples
    for(n=NCoef; n>0; n--) {
       x[n] = x[n-1];
       y[n] = y[n-1];
    }

    //Calculate the new output
    x[0] = NewSample;
    y[0] = ACoef[0] * x[0];
    for(n=1; n<=NCoef; n++)
        y[0] += ACoef[n] * x[n] - BCoef[n] * y[n];
    
    return y[0];
}
