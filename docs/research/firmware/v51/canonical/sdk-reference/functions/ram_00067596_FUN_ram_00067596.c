/* Address: ram:00067596; name: FUN_ram_00067596; body bytes: 276 */

undefined4 FUN_ram_00067596(uint param_1,undefined4 param_2)

{
  int iVar1;
  undefined1 uVar2;
  undefined2 uVar3;
  short sVar4;
  undefined4 uVar5;
  int iVar6;
  uint uVar7;
  
  gp = 0x20004000;
  if ((DAT_ram_20001db4 == 0) || (-1 < *(int *)(DAT_ram_20001db4 + 0x54) << 5)) {
    iVar6 = FUN_ram_00054de4(param_2);
    if (iVar6 == 0) {
      gp = 0x20004000;
      return 0x42;
    }
    uVar7 = *(uint *)(iVar6 + 0x54);
    if ((param_1 & 1) == 0) {
      *(uint *)(iVar6 + 0x54) = uVar7 & 0xfffffff3;
      if (*(char *)(iVar6 + 0x7d) != -1) {
        FUN_ram_00042494();
      }
    }
    else {
      if (((uVar7 & 1) != 0) || ((*(byte *)(iVar6 + 0x60) & 0x33) != 0)) goto LAB_ram_000675bc;
      if ((param_1 & 2) == 0) {
        uVar7 = uVar7 & 0xfffffbff;
      }
      else {
        uVar7 = uVar7 | 0x400;
        if ((DAT_ram_20001e2c & 0x10) == 0) {
          gp = 0x20004000;
          return 0x11;
        }
      }
      *(uint *)(iVar6 + 0x54) = uVar7;
      uVar3 = FUN_ram_00042910(0,0xffff);
      *(undefined2 *)(iVar6 + 0x88) = uVar3;
      uVar5 = BLE_AccessAddressGenerate();
      *(undefined4 *)(iVar6 + 0x8c) = uVar5;
      uVar5 = FUN_ram_00042934(0,0xffffff);
      iVar1 = iVar6 + 0x98;
      *(undefined4 *)(iVar6 + 0x90) = uVar5;
      tmos_memcpy(iVar1,&DAT_ram_20001e56,5);
      FUN_ram_200012e0(0xffffffb0,iVar1);
      uVar2 = FUN_ram_000582da(iVar1);
      *(undefined1 *)(iVar6 + 0x81) = uVar2;
      *(uint *)(iVar6 + 0x54) = *(uint *)(iVar6 + 0x54) & 0xfffffff7 | 4;
      if (*(char *)(iVar6 + 0xc) == '\x01') {
        sVar4 = FUN_ram_000428ec(1,200);
        *(ushort *)(iVar6 + 0x6a) = *(short *)(iVar6 + 0x6a) + 1U & 0xf | sVar4 << 4;
      }
    }
    uVar5 = 0;
  }
  else {
LAB_ram_000675bc:
    uVar5 = 0xc;
  }
  return uVar5;
}

