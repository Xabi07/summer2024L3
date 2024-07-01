#include "mbed.h"
#include "LSM6DSLSensor.h"

#define PI 3.141592654
float denom = 0;
//volatile float res = 0;

static DevI2C devI2c(PB_11,PB_10);
static LSM6DSLSensor acc_gyro(&devI2c,0xD4,D4,D5); // high address



float computeAnglePitch(int x, int y, int z){
    float pitchres = 0;
    y = (float) y*y;
    z = (float) z*z;
    x = (float) x;

    pitchres = atan(x/(sqrt(y+z)));
    pitchres = (pitchres * 180)/PI;

    //res = sqrt(x/((y^2)+ (z^2)));

    return pitchres;
}
float computeAngleRoll(int x, int y, int z){
    float rollres = 0;
    y = (float) y;
    z = (float) z*z;
    x = (float) x*x;

    rollres = atan(y/(sqrt(x+z)));
    rollres = (rollres * 180)/PI;

    //res = sqrt(x/((y^2)+ (z^2)));

    return rollres;
}
/* Simple main function */
int main() {
    uint8_t id;
    int32_t axes[3];
    float res=0;
    float res1 = 0;
    acc_gyro.init(NULL);

    acc_gyro.enable_x();
    acc_gyro.enable_g();

    printf("This is an accelerometer example running on Mbed OS %d.%d.%d.\n", MBED_MAJOR_VERSION, MBED_MINOR_VERSION, MBED_PATCH_VERSION);
    acc_gyro.read_id(&id);
    printf("LSM6DSL accelerometer & gyroscope = 0x%X\r\n", id);

    while(1) {

        acc_gyro.get_x_axes(axes);
        res = computeAnglePitch(axes[0], axes[1], axes[2]);
        res1 = computeAngleRoll(axes[0], axes[1], axes[2]);
        printf("LSM6DSL: %6d, %6d, %6d, %3.2f, %3.2f\r\n", axes[0], axes[1], axes[2], res, res1) ;


        thread_sleep_for(2000);

    }
}
