#ifndef RFMAX_H
#define RFMAX_H

#include <QObject>

class RFMax
{
public:
    RFMax();

//private:

    typedef enum: char{
        IR_MODULE = 'W'
    }ControllerType_t;

    typedef enum: char{
        N = 'N',
        P = 'P'
    }Flag_t;

    typedef enum: char{
        SHADETRONIC = '0',
        SCHNEIDER = '1',
        SIEMENS = '2',
        MDT = '3'
    }BR_t;

    typedef struct{
        char preambula[3];
        char addr[4];
        ControllerType_t type;
        Flag_t flag;
        char day[2];
        char mounth[2];
        char year[4];
        BR_t br;
        char stopMarker;
    }PacketToPcType_1_t;

    typedef struct{
        char preambula[3];
        char chanel[2];
        char group[4];
        char description[16];
        char stopMarker;
    }PacketToPcType_2_t;

    typedef struct{
        char preambula[3];
        char addr[4];
        ControllerType_t type;
        Flag_t flag;
        char addrNew[4];
        char password[4];
        char day[2];
        char mounth[2];
        char year[4];
        BR_t br;
        char stopMarker;
    }PacketToMcuType_1_t;

    typedef struct{
        char preambula[3];
        char addr[4];
        char chanel[2];
        char group[4];
        char description[16];
        char stopMarker;
    }PacketToMcuType_2_t;

    typedef struct{
        PacketToMcuType_1_t header;
        PacketToMcuType_2_t data[30];
    }RFMAX_Type;


    PacketToPcType_1_t  *packetToPcType_1;
    PacketToPcType_2_t  *packetToPcType_2;
    PacketToMcuType_1_t *packetToMcuType_1;
    PacketToMcuType_2_t *packetToMcuType_2;

public:
    RFMAX_Type *rfMax;
    bool detected;
    uint8_t currentAddr;//Адрес байта в структуре в который будет проводиться запись
    size_t getSizeRFMAX_Type();
};

#endif // RFMAX_H
