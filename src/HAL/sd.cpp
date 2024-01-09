#include <SPI.h>
#include <SdFat.h>

#include "hal.h"
SdFat sd;

SPIClass hspi(HSPI);
#define SD_CONFIG SdSpiConfig(SD_CS_PIN, DEDICATED_SPI, SD_SCK_MHZ(16), &hspi)

void printCardInfo() {
  Serial.print("Card type: ");
  // 读取csd
  csd_t csd;
  sd.card()->readCSD(&csd);
  switch (sd.card()->type()) {
    case SD_CARD_TYPE_SD1:
      Serial.println("SD1");
      break;
    case SD_CARD_TYPE_SD2:
      Serial.println("SD2");
      break;
    case SD_CARD_TYPE_SDHC:
      if (csd.capacity() < 70000000) {
        Serial.println("SDHC");
      } else {
        Serial.println("SDXC");
      }
      break;
    default:
      Serial.print("Unknown: ");
  }
  // 打印已用和可用空间
  uint64_t cardTotalSize = sd.card()->sectorCount() / 2;  // KB
  uint64_t cardFreeSize =
      sd.vol()->freeClusterCount() * sd.vol()->sectorsPerCluster() / 2;  // KB
  uint64_t cardUsedSize = cardTotalSize - cardFreeSize;                  // KB
  // 用合适的单位打印空间信息
  if (cardTotalSize > 1024 * 1024) {
    Serial.printf("SD卡总容量: %llfGB\n", 1.0 * cardTotalSize / 1024 / 1024);
  } else {
    Serial.printf("SD卡总容量: %llfMB\n", 1.0 * cardTotalSize / 1024);
  }

  if (cardUsedSize > 1024 * 1024) {
    Serial.printf("SD卡已用: %llfGB\n", 1.0 * cardUsedSize / 1024 / 1024);
  } else {
    Serial.printf("SD卡已用: %llfMB\n", 1.0 * cardUsedSize / 1024);
  }

  if (cardFreeSize > 1024 * 1024) {
    Serial.printf("SD卡可用: %llfGB\n", 1.0 * cardFreeSize / 1024 / 1024);
  } else {
    Serial.printf("SD卡可用: %llfMB\n", 1.0 * cardFreeSize / 1024);
  }
}

void sd_init() {
  // 初始化SD卡
  hspi.begin(SD_SCK_PIN, SD_MISO_PIN, SD_MOSI_PIN, SD_CS_PIN);
  if (!sd.begin(SD_CONFIG)) {
    Serial.println("SD Card Mount Failed");
    return;
  }
  printCardInfo();
}