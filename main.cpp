#include "mbed.h"
#include "LSM6DSLSensor.h"

#define PI 3.141592654
float denom = 0;
float led1var = 0;
float led2var = 0;
float led3var = 0;
//volatile float res = 0;
//Pwmout led3(LED3);
//DigitalOut led3(LED3);
PwmOut l3(LED3);
PwmOut l1(LED1);
PwmOut l2(LED2);


static DevI2C devI2c(PB_11,PB_10);
static LSM6DSLSensor acc_gyro(&devI2c,0xD4,D4,D5); // high address

/*This is a program that uses the LSM6DSL library to interface to the many sensors on board of the mBED device.
This program calculates the Pitch angle and Roll angle of the mBED device and prints the data to screen. Two functions 
were created to calculated the angles, inside each of the functions are the calculations required to obtain the 
correct angles, then next two functions show how the calculations were performed
*/

volatile int32_t xvar = 0;
volatile int32_t yvar = 0;
volatile int32_t zvar = 0;

float computeAnglePitch(int32_t x, int32_t y, int32_t z){   //function to calculate the Pith angle 
    float pitchres = 0;
    y = (float) y*y;
    z = (float) z*z;
    x = (float) x;

    pitchres = atan(x/(sqrt(y+z)));
    pitchres = (pitchres * 180)/PI;

    //res = sqrt(x/((y^2)+ (z^2)));

    return pitchres;
}
float computeAngleRoll(int32_t x, int32_t y, int32_t z){    //function to calculate the Roll angle
    float rollres = 0;
    y = (float) y;
    z = (float) z*z;
    x = (float) x*x;

    rollres = atan(y/(sqrt(x+z)));
    rollres = (rollres * 180)/PI;

    //res = sqrt(x/((y^2)+ (z^2)));

    return rollres;
}
void incL1brightness(){
    if(led1var == 1){
        l1 = 1;
        led1var = 1;
    }
    else if(led1var < 1){
        led1var += 0.1;
        l1 = led1var;
    }

}
void decL1brightness(){
    if(led1var <= 1 && led1var > 0){
        led1var -= 0.1;
    }
    else if(led1var == 0){
        led1var = 0.1;
        l1 = led1var;
    }

}
void incL2brightness(){
    if(led2var == 1){
        l2 = 1;
        led2var = 1;
    }
    else if(led2var < 1){
        led2var += 0.1;
        l2 = led2var;
    }

}
void decL2brightness(){
    if(led2var <= 1 && led2var > 0){
        led2var -= 0.1;
    }
    else if(led2var == 0){
        led2var = 0.1;
        l2 = led2var;
    }

}
void incL3brightness(){
    l3 = 1.0;
//    if(led3var == 1){
//        l3 = 1;
//        led3var = 1;
//    }
//    else if(led3var < 1){
//        led3var += 0.1;
//        l3 = led3var;
//    }

}
void decL3brightness(){
    l3 = 0.1;
//    if(led3var <= 1 && led3var > 0){
//        led3var -= 0.1;
//    }
//    else if(led3var == 0){
//        led3var = 0.1;
//        l3 = led3var;
//    }

}
//void incL1brightness(float lled){
//    if(led1var == 1){
//        l1 = 1;
 //       led1var = 1;
//    }
//    else if(led1var < 1){
//        led1var += 0.1;
//       l1 = led1var;
//    }
//}
/* Simple main function to print the Roll and Pith of the mBED */
int main() {
    uint8_t id;
    int32_t axes[3];
    float res=0;
    float res1 = 0;
    acc_gyro.init(NULL);
    l1 = 0.0;
    l2 = 0.0;
    l3 = 0.0;

    acc_gyro.enable_x();
    acc_gyro.enable_g();

    printf("This is an accelerometer example running on Mbed OS %d.%d.%d.\n", MBED_MAJOR_VERSION, MBED_MINOR_VERSION, MBED_PATCH_VERSION);
    acc_gyro.read_id(&id);
    printf("LSM6DSL accelerometer & gyroscope = 0x%X\r\n", id);

    thread_sleep_for(2000);
        //led3 = 0.5;
    l1 = 1;
    l2 = 1;
    l3 = 1;
    thread_sleep_for(3000);
    l1 = 0.1;
    l2 = 0.1;
    l3 = 0.1;

    while(1) {

        acc_gyro.get_x_axes(axes);      //accquires the data from the gyro before calling the compute functions
        res = computeAnglePitch(axes[0], axes[1], axes[2]); //calls the Pitch compute function
        res1 = computeAngleRoll(axes[0], axes[1], axes[2]); //calls the Roll compute function
        printf("LSM6DSL: %6d, %6d, %6d, %3.2f, %3.2f\r\n", axes[0], axes[1], axes[2], res, res1) ; //prints the Pith and Roll information every 2 seconds
        xvar = axes[0];
        yvar = axes[1];
        zvar = axes[2];
        //led3 = 1;
        thread_sleep_for(1000);//if axes[0] has increased add 0.1% to brightness of Led 1

       if(xvar > -100 && xvar < 100){
           //incL1brightness();
           l1 = 0.1;
           }
           else if((xvar > -300 && xvar <-100) || (xvar >100 && xvar < 300)){
               l1 = 0.3;
            }    //else if(xvar < axes[0]){
            else if((xvar > -700 && xvar <-300) || (xvar >300 && xvar < 700)){
               l1 = 0.6;
            }    //else if(xvar < axes[0]){
           else if((xvar > -1010 && xvar <-700) || (xvar >700 && xvar < 1010)){
               l1 = 1;
            }    //else if(xvar < axes[0]){
       if(yvar > -100 && yvar < 100){
           //incL1brightness();
           l2 = 0.1;
           }
           else if((yvar > -300 && yvar <-100) || (yvar >100 && yvar < 300)){
               l2 = 0.3;
            }    //else if(xvar < axes[0]){
            else if((yvar > -700 && yvar <-300) || (yvar >300 && yvar < 700)){
               l2 = 0.6;
            }    //else if(xvar < axes[0]){
           else if((yvar > -1010 && yvar <-700) || (yvar >700 && yvar < 1010)){
               l2 = 1;
            }    //else if(xvar < axes[0]){

       if(zvar > 500){
           incL3brightness();
           }
           else if(zvar < 100){
               decL3brightness();
           }
    }
}

//       if(yvar > axes[1]){
//           incL2brightness();
//           }
//           else if(yvar < axes[1]){
//               decL2brightness();
//           }

 //     if(xvar > axes[0]){
 //          incL1brightness(float led1var);
 //          }
 //          else if(xvar < axes[0]){
 //              decL1brightness();
 //          } 
