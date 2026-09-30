/* Address: ram:00065eb8; name: FUN_ram_00065eb8; body bytes: 176 */

undefined4 FUN_ram_00065eb8(int param_1)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  byte bVar3;
  
  gp = 0x20004000;
  if (param_1 == 0) {
    return 0x12;
  }
  if ((((DAT_ram_20001db4 == 0) || (uVar1 = 0xc, *(char *)(DAT_ram_20001db4 + 0xc) == '\0')) &&
      ((DAT_ram_20001dd8 == 0 || (uVar1 = 0xc, *(char *)(DAT_ram_20001dd8 + 0xb) == '\0')))) &&
     ((DAT_ram_20001de8 == 0 || (uVar1 = 0xc, *(char *)(DAT_ram_20001de8 + 7) == '\0')))) {
    DAT_ram_20001d62 = 1;
    tmos_memcpy(&DAT_ram_20001e3e,param_1,6);
    bVar3 = *(byte *)(param_1 + 5) & 0xc0;
    if (bVar3 == 0xc0) {
      puVar2 = &DAT_ram_20001e44;
    }
    else if ((*(byte *)(param_1 + 5) & 0xc0) == 0) {
      puVar2 = (undefined4 *)&DAT_ram_20001e4a;
    }
    else {
      if (bVar3 != 0x40) {
        gp = 0x20004000;
        return 0x12;
      }
      puVar2 = (undefined4 *)&DAT_ram_20001e50;
    }
    tmos_memcpy(puVar2,param_1,6);
    uVar1 = 0;
  }
  return uVar1;
}

