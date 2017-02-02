/*
 * s7s_SPI.h
 *
 *  Created on: Jan 13, 2017
 *      Author: User
 *      a collection of routines that converts the string returned from
 *      ParseJSONData() in main.c (using the tokens built from the jsmn code)
 *      and places these into a struct with the appropriate positions filled
 *      to pass on to the 4 digit 7-segment display
 */

#ifndef S7S_SPI_H_
#define S7S_SPI_H_
void spi_Open_s7s();
/* holds digits to display on 4 digit display
 * left to right characters 1,2,3,4. chars 1&2
 * represent minutes for first bus, 3&4 2nd bus
 */
//convert strings to enum
typedef enum {_75, _17, Time} DATA_KEY;
const static struct {
    DATA_KEY    val;
    const char *str;
}conversion[] = {
                 {_75, "75"},
                 {_17, "17"},
                 {Time, "Time"}
};
struct displayChars{
    char pos1;
    char pos2;
    char pos3;
    char pos4;
    char errBus1;
    char errBus2;
};

/*struct displayChars{
    int pos1; //leftmost char in 4 digit display
    int pos2;
    int pos3;
    int pos4;
    int err12; //decimal point indicator between l & 2
    int err34; //decimal point indicator between 3 & 4
    int timeColon; //colon to be displayed between 2 & 3
};
void spi_Write_s7s(int displayChar);
typedef enum {_75Ea, _75Eb, _75a, _75b, Time, compErr} VALUE;
const static struct {
    VALUE val;
    const char *str;
}conversion[] = {
                 {_75Ea, "75Ea"},
                 {_75Eb, "75Eb"},
                 {_75a, "75a"},
                 {_75b, "75b"},
                 {Time, "Time"}
};
VALUE str2enum (const char *str);
*/
/* places minutes and error flags into struct displayChars */
void placeData(char *str, struct displayChars *dcPtr, int busNo, int dataKind);

#endif /* S7S_SPI_H_ */
