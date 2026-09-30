/* Offline reconstruction of seven MP305B V51 read-reply builders.
 * RAM is a synthetic snapshot starting at processor address 0x1ffe0000.
 * The table gives exact byte sources, without assigning unproved physical
 * units. Preconditions: RAM contains at least 0x20000 bytes; reply holds 70
 * bytes.
 */
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#define RAM_BASE UINT32_C(0x1ffe0000)
struct field {
  uint8_t offset, count;
  uint32_t address;
};
static uint8_t byte_at(const uint8_t *ram, uint32_t a) {
  return ram[a - RAM_BASE];
}
static uint16_t half_at(const uint8_t *ram, uint32_t a) {
  return (uint16_t)(byte_at(ram, a) | ((uint16_t)byte_at(ram, a + 1) << 8));
}
static uint32_t word_at(const uint8_t *ram, uint32_t a) {
  return (uint32_t)half_at(ram, a) | ((uint32_t)half_at(ram, a + 2) << 16);
}
static void copy_fields(const uint8_t *ram, uint8_t *reply,
                        const struct field *fields, size_t count) {
  for (size_t i = 0; i < count; ++i)
    memcpy(reply + fields[i].offset, ram + fields[i].address - RAM_BASE,
           fields[i].count);
}
#define COPY_FIELDS(fields)                                                    \
  copy_fields(ram, reply, fields, sizeof(fields) / sizeof(fields[0]))
static const struct field c2[] = {
    {1, 1, 0x1fffaace},  {2, 1, 0x1fffaada},  {3, 1, 0x1fffab06},
    {4, 2, 0x1fffab78},  {6, 2, 0x1fffab74},  {8, 2, 0x1fffab7a},
    {10, 2, 0x1fffab76}, {12, 4, 0x1fffab9c}, {16, 4, 0x1fffaba0},
    {20, 2, 0x1fffab7c}, {22, 1, 0x1fffaade}, {23, 1, 0x1fffaae4},
    {24, 1, 0x1fffaadc}, {25, 1, 0x1fffaad1}, {26, 1, 0x1fffaafc},
    {27, 1, 0x1fffab03}, {28, 1, 0x1fffab04}, {29, 1, 0x1fffab05},
    {30, 2, 0x1fffab6a}, {33, 4, 0x1fffa980}};
static const struct field c4[] = {{1, 1, 0x1fffaaf9}, {2, 1, 0x1fffaafe},
                                  {3, 1, 0x1fffaafa}, {4, 1, 0x1fffaaff},
                                  {5, 1, 0x1fffaafb}, {6, 2, 0x1fffab62},
                                  {8, 2, 0x1fffab64}, {10, 2, 0x1fffab70}};
static const struct field ea[] = {
    {1, 1, 0x1fffac96}, {2, 2, 0x1fffac94},  {4, 1, 0x1fffac90},
    {5, 2, 0x1fffac92}, {7, 1, 0x1fffac98},  {8, 1, 0x1fffac99},
    {9, 4, 0x1fffac9c}, {13, 4, 0x1fffaca0}, {17, 4, 0x1fffaca4}};
static const struct field ec[] = {
    {1, 1, 0x1fffaada},  {2, 1, 0x1fffab06},  {3, 2, 0x1fffab80},
    {5, 4, 0x1fffaba4},  {9, 1, 0x1fffab46},  {10, 1, 0x1fffab45},
    {11, 2, 0x1fffab7e}, {13, 4, 0x1fffaba8}, {17, 4, 0x1fffabac},
    {21, 2, 0x1fffab82}, {23, 1, 0x1fffab44}, {24, 1, 0x1fffaad1},
    {25, 1, 0x1fffaafc}, {26, 1, 0x1fffab05}};
static const struct field de[] = {
    {1, 1, 0x1fffaace},  {2, 1, 0x1fffaada},  {3, 1, 0x1fffab06},
    {4, 2, 0x1fffab78},  {6, 2, 0x1fffab7a},  {12, 4, 0x1fffaba0},
    {16, 2, 0x1fffab7c}, {19, 1, 0x1fffaad1}, {20, 1, 0x1fffaafc},
    {21, 1, 0x1fffab05}, {22, 1, 0x1fffaaec}, {27, 1, 0x1fffaaeb},
    {28, 1, 0x1fffacac}, {29, 1, 0x1fffacae}, {30, 2, 0x1fffacb0},
    {32, 1, 0x1fffacb4}, {33, 1, 0x1fffacb2}, {34, 1, 0x1fffacb6},
    {35, 1, 0x1fffacb8}, {36, 1, 0x1fffacbc}, {37, 1, 0x1fffacba},
    {38, 1, 0x1fff9b8e}, {39, 4, 0x1fff9b3c}, {43, 4, 0x1fff9b40},
    {47, 4, 0x1fff9b44}, {51, 4, 0x1fff9b48}, {55, 4, 0x1fff9b4c},
    {59, 4, 0x1fff9b50}, {63, 2, 0x1fffab6a}, {65, 4, 0x1fffa980}};

/* Return zero for an opcode outside this reconstruction's scope.
 * Original entry addresses: C2=158bc, C4=15ef8, DC=1565c, DE=15694,
 * E4=15630, EA=154ac, EC=1555c (all hexadecimal).
 */
size_t reconstructed_read(const uint8_t *ram, const uint8_t *request,
                          size_t length, uint8_t *reply, uint8_t type) {
  size_t n;
  reply[0] = (uint8_t)(request[0] + 1);
  switch (request[0]) {
  case 0xc2:
    COPY_FIELDS(c2);
    n = 37;
    reply[32] = word_at(ram, 0x1ffe02a0) == 0 ? 1 : byte_at(ram, 0x1fffaadd);
    break;
  case 0xc4:
    COPY_FIELDS(c4);
    n = 12;
    break;
  case 0xdc: {
    uint8_t index = byte_at(ram, 0x1fffa408);
    reply[1] = byte_at(ram, 0x1fffa3fe + index);
    reply[2] = byte_at(ram, 0x1fffa3f4 + index);
    n = 3;
    break;
  }
  case 0xde:
    COPY_FIELDS(de);
    n = 69;
    if (byte_at(ram, 0x1fffaafc) == 1) {
      memcpy(reply + 8, ram + 0x1fffab94 - RAM_BASE, 2);
      reply[10] = 0;
      reply[11] = 0;
    } else
      memcpy(reply + 8, ram + 0x1fffab9c - RAM_BASE, 4);
    reply[18] = (half_at(ram, 0x1fffab48) & 0x8000)
                    ? 1
                    : (uint8_t)(byte_at(ram, 0x1fffab48) + 1);
    if (word_at(ram, 0x1fffab84) & UINT32_C(0x80000000))
      memset(reply + 23, 0, 4);
    else
      memcpy(reply + 23, ram + 0x1fffab84 - RAM_BASE, 4);
    break;
  case 0xe4:
    reply[1] = (uint8_t)(byte_at(ram, 0x1fffa34a) + 1);
    n = 2;
    break;
  case 0xea:
    COPY_FIELDS(ea);
    n = 21;
    break;
  case 0xec: {
    COPY_FIELDS(ec);
    n = 31;
    uint32_t flags = word_at(ram, 0x1fffaca8) | half_at(ram, 0x1fffab6a);
    for (unsigned i = 0; i < 4; ++i)
      reply[27 + i] = (uint8_t)(flags >> (8 * i));
    break;
  }
  default:
    return 0;
  }
  if (type == 6)
    reply[n++] = request[length - 1];
  return n;
}
