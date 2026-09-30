/* Address: ram:0006656c; name: FUN_ram_0006656c; body bytes: 296 */

undefined4 FUN_ram_0006656c(byte *param_1)

{
  int *piVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  byte bVar5;
  int *piVar6;
  int iVar7;
  byte *pbVar8;
  
  piVar1 = (int *)DAT_ram_20001df0;
  gp = 0x20004000;
  if (param_1 == (byte *)0x0) {
    return 0x12;
  }
  param_1[4] = param_1[4] & 0x1f;
  for (; piVar6 = DAT_ram_20001db8, piVar1 != (int *)0x0; piVar1 = (int *)*piVar1) {
    if (*(char *)((int)piVar1 + 0xb) == '\0') {
      piVar1[0x29] = piVar1[0x29] | 2;
      tmos_memcpy(piVar1 + 0x4a,param_1,5);
    }
    else {
      if ((*(byte *)(piVar1 + 0x5d) & 1) != 0) {
        iVar2 = 0;
        pbVar8 = param_1;
        do {
          uVar3 = 0;
          do {
            iVar4 = (uVar3 >> 2) + iVar2;
            iVar7 = (uVar3 & 3) << 1;
            if (((int)(uint)*pbVar8 >> (uVar3 & 0x1f) & 1U) == 0) {
              bVar5 = (byte)(3 << iVar7);
            }
            else {
              bVar5 = (byte)(1 << iVar7);
            }
            *(byte *)((int)piVar1 + iVar4 + 0x17d) = bVar5 | *(byte *)((int)piVar1 + iVar4 + 0x17d);
            uVar3 = uVar3 + 1;
          } while (uVar3 != 8);
          iVar2 = iVar2 + 2;
          pbVar8 = pbVar8 + 1;
        } while (iVar2 != 10);
      }
      iVar2 = tmos_memcmp(piVar1 + 0x5e,param_1,5);
      if (iVar2 == 0) {
        tmos_memcpy(piVar1 + 0x5e,param_1,5);
        *(byte *)(piVar1 + 0x5d) = *(byte *)(piVar1 + 0x5d) | 8;
      }
    }
  }
  for (; piVar6 != (int *)0x0; piVar6 = (int *)*piVar6) {
    if (*(char *)(piVar6 + 0x1f) == '\x03') {
      *(undefined1 *)(piVar6 + 0x1f) = 0x10;
    }
  }
  tmos_memcpy(&DAT_ram_20001e56,param_1,5);
  return 0;
}

