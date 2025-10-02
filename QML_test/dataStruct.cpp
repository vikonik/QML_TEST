#include "dataStruct.h"

// Инициализация дефолтного канала
OneChanelToDevice_t oneChanelDefaulsSetting(
    "0000",   // address
    "A",      // type
    "P",      // flag
    "0000",   // newAddres
    "K8r4",   // paswordForData
    "0"       // dir
);



// Инициализация дефолтных настроек
SixChanelToDevice_t sixChanelDefaulsSetting = {
    SixChanelToDeviceChanel_t("0000", "B", "P", "0000", "1", "K8r4"),
    SixChanelToDeviceChanel_t("0000", "B", "P", "0000", "2", "0000"),
    SixChanelToDeviceChanel_t("0000", "B", "P", "0000", "3", "0000"),
    SixChanelToDeviceChanel_t("0000", "B", "P", "0000", "4", "0000"),
    SixChanelToDeviceChanel_t("0000", "B", "P", "0000", "5", "0000"),
    SixChanelToDeviceChanel_t("0000", "B", "P", "0000", "6", "0000")
};
