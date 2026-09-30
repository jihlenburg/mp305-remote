/* Address: ram:00001e18; name: FUN_ram_00001e18; body bytes: 398 */

/* WARNING: Removing unreachable block (ram,0x00001e40) */
/* WARNING: Removing unreachable block (ram,0x00001f20) */
/* WARNING: Removing unreachable block (ram,0x00001f14) */
/* WARNING: Removing unreachable block (ram,0x00001e36) */
/* WARNING: Removing unreachable block (ram,0x00001e6a) */

void FUN_ram_00001e18(uint param_1,uint param_2,int param_3,uint param_4,int param_5,uint param_6)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  
  gp = &DAT_ram_20002000;
  uVar3 = 0;
  uVar2 = param_1;
  while (0x7e4 < uVar2) {
    uVar2 = uVar2 - 1;
    iVar1 = 0x16e;
    if (((int)uVar2 % 400 != 0) && (iVar1 = 0x16d, (int)uVar2 % 100 != 0)) {
      iVar1 = ((uVar2 & 3) == 0) + 0x16d;
    }
    uVar3 = uVar3 + iVar1 & 0xffff;
  }
  for (; 1 < param_2; param_2 = param_2 - 1 & 0xffff) {
    if (param_2 == 3) {
      uVar2 = 1;
      if ((param_1 % 400 != 0) && (uVar2 = 0, param_1 % 100 != 0)) {
        uVar2 = (uint)((param_1 & 3) == 0);
      }
      iVar1 = uVar2 + 0x1c;
    }
    else {
      uVar2 = param_2 & 1;
      if (param_2 < 9) {
        uVar2 = (uint)(uVar2 == 0);
      }
      iVar1 = uVar2 + 0x1e;
    }
    uVar3 = iVar1 + uVar3 & 0xffff;
  }
  do {
  } while ((DAT_ram_4000102f & 0x80) == 0);
  do {
  } while (((param_3 + -1 + uVar3 & 0xffff ^ DAT_ram_4000103c) & 0x3fff) != 0);
  DAT_ram_40001034 =
       (param_5 * 0x1e + (param_6 >> 1) + (param_4 % 0x18) * 0x708) * 0x10000 | (param_6 & 1) << 0xf
  ;
  DAT_ram_40001031 = DAT_ram_40001031 | 0xc0;
  DAT_ram_40001040 = 0;
  return;
}

