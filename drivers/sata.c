#include <stdint.h>
#include <stddef.h>

// sata ovladac

#define SATA_BASE 0x1F0
#define SATA_CONTROL 0x3F6

typedef struct {
    uint16_t data;
    uint8_t error;
    uint8_t sector_count;
    uint8_t lba_low;
    uint8_t lba_mid;
    uint8_t lba_high;
    uint8_t device;
    uint8_t command;
    uint8_t status;
} sata_reg_t;

volatile sata_reg_t* sata = (volatile sata_reg_t*)SATA_BASE;

void sata_zapis(uint32_t lba, uint8_t sektor_pocet, const uint8_t* buffer) {
    sata->sector_count = sektor_pocet;
    sata->lba_low = (uint8_t)(lba & 0xFF);
    sata->lba_mid = (uint8_t)((lba >> 8) & 0xFF);
    sata->lba_high = (uint8_t)((lba >> 16) & 0xFF);
    sata->device = 0xE0 | ((lba >> 24) & 0x0F);
    sata->command = 0x30; // Write sectors

    for (uint8_t i = 0; i < sektor_pocet; i++) {
        for (uint16_t j = 0; j < 256; j++) {
            sata->data = ((uint16_t*)buffer)[i * 256 + j];
        }
    }
}

void sata_cteni(uint32_t lba, uint8_t sektor_pocet, uint8_t* buffer) {
    sata->sector_count = sektor_pocet;
    sata->lba_low = (uint8_t)(lba & 0xFF);
    sata->lba_mid = (uint8_t)((lba >> 8) & 0xFF);
    sata->lba_high = (uint8_t)((lba >> 16) & 0xFF);
    sata->device = 0xE0 | ((lba >> 24) & 0x0F);
    sata->command = 0x20; // cteni sektoru

    for (uint8_t i = 0; i < sektor_pocet; i++) {
        for (uint16_t j = 0; j < 256; j++) {
            ((uint16_t*)buffer)[i * 256 + j] = sata->data;
        }
    }
}