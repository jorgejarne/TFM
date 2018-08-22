/**
 * This example shows how to use the Thermo3 Click wrapper of the LetMeCreate
 * library.
 *
 * It reads the temperature from the sensor and exits.
 *
 * The Thermo3 Click must be inserted in Mikrobus 1 before running this program.
 */

#include <stdio.h>
#include <letmecreate/letmecreate.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    float temperature = 0.0;
    char temp[8];
    char command[2048];

    i2c_init();
    i2c_select_bus(MIKROBUS_2);


    printf("-------------------------------------------------------------------- \n");
    printf("|                 Bienvenido al cliente MQTT de Ci40               |\n");
    printf("-------------------------------------------------------------------- \n");

  
    while(1){
	    thermo3_click_enable(0);
	    thermo3_click_get_temperature(&temperature);
	    printf("\n temperature: %.3f degrees celsius\n", temperature);
	    thermo3_click_disable();
	    strcpy( command, "mosquitto_pub -h 192.168.1.91 -p 1883 -t 'casa/salon/temperatura' -m");
	    //mosquitto.org
	    //strcat(command,argv[1]);
	    //strcat(command," -p 1883 -t ’");
	    //strcat(command,argv[2]);
	    //strcat(command,"’ -m ");
	    snprintf(temp,8,"%f",temperature); // conversion de la variable leida(float a char)
	    strcat(command,temp);
	    //strcat(command,"º ");
	    system(command);
	    Sleep(5000);
    }

    i2c_release();

    return 0;
}
